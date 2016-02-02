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


#include <lib/mhandle/mhandle.h>
#include <lib/util/debug.h>
#include <mem-system/memory.h>

#include "isa.h"
#include "ndrange.h"
#include "wavefront.h"
#include "work-group.h"
#include "work-item.h"

/* MIAOW Start */
//#define MIAOW_DEBUG
#include <math.h>
/* MIAOW Stop */
	

/*
 * Public Functions
 */

/*MIAOW Start */
extern int kernel_config_count;
extern FILE* config;
/*MIAOW Stop */


struct si_work_group_t *si_work_group_create(unsigned int work_group_id, 
	struct si_ndrange_t *ndrange)
{
	struct si_bin_enc_user_element_t *user_elements;
	struct si_wavefront_t *wavefront;
	struct si_work_group_t *work_group;
	struct si_work_item_t *work_item;

	/*MIAOW Start */
	struct opencl_si_kernel_t *kernel = ndrange->kernel;
	unsigned long long mask = 0x00000000;
	/*MIAOW Stop */

	int i;
	int lid;
	int lidx, lidy, lidz;
	int tid;
	int user_element_count;
	int wavefront_id;
	int wavefront_offset;
	int work_item_id;
	int work_item_gidx_start;
	int work_item_gidy_start;
	int work_item_gidz_start;


	/*MIAOW start*/
	//UNIT TEST
	
	char unit_test_input_buf[150000];
	char *tok = NULL;
	char *config_read_result = NULL;
	char vreg_str[64][2500];
	char sreg_str[2500];
	int num_of_threads = 0;

	FILE* unit_test_config = fopen("unit_test_config.txt", "r");
	if (unit_test_config != 0)
	{

		ndrange->local_size3[2] = 1;
		ndrange->local_size3[1] = 1;
		ndrange->global_size3[2] = 1;
		ndrange->global_size3[1] = 1;
		
		config_read_result = fgets(unit_test_input_buf, 150000, unit_test_config);
		if(config_read_result != NULL)
		{
			tok = strtok(unit_test_input_buf, ";"); //WG count
			ndrange->group_count = atoi(tok);

			tok = strtok(NULL, ";"); //total number of threads
			num_of_threads = atoi(tok);

			ndrange->global_size = atoi(tok);
			ndrange->global_size3[0] = atoi(tok);
			ndrange->local_size3[0] = atoi(tok);
			ndrange->local_size = atoi(tok);

		}
	}

	//WorkGroup count and thread count
	//fprintf(config,"%d;%d;\n", ndrange->group_count, ndrange->global_size);

#ifdef MIAOW_DEBUG
	fflush(config);
#endif
	/*MIAOW stop*/

	/* Number of in work-items in work-group */
	unsigned int work_items_per_group = ndrange->local_size3[0] * 
		ndrange->local_size3[1] * ndrange->local_size3[2];
	assert(work_items_per_group > 0);

	/* Number of wavefronts in work-group */
	unsigned int wavefronts_per_group = (work_items_per_group + 
		(si_emu_wavefront_size - 1)) / si_emu_wavefront_size;
	assert(wavefronts_per_group > 0);

	/* Initialize */
	work_group = xcalloc(1, sizeof(struct si_work_group_t));
	work_group->id = work_group_id;
	work_group->ndrange = ndrange;

	/* Create LDS */
	work_group->lds_module = mem_create();
	work_group->lds_module->safe = 0;

	/* Allocate pointers for work-items (will actually be created when
	 * wavefronts are created) */
	work_group->work_items = xcalloc(si_emu_wavefront_size * 
		wavefronts_per_group, sizeof(void *));
	work_group->wavefronts = xcalloc(wavefronts_per_group, sizeof(void *));
	work_group->wavefront_count = wavefronts_per_group;

	/* Allocate wavefronts and work-items */
	SI_FOREACH_WAVEFRONT_IN_WORK_GROUP(work_group, wavefront_id)
	{
		work_group->wavefronts[wavefront_id] = si_wavefront_create(
			work_group->id * wavefronts_per_group + wavefront_id,
			work_group);

		wavefront = work_group->wavefronts[wavefront_id];

		SI_FOREACH_WORK_ITEM_IN_WAVEFRONT(wavefront, work_item_id)
		{
			wavefront_offset = wavefront_id * si_emu_wavefront_size;

			work_group->work_items[wavefront_offset+work_item_id] = 
				wavefront->work_items[work_item_id];
			work_group->work_items[wavefront_offset+work_item_id]->
				work_group = work_group;
		}
	}

	/* Initialize work-group and work-item metadata */
	work_group->id_3d[0] = work_group_id % ndrange->group_count3[0];
	work_group->id_3d[1] = (work_group_id / ndrange->group_count3[0]) % 
		ndrange->group_count3[1];
	work_group->id_3d[2] = work_group_id / (ndrange->group_count3[0] * 
		ndrange->group_count3[1]);
	work_group->id = work_group_id;

#ifdef MIAOW_DEBUG
	fprintf(config, "Processing Workitems\n");
	fflush(config);
#endif

	/* Number of work-items in work-group */
	work_group->work_item_count = ndrange->local_size3[2] *
		ndrange->local_size3[1] * ndrange->local_size3[0];

	/* Global ID of work-item (0,0,0) within the work group */
	work_item_gidx_start = work_group->id_3d[0] * ndrange->local_size3[0];
	work_item_gidy_start = work_group->id_3d[1] * ndrange->local_size3[1];
	work_item_gidz_start = work_group->id_3d[2] * ndrange->local_size3[2];

	/* Initialize work-item metadata */
	lid = 0;
	tid = work_group->id * work_items_per_group;
	for (lidz = 0; lidz < ndrange->local_size3[2]; lidz++)
	{
		for (lidy = 0; lidy < ndrange->local_size3[1]; lidy++)
		{
			for (lidx = 0; lidx < ndrange->local_size3[0]; lidx++)
			{
				work_item = work_group->work_items[lid];

				/* Global IDs */
				work_item->id_3d[0] = work_item_gidx_start + 
					lidx;
				work_item->id_3d[1] = work_item_gidy_start + 
					lidy;
				work_item->id_3d[2] = work_item_gidz_start + 
					lidz;
				work_item->id = tid;

				/* Local IDs */
				work_item->id_in_work_group_3d[0] = lidx;
				work_item->id_in_work_group_3d[1] = lidy;
				work_item->id_in_work_group_3d[2] = lidz;
				work_item->id_in_work_group = lid;

				/*MIAOW Start */
				work_item->id = work_item->id_in_wavefront; 
				/*MIAOW Stop */

				/* First, last, and number of work-items 
				 * in wavefront */
				wavefront = work_item->wavefront;
				if (!wavefront->work_item_count)
				{
					wavefront->work_item_id_first = tid;
				}
				wavefront->work_item_id_last = tid;
				wavefront->work_item_count++;

				/* Next work-item */
				tid++;
				lid++;


				// Not sure if this m2s execution mask is correct
				/* Initialize the execution mask */
				/*MIAOW Start */
				//unsigned long long mask = 0x00000000;
				/*MIAOW Stop */
				/*
				if (work_item->id_in_wavefront < 32)
				{
					mask |= 1 << work_item->id_in_wavefront; 
					wavefront->sreg[SI_EXEC].as_uint |= 	1 << work_item->id_in_wavefront;
				}
				else if (work_item->id_in_wavefront < 64)
				{

					mask |= 1 << work_item->id_in_wavefront; 
					wavefront->sreg[SI_EXEC + 1].as_uint |= 
						1 << work_item->id_in_wavefront;
				}
				else 
				{
					fatal("%s: invalid work-item id (%d)",
						__FUNCTION__, 
						work_item->id_in_wavefront);
				}
				*/

			}
		}
	}

	/* Intialize wavefront state */
	SI_FOREACH_WAVEFRONT_IN_WORK_GROUP(work_group, wavefront_id)
	{
		wavefront = work_group->wavefronts[wavefront_id];
		

		/* Set PC */
		wavefront->pc = 0;

		//Initializing all sreg values to zero, so that config.txt doesnt change with each run
  	/*MIAOW start*/
		for (int sreg_init_index = 0; sreg_init_index < 256; sreg_init_index++)
		{
//			work_item->sreg[vreg_init_index].as_int = 0;
		}

		/* Save work-group IDs in scalar registers */
		wavefront->sreg[ndrange->wg_id_sgpr].as_int =
			wavefront->work_group->id_3d[0];
		wavefront->sreg[ndrange->wg_id_sgpr + 1].as_int =
			wavefront->work_group->id_3d[1];
		wavefront->sreg[ndrange->wg_id_sgpr + 2].as_int =
			wavefront->work_group->id_3d[2];

		//Initializing all vreg values to zero, so that config.txt doesnt change with each run
  	/*MIAOW start*/
		for (int vreg_init_index = 0; vreg_init_index < 256; vreg_init_index++)
		{
	//		work_item->vreg[vreg_init_index].as_int = 0;
		}
  	/*MIAOW stop*/

		SI_FOREACH_WORK_ITEM_IN_WAVEFRONT(wavefront, work_item_id)
		{
			/* Store work-item IDs in vector registers */
			work_item = wavefront->work_items[work_item_id];

			/* V0 */
			work_item->vreg[0].as_int = 
				work_item->id_in_work_group_3d[0];  
			/* V1 */
			work_item->vreg[1].as_int = 
				work_item->id_in_work_group_3d[1]; 
			/* V2 */
			work_item->vreg[2].as_int = 
				work_item->id_in_work_group_3d[2];

		}

		/* Initialize sreg pointers to internal data structures */
		user_element_count = ndrange->userElementCount;
		user_elements = ndrange->userElements;
		for (i = 0; i < user_element_count; i++)
		{
			if (user_elements[i].dataClass == IMM_CONST_BUFFER)
			{
				/* Store CB pointer in sregs */
				si_wavefront_init_sreg_with_cb(wavefront,
					user_elements[i].startUserReg,
					user_elements[i].userRegCount,
					user_elements[i].apiSlot);
			}
			else if (user_elements[i].dataClass == IMM_UAV)
			{
				/* Store UAV pointer in sregs */
				si_wavefront_init_sreg_with_uav(wavefront,
					user_elements[i].startUserReg,
					user_elements[i].userRegCount,
					user_elements[i].apiSlot);
			}
			else if (user_elements[i].dataClass ==
				PTR_CONST_BUFFER_TABLE)
			{
				/* Store CB table in sregs */
				si_wavefront_init_sreg_with_cb_table(wavefront,
					user_elements[i].startUserReg,
					user_elements[i].userRegCount);
			}
			else if (user_elements[i].dataClass == PTR_UAV_TABLE)
			{
				/* Store UAV table in sregs */
				si_wavefront_init_sreg_with_uav_table(
					wavefront,
					user_elements[i].startUserReg,
					user_elements[i].userRegCount);
			}
			else if (user_elements[i].dataClass == PTR_VERTEX_BUFFER_TABLE)
			{
				/* Store VB table in sregs */
				si_wavefront_init_sreg_with_vertex_buffer_table(
					wavefront,
					user_elements[i].startUserReg,
					user_elements[i].userRegCount);
			}
			else if (user_elements[i].dataClass == SUB_PTR_FETCH_SHADER)
			{
				/* Store Fetch Shader pointer in sregs */
				si_wavefront_init_sreg_with_fetch_shader(
					wavefront,
					user_elements[i].startUserReg,
					user_elements[i].userRegCount);
			}
			else if (user_elements[i].dataClass == IMM_SAMPLER)
			{
				/* Store sampler in sregs */
				assert(0);
			}
			else if (user_elements[i].dataClass ==
				PTR_RESOURCE_TABLE)
			{
				/* Store resource table in sregs */
				assert(0);
			}
			else if (user_elements[i].dataClass ==
				PTR_INTERNAL_GLOBAL_TABLE)
			{
				fatal("%s: PTR_INTERNAL_GLOBAL_TABLE not "
					"supported", __FUNCTION__);
			}
			else
			{
				fatal("%s: Unimplemented User Element: "
					"dataClass:%d", __FUNCTION__,
					user_elements[i].dataClass);
			}
		}

	
		//Simpler way of execution mask generation instead of iterating over each work-item
		/*MIAOW Start */
		unsigned long long mask;
		if(wavefront->work_item_count == 64)
		{
			mask = 0xFFFFFFFFFFFFFFFF;
		}
		else
		{
			mask = powl(2, wavefront->work_item_count) - 1;
		}

		wavefront->sreg[SI_EXEC].as_uint = (unsigned int)mask;
		wavefront->sreg[SI_EXEC + 1].as_uint = mask>>32;
		wavefront->sreg[SI_EXECZ].as_int = 0;
		/*MIAOW Stop */
		
		/*MIAOW start*/
		
		if(config_read_result != NULL)
		{
			if(NULL != fgets(unit_test_input_buf, 150000, unit_test_config))
			{
				int num_of_threads = 0;
				int thread_init_count = 0;

				tok = strtok(unit_test_input_buf, ";"); //WGID
				tok = strtok(NULL, ";"); //WFID
				tok = strtok(NULL, ";"); //WF count
				tok = strtok(NULL, ";"); //work-item count

				num_of_threads = atoi(tok);

#ifdef MIAOW_DEBUG
	if (num_of_threads != wavefront->work_item_count)
	{
	fprintf(config, "num_thread MISMATCH %d!=%d\n", num_of_threads, wavefront->work_item_count);
	}
	else
	{
	fprintf(config, "num_thread match %d=%d\n", num_of_threads, wavefront->work_item_count);
	}
	fflush(config);
#endif

				tok = strtok(NULL, ";"); //VREG size
				kernel->bin_file->enc_dict_entry_southern_islands->num_vgpr_used = atoi(tok);

				tok = strtok(NULL, ";"); //SREG size
				kernel->bin_file->enc_dict_entry_southern_islands->num_sgpr_used = atoi(tok);

				tok = strtok(NULL, ";"); //LDS size
				kernel->bin_file->enc_dict_entry_southern_islands->lds_size_used = atoi(tok);

				for(thread_init_count = 0; thread_init_count < num_of_threads; thread_init_count++)
				{
					tok = strtok(NULL, ";");
					strcpy((char*)vreg_str[thread_init_count], tok);
					assert(vreg_str[thread_init_count][0] == 'V');
				}

				tok = strtok(NULL, ";");
				strcpy((char*)sreg_str, tok);
				assert(sreg_str[0] == 'S');

				tok = strtok(NULL, ";"); //PC
			}

#ifdef MIAOW_DEBUG
	fprintf(config, "Initializing VREG \n");
	fflush(config);
#endif

			//VREG value init
			int wi_init_count = 0;
			for (wi_init_count = 0; wi_init_count < wavefront->work_item_count; wi_init_count++)
			{
				if (wavefront->work_items != NULL)
				{
					int vreg_init_count = 0;
					char* reg_tok;
					struct si_work_item_t *wi = wavefront->work_items[wi_init_count];

					reg_tok = strtok(vreg_str[wi_init_count], ":");
					reg_tok = strtok(NULL, "=");

					for(vreg_init_count = 0; reg_tok != NULL; vreg_init_count++)
					{
						int vreg_index = atoi(reg_tok);
						reg_tok = strtok(NULL, ",");
						assert(reg_tok != NULL);
						wi->vreg[vreg_index].as_int = atoi(reg_tok);
						reg_tok = strtok(NULL, "=");
					}

					// make sure that all reg values were read
					assert(reg_tok == NULL);
				}
			}

#ifdef MIAOW_DEBUG
	fprintf(config, "Initializing SREG \n");
	fflush(config);
#endif

#ifdef MIAOW_DEBUG
	fprintf(config, "mask: %lld \n", mask);
	fprintf(config, "MASK HI: %u \n", wavefront->sreg[SI_EXEC + 1].as_uint);
	fprintf(config, "MASK LO: %u \n", wavefront->sreg[SI_EXEC].as_uint);
	fflush(config);
#endif

	//SREG value init
			int sreg_init_count = 0;
			char* sreg_tok;
			sreg_tok = strtok(sreg_str, ":");
			sreg_tok = strtok(NULL, "=");
			
			for(sreg_init_count=0; sreg_tok != NULL; sreg_init_count++)
			{
				int sreg_index = atoi(sreg_tok);
				sreg_tok = strtok(NULL, ",");
				assert(sreg_tok != NULL);
				wavefront->sreg[sreg_index].as_int = atoi(sreg_tok);
				sreg_tok = strtok(NULL, "=");
			}
			// make sure that all reg values were read
			assert(sreg_tok == NULL);
		}
	
		/*MIAOW stop*/ // All the unit_test configuration data is read here

	/*MIAOW Start*/
	//Print the configuration here

	//WorGroup ID
	fprintf(config, "%d;", wavefront->work_group->id);

	//Wavefront ID
	fprintf(config, "%d;", wavefront->id);

	//WorGroup Count
	fprintf(config, "%d;", wavefront->work_group->wavefront_count);

	//Work-Item Count
	fprintf(config, "%d;", wavefront->work_item_count);

	//VGPR Size, SGPR size, LDS size
	if (kernel->bin_file->enc_dict_entry_southern_islands->num_vgpr_used)
		fprintf(config, "%d;", kernel->bin_file->enc_dict_entry_southern_islands->num_vgpr_used);
	else
		fprintf(config, "%d;", 1);
	
	fprintf(config, "%d;", kernel->bin_file->enc_dict_entry_southern_islands->num_sgpr_used);
	
	fprintf(config, "%d;", kernel->bin_file->enc_dict_entry_southern_islands->lds_size_used);
	
#ifdef MIAOW_DEBUG
	fflush(config);
#endif

		int wi_count = 0;
		for (wi_count = 0; wi_count < wavefront->work_item_count; wi_count++)
		{
			//VGPR initial values
			if (wavefront->work_items != NULL)
			{
				struct si_work_item_t* wi = wavefront->work_items[wi_count];

				fprintf(config,"V:");
				int vgpr_count = 0;
				
				if (kernel->bin_file->enc_dict_entry_southern_islands->num_vgpr_used)
				{

					//fprintf(config,"wi-count: %d ", wi_count);
					for (vgpr_count = 0; vgpr_count < (kernel->bin_file->enc_dict_entry_southern_islands->num_vgpr_used - 1); vgpr_count++)
					{
						//All VGPR values except the last
						fprintf(config,"%d=%d,", vgpr_count, wi->vreg[vgpr_count]);
					}
					//Last VGPR value
					fprintf(config,"%d=%d;", vgpr_count, wi->vreg[vgpr_count]);
				}
				else
				{
					fprintf(config,"%d=%d;", vgpr_count, wi->vreg[vgpr_count]); //hack for num_vgprs=0
				}
			}
		}

		/*
	 struct si_wavefront_t* wf = work_group->wavefronts[wavefront_id];                              
   struct si_work_item_t* wi = wf->work_items[63];                                     
   fprintf(config, "|_____Debug_check-V0: %d_____|", wi->vreg[0].as_int);
	*/

	 //SGPR initial values
		fprintf(config,"S:");
		int sgpr_count = 0;
	
		for (sgpr_count = 0; sgpr_count < (kernel->bin_file->enc_dict_entry_southern_islands->num_sgpr_used - 1); sgpr_count++)
		{
			//All SGPR values except the last
			fprintf(config,"%d=%d,", sgpr_count, wavefront->sreg[sgpr_count]);
		}
		
		//Last SGPR value
		fprintf(config,"%d=%d;", sgpr_count, wavefront->sreg[sgpr_count]);

		//PC start
		//fprintf(config,"%d",wavefront->wavefront_pool_start);
		fprintf(config, "0");
		fprintf(config,"\n");
		/*MIAOW stop*/
	
	}
	

	/*MIAOW stop */

	/* Statistics */
	si_emu->work_group_count++;

	/*
	int ia;
	for(ia =0; ia < 4; ia++)
	{
	 struct si_wavefront_t* wfa = work_group->wavefronts[ia];                              
   struct si_work_item_t* wia = wfa->work_items[63];                                     
   fprintf(config, "|_____After config debug check-V0: %d_____|\n", wia->vreg[0].as_int);
	}
	*/

	/* Return */
	return work_group;
}

void si_work_group_free(struct si_work_group_t *work_group)
{
	struct si_wavefront_t *wavefront;

	int wavefront_id;
	int work_item_id; 

	assert(work_group);

	/* Free wavefronts and work-items */
	SI_FOREACH_WAVEFRONT_IN_WORK_GROUP(work_group, wavefront_id)
	{
		wavefront = work_group->wavefronts[wavefront_id];

		SI_FOREACH_WORK_ITEM_IN_WAVEFRONT(wavefront, work_item_id)
		{
			si_work_item_free(wavefront->work_items[work_item_id]);
		}

		si_work_item_free(wavefront->scalar_work_item);
		si_wavefront_free(wavefront);
	}
	free(work_group->wavefronts);
	free(work_group->work_items);

	/* Free LDS memory module */
	mem_free(work_group->lds_module);

	/* Free work-group */
	memset(work_group, 0, sizeof(struct si_work_group_t));
	free(work_group);
	work_group = NULL;
}
