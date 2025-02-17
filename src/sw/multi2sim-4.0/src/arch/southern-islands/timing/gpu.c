/*
 *  Multi2Sim
 *  Copyright (C) 2012  Rafael Ubal (ubal@ece.neu.edu)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <assert.h>

#include <arch/common/arch.h>
#include <arch/southern-islands/asm/bin-file.h>
#include <arch/southern-islands/emu/emu.h>
#include <arch/southern-islands/emu/ndrange.h>
#include <driver/opencl-old/southern-islands/kernel.h>
#include <lib/esim/esim.h>
#include <lib/esim/trace.h>
#include <lib/mhandle/mhandle.h>
#include <lib/util/config.h>
#include <lib/util/debug.h>
#include <lib/util/file.h>
#include <lib/util/linked-list.h>
#include <lib/util/misc.h>
#include <lib/util/timer.h>

#include "gpu.h"
#include "calc.h"
#include "compute-unit.h"
#include "mem-config.h"
#include "uop.h"

#include "cycle-interval-report.h"

static char *si_err_stall =
	"\tThe Southern Islands GPU has not completed execution of any in-flight\n"
	"\tinstruction for 1M cycles. Most likely, this means that a\n"
	"\tdeadlock condition occurred in the management of some modeled\n"
	"\tstructure (network, memory system, pipeline queues, etc.).\n";

/*
 * Global variables
 */

char *si_gpu_config_help =
	"The Southern Islands GPU configuration file is a plain text INI file \n"
	"defining the parameters of the Southern Islands model for a detailed \n"
	"(architectural) configuration. This file is passed to Multi2Sim with \n"
	"the '--si-config <file>' option, and should always be used together  \n"
	"with option '--si-sim detailed'.\n" 
	"\n"
	"The following is a list of the sections allowed in the GPU configuration\n"
	"file, along with the list of variables for each section.\n"
	"\n"
	"Section '[ Device ]': parameters for the GPU.\n"
	"\n"
	"  NumComputeUnits = <num> (Default = 32)\n"
	"      Number of compute units in the GPU.\n"
	"  MaxWavefrontsPerWorkGroup = <num> (Default = 16)\n"
	"      The maximum size of a work group.\n"
	"\n"
	"Section '[ ComputeUnit ]': parameters for the Compute Units.\n"
	"\n"
	"  NumWavefrontPools = <num> (Default = 4)\n"
	"      Number of wavefront pools/SIMDs per compute unit.\n"
	"  MaxWorkGroupsPerWavefrontPool = <num> (Default = 10)\n"
	"      The maximum number of work groups that can be scheduled to a\n"
	"      wavefront pool at a time.\n"
	"  MaxWavefrontsPerWavefrontPool = <num> (Default = 10)\n"
	"      The maximum number of wavefronts that can be scheduled to a\n"
	"      wavefront pool at a time.\n"
	"  NumVectorRegisters = <num> (Default = 65536)\n"
	"      Number of vector registers per compute unit. These registers are\n"
	"      divided evenly between all wavefront pools/SIMDs.\n"
	"  NumScalarRegisters = <num> (Default = 2048)\n"
	"      Number of scalar registers per compute unit. These registers are\n"
	"      shared by all wavefront pools/SIMDs.\n"
	"\n"
	"Section '[ FrontEnd ]': parameters for fetch and issue.\n"
	"\n"
	"  FetchLatency = <cycles> (Default = 5)\n"
	"      Latency of instruction memory in number of cycles.\n"
	"  FetchWidth = <num> (Default = 4)\n"
	"      Maximum number of instructions fetched per cycle.\n"
	"  FetchBufferSize = <num> (Default = 10)\n"
	"      Size of the buffer holding fetched instructions.\n"
	"  IssueLatency = <cycles> (Default = 1)\n"
	"      Latency of the decode stage in number of cycles.\n"
	"  IssueWidth = <num> (Default = 5)\n"
	"      Number of instructions that can be issued per cycle.\n"
	"  MaxInstIssuedPerType = <num> (Default = 1)\n"
	"      Maximum number of instructions that can be issued of each type\n"
	"      (SIMD, scalar, etc.) in a single cycle.\n"
	"\n"
	"Section '[ SIMDUnit ]': parameters for the SIMD Units.\n"
	"\n"
	"  NumSIMDLanes = <num> (Default = 16)\n"
	"      Number of lanes per SIMD.  This number must divide the wavefront\n"
	"      size (64) evenly.\n" 
	"  Width = <num> (Default = 1)\n"
	"      Maximum number of instructions processed per cycle.\n"
	"  IssueBufferSize = <num> (Default = 1)\n"
	"      Size of the buffer holding issued instructions.\n"
	"  DecodeLatency = <cycles> (Default = 1)\n"
	"      Latency of the decode stage in number of cycles.\n"
	"  DecodeWidth = <num> (Default = 1)\n"
	"      Number of instructions that can be decoded per cycle.\n"
	"  DecodeBufferSize = <num> (Default = 1)\n"
	"      Size of the buffer holding decoded instructions.\n"
	"  ReadExecWriteLatency = <cycles> (Default = 8)\n"
	"      Number of cycles it takes to read operands from the register\n"
	"      files, execute the SIMD ALU operation, and write the results\n"
	"      out to the register file for a single subwavefront. It makes\n"
	"      sense to combine the three stages since they wavefront is\n"
	"      pipelined across all of them and can therefore be in different\n"
	"      stages at the same time.\n"
	"  ReadExecWriteBufferSize = <num> (Default = 2)\n"
	"      Size of the buffer holding instructions that have began the\n"
	"      read-exec-write stages.\n"
	"\n"
	"Section '[ ScalarUnit ]': parameters for the Scalar Units.\n"
	"\n"
	"  Width = <num> (Default = 1)\n"
	"      Maximum number of instructions processed per cycle.\n"
	"  IssueBufferSize = <num> (Default = 4)\n"
	"      Size of the buffer holding issued instructions.\n"
	"  DecodeLatency = <cycles> (Default = 1)\n"
	"      Latency of the decode stage in number of cycles.\n"
	"  DecodeWidth = <num> (Default = 1)\n"
	"      Number of instructions that can be decoded per cycle.\n"
	"  ReadLatency = <cycles> (Default = 1)\n"
	"      Latency of register file access in number of cycles for reads.\n"
	"  ReadBufferSize = <num> (Default = 1)\n"
	"      Size of the buffer holding register read instructions.\n"
	"  ALULatency = <cycles> (Default = 4)\n"
	"      Latency of ALU execution in number of cycles.\n"
	"  ExecBufferSize = <num> (Default = 16)\n"
	"      Size of the buffer holding in-flight memory instructions and\n"
	"      executing ALU instructions.\n"
	"  WriteLatency = <cycles> (Default = 1)\n"
	"      Latency of register file access in number of cycles for writes.\n"
	"  WriteBufferSize = <num> (Default = 1)\n"
	"      Size of the buffer holding register write instructions.\n"
	"\n"
	"Section '[ BranchUnit ]': parameters for the Branch Units.\n"
	"\n"
	"  Width = <num> (Default = 1)\n"
	"      Maximum number of instructions processed per cycle.\n"
	"  IssueBufferSize = <num> (Default = 4)\n"
	"      Size of the buffer holding issued instructions.\n"
	"  DecodeLatency = <cycles> (Default = 1)\n"
	"      Latency of the decode stage in number of cycles.\n"
	"  DecodeWidth = <num> (Default = 1)\n"
	"      Number of instructions that can be decoded per cycle.\n"
	"  ReadLatency = <cycles> (Default = 1)\n"
	"      Latency of register file access in number of cycles for reads.\n"
	"  ReadBufferSize = <num> (Default = 1)\n"
	"      Size of the buffer holding register read instructions.\n"
    "  ExecLatency = <cycles> (Default = 1)\n"
    "      Latency of execution in number of cycles.\n"
    "  ExecBufferSize = <num> (Default = 1)\n"
    "      Size of the buffer holding executing instructions.\n"
	"  WriteLatency = <cycles> (Default = 1)\n"
	"      Latency of register file access in number of cycles for writes.\n"
	"  WriteBufferSize = <num> (Default = 1)\n"
	"      Size of the buffer holding register write instructions.\n"
	"\n"
	"Section '[ LDSUnit ]': parameters for the LDS Units.\n"
	"\n"
	"  Width = <num> (Default = 1)\n"
	"      Maximum number of instructions processed per cycle.\n"
	"  IssueBufferSize = <num> (Default = 4)\n"
	"      Size of the buffer holding issued instructions.\n"
	"  DecodeLatency = <cycles> (Default = 1)\n"
	"      Latency of the decode stage in number of cycles.\n"
	"  DecodeWidth = <num> (Default = 1)\n"
	"      Number of instructions that can be decoded per cycle.\n"
	"  ReadLatency = <cycles> (Default = 1)\n"
	"      Latency of register file access in number of cycles for reads.\n"
	"  ReadBufferSize = <num> (Default = 1)\n"
	"      Size of the buffer holding register read instructions.\n"
	"  MaxInflightMem = <num> (Default = 32)\n"
	"      Maximum number of in-flight memory accesses.\n"
	"  WriteLatency = <cycles> (Default = 1)\n"
	"      Latency of register file access in number of cycles for writes.\n"
	"  WriteBufferSize = <num> (Default = 1)\n"
	"      Size of the buffer holding register write instructions.\n"
	"\n"
	"Section '[ VectorMemUnit ]': parameters for the Vector Memory Units.\n"
	"\n"
	"  Width = <num> (Default = 1)\n"
	"      Maximum number of instructions processed per cycle.\n"
	"  IssueBufferSize = <num> (Default = 4)\n"
	"      Size of the buffer holding issued instructions.\n"
	"  DecodeLatency = <cycles> (Default = 1)\n"
	"      Latency of the decode stage in number of cycles.\n"
	"  DecodeWidth = <num> (Default = 1)\n"
	"      Number of instructions that can be decoded per cycle.\n"
	"  ReadLatency = <cycles> (Default = 1)\n"
	"      Latency of register file access in number of cycles for reads.\n"
	"  ReadBufferSize = <num> (Default = 1)\n"
	"      Size of the buffer holding register read instructions.\n"
	"  MaxInflightMem = <num> (Default = 32)\n"
	"      Maximum number of in-flight memory accesses.\n"
	"  WriteLatency = <cycles> (Default = 1)\n"
	"      Latency of register file access in number of cycles for writes.\n"
	"  WriteBufferSize = <num> (Default = 1)\n"
	"      Size of the buffer holding register write instructions.\n"
	"\n"
	"Section '[ LDS ]': defines the parameters of the Local Data Share\n"
	"on each compute unit.\n"
	"\n"
	"  Size = <bytes> (Default = 64 KB)\n"
	"      Local memory capacity per compute unit. This value must be equal\n"
	"      or larger than BlockSize * Banks.\n"
	"  AllocSize = <bytes> (Default = 16)\n"
	"      Minimum amount of local memory allocated at a time for\n"
	"      each work-group.\n" 
	"  BlockSize = <bytes> (Default = 64)\n"
	"      Access block size, used for access coalescing purposes\n"
	"      among work-items.\n"
	"  Latency = <num_cycles> (Default = 2)\n"
	"      Latency for an access in number of cycles.\n"
	"  Ports = <num> (Default = 4)\n"
	"      Number of ports.\n"
	"\n";

char *si_gpu_config_file_name = "";
char *si_gpu_dump_default_config_file_name = "";
char *si_gpu_report_file_name = "";

int si_trace_category;

/* Default parameters based on the AMD Radeon HD 7970 */
unsigned long long si_gpu_device_type = 4; /* CL_DEVICE_TYPE_GPU */
unsigned int si_gpu_device_vendor_id = 1234; /* Completely arbitrary */

char *si_gpu_device_profile = "FULL_PROFILE";
char *si_gpu_device_name = "Multi2Sim Southern Islands GPU";
char *si_gpu_device_vendor = "www.multi2sim.org";
char *si_gpu_device_extensions = "cl_amd_fp64 cl_khr_global_int32_base_atomics "
	"cl_khr_global_int32_extended_atomics cl_khr_local_int32_base_atomics "
	"cl_khr_local_int32_extended_atomics cl_khr_byte_addressable_store "
	"cl_khr_gl_sharing cl_ext_device_fission cl_amd_device_attribute_query "
	"cl_amd_media_ops cl_amd_popcnt cl_amd_printf ";
char *si_gpu_device_version = "OpenCL 1.2 AMD-APP-SDK-v2.7";
char *si_gpu_driver_version = VERSION;
char *si_gpu_opencl_version = "OpenCL C 1.2";

/* OpenCL Device Query Information */
unsigned int si_gpu_work_item_dimensions = 3;  /* FIXME */
unsigned int si_gpu_work_item_sizes[3] = {256, 256, 256};  /* FIXME */
unsigned int si_gpu_work_group_size = 256 * 256 * 256;  /* FIXME */

unsigned int si_gpu_image_support = 1; /* CL_TRUE */
unsigned int si_gpu_max_read_image_args = 128;  /* The minimum value */
unsigned int si_gpu_max_write_image_args = 8;  /* The minimum value */

unsigned int si_gpu_image2d_max_width = 8192;  /* The minimum value */
unsigned int si_gpu_image2d_max_height = 8192;  /* The minimum value */
unsigned int si_gpu_image3d_max_width = 2048;  /* The minimum value */
unsigned int si_gpu_image3d_max_height = 2048;  /* The minimum value */
unsigned int si_gpu_image3d_max_depth = 2048;  /* The minimum value */
unsigned int si_gpu_max_samplers = 16;  /* The minimum value */

unsigned int si_gpu_max_parameter_size = 1024;  /* The minimum value */
/* FIXME */
unsigned int si_gpu_mem_base_addr_align = 16 * 8;  /* size of long16 in bits */ 
/* FIXME */
unsigned int si_gpu_min_data_type_align_size = 16;  /* size of long16 in bytes 
													 deprecated in OpenCL 1.2 */

/* bit field, all single floating point capabilities supported */ /* FIXME */
unsigned int si_gpu_single_fp_config = 255;  
/* bit field, all double floating point capabilities supported */ /* FIXME */
unsigned int si_gpu_double_fp_config = 255;  

unsigned int si_gpu_max_clock_frequency = 925;
unsigned int si_gpu_address_bits = 32;

unsigned int si_gpu_global_mem_cache_type = 2;  /* CL_READ_WRITE_CACHE */
unsigned int si_gpu_global_mem_cacheline_size = 256; /* FIXME */
unsigned long long si_gpu_global_mem_cache_size = 1ull << 23;  /* 8MB */ /* FIXME */
unsigned long long si_gpu_global_mem_size = 1ull << 32;  /* 4GB of global memory reported */
unsigned long long si_gpu_max_mem_alloc_size = (1ull << 32) / 4; /* FIXME */

unsigned int si_gpu_local_mem_type = 1;  /* CL_LOCAL */

unsigned long long si_gpu_max_constant_buffer_size = 1ull << 16;  /* 64KB */ /* The minimum value acceptable */
unsigned int si_gpu_max_constant_args = 8;  /* The minimum value acceptable */

unsigned int si_gpu_vector_width_half = 0; /* No support for cl_khr_fp16 */

unsigned int si_gpu_error_correction_support = 1;  /* FIXME */
unsigned int si_gpu_host_unified_memory = 0;  /* FIXME */
unsigned int si_gpu_profiling_timer_resolution = 10;  /* ns */ /* FIXME */
unsigned int si_gpu_endian_little = 1;  /* FIXME */

unsigned int si_gpu_device_available = 1;  /* FIXME */
unsigned int si_gpu_compiler_available = 1;  /* FIXME */
unsigned int si_gpu_linker_available = 1;  /* FIXME */
unsigned int si_gpu_execution_capabilities = 1;  /* bit field, CL_EXEC_KERNEL only */ /* FIXME */

unsigned int si_gpu_queue_properties = 2;  /* bit field, profiling enabled, no out of order execution */

unsigned int si_gpu_platform = 0;  /* FIXME */

struct str_map_t si_gpu_register_alloc_granularity_map =
{
	2, {
		{ "Wavefront", si_gpu_register_alloc_wavefront },
		{ "WorkGroup", si_gpu_register_alloc_work_group }
	}
};
enum si_gpu_register_alloc_granularity_t si_gpu_register_alloc_granularity;

/* Device parameters */
int si_gpu_num_compute_units = 32;

/* Compute unit parameters */
int si_gpu_num_wavefront_pools = 4; /* Per CU */
int si_gpu_max_work_groups_per_wavefront_pool = 10;
int si_gpu_max_wavefronts_per_wavefront_pool = 10; 
int si_gpu_num_vector_registers = 65536; /* Per CU */
int si_gpu_num_scalar_registers = 2048; /* Per CU */
unsigned int si_gpu_register_alloc_size = 32;

/* Front-end parameters */
int si_gpu_fe_fetch_latency = 5;
int si_gpu_fe_fetch_width = 4;
int si_gpu_fe_fetch_buffer_size = 10;
int si_gpu_fe_issue_latency = 1;
int si_gpu_fe_issue_width = 5;
int si_gpu_fe_max_inst_issued_per_type = 1;

/* SIMD unit parameters */
int si_gpu_simd_num_simd_lanes = 16; /* Per SIMD */
int si_gpu_simd_width = 1;
int si_gpu_simd_issue_buffer_size = 1;
int si_gpu_simd_decode_latency = 1;
int si_gpu_simd_decode_buffer_size = 1;
int si_gpu_simd_exec_latency = 8;
int si_gpu_simd_exec_buffer_size = 2;

/* Scalar unit parameters */
int si_gpu_scalar_unit_width = 1;
int si_gpu_scalar_unit_issue_buffer_size = 1;
int si_gpu_scalar_unit_decode_latency = 1;
int si_gpu_scalar_unit_decode_buffer_size = 1;
int si_gpu_scalar_unit_read_latency = 1;
int si_gpu_scalar_unit_read_buffer_size = 1;
int si_gpu_scalar_unit_exec_latency = 1;
int si_gpu_scalar_unit_exec_buffer_size = 16;
int si_gpu_scalar_unit_write_latency = 1;
int si_gpu_scalar_unit_write_buffer_size = 1;

/* Branch unit parameters */
int si_gpu_branch_unit_width = 1;
int si_gpu_branch_unit_issue_buffer_size = 1;
int si_gpu_branch_unit_decode_latency = 1;
int si_gpu_branch_unit_decode_buffer_size = 1;
int si_gpu_branch_unit_read_latency = 1;
int si_gpu_branch_unit_read_buffer_size = 1;
int si_gpu_branch_unit_exec_latency = 1;
int si_gpu_branch_unit_exec_buffer_size = 1;
int si_gpu_branch_unit_write_latency = 1;
int si_gpu_branch_unit_write_buffer_size = 1;

/* LDS unit parameters */
int si_gpu_lds_width = 1;
int si_gpu_lds_issue_buffer_size = 1;
int si_gpu_lds_decode_latency = 1;
int si_gpu_lds_decode_buffer_size = 1;
int si_gpu_lds_read_latency = 1;
int si_gpu_lds_read_buffer_size = 1;
int si_gpu_lds_max_inflight_mem_accesses = 32;
int si_gpu_lds_write_latency = 1;
int si_gpu_lds_write_buffer_size = 1;

/* Vector mem unit parameters */
int si_gpu_vector_mem_width = 1;
int si_gpu_vector_mem_issue_buffer_size = 1;
int si_gpu_vector_mem_decode_latency = 1;
int si_gpu_vector_mem_decode_buffer_size = 1;
int si_gpu_vector_mem_read_latency = 1;
int si_gpu_vector_mem_read_buffer_size = 1;
int si_gpu_vector_mem_max_inflight_mem_accesses = 32;
int si_gpu_vector_mem_write_latency = 1;
int si_gpu_vector_mem_write_buffer_size = 1;

/* LDS memory parameters */
int si_gpu_lds_size = 65536; /* 64KB */
int si_gpu_lds_alloc_size = 64; 
int si_gpu_lds_latency = 2;
int si_gpu_lds_block_size = 64;
int si_gpu_lds_num_ports = 2;

struct si_gpu_t *si_gpu;

/*
 * Private Functions
 */

/* Version of Southern Islands trace producer.
 * See 'src/visual/southern-islands/gpu.c' for Southern Islands trace consumer. */

#define SI_TRACE_VERSION_MAJOR		1
#define SI_TRACE_VERSION_MINOR		1


static void si_gpu_device_init()
{
	struct si_compute_unit_t *compute_unit;
	int compute_unit_id;

	/* Initialize */
	si_gpu = xcalloc(1, sizeof(struct si_gpu_t));

	/* Initialize compute units */
	si_gpu->compute_units = xcalloc(si_gpu_num_compute_units, sizeof(void *));
	SI_GPU_FOREACH_COMPUTE_UNIT(compute_unit_id)
	{
		si_gpu->compute_units[compute_unit_id] = si_compute_unit_create();
		compute_unit = si_gpu->compute_units[compute_unit_id];
		compute_unit->id = compute_unit_id;
		DOUBLE_LINKED_LIST_INSERT_TAIL(si_gpu, compute_unit_ready, compute_unit);
	}

	/* Trace */
	si_trace_header("si.init version=\"%d.%d\" num_compute_units=%d\n",
		SI_TRACE_VERSION_MAJOR, SI_TRACE_VERSION_MINOR,
		si_gpu_num_compute_units);
}


static void si_config_read(void)
{
	struct config_t *gpu_config;
	char *section;
	char *err_note =
		"\tPlease run 'm2s --si-help' or consult the Multi2Sim Guide for a\n"
		"\tdescription of the GPU configuration file format.";

	//char *gpu_register_alloc_granularity_str;

	/* Load GPU configuration file */
	gpu_config = config_create(si_gpu_config_file_name);
	if (*si_gpu_config_file_name)
		config_load(gpu_config);
	
	/* Device */
	section = "Device";

	si_gpu_num_compute_units = config_read_int(
		gpu_config, section, "NumComputeUnits", si_gpu_num_compute_units);
	if (si_gpu_num_compute_units < 1)
		fatal("%s: invalid value for 'NumComputeUnits'.\n%s", 
			si_gpu_config_file_name, err_note);

#if 0
	si_gpu_register_alloc_size = config_read_int(
		gpu_config, section, "RegisterAllocSize", si_gpu_register_alloc_size);
	if (si_gpu_register_alloc_size < 1)
		fatal("%s: invalid value for 'RegisterAllocSize'.\n%s", 
			si_gpu_config_file_name, err_note);
	if (si_gpu_num_registers % si_gpu_register_alloc_size)
		fatal("%s: 'NumRegisters' not a multiple of 'RegisterAllocSize'.\n%s",
			si_gpu_config_file_name, err_note);

	gpu_register_alloc_granularity_str = config_read_string(
		gpu_config, section, "RegisterAllocGranularity", "WorkGroup");
	si_gpu_register_alloc_granularity = str_map_string_case(
		&si_gpu_register_alloc_granularity_map, 
		gpu_register_alloc_granularity_str);
	if (si_gpu_register_alloc_granularity == si_gpu_register_alloc_invalid)
		fatal("%s: invalid value for 'RegisterAllocGranularity'.\n%s",
			si_gpu_config_file_name, err_note);
#endif

	/* Compute Unit */
	section = "ComputeUnit";

	si_gpu_num_wavefront_pools = config_read_int(
		gpu_config, section, "NumWavefrontPools", si_gpu_num_wavefront_pools);
	if (si_gpu_num_wavefront_pools < 1)
		fatal("%s: invalid value for 'NumWavefrontPools'.\n%s", 
				si_gpu_config_file_name, err_note);

	si_gpu_max_work_groups_per_wavefront_pool = config_read_int(
		gpu_config, section, "MaxWorkGroupsPerWavefrontPool",
		si_gpu_max_work_groups_per_wavefront_pool);
	if (si_gpu_max_work_groups_per_wavefront_pool < 1)
		fatal("%s: invalid value for 'MaxWorkGroupsPerWavefrontPool'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_max_wavefronts_per_wavefront_pool = config_read_int(
		gpu_config, section, "MaxWavefrontsPerWavefrontPool",
		si_gpu_max_wavefronts_per_wavefront_pool);
	if (si_gpu_max_wavefronts_per_wavefront_pool < 1)
		fatal("%s: invalid value for 'MaxWavefrontsPerWavefrontPool'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_num_vector_registers = config_read_int(
		gpu_config, section, "NumVectorRegisters", si_gpu_num_vector_registers);
	if (si_gpu_num_vector_registers < 1)
		fatal("%s: invalid value for 'NumVectorRegisters'.\n%s", 
			si_gpu_config_file_name, err_note);

	si_gpu_num_scalar_registers = config_read_int(
		gpu_config, section, "NumScalarRegisters", si_gpu_num_scalar_registers);
	if (si_gpu_num_scalar_registers < 1)
		fatal("%s: invalid value for 'NumScalarRegisters'.\n%s", 
			si_gpu_config_file_name, err_note);

	/* Front End */
	section = "FrontEnd";

	si_gpu_fe_fetch_latency = config_read_int(
		gpu_config, section, "FetchLatency", si_gpu_fe_fetch_latency);
	if (si_gpu_fe_fetch_latency < 0)
		fatal("%s: invalid value for 'FetchLatency'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_fe_fetch_width = config_read_int(
		gpu_config, section, "FetchWidth", si_gpu_fe_fetch_width);
	if (si_gpu_fe_fetch_width < 1)
		fatal("%s: invalid value for 'FetchWidth'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_fe_fetch_buffer_size = config_read_int(
		gpu_config, section, "FetchBufferSize", si_gpu_fe_fetch_buffer_size);
	if (si_gpu_fe_fetch_buffer_size < 1)
		fatal("%s: invalid value for 'FetchBufferSize'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_fe_issue_latency = config_read_int(
		gpu_config, section, "IssueLatency", si_gpu_fe_issue_latency);
	if (si_gpu_fe_issue_latency < 0)
		fatal("%s: invalid value for 'IssueLatency'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_fe_issue_width = config_read_int(
		gpu_config, section, "IssueWidth", si_gpu_fe_issue_width);
	if (si_gpu_fe_issue_width < 1)
		fatal("%s: invalid value for 'IssueWidth'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_fe_max_inst_issued_per_type = config_read_int(
		gpu_config, section, "MaxInstIssuedPerType", 
		si_gpu_fe_max_inst_issued_per_type);
	if (si_gpu_fe_max_inst_issued_per_type < 1)
		fatal("%s: invalid value for 'MaxInstIssuedPerType'.\n%s",
			si_gpu_config_file_name, err_note);

	/* SIMD Unit */
	section = "SIMDUnit";

	si_gpu_simd_num_simd_lanes = config_read_int(
		gpu_config, section, "NumSIMDLanes", si_gpu_simd_num_simd_lanes);
	if (si_gpu_simd_num_simd_lanes < 1)
		fatal("%s: invalid value for 'NumSIMDLanes'.\n%s", 
			si_gpu_config_file_name, err_note);

	si_gpu_simd_width = config_read_int(
		gpu_config, section, "Width", si_gpu_simd_width);
	if (si_gpu_simd_width < 1)
		fatal("%s: invalid value for 'Width'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_simd_issue_buffer_size = config_read_int(
		gpu_config, section, "IssueBufferSize", si_gpu_simd_issue_buffer_size);
	if (si_gpu_simd_issue_buffer_size < 1)
		fatal("%s: invalid value for 'IssueBufferSize'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_simd_decode_latency = config_read_int(
		gpu_config, section, "DecodeLatency", si_gpu_simd_decode_latency);
	if (si_gpu_simd_decode_latency < 0)
		fatal("%s: invalid value for 'DecodeLatency'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_simd_decode_buffer_size = config_read_int(
		gpu_config, section, "DecodeBufferSize", 
		si_gpu_simd_decode_buffer_size);
	if (si_gpu_simd_decode_buffer_size < 1)
		fatal("%s: invalid value for 'DecodeBufferSize'.\n%s",
			si_gpu_config_file_name, err_note);

	/* FIXME Need to compute this dynamically based on the number
	 * of the number of SIMD lanes */
	si_gpu_simd_exec_latency = config_read_int(
		gpu_config, section, "ReadExecWriteLatency", si_gpu_simd_exec_latency);
	if (si_gpu_simd_exec_latency < 0)
		fatal("%s: invalid value for 'ReadExecWriteLatency'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_simd_exec_buffer_size = config_read_int(
		gpu_config, section, "ReadExecWriteBufferSize", 
		si_gpu_simd_exec_buffer_size);
	if (si_gpu_simd_exec_buffer_size < 1)
		fatal("%s: invalid value for 'ReadExecWriteBufferSize'.\n%s",
			si_gpu_config_file_name, err_note);

	/* Scalar Unit */
	section = "ScalarUnit";

	si_gpu_scalar_unit_width = config_read_int(
		gpu_config, section, "Width", si_gpu_scalar_unit_width);
	if (si_gpu_scalar_unit_width < 1)
		fatal("%s: invalid value for 'Width'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_scalar_unit_issue_buffer_size = config_read_int(
		gpu_config, section, "IssueBufferSize", 
		si_gpu_scalar_unit_issue_buffer_size);
	if (si_gpu_scalar_unit_issue_buffer_size < 1)
		fatal("%s: invalid value for 'IssueBufferSize'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_scalar_unit_decode_latency = config_read_int(
		gpu_config, section, "DecodeLatency", 
		si_gpu_scalar_unit_decode_latency);
	if (si_gpu_scalar_unit_decode_latency < 0)
		fatal("%s: invalid value for 'DecodeLatency'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_scalar_unit_decode_buffer_size = config_read_int(
		gpu_config, section, "DecodeBufferSize", 
		si_gpu_scalar_unit_decode_buffer_size);
	if (si_gpu_scalar_unit_decode_buffer_size < 1)
		fatal("%s: invalid value for 'DecodeBufferSize'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_scalar_unit_read_latency = config_read_int(
		gpu_config, section, "ReadLatency", si_gpu_scalar_unit_read_latency);
	if (si_gpu_scalar_unit_read_latency < 0)
		fatal("%s: invalid value for 'ReadLatency'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_scalar_unit_read_buffer_size = config_read_int(
		gpu_config, section, "ReadBufferSize", 
		si_gpu_scalar_unit_read_buffer_size);
	if (si_gpu_scalar_unit_read_buffer_size < 1)
		fatal("%s: invalid value for 'ReadBufferSize'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_scalar_unit_exec_latency = config_read_int(
		gpu_config, section, "ALULatency", si_gpu_scalar_unit_exec_latency);
	if (si_gpu_scalar_unit_exec_latency < 0)
		fatal("%s: invalid value for 'ALULatency'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_scalar_unit_exec_buffer_size= config_read_int(
		gpu_config, section, "ExecBufferSize", 
		si_gpu_scalar_unit_exec_buffer_size);
	if (si_gpu_scalar_unit_exec_buffer_size < 1)
		fatal("%s: invalid value for 'ExecBufferSize'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_scalar_unit_write_latency = config_read_int(
		gpu_config, section, "WriteLatency", si_gpu_scalar_unit_write_latency);
	if (si_gpu_scalar_unit_write_latency < 0)
		fatal("%s: invalid value for 'WriteLatency'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_scalar_unit_write_buffer_size = config_read_int(
		gpu_config, section, "WriteBufferSize", 
		si_gpu_scalar_unit_write_buffer_size);
	if (si_gpu_scalar_unit_write_buffer_size < 1)
		fatal("%s: invalid value for 'WriteBufferSize'.\n%s",
			si_gpu_config_file_name, err_note);

	/* Branch Unit */
	section = "BranchUnit";

	si_gpu_branch_unit_width = config_read_int(
		gpu_config, section, "Width", si_gpu_branch_unit_width);
	if (si_gpu_branch_unit_width < 1)
		fatal("%s: invalid value for 'Width'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_branch_unit_issue_buffer_size = config_read_int(
		gpu_config, section, "IssueBufferSize", 
		si_gpu_branch_unit_issue_buffer_size);
	if (si_gpu_branch_unit_issue_buffer_size < 1)
		fatal("%s: invalid value for 'IssueBufferSize'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_branch_unit_decode_latency = config_read_int(
		gpu_config, section, "DecodeLatency", 
		si_gpu_branch_unit_decode_latency);
	if (si_gpu_branch_unit_decode_latency < 0)
		fatal("%s: invalid value for 'DecodeLatency'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_branch_unit_decode_buffer_size = config_read_int(
		gpu_config, section, "DecodeBufferSize", 
		si_gpu_branch_unit_decode_buffer_size);
	if (si_gpu_branch_unit_decode_buffer_size < 1)
		fatal("%s: invalid value for 'DecodeBufferSize'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_branch_unit_read_latency = config_read_int(
		gpu_config, section, "ReadLatency", si_gpu_branch_unit_read_latency);
	if (si_gpu_branch_unit_read_latency < 0)
		fatal("%s: invalid value for 'ReadLatency'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_branch_unit_read_buffer_size = config_read_int(
		gpu_config, section, "ReadBufferSize", 
		si_gpu_branch_unit_read_buffer_size);
	if (si_gpu_branch_unit_read_buffer_size < 1)
		fatal("%s: invalid value for 'ReadBufferSize'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_branch_unit_exec_latency = config_read_int(
		gpu_config, section, "ExecLatency", si_gpu_branch_unit_exec_latency);
	if (si_gpu_branch_unit_exec_latency < 0)
		fatal("%s: invalid value for 'ExecLatency'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_branch_unit_exec_buffer_size= config_read_int(
		gpu_config, section, "ExecBufferSize", 
		si_gpu_branch_unit_exec_buffer_size);
	if (si_gpu_branch_unit_exec_buffer_size < 1)
		fatal("%s: invalid value for 'ExecBufferSize'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_branch_unit_write_latency = config_read_int(
		gpu_config, section, "WriteLatency", si_gpu_branch_unit_write_latency);
	if (si_gpu_branch_unit_write_latency < 0)
		fatal("%s: invalid value for 'WriteLatency'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_branch_unit_write_buffer_size = config_read_int(
		gpu_config, section, "WriteBufferSize", 
		si_gpu_branch_unit_write_buffer_size);
	if (si_gpu_branch_unit_write_buffer_size < 1)
		fatal("%s: invalid value for 'WriteBufferSize'.\n%s",
			si_gpu_config_file_name, err_note);

	/* LDS Unit */
	section = "LDSUnit";

	si_gpu_lds_width = config_read_int(
		gpu_config, section, "Width", si_gpu_lds_width);
	if (si_gpu_lds_width < 1)
		fatal("%s: invalid value for 'Width'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_lds_issue_buffer_size = config_read_int(
		gpu_config, section, "IssueBufferSize", si_gpu_lds_issue_buffer_size);
	if (si_gpu_lds_issue_buffer_size < 1)
		fatal("%s: invalid value for 'IssueBufferSize'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_lds_decode_latency = config_read_int(
		gpu_config, section, "DecodeLatency", si_gpu_lds_decode_latency);
	if (si_gpu_lds_decode_latency < 0)
		fatal("%s: invalid value for 'DecodeLatency'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_lds_decode_buffer_size = config_read_int(
		gpu_config, section, "DecodeBufferSize", si_gpu_lds_decode_buffer_size);
	if (si_gpu_lds_decode_buffer_size < 1)
		fatal("%s: invalid value for 'DecodeBufferSize'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_lds_read_latency = config_read_int(
		gpu_config, section, "ReadLatency", si_gpu_lds_read_latency);
	if (si_gpu_lds_read_latency < 0)
		fatal("%s: invalid value for 'ReadLatency'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_lds_read_buffer_size = config_read_int(
		gpu_config, section, "ReadBufferSize", si_gpu_lds_read_buffer_size);
	if (si_gpu_lds_read_buffer_size < 1)
		fatal("%s: invalid value for 'ReadBufferSize'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_lds_max_inflight_mem_accesses = config_read_int(
		gpu_config, section, "MaxInflightMem", 
		si_gpu_lds_max_inflight_mem_accesses);
	if (si_gpu_lds_max_inflight_mem_accesses < 1)
		fatal("%s: invalid value for 'MaxInflightMem'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_lds_write_latency = config_read_int(
		gpu_config, section, "WriteLatency", si_gpu_lds_write_latency);
	if (si_gpu_lds_write_latency < 0)
		fatal("%s: invalid value for 'WriteLatency'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_lds_write_buffer_size = config_read_int(
		gpu_config, section, "WriteBufferSize", si_gpu_lds_write_buffer_size);
	if (si_gpu_lds_write_buffer_size < 1)
		fatal("%s: invalid value for 'WriteBufferSize'.\n%s",
			si_gpu_config_file_name, err_note);

	/* VectorMem Unit */
	section = "VectorMemUnit";
	
	si_gpu_vector_mem_width = config_read_int(
		gpu_config, section, "Width", si_gpu_vector_mem_width);
	if (si_gpu_vector_mem_width < 1)
		fatal("%s: invalid value for 'Width'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_vector_mem_issue_buffer_size = config_read_int(
		gpu_config, section, "IssueBufferSize", 
		si_gpu_vector_mem_issue_buffer_size);
	if (si_gpu_vector_mem_issue_buffer_size < 1)
		fatal("%s: invalid value for 'IssueBufferSize'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_vector_mem_decode_latency = config_read_int(
		gpu_config, section, "DecodeLatency", 
		si_gpu_vector_mem_decode_latency);
	if (si_gpu_vector_mem_decode_latency < 0)
		fatal("%s: invalid value for 'DecodeLatency'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_vector_mem_decode_buffer_size = config_read_int(
		gpu_config, section, "DecodeBufferSize", 
		si_gpu_vector_mem_decode_buffer_size);
	if (si_gpu_vector_mem_decode_buffer_size < 1)
		fatal("%s: invalid value for 'DecodeBufferSize'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_vector_mem_read_latency = config_read_int(
		gpu_config, section, "ReadLatency", si_gpu_vector_mem_read_latency);
	if (si_gpu_vector_mem_read_latency < 0)
		fatal("%s: invalid value for 'ReadLatency'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_vector_mem_read_buffer_size = config_read_int(
		gpu_config, section, "ReadBufferSize", 
		si_gpu_vector_mem_read_buffer_size);
	if (si_gpu_vector_mem_read_buffer_size < 1)
		fatal("%s: invalid value for 'ReadBufferSize'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_vector_mem_max_inflight_mem_accesses = config_read_int(
		gpu_config, section, "MaxInflightMem", 
		si_gpu_vector_mem_max_inflight_mem_accesses);
	if (si_gpu_vector_mem_max_inflight_mem_accesses < 1)
		fatal("%s: invalid value for 'MaxInflightMem'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_vector_mem_write_latency = config_read_int(
		gpu_config, section, "WriteLatency", si_gpu_vector_mem_write_latency);
	if (si_gpu_vector_mem_write_latency < 0)
		fatal("%s: invalid value for 'WriteLatency'.\n%s",
			si_gpu_config_file_name, err_note);

	si_gpu_vector_mem_write_buffer_size = config_read_int(
		gpu_config, section, "WriteBufferSize", 
		si_gpu_vector_mem_write_buffer_size);
	if (si_gpu_vector_mem_write_buffer_size < 1)
		fatal("%s: invalid value for 'WriteBufferSize'.\n%s",
			si_gpu_config_file_name, err_note);

	/* Local memory */
	section = "LocalDataShare";

	si_gpu_lds_size = config_read_int(
		gpu_config, section, "Size", si_gpu_lds_size);
	si_gpu_lds_alloc_size = config_read_int(
		gpu_config, section, "AllocSize", si_gpu_lds_alloc_size);
	si_gpu_lds_block_size = config_read_int(
		gpu_config, section, "BlockSize", si_gpu_lds_block_size);
	si_gpu_lds_latency = config_read_int(
		gpu_config, section, "Latency", si_gpu_lds_latency);
	si_gpu_lds_num_ports = config_read_int(
		gpu_config, section, "Ports", si_gpu_lds_num_ports);

	if ((si_gpu_lds_size & (si_gpu_lds_size - 1)) || si_gpu_lds_size < 4)
		fatal("%s: %s->Size must be a power of two and at least 4.\n%s",
			si_gpu_config_file_name, section, err_note);
	if (si_gpu_lds_alloc_size < 1)
		fatal("%s: invalid value for %s->Allocsize.\n%s", 
			si_gpu_config_file_name, section, err_note);
	if (si_gpu_lds_size % si_gpu_lds_alloc_size)
		fatal("%s: %s->Size must be a multiple of %s->AllocSize.\n%s", 
			si_gpu_config_file_name, section, section, err_note);
	if ((si_gpu_lds_block_size & (si_gpu_lds_block_size - 1)) || 
		si_gpu_lds_block_size < 4)
		fatal("%s: %s->BlockSize must be a power of two and at least 4.\n%s",
			si_gpu_config_file_name, section, err_note);
	if (si_gpu_lds_alloc_size % si_gpu_lds_block_size)
		fatal("%s: %s->AllocSize must be a multiple of %s->BlockSize.\n%s", 
			si_gpu_config_file_name, section, section, err_note);
	if (si_gpu_lds_latency < 1)
		fatal("%s: invalid value for %s->Latency.\n%s", 
			si_gpu_config_file_name, section, err_note);
	if (si_gpu_lds_size < si_gpu_lds_block_size)
		fatal("%s: %s->Size cannot be smaller than %s->BlockSize * "
			"%s->Banks.\n%s", si_gpu_config_file_name, section, 
			section, section, err_note);
	
	/* Cycle Interval report */
	si_spatial_report_config_read(gpu_config);

	/* Close GPU configuration file */
	config_check(gpu_config);
	config_free(gpu_config);
}


void si_config_dump(FILE *f)
{
	/* Device */
	fprintf(f, "[ Device ]\n");
	fprintf(f, "NumComputeUnits = %d\n", si_gpu_num_compute_units);
	fprintf(f, "\n");

	/* Compute Unit */
	fprintf(f, "[ ComputeUnit ]\n");
	fprintf(f, "NumWavefrontPools = %d\n", si_gpu_num_wavefront_pools);
	fprintf(f, "NumVectorRegisters = %d\n", si_gpu_num_vector_registers);
	fprintf(f, "NumScalarRegisters = %d\n", si_gpu_num_scalar_registers);
	fprintf(f, "MaxWorkGroupsPerWavefrontPool = %d\n", 
		si_gpu_max_work_groups_per_wavefront_pool);
	fprintf(f, "MaxWavefrontsPerWavefrontPool = %d\n", 
		si_gpu_max_wavefronts_per_wavefront_pool);
	fprintf(f, "\n");
	/*
	fprintf(f, "RegisterAllocSize = %d\n", si_gpu_register_alloc_size);
	fprintf(f, "RegisterAllocGranularity = %s\n", 
		str_map_value(&si_gpu_register_alloc_granularity_map, 
		si_gpu_register_alloc_granularity));
	*/

	/* Front-End */
	fprintf(f, "[ FrontEnd ]\n");
	fprintf(f, "FetchLatency = %d\n", si_gpu_fe_fetch_latency);
	fprintf(f, "FetchWidth = %d\n", si_gpu_fe_fetch_width);
	fprintf(f, "FetchBufferSize = %d\n", si_gpu_fe_fetch_buffer_size);
	fprintf(f, "IssueLatency = %d\n", si_gpu_fe_issue_latency);
	fprintf(f, "IssueWidth = %d\n", si_gpu_fe_issue_width);
	fprintf(f, "MaxInstIssuedPerType = %d\n", 
		si_gpu_fe_max_inst_issued_per_type);
	fprintf(f, "\n");

	/* SIMD Unit */
	fprintf(f, "[ SIMDUnit ]\n");
	fprintf(f, "NumSIMDLanes = %d\n", si_gpu_simd_num_simd_lanes);
	fprintf(f, "Width = %d\n", si_gpu_simd_width);
	fprintf(f, "IssueBufferSize = %d\n", si_gpu_simd_issue_buffer_size);
	fprintf(f, "DecodeLatency = %d\n", si_gpu_simd_decode_latency);
	fprintf(f, "DecodeBufferSize = %d\n", si_gpu_simd_decode_buffer_size);
	fprintf(f, "ReadExecWriteLatency = %d\n", si_gpu_simd_exec_latency);
	fprintf(f, "ReadExecWriteBufferSize = %d\n", si_gpu_simd_exec_buffer_size);
	fprintf(f, "\n");

	/* Scalar Unit */
	fprintf(f, "[ ScalarUnit ]\n");
	fprintf(f, "Width = %d\n", si_gpu_scalar_unit_width);
	fprintf(f, "IssueBufferSize = %d\n", si_gpu_scalar_unit_issue_buffer_size);
	fprintf(f, "DecodeLatency = %d\n", si_gpu_scalar_unit_decode_latency);
	fprintf(f, "DecodeBufferSize = %d\n", 
		si_gpu_scalar_unit_decode_buffer_size);
	fprintf(f, "ReadLatency = %d\n", si_gpu_scalar_unit_read_latency);
	fprintf(f, "ReadBufferSize = %d\n", si_gpu_scalar_unit_read_buffer_size);
	fprintf(f, "ALULatency = %d\n", si_gpu_scalar_unit_exec_latency);
	fprintf(f, "ExecBufferSize = %d\n", si_gpu_scalar_unit_exec_buffer_size);
	fprintf(f, "WriteLatency = %d\n", si_gpu_scalar_unit_write_latency);
	fprintf(f, "WriteBufferSize = %d\n", si_gpu_scalar_unit_write_buffer_size);
	fprintf(f, "\n");

	/* Branch Unit */
	fprintf(f, "[ BranchUnit ]\n");
	fprintf(f, "Width = %d\n", si_gpu_branch_unit_width);
	fprintf(f, "IssueBufferSize = %d\n", si_gpu_branch_unit_issue_buffer_size);
	fprintf(f, "DecodeLatency = %d\n", si_gpu_branch_unit_decode_latency);
	fprintf(f, "DecodeBufferSize = %d\n", 
		si_gpu_branch_unit_decode_buffer_size);
	fprintf(f, "ReadLatency = %d\n", si_gpu_branch_unit_read_latency);
	fprintf(f, "ReadBufferSize = %d\n", si_gpu_branch_unit_read_buffer_size);
	fprintf(f, "ExecLatency = %d\n", si_gpu_branch_unit_exec_latency);
	fprintf(f, "ExecBufferSize = %d\n", si_gpu_branch_unit_exec_buffer_size);
	fprintf(f, "WriteLatency = %d\n", si_gpu_branch_unit_write_latency);
	fprintf(f, "WriteBufferSize = %d\n", si_gpu_branch_unit_write_buffer_size);
	fprintf(f, "\n");

	/* LDS */
	fprintf(f, "[ LDSUnit ]\n");
	fprintf(f, "Width = %d\n", si_gpu_lds_width);
	fprintf(f, "IssueBufferSize = %d\n", si_gpu_lds_issue_buffer_size);
	fprintf(f, "DecodeLatency = %d\n", si_gpu_lds_decode_latency);
	fprintf(f, "DecodeBufferSize = %d\n", 
		si_gpu_lds_decode_buffer_size);
	fprintf(f, "ReadLatency = %d\n", si_gpu_lds_read_latency);
	fprintf(f, "ReadBufferSize = %d\n", si_gpu_lds_read_buffer_size);
	fprintf(f, "MaxInflightMem = %d\n", si_gpu_lds_max_inflight_mem_accesses);
	fprintf(f, "WriteLatency = %d\n", si_gpu_lds_write_latency);
	fprintf(f, "WriteBufferSize = %d\n", si_gpu_lds_write_buffer_size);
	fprintf(f, "\n");

	/* Vector Memory */
	fprintf(f, "[ VectorMemUnit ]\n");
	fprintf(f, "Width = %d\n", si_gpu_vector_mem_width);
	fprintf(f, "IssueBufferSize = %d\n", si_gpu_vector_mem_issue_buffer_size);
	fprintf(f, "DecodeLatency = %d\n", si_gpu_vector_mem_decode_latency);
	fprintf(f, "DecodeBufferSize = %d\n", 
		si_gpu_vector_mem_decode_buffer_size);
	fprintf(f, "ReadLatency = %d\n", si_gpu_vector_mem_read_latency);
	fprintf(f, "ReadBufferSize = %d\n", si_gpu_vector_mem_read_buffer_size);
	fprintf(f, "MaxInflightMem = %d\n", 
		si_gpu_vector_mem_max_inflight_mem_accesses);
	fprintf(f, "WriteLatency = %d\n", si_gpu_vector_mem_write_latency);
	fprintf(f, "WriteBufferSize = %d\n", si_gpu_vector_mem_write_buffer_size);
	fprintf(f, "\n");

	/* LDS */
	fprintf(f, "[ LocalDataShare ]\n");
	fprintf(f, "Size = %d\n", si_gpu_lds_size);
	fprintf(f, "AllocSize = %d\n", si_gpu_lds_alloc_size);
	fprintf(f, "BlockSize = %d\n", si_gpu_lds_block_size);
	fprintf(f, "Latency = %d\n", si_gpu_lds_latency);
	fprintf(f, "Ports = %d\n", si_gpu_lds_num_ports);
	fprintf(f, "\n");

	/* End of configuration */
	fprintf(f, "\n");
}


static void si_gpu_map_ndrange(struct si_ndrange_t *ndrange)
{
	int compute_unit_id;

	/* Assign current ND-Range */
	assert(!si_gpu->ndrange);
	si_gpu->ndrange = ndrange;

	/* Check that at least one work-group can be allocated per Wavefront Pool */
	si_gpu->work_groups_per_wavefront_pool = 
		si_calc_get_work_groups_per_wavefront_pool(ndrange->kernel->local_size, 
		ndrange->kernel->bin_file->enc_dict_entry_southern_islands->
		num_vgpr_used, ndrange->local_mem_top);
	if (!si_gpu->work_groups_per_wavefront_pool)
		fatal("work-group resources cannot be allocated to a compute unit.\n"
			"\tA compute unit in the GPU has a limit in number of wavefronts, number\n"
			"\tof registers, and amount of local memory. If the work-group size\n"
			"\texceeds any of these limits, the ND-Range cannot be executed.\n");

	/* Calculate limit of wavefronts and work-items per Wavefront Pool */
	si_gpu->wavefronts_per_wavefront_pool = si_gpu->work_groups_per_wavefront_pool * 
		ndrange->wavefronts_per_work_group;
	si_gpu->work_items_per_wavefront_pool = si_gpu->wavefronts_per_wavefront_pool * 
		si_emu_wavefront_size;

	/* Calculate limit of work groups, wavefronts and work-items per compute unit */
	si_gpu->work_groups_per_compute_unit = si_gpu->work_groups_per_wavefront_pool * 
		si_gpu_num_wavefront_pools;
	si_gpu->wavefronts_per_compute_unit = si_gpu->wavefronts_per_wavefront_pool * 
		si_gpu_num_wavefront_pools;
	si_gpu->work_items_per_compute_unit = si_gpu->work_items_per_wavefront_pool * 
		si_gpu_num_wavefront_pools;
	assert(si_gpu->work_groups_per_wavefront_pool <= si_gpu_max_work_groups_per_wavefront_pool);
	assert(si_gpu->wavefronts_per_wavefront_pool <= si_gpu_max_wavefronts_per_wavefront_pool);

	/* Reset architectural state */
	SI_GPU_FOREACH_COMPUTE_UNIT(compute_unit_id)
	{
		// FIXME
		//compute_unit = si_gpu->compute_units[compute_unit_id];
		//compute_unit->simd.decode_index = 0;
		//compute_unit->simd.execute_index = 0;
	}
}


static void si_gpu_unmap_ndrange(void)
{
	/* Dump stats */
	si_ndrange_dump(si_gpu->ndrange, si_emu_report_file);

	/* Unmap */
	si_gpu->ndrange = NULL;
}




/*
 * Public Functions
 */

void si_gpu_init(void)
{
	/* Trace */
	si_trace_category = trace_new_category();

	/* Register functions for architecture */
	si_emu_arch->mem_config_check_func = si_mem_config_check;
	si_emu_arch->mem_config_default_func = si_mem_config_default;
	si_emu_arch->mem_config_parse_entry_func = si_mem_config_parse_entry;

	/* Try to open report file */
	if (si_gpu_report_file_name[0] && !file_can_open_for_write(si_gpu_report_file_name))
		fatal("%s: cannot open GPU pipeline report file",
			si_gpu_report_file_name);

	/* Read configuration file */
	si_config_read();

	/* Initializations */
	si_gpu_device_init();
	si_uop_init();
}


void si_gpu_done()
{
	struct si_compute_unit_t *compute_unit;
	int compute_unit_id;

	/* GPU pipeline report */
	si_gpu_dump_report();

	/* Free stream cores, compute units, and device */
	SI_GPU_FOREACH_COMPUTE_UNIT(compute_unit_id)
	{
		compute_unit = si_gpu->compute_units[compute_unit_id];
		si_compute_unit_free(compute_unit);
	}
	free(si_gpu->compute_units);

	/* Free GPU */
	free(si_gpu);

	if(si_spatial_report_active)
		si_cu_spatial_report_done();


	/* Finalizations */
	si_uop_done();
}


void si_gpu_dump_default_config(char *filename)
{
	FILE *f;

	/* Open file */
	f = file_open_for_write(filename);
	if (!f)
		return;

	si_config_dump(f);

	file_close(f);
}


void si_gpu_dump_report(void)
{
	struct si_compute_unit_t *compute_unit;
	struct mod_t *local_mod;
	int compute_unit_id;

	FILE *f;

	double inst_per_cycle;

	long long coalesced_reads;
	long long coalesced_writes;

	/* Open file */
	f = file_open_for_write(si_gpu_report_file_name);
	if (!f)
		return;

	/* Dump GPU configuration */
	fprintf(f, ";\n; GPU Configuration\n;\n\n");
	si_config_dump(f);

	/* Report for device */
	fprintf(f, ";\n; Simulation Statistics\n;\n\n");
	inst_per_cycle = si_gpu->cycle ? (double) si_emu->inst_count / si_gpu->cycle : 0.0;
	fprintf(f, "[ Device ]\n\n");
	fprintf(f, "NDRangeCount = %d\n", si_emu->ndrange_count);
	fprintf(f, "Instructions = %lld\n", si_emu->inst_count);
	fprintf(f, "Scalar ALU Instructions = %lld\n", si_emu->scalar_alu_inst_count);
	fprintf(f, "Scalar Mem Instructions = %lld\n", si_emu->scalar_mem_inst_count);
	fprintf(f, "Branch Instructions = %lld\n", si_emu->branch_inst_count);
	fprintf(f, "Vector ALU Instructions = %lld\n", si_emu->vector_alu_inst_count);
	fprintf(f, "Local Memory Instructions = %lld\n", si_emu->local_mem_inst_count);
	fprintf(f, "Vector Mem Instructions = %lld\n", si_emu->vector_mem_inst_count);
	fprintf(f, "Cycles = %lld\n", si_gpu->cycle);
	fprintf(f, "InstructionsPerCycle = %.4g\n", inst_per_cycle);
	fprintf(f, "\n\n");

	/* Report for compute units */
	SI_GPU_FOREACH_COMPUTE_UNIT(compute_unit_id)
	{
		compute_unit = si_gpu->compute_units[compute_unit_id];
		local_mod = compute_unit->local_memory;

		inst_per_cycle = compute_unit->cycle ? (double) compute_unit->inst_count
			/ compute_unit->cycle : 0.0;
		coalesced_reads = local_mod->reads - local_mod->effective_reads;
		coalesced_writes = local_mod->writes - local_mod->effective_writes;

		fprintf(f, "[ ComputeUnit %d ]\n\n", compute_unit_id);

		fprintf(f, "WorkGroupCount = %lld\n", compute_unit->mapped_work_groups);
		fprintf(f, "Instructions = %lld\n", compute_unit->inst_count);
		fprintf(f, "Scalar ALU Instructions = %lld\n", compute_unit->scalar_alu_inst_count);
		fprintf(f, "Scalar Mem Instructions = %lld\n", compute_unit->scalar_mem_inst_count);
		fprintf(f, "Branch Instructions = %lld\n", compute_unit->branch_inst_count);
		fprintf(f, "SIMD Instructions = %lld\n", compute_unit->simd_inst_count);
		fprintf(f, "Vector Mem Instructions = %lld\n", compute_unit->vector_mem_inst_count);
		fprintf(f, "Local Mem Instructions = %lld\n", compute_unit->local_mem_inst_count);
		fprintf(f, "Cycles = %lld\n", compute_unit->cycle);
		fprintf(f, "InstructionsPerCycle = %.4g\n", inst_per_cycle);
		fprintf(f, "\n");

		fprintf(f, "LocalMemory.Accesses = %lld\n", local_mod->reads + local_mod->writes);
		fprintf(f, "LocalMemory.Reads = %lld\n", local_mod->reads);
		fprintf(f, "LocalMemory.EffectiveReads = %lld\n", local_mod->effective_reads);
		fprintf(f, "LocalMemory.CoalescedReads = %lld\n", coalesced_reads);
		fprintf(f, "LocalMemory.Writes = %lld\n", local_mod->writes);
		fprintf(f, "LocalMemory.EffectiveWrites = %lld\n", local_mod->effective_writes);
		fprintf(f, "LocalMemory.CoalescedWrites = %lld\n", coalesced_writes);
		fprintf(f, "\n\n");
	}

	file_close(f);
}

void si_gpu_dump_summary(FILE *f)
{
	double time_in_sec;
	double cycles_per_sec;

	/* Calculate statistics */
	time_in_sec = (double) m2s_timer_get_value(si_emu->timer) / 1.0e6;
	cycles_per_sec = time_in_sec > 0.0 ? 
		(double) si_gpu->cycle / time_in_sec : 0.0;

	/* Print statistics */
	fprintf(f, "Cycles = %lld\n", si_gpu->cycle);
	fprintf(f, "SimulatedCyclesPerSecond = %.0f\n", cycles_per_sec);
	//fprintf(f, "Time at 925MHz = %.3fms\n", si_gpu->cycle/925000.0);
}


/* Run one iteration of the Southern Islands GPU timing simulation loop. */
int si_gpu_run(void)
{
	struct si_ndrange_t *ndrange;

	struct si_compute_unit_t *compute_unit;
	struct si_compute_unit_t *compute_unit_next;

	/* For efficiency when no Southern Islands emulation is selected, exit here
	 * if the list of existing ND-Ranges is empty. */
	if (!si_emu->ndrange_list_count)
		return 0;

	/* Start one ND-Range in state 'pending' */
	while ((ndrange = si_emu->pending_ndrange_list_head))
	{
		/* Currently not supported for more than 1 ND-Range */
		if (si_gpu->ndrange)
			fatal("%s: Southern Islands GPU timing simulation not supported "
				"for multiple ND-Ranges", __FUNCTION__);

		/* Set ND-Range status to 'running' */
		si_ndrange_clear_status(ndrange, si_ndrange_pending);
		si_ndrange_set_status(ndrange, si_ndrange_running);

		/* Trace */
		si_trace("si.new_ndrange id=%d wg_first=%d wg_count=%d\n", ndrange->id,
			ndrange->work_group_id_first, ndrange->work_group_count);

		/* Map ND-Range to GPU */
		si_gpu_map_ndrange(ndrange);
		si_calc_plot();
	}

	/* Mapped ND-Range */
	ndrange = si_gpu->ndrange;
	assert(ndrange);

	/* Allocate work-groups to compute units */
	while (si_gpu->compute_unit_ready_list_head && ndrange->pending_list_head)
		si_compute_unit_map_work_group(si_gpu->compute_unit_ready_list_head,
			ndrange->pending_list_head);

	/* One more cycle */
	si_gpu->cycle++;

	/* Stop if maximum number of GPU cycles exceeded */
	if (si_emu_max_cycles && si_gpu->cycle >= si_emu_max_cycles)
		esim_finish = esim_finish_si_max_cycles;

	/* Stop if maximum number of GPU instructions exceeded */
	if (si_emu_max_inst && si_emu->inst_count >= si_emu_max_inst)
		esim_finish = esim_finish_si_max_inst;

	/* Stop if there was a simulation stall */
	if ((si_gpu->cycle-si_gpu->last_complete_cycle) > 1000000)
	{
		warning("Southern Islands GPU simulation stalled.\n%s", si_err_stall);
		esim_finish = esim_finish_stall;
	}

	/* Stop if any reason met */
	if (esim_finish)
		return 1;

	/* Run one loop iteration on each busy compute unit */
	for (compute_unit = si_gpu->compute_unit_busy_list_head; compute_unit;
		compute_unit = compute_unit_next)
	{
		/* Store next busy compute unit, since this can change
		 * during the compute unit simulation loop iteration. */
		compute_unit_next = compute_unit->compute_unit_busy_list_next;

		/* Run one cycle */
		si_compute_unit_run(compute_unit);
	}

	/* If ND-Range finished execution in all compute units, free it. */
	if (!si_gpu->compute_unit_busy_list_count)
	{
		/* Dump ND-Range report */
		si_ndrange_dump(ndrange, si_emu_report_file);

		/* Stop if maximum number of kernels reached */
		if (si_emu_max_kernels && si_emu->ndrange_count >= si_emu_max_kernels)
			esim_finish = esim_finish_si_max_kernels;

		/* Finalize and free ND-Range */
		assert(si_ndrange_get_status(ndrange, si_ndrange_finished));
		si_gpu_unmap_ndrange();
		si_ndrange_free(ndrange);
	}

	/* Return true */
	return 1;
}
