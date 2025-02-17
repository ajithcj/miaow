#include <lib/esim/esim.h>
#include <lib/util/config.h>
#include <lib/util/debug.h>
#include <lib/util/file.h>
#include <lib/util/string.h>

#include "uop.h"
#include "cycle-interval-report.h"

#include "compute-unit.h"

int si_spatial_report_active = 0 ;

static int spatial_profiling_interval = 10000;
static char *si_spatial_report_section_name = "SISpatialReport";
static FILE *spatial_report_file;
static char *spatial_report_filename = "report-cu-spatial";


void si_spatial_report_config_read(struct config_t *config)
{
	char *section;
	char *file_name;

	/*Nothing if section or config is not present */
	section = si_spatial_report_section_name;
	if (!config_section_exists(config, section))
	{
		/*no spatial profiling */
		return;
	}

	/* Spatial reports are active */
	si_spatial_report_active = 1;

	/* Interval */
	config_var_enforce(config, section, "Interval");
	spatial_profiling_interval = config_read_int(config, section,
		"Interval", spatial_profiling_interval);

	/* File name */
	config_var_enforce(config, section, "File");
	file_name = config_read_string(config, section, "File", NULL);
	if (!file_name || !*file_name)
		fatal("%s: %s: invalid or missing value for 'File'",
			si_spatial_report_section_name, section);
	spatial_report_filename = str_set(NULL, file_name);

	spatial_report_file = file_open_for_write(spatial_report_filename);
	if (!spatial_report_file)
		fatal("%s: could not open spatial report file",
				spatial_report_filename);

}

void si_cu_spatial_report_init()
{

}

void si_cu_spatial_report_done()
{

	fclose(spatial_report_file);
	spatial_report_file = NULL;
	str_free(spatial_report_filename);
}

void si_cu_spatial_report_dump(struct si_compute_unit_t *compute_unit)
{

	FILE *f = spatial_report_file ;
	fprintf(f,"CU,%d,MemAcc,%lld,MappedWGs,%lld,Cycles,%lld\n",
			compute_unit->id,
			compute_unit->vector_mem_unit.inflight_mem_accesses,
			compute_unit->interval_mapped_work_groups,
			esim_cycle);

}


void si_report_global_mem_inflight( struct si_compute_unit_t *compute_unit, int long long pending_accesses)
{
	/* Read stage adds a negative number for accesses added
	 * Write stage adds a positive number for accesses finished
	 */
	compute_unit->vector_mem_unit.inflight_mem_accesses += pending_accesses;

}

void si_report_global_mem_finish( struct si_compute_unit_t *compute_unit, int long long completed_accesses)
{
	/* Read stage adds a negative number for accesses added */
	/* Write stage adds a positive number for accesses finished */
	compute_unit->vector_mem_unit.inflight_mem_accesses -= completed_accesses;

}

void si_report_mapped_work_group(struct si_compute_unit_t *compute_unit)
{
	/*TODO Add calculation here to change this to wavefront pool entries used */
	compute_unit->interval_mapped_work_groups++;
}

void si_cu_interval_update(struct si_compute_unit_t *compute_unit)
{
	/* If interval - reset the counters in all the engines */
	compute_unit->interval_cycle ++;

	if ( !(esim_cycle % spatial_profiling_interval))
	{
		si_cu_spatial_report_dump(compute_unit);

		/*
		 * This counter is not reset since memory accesses could still
		 * be in flight in the hierarchy
		 * compute_unit->inflight_mem_accesses = 0;
		 */
		compute_unit->interval_cycle = 0;
		compute_unit->interval_mapped_work_groups = 0;
	}
}
