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
#include <unistd.h>

#include <arch/southern-islands/asm/bin-file.h>
#include <arch/southern-islands/emu/emu.h>
#include <arch/southern-islands/emu/ndrange.h>
#include <driver/opencl-old/southern-islands/kernel.h>
#include <lib/util/debug.h>
#include <lib/util/file.h>
#include <lib/util/misc.h>

#include "calc.h"
#include "gpu.h"


char *si_gpu_calc_file_name = "";

static char *err_gnuplot_msg =
	"\nThe execution of the 'gnuplot' command-line failed. Please check that this\n"
	"\napplication is installed on your system. An error message could have occurred\n"
	"\nas well if gnuplot commands generated by Multi2Sim are not supported in the\n"
	"\ngnuplot version currently installed.\n";


int si_calc_get_work_groups_per_wavefront_pool(int work_items_per_work_group,
	int registers_per_work_item, int local_mem_per_work_group)
{
	int wavefronts_per_work_group;
	int registers_per_work_group;
	int max_work_groups_limitted_by_max_wavefronts;
	int max_work_groups_limitted_by_num_registers;
	int max_work_groups_limitted_by_local_mem;
	int work_groups_per_wavefront_pool;

	/* Get maximum number of work-groups per SIMD as limited by the 
	 * maximum number of wavefronts, given the number of wavefronts per 
	 * work-group in the NDRange */
	assert(si_emu_wavefront_size > 0);
	wavefronts_per_work_group = (work_items_per_work_group + 
		si_emu_wavefront_size - 1) / si_emu_wavefront_size;
	max_work_groups_limitted_by_max_wavefronts = 
		si_gpu_max_wavefronts_per_wavefront_pool /
		wavefronts_per_work_group;

	/* Get maximum number of work-groups per SIMD as limited by the number of
	 * available registers, given the number of registers used per work-item. */
	if (si_gpu_register_alloc_granularity == si_gpu_register_alloc_wavefront)
	{
		registers_per_work_group = ROUND_UP(registers_per_work_item * 
			si_emu_wavefront_size, si_gpu_register_alloc_size) * 
			wavefronts_per_work_group;
	}
	else
	{
		registers_per_work_group = ROUND_UP(registers_per_work_item *
			work_items_per_work_group, si_gpu_register_alloc_size);
	}
	/* FIXME need to account for scalar registers */
	max_work_groups_limitted_by_num_registers = registers_per_work_group ?
		si_gpu_num_vector_registers / registers_per_work_group :
		si_gpu_max_work_groups_per_wavefront_pool;

	/* Get maximum number of work-groups per SIMD as limited by the amount of
	 * available local memory, given the local memory used by each work-group 
	 * in the NDRange */
	local_mem_per_work_group = ROUND_UP(local_mem_per_work_group, 
		si_gpu_lds_alloc_size);
	max_work_groups_limitted_by_local_mem = local_mem_per_work_group ?
		si_gpu_lds_size / local_mem_per_work_group :
		si_gpu_max_work_groups_per_wavefront_pool;

	/* Based on the limits above, calculate the actual limit of work-groups 
	 * per SIMD. */
	work_groups_per_wavefront_pool = si_gpu_max_work_groups_per_wavefront_pool;
	work_groups_per_wavefront_pool = MIN(work_groups_per_wavefront_pool,
		max_work_groups_limitted_by_max_wavefronts);
	work_groups_per_wavefront_pool= MIN(work_groups_per_wavefront_pool, 
		max_work_groups_limitted_by_num_registers);
	work_groups_per_wavefront_pool = MIN(work_groups_per_wavefront_pool, 
		max_work_groups_limitted_by_local_mem);

	/* Return */
	return work_groups_per_wavefront_pool;
}


static void si_calc_plot_work_items_per_work_group(void)
{
	FILE *data_file, *script_file;

	char plot_file_name[MAX_PATH_SIZE];
	char data_file_name[MAX_PATH_SIZE];
	char script_file_name[MAX_PATH_SIZE];
	char cmd[MAX_PATH_SIZE];
	
	int local_mem_per_work_group;
	int work_items_per_work_group;
	int registers_per_work_item;

	int wavefronts_per_work_group;
	int work_groups_per_wavefront_pool;
	int wavefronts_per_wavefront_pool;

	int err;

	/* Create plot file */
	snprintf(plot_file_name, MAX_PATH_SIZE, "%s.%d.work_items.eps",
		si_gpu_calc_file_name, si_gpu->ndrange->id);
	if (!file_can_open_for_write(plot_file_name))
		fatal("%s: cannot write GPU occupancy calculation plot", plot_file_name);

	/* Generate data file */
	data_file = file_create_temp(data_file_name, MAX_PATH_SIZE);
	local_mem_per_work_group = si_gpu->ndrange->local_mem_top;
	registers_per_work_item = 
		si_gpu->ndrange->kernel->bin_file->enc_dict_entry_southern_islands->
		num_vgpr_used;
	for (work_items_per_work_group = si_emu_wavefront_size;
		work_items_per_work_group < (si_gpu_max_wavefronts_per_wavefront_pool * 
		si_emu_wavefront_size);
		work_items_per_work_group += si_emu_wavefront_size)
	{
		/* Calculate point */
		work_groups_per_wavefront_pool = si_calc_get_work_groups_per_wavefront_pool(
			work_items_per_work_group, registers_per_work_item, 
			local_mem_per_work_group);
		wavefronts_per_work_group = (work_items_per_work_group + 
			si_emu_wavefront_size - 1) / si_emu_wavefront_size;
		wavefronts_per_wavefront_pool = work_groups_per_wavefront_pool * 
			wavefronts_per_work_group;

		/* Dump line to data file */
		fprintf(data_file, "%d %d\n", work_items_per_work_group, 
				wavefronts_per_wavefront_pool);
	}
	fclose(data_file);

	/* Current data point */
	work_items_per_work_group = ROUND_UP(si_gpu->ndrange->kernel->local_size, 
		si_emu_wavefront_size);
	work_groups_per_wavefront_pool = si_calc_get_work_groups_per_wavefront_pool(
		work_items_per_work_group, registers_per_work_item, local_mem_per_work_group);
	wavefronts_per_work_group = (work_items_per_work_group + si_emu_wavefront_size - 1) / 
		si_emu_wavefront_size;
	wavefronts_per_wavefront_pool = work_groups_per_wavefront_pool * wavefronts_per_work_group;

	/* Generate gnuplot script */
	script_file = file_create_temp(script_file_name, MAX_PATH_SIZE);
	fprintf(script_file, "set term postscript eps color solid\n");
	fprintf(script_file, "set nokey\n");
	fprintf(script_file, "set xlabel 'Work-items per work-group'\n");
	fprintf(script_file, "set ylabel 'Wavefronts per SIMD'\n");
	fprintf(script_file, "set size 0.65, 0.5\n");
	fprintf(script_file, "set grid ytics\n");
	fprintf(script_file, "plot '%s' w linespoints lt 3 lw 5 pt 84 ps 2, ", data_file_name);
	fprintf(script_file, "'-' w linespoints lt 1 lw 4 pt 82 ps 2\n%d %d\ne\n",
		work_items_per_work_group, wavefronts_per_wavefront_pool);
	fclose(script_file);

	/* Plot */
	sprintf(cmd, "gnuplot %s > %s", script_file_name, plot_file_name);
	err = system(cmd);
	if (err)
		warning("could not execute gnuplot\n%s", err_gnuplot_msg);

	/* Remove temporary files */
	unlink(data_file_name);
	unlink(script_file_name);
}


static void si_calc_plot_registers_per_work_item(void)
{
	FILE *data_file, *script_file;

	char plot_file_name[MAX_PATH_SIZE];
	char data_file_name[MAX_PATH_SIZE];
	char script_file_name[MAX_PATH_SIZE];
	char cmd[MAX_PATH_SIZE];
	
	int local_mem_per_work_group;
	int work_items_per_work_group;
	int registers_per_work_item;

	int wavefronts_per_work_group;
	int work_groups_per_wavefront_pool;
	int wavefronts_per_wavefront_pool;

	int err;

	/* Create plot file */
	snprintf(plot_file_name, MAX_PATH_SIZE, "%s.%d.registers.eps",
		si_gpu_calc_file_name, si_gpu->ndrange->id);
	if (!file_can_open_for_write(plot_file_name))
		fatal("%s: cannot write GPU occupancy calculation plot", plot_file_name);

	/* Generate data file */
	data_file = file_create_temp(data_file_name, MAX_PATH_SIZE);
	local_mem_per_work_group = si_gpu->ndrange->local_mem_top;
	work_items_per_work_group = si_gpu->ndrange->kernel->local_size;
	wavefronts_per_work_group = (work_items_per_work_group + si_emu_wavefront_size - 1) / 
		si_emu_wavefront_size;
	for (registers_per_work_item = 1; registers_per_work_item <= 128; 
		registers_per_work_item += 4)
	{
		/* Calculate point */
		work_groups_per_wavefront_pool = si_calc_get_work_groups_per_wavefront_pool(
			work_items_per_work_group, registers_per_work_item, 
			local_mem_per_work_group);
		wavefronts_per_wavefront_pool = work_groups_per_wavefront_pool * 
			wavefronts_per_work_group;

		/* Dump line to data file */
		fprintf(data_file, "%d %d\n", registers_per_work_item, wavefronts_per_wavefront_pool);
	}
	fclose(data_file);

	/* Current data point */
	registers_per_work_item = 
		si_gpu->ndrange->kernel->bin_file->enc_dict_entry_southern_islands->
		num_vgpr_used;
	work_groups_per_wavefront_pool = si_calc_get_work_groups_per_wavefront_pool(
		work_items_per_work_group, registers_per_work_item, local_mem_per_work_group);
	wavefronts_per_wavefront_pool = work_groups_per_wavefront_pool * wavefronts_per_work_group;

	/* Generate gnuplot script */
	script_file = file_create_temp(script_file_name, MAX_PATH_SIZE);
	fprintf(script_file, "set term postscript eps color solid\n");
	fprintf(script_file, "set nokey\n");
	fprintf(script_file, "set xlabel 'Registers per work-item'\n");
	fprintf(script_file, "set ylabel 'Wavefronts per SIMD'\n");
	fprintf(script_file, "set xrange [0:128]\n");
	fprintf(script_file, "set yrange [0:]\n");
	fprintf(script_file, "set xtics (0,16,32,48,64,80,96,112,128)\n");
	fprintf(script_file, "set size 0.65, 0.5\n");
	fprintf(script_file, "set grid ytics\n");
	fprintf(script_file, "plot '%s' w linespoints lt 3 lw 5 pt 84 ps 2, ", data_file_name);
	fprintf(script_file, "'-' w linespoints lt 1 lw 4 pt 82 ps 2\n%d %d\ne\n",
		registers_per_work_item, wavefronts_per_wavefront_pool);
	fclose(script_file);

	/* Plot */
	sprintf(cmd, "gnuplot %s > %s", script_file_name, plot_file_name);
	err = system(cmd);
	if (err)
		warning("could not execute gnuplot\n%s", err_gnuplot_msg);

	/* Remove temporary files */
	unlink(data_file_name);
	unlink(script_file_name);
}


static void si_calc_plot_local_mem_per_work_group(void)
{
	FILE *data_file, *script_file;

	char plot_file_name[MAX_PATH_SIZE];
	char data_file_name[MAX_PATH_SIZE];
	char script_file_name[MAX_PATH_SIZE];
	char cmd[MAX_PATH_SIZE];
	
	int local_mem_per_work_group;
	int work_items_per_work_group;
	int registers_per_work_item;

	int wavefronts_per_work_group;
	int work_groups_per_wavefront_pool;
	int wavefronts_per_wavefront_pool;
	int local_mem_step;

	int err;

	/* Create plot file */
	snprintf(plot_file_name, MAX_PATH_SIZE, "%s.%d.local_mem.eps",
		si_gpu_calc_file_name, si_gpu->ndrange->id);
	if (!file_can_open_for_write(plot_file_name))
		fatal("%s: cannot write GPU occupancy calculation plot", 
			plot_file_name);

	/* Generate data file */
	data_file = file_create_temp(data_file_name, MAX_PATH_SIZE);
	registers_per_work_item = 
		si_gpu->ndrange->kernel->bin_file->enc_dict_entry_southern_islands->
		num_vgpr_used;
	local_mem_step = MAX(1, si_gpu_lds_size / 32);
	work_items_per_work_group = si_gpu->ndrange->kernel->local_size;
	wavefronts_per_work_group = (work_items_per_work_group + 
		si_emu_wavefront_size - 1) / si_emu_wavefront_size;
	for (local_mem_per_work_group = local_mem_step;
		local_mem_per_work_group <= si_gpu_lds_size;
		local_mem_per_work_group += local_mem_step)
	{
		/* Calculate point */
		work_groups_per_wavefront_pool = 
			si_calc_get_work_groups_per_wavefront_pool(
			work_items_per_work_group, registers_per_work_item, 
			local_mem_per_work_group);
		wavefronts_per_wavefront_pool = work_groups_per_wavefront_pool * 
			wavefronts_per_work_group;

		/* Dump line to data file */
		fprintf(data_file, "%d %d\n", local_mem_per_work_group, 
			wavefronts_per_wavefront_pool);
	}
	fclose(data_file);

	/* Current data point */
	local_mem_per_work_group = si_gpu->ndrange->local_mem_top;
	work_groups_per_wavefront_pool = si_calc_get_work_groups_per_wavefront_pool(
		work_items_per_work_group, registers_per_work_item, local_mem_per_work_group);
	wavefronts_per_wavefront_pool = work_groups_per_wavefront_pool * wavefronts_per_work_group;

	/* Generate gnuplot script */
	script_file = file_create_temp(script_file_name, MAX_PATH_SIZE);
	fprintf(script_file, "set term postscript eps color solid\n");
	fprintf(script_file, "set nokey\n");
	fprintf(script_file, "set xlabel 'Local memory used per work-group (KB)'\n");
	fprintf(script_file, "set ylabel 'Wavefronts per SIMD'\n");
	fprintf(script_file, "set xrange [0:%d]\n", si_gpu_lds_size / 1024);
	fprintf(script_file, "set yrange [0:]\n");
	fprintf(script_file, "set size 0.65, 0.5\n");
	fprintf(script_file, "set grid ytics\n");
	fprintf(script_file, "plot '%s' u ($1/1024):2 w linespoints lt 3 lw 5 pt 84 ps 2, ", 
		data_file_name);
	fprintf(script_file, "'-' u ($1/1024):2 w linespoints lt 1 lw 4 pt 82 ps 2\n%d %d\ne\n",
		local_mem_per_work_group, wavefronts_per_wavefront_pool);
	fclose(script_file);

	/* Plot */
	sprintf(cmd, "gnuplot %s > %s", script_file_name, plot_file_name);
	err = system(cmd);
	if (err)
		warning("could not execute gnuplot\n%s", err_gnuplot_msg);

	/* Remove temporary files */
	unlink(data_file_name);
	unlink(script_file_name);
}


void si_calc_plot(void)
{
	int ret;

	/* If no file specified for plots, done */
	if (!*si_gpu_calc_file_name)
		return;

	/* Find 'gnuplot' */
	ret = system("which gnuplot >/dev/null 2>&1");
	if (ret)
		fatal("GPU occupancy calculation plots could not be generated.\n"
			"\tThe tool 'gnuplot' is required to generate GPU occupancy plots. Please\n"
			"\tmake sure that it is installed on your system and retry.\n");

	/* Plot varying work-items per work-group */
	si_calc_plot_work_items_per_work_group();

	/* Plot varying registers per work-item */
	si_calc_plot_registers_per_work_item();

	/* Plot varying local memory per work-group */
	si_calc_plot_local_mem_per_work_group();
}

