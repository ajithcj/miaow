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

#include <ctype.h>
#include <string.h>

#include <lib/util/debug.h>
#include <lib/util/elf-format.h>
#include <lib/util/list.h>
#include <lib/util/misc.h>
#include <lib/util/string.h>

#include "asm.h"


void arm_disasm_init()
{
	struct arm_inst_info_t *info;
	int i;
	int j;
	/* Form the Instruction table and read Information from table*/
#define DEFINST(_name, _fmt_str, _category, _arg1, _arg2) \
	switch (ARM_CAT_##_category) { \
	case ARM_CAT_DPR_REG: \
	arm_inst_info[_arg1 * 16 + 0].opcode = ARM_INST_##_name; \
	info = &arm_inst_info[_arg1 * 16 + 0 ]; \
	info->inst = ARM_INST_##_name; \
	info->category = ARM_CAT_##_category; \
	info->name = #_name; \
	info->fmt_str = _fmt_str; \
	info->size = 4;\
	info->opcode = ARM_INST_##_name; \
	arm_inst_info[_arg1 * 16 + 1].opcode = ARM_INST_##_name; \
	info = &arm_inst_info[_arg1 * 16 + 1 ]; \
	info->inst = ARM_INST_##_name; \
	info->category = ARM_CAT_##_category; \
	info->name = #_name; \
	info->fmt_str = _fmt_str; \
	info->size = 4;\
	info->opcode = ARM_INST_##_name; \
	arm_inst_info[_arg1 * 16 + 2].opcode = ARM_INST_##_name; \
	info = &arm_inst_info[_arg1 * 16 + 2 ]; \
	info->inst = ARM_INST_##_name; \
	info->category = ARM_CAT_##_category; \
	info->name = #_name; \
	info->fmt_str = _fmt_str; \
	info->size = 4;\
	info->opcode = ARM_INST_##_name; \
	arm_inst_info[_arg1 * 16 + 3].opcode = ARM_INST_##_name; \
	info = &arm_inst_info[_arg1 * 16 + 3 ]; \
	info->inst = ARM_INST_##_name; \
	info->category = ARM_CAT_##_category; \
	info->name = #_name; \
	info->fmt_str = _fmt_str; \
	info->size = 4;\
	info->opcode = ARM_INST_##_name; \
	arm_inst_info[_arg1 * 16 + 4].opcode = ARM_INST_##_name; \
	info = &arm_inst_info[_arg1 * 16 + 4 ]; \
	info->inst = ARM_INST_##_name; \
	info->category = ARM_CAT_##_category; \
	info->name = #_name; \
	info->fmt_str = _fmt_str; \
	info->size = 4;\
	info->opcode = ARM_INST_##_name; \
	arm_inst_info[_arg1 * 16 + 5].opcode = ARM_INST_##_name; \
	info = &arm_inst_info[_arg1 * 16 + 5 ]; \
	info->inst = ARM_INST_##_name; \
	info->category = ARM_CAT_##_category; \
	info->name = #_name; \
	info->fmt_str = _fmt_str; \
	info->size = 4;\
	info->opcode = ARM_INST_##_name; \
	arm_inst_info[_arg1 * 16 + 6].opcode = ARM_INST_##_name; \
	info = &arm_inst_info[_arg1 * 16 + 6 ]; \
	info->inst = ARM_INST_##_name; \
	info->category = ARM_CAT_##_category; \
	info->name = #_name; \
	info->fmt_str = _fmt_str; \
	info->size = 4;\
	info->opcode = ARM_INST_##_name; \
	arm_inst_info[_arg1 * 16 + 7].opcode = ARM_INST_##_name; \
	info = &arm_inst_info[_arg1 * 16 + 7 ]; \
	info->inst = ARM_INST_##_name; \
	info->category = ARM_CAT_##_category; \
	info->name = #_name; \
	info->fmt_str = _fmt_str; \
	info->size = 4;\
	info->opcode = ARM_INST_##_name; \
	arm_inst_info[_arg1 * 16 + 8].opcode = ARM_INST_##_name; \
	info = &arm_inst_info[_arg1 * 16 + 8 ]; \
	info->inst = ARM_INST_##_name; \
	info->category = ARM_CAT_##_category; \
	info->name = #_name; \
	info->fmt_str = _fmt_str; \
	info->size = 4;\
	info->opcode = ARM_INST_##_name; \
	arm_inst_info[_arg1 * 16 + 10].opcode = ARM_INST_##_name; \
	info = &arm_inst_info[_arg1 * 16 + 10 ]; \
	info->inst = ARM_INST_##_name; \
	info->category = ARM_CAT_##_category; \
	info->name = #_name; \
	info->fmt_str = _fmt_str; \
	info->size = 4;\
	info->opcode = ARM_INST_##_name; \
	arm_inst_info[_arg1 * 16 + 12].opcode = ARM_INST_##_name; \
	info = &arm_inst_info[_arg1 * 16 + 12 ]; \
	info->inst = ARM_INST_##_name; \
	info->category = ARM_CAT_##_category; \
	info->name = #_name; \
	info->fmt_str = _fmt_str; \
	info->size = 4;\
	info->opcode = ARM_INST_##_name; \
	arm_inst_info[_arg1 * 16 + 14].opcode = ARM_INST_##_name; \
	info = &arm_inst_info[_arg1 * 16 + 14 ]; \
	info->inst = ARM_INST_##_name; \
	info->category = ARM_CAT_##_category; \
	info->name = #_name; \
	info->fmt_str = _fmt_str; \
	info->size = 4;\
	info->opcode = ARM_INST_##_name; \
	break; \
	case ARM_CAT_DPR_IMM: \
	for (i = 0; i < 16; i++ ){\
	arm_inst_info[_arg1 * 16 + i].opcode = ARM_INST_##_name;\
	info = &arm_inst_info[_arg1 * 16 + i ]; \
	info->inst = ARM_INST_##_name; \
	info->category = ARM_CAT_##_category; \
	info->name = #_name; \
	info->fmt_str = _fmt_str; \
	info->size = 4;\
	info->opcode = ARM_INST_##_name; \
	}\
	break;\
	case ARM_CAT_DPR_SAT:\
	arm_inst_info[_arg1 * 16 + 5].opcode = ARM_INST_##_name;\
	info = &arm_inst_info[_arg1 * 16 + 5 ]; \
	info->inst = ARM_INST_##_name; \
	info->category = ARM_CAT_##_category; \
	info->name = #_name; \
	info->fmt_str = _fmt_str; \
	info->size = 4;\
	info->opcode = ARM_INST_##_name; \
	break;\
	case ARM_CAT_PSR:\
	arm_inst_info[_arg1 * 16 + 0].opcode = ARM_INST_##_name;\
	info = &arm_inst_info[_arg1 * 16 + 0 ]; \
	info->inst = ARM_INST_##_name; \
	info->category = ARM_CAT_##_category; \
	info->name = #_name; \
	info->fmt_str = _fmt_str; \
	info->size = 4;\
	info->opcode = ARM_INST_##_name; \
	break;\
	case ARM_CAT_MULT:\
	arm_inst_info[_arg1 * 16 + 9].opcode = ARM_INST_##_name;\
	info = &arm_inst_info[_arg1 * 16 + 9 ]; \
	info->inst = ARM_INST_##_name; \
	info->category = ARM_CAT_##_category; \
	info->name = #_name; \
	info->fmt_str = _fmt_str; \
	info->size = 4;\
	info->opcode = ARM_INST_##_name; \
	break;\
	case ARM_CAT_MULT_SIGN:\
	arm_inst_info[_arg1 * 16 + 8].opcode = ARM_INST_##_name;\
	info = &arm_inst_info[_arg1 * 16 + 8 ]; \
	info->inst = ARM_INST_##_name; \
	info->category = ARM_CAT_##_category; \
	info->name = #_name; \
	info->fmt_str = _fmt_str; \
	info->size = 4;\
	info->opcode = ARM_INST_##_name; \
	arm_inst_info[_arg1 * 16 + 10].opcode = ARM_INST_##_name;\
	info = &arm_inst_info[_arg1 * 16 + 10 ]; \
	info->inst = ARM_INST_##_name; \
	info->category = ARM_CAT_##_category; \
	info->name = #_name; \
	info->fmt_str = _fmt_str; \
	info->size = 4;\
	info->opcode = ARM_INST_##_name; \
	arm_inst_info[_arg1 * 16 + 12].opcode = ARM_INST_##_name;\
	info = &arm_inst_info[_arg1 * 16 + 12 ]; \
	info->inst = ARM_INST_##_name; \
	info->category = ARM_CAT_##_category; \
	info->name = #_name; \
	info->fmt_str = _fmt_str; \
	info->size = 4;\
	info->opcode = ARM_INST_##_name; \
	arm_inst_info[_arg1 * 16 + 14].opcode = ARM_INST_##_name;\
	info = &arm_inst_info[_arg1 * 16 + 14 ]; \
	info->inst = ARM_INST_##_name; \
	info->category = ARM_CAT_##_category; \
	info->name = #_name; \
	info->fmt_str = _fmt_str; \
	info->size = 4;\
	info->opcode = ARM_INST_##_name; \
	break;\
	case ARM_CAT_MULT_LN:\
	arm_inst_info[_arg1 * 16 + 9].opcode = ARM_INST_##_name;\
	info = &arm_inst_info[_arg1 * 16 + 9 ]; \
	info->inst = ARM_INST_##_name; \
	info->category = ARM_CAT_##_category; \
	info->name = #_name; \
	info->fmt_str = _fmt_str; \
	info->size = 4;\
	info->opcode = ARM_INST_##_name; \
	break;\
	case ARM_CAT_MULT_LN_SIGN:\
	arm_inst_info[_arg1 * 16 + 8].opcode = ARM_INST_##_name;\
	info = &arm_inst_info[_arg1 * 16 + 8 ]; \
	info->inst = ARM_INST_##_name; \
	info->category = ARM_CAT_##_category; \
	info->name = #_name; \
	info->fmt_str = _fmt_str; \
	info->size = 4;\
	info->opcode = ARM_INST_##_name; \
	break;\
	case ARM_CAT_SDSWP:\
	arm_inst_info[_arg1 * 16 + 9].opcode = ARM_INST_##_name;\
	info = &arm_inst_info[_arg1 * 16 + 9 ]; \
	info->inst = ARM_INST_##_name; \
	info->category = ARM_CAT_##_category; \
	info->name = #_name; \
	info->fmt_str = _fmt_str; \
	info->size = 4;\
	info->opcode = ARM_INST_##_name; \
	break;\
	case ARM_CAT_BAX:\
	arm_inst_info[_arg1 * 16 + _arg2].opcode = ARM_INST_##_name;\
	info = &arm_inst_info[_arg1 * 16 + _arg2 ]; \
	info->inst = ARM_INST_##_name; \
	info->category = ARM_CAT_##_category; \
	info->name = #_name; \
	info->fmt_str = _fmt_str; \
	info->size = 4;\
	info->opcode = ARM_INST_##_name; \
	break;\
	case ARM_CAT_HFWRD_REG:\
	arm_inst_info[_arg1 * 16 + _arg2].opcode = ARM_INST_##_name;\
	info = &arm_inst_info[_arg1 * 16 + _arg2 ]; \
	info->inst = ARM_INST_##_name; \
	info->category = ARM_CAT_##_category; \
	info->name = #_name; \
	info->fmt_str = _fmt_str; \
	info->size = 4;\
	info->opcode = ARM_INST_##_name; \
	break;\
	case ARM_CAT_HFWRD_IMM:\
	arm_inst_info[_arg1 * 16 + _arg2].opcode = ARM_INST_##_name;\
	info = &arm_inst_info[_arg1 * 16 + _arg2 ]; \
	info->inst = ARM_INST_##_name; \
	info->category = ARM_CAT_##_category; \
	info->name = #_name; \
	info->fmt_str = _fmt_str; \
	info->size = 4;\
	info->opcode = ARM_INST_##_name; \
	break;\
	case ARM_CAT_SDTR:\
	if (_arg2 == 0xff){\
	for (i = 0; i < 16; i++){\
	arm_inst_info[_arg1 * 16 + i].opcode = ARM_INST_##_name;\
	info = &arm_inst_info[_arg1 * 16 + i ]; \
	info->inst = ARM_INST_##_name; \
	info->category = ARM_CAT_##_category; \
	info->name = #_name; \
	info->fmt_str = _fmt_str; \
	info->size = 4;\
	info->opcode = ARM_INST_##_name; \
	}\
	}\
	else{\
	arm_inst_info[_arg1 * 16 + _arg2].opcode = ARM_INST_##_name;\
	info = &arm_inst_info[_arg1 * 16 + _arg2 ]; \
	info->inst = ARM_INST_##_name; \
	info->category = ARM_CAT_##_category; \
	info->name = #_name; \
	info->fmt_str = _fmt_str; \
	info->size = 4;\
	info->opcode = ARM_INST_##_name; \
	arm_inst_info[_arg1 * 16 + (_arg2 + 8)].opcode = ARM_INST_##_name;\
	info = &arm_inst_info[_arg1 * 16 + (_arg2 + 8)]; \
	info->inst = ARM_INST_##_name; \
	info->category = ARM_CAT_##_category; \
	info->name = #_name; \
	info->fmt_str = _fmt_str; \
	info->size = 4;\
	info->opcode = ARM_INST_##_name; \
	}\
	break;\
	case ARM_CAT_BRNCH:\
	for (i = 0 ; i < 16; i++){\
	for (j = 0 ; j < 16; j++){\
	arm_inst_info[(_arg1 + i ) * 16 + j].opcode = ARM_INST_##_name;\
	info = &arm_inst_info[(_arg1 + i) * 16 + j ]; \
	info->inst = ARM_INST_##_name; \
	info->category = ARM_CAT_##_category; \
	info->name = #_name; \
	info->fmt_str = _fmt_str; \
	info->size = 4;\
	info->opcode = ARM_INST_##_name; \
	}\
	}\
	break;\
	case ARM_CAT_BDTR:\
	for (i = 0; i < 16; i++){\
	arm_inst_info[_arg1 * 16 + i].opcode = ARM_INST_##_name;\
	info = &arm_inst_info[_arg1 * 16 + i ]; \
	info->inst = ARM_INST_##_name; \
	info->category = ARM_CAT_##_category; \
	info->name = #_name; \
	info->fmt_str = _fmt_str; \
	info->size = 4;\
	info->opcode = ARM_INST_##_name; \
	}\
	break;\
	case ARM_CAT_SWI_SVC:\
	for (i = 0 ; i < 16; i++){\
	for (j = 0 ; j < 16; j++){\
	arm_inst_info[(_arg1 + i ) * 16 + j].opcode = ARM_INST_##_name;\
	info = &arm_inst_info[(_arg1 + i) * 16 + j ]; \
	info->inst = ARM_INST_##_name; \
	info->category = ARM_CAT_##_category; \
	info->name = #_name; \
	info->fmt_str = _fmt_str; \
	info->size = 4;\
	info->opcode = ARM_INST_##_name; \
	}\
	}\
	break;\
	case ARM_CAT_CPR_DTR:\
	arm_inst_info[_arg1 * 16 + _arg2].opcode = ARM_INST_##_name;\
	info = &arm_inst_info[_arg1 * 16 + _arg2 ]; \
	info->inst = ARM_INST_##_name; \
	info->category = ARM_CAT_##_category; \
	info->name = #_name; \
	info->fmt_str = _fmt_str; \
	info->size = 4;\
	info->opcode = ARM_INST_##_name; \
	break;\
	case ARM_CAT_VFP:\
	for (i = 0; i < 16; i++){\
	arm_inst_info[_arg1 * 16 + i].opcode = ARM_INST_##_name;\
	info = &arm_inst_info[_arg1 * 16 + i ]; \
	info->inst = ARM_INST_##_name; \
	info->category = ARM_CAT_##_category; \
	info->name = #_name; \
	info->fmt_str = _fmt_str; \
	info->size = 4;\
	info->opcode = ARM_INST_##_name; \
	}\
	break;\
	}
#include "asm.dat"
#undef DEFINST
}

static int arm_token_comp(char *fmt_str, char *token_str, int *token_len)
{
	*token_len = strlen(token_str);
	return !strncmp(fmt_str, token_str, *token_len) &&
		!isalnum(fmt_str[*token_len]);
}

void arm_inst_decode(struct arm_inst_t *inst)
{
	unsigned int arg1;
	unsigned int arg2;

	arg1 = ((inst->dword.bytes[3] & 0x0f) << 4) | ((inst->dword.bytes[2] & 0xf0) >> 4);

	arg2 = ((inst->dword.bytes[0] & 0xf0) >> 4);

	inst->info = &arm_inst_info[arg1 * 16 + arg2];

}

void arm_inst_hex_dump(FILE *f , void *inst_ptr , unsigned int inst_addr)
{
	printf("%8x:	%08x	", inst_addr, *(unsigned int *) inst_ptr);
}

void arm_inst_dump(FILE *f , char *str , int inst_str_size , void *inst_ptr ,
	unsigned int inst_index, unsigned int inst_addr)
{
	struct arm_inst_t inst;
	int byte_index;
	char *inst_str;
	char **inst_str_ptr;
	char *fmt_str;
	int token_len;

	inst.addr = inst_index;
	for (byte_index = 0; byte_index < 4; ++byte_index)
		inst.dword.bytes[byte_index] = *(unsigned char *) (inst_ptr
			+ byte_index);

	arm_inst_decode(&inst);

	inst_str = str;
	inst_str_ptr = &str;
	fmt_str = inst.info->fmt_str;
	if (fmt_str)
	{
		while (*fmt_str)
		{
			if (*fmt_str != '%')
			{
				if (!(*fmt_str == ' ' && *inst_str_ptr == inst_str))
					str_printf(inst_str_ptr, &inst_str_size, "%c",
						*fmt_str);
				++fmt_str;
				continue;
			}

			++fmt_str;
			if (arm_token_comp(fmt_str, "rd", &token_len))
				arm_inst_dump_RD(inst_str_ptr, &inst_str_size, &inst,
					inst.info->category);
			else if (arm_token_comp(fmt_str, "rn", &token_len))
				arm_inst_dump_RN(inst_str_ptr, &inst_str_size, &inst,
					inst.info->category);
			else if (arm_token_comp(fmt_str, "rm", &token_len))
				arm_inst_dump_RM(inst_str_ptr, &inst_str_size, &inst,
					inst.info->category);
			else if (arm_token_comp(fmt_str, "rs", &token_len))
				arm_inst_dump_RS(inst_str_ptr, &inst_str_size, &inst,
					inst.info->category);
			else if (arm_token_comp(fmt_str, "rt", &token_len))
				arm_inst_dump_RT(inst_str_ptr, &inst_str_size, &inst,
					inst.info->category);
			else if (arm_token_comp(fmt_str, "op2", &token_len))
				arm_inst_dump_OP2(inst_str_ptr, &inst_str_size, &inst,
					inst.info->category);
			else if (arm_token_comp(fmt_str, "cond", &token_len))
				arm_inst_dump_COND(inst_str_ptr, &inst_str_size, &inst,
					inst.info->category);
			else if (arm_token_comp(fmt_str, "rdlo", &token_len))
				arm_inst_dump_RDLO(inst_str_ptr, &inst_str_size, &inst,
					inst.info->category);
			else if (arm_token_comp(fmt_str, "rdhi", &token_len))
				arm_inst_dump_RDHI(inst_str_ptr, &inst_str_size, &inst,
					inst.info->category);
			else if (arm_token_comp(fmt_str, "psr", &token_len))
				arm_inst_dump_PSR(inst_str_ptr, &inst_str_size, &inst,
					inst.info->category);
			else if (arm_token_comp(fmt_str, "op2psr", &token_len))
				arm_inst_dump_OP2_PSR(inst_str_ptr, &inst_str_size, &inst,
					inst.info->category);
			else if (arm_token_comp(fmt_str, "amode3", &token_len))
				arm_inst_dump_AMODE_3(inst_str_ptr, &inst_str_size, &inst,
					inst.info->category);
			else if (arm_token_comp(fmt_str, "amode2", &token_len))
				arm_inst_dump_AMODE_2(inst_str_ptr, &inst_str_size, &inst,
					inst.info->category);
			else if (arm_token_comp(fmt_str, "idx", &token_len))
				arm_inst_dump_IDX(inst_str_ptr, &inst_str_size, &inst,
					inst.info->category);
			else if (arm_token_comp(fmt_str, "baddr", &token_len))
				arm_inst_dump_BADDR(inst_str_ptr, &inst_str_size, &inst,
					inst.info->category, inst_addr);
			else if (arm_token_comp(fmt_str, "regs", &token_len))
				arm_inst_dump_REGS(inst_str_ptr, &inst_str_size, &inst,
					inst.info->category);
			else if (arm_token_comp(fmt_str, "immd24", &token_len))
				arm_inst_dump_IMMD24(inst_str_ptr, &inst_str_size, &inst,
					inst.info->category);
			else if (arm_token_comp(fmt_str, "immd16", &token_len))
				arm_inst_dump_IMMD16(inst_str_ptr, &inst_str_size, &inst,
					inst.info->category);
			else if (arm_token_comp(fmt_str, "copr", &token_len))
				arm_inst_dump_COPR(inst_str_ptr, &inst_str_size, &inst,
					inst.info->category);
			else if (arm_token_comp(fmt_str, "amode5", &token_len))
				arm_inst_dump_AMODE_5(inst_str_ptr, &inst_str_size, &inst,
					inst.info->category);
			else if (arm_token_comp(fmt_str, "vfp1STMIA", &token_len))
				arm_inst_dump_VFP1STM(inst_str_ptr, &inst_str_size, &inst,
					inst.info->category);
			else if (arm_token_comp(fmt_str, "vfp1LDMIA", &token_len))
				arm_inst_dump_VFP1LDM(inst_str_ptr, &inst_str_size, &inst,
					inst.info->category);
			else if (arm_token_comp(fmt_str, "vfpregs", &token_len))
				arm_inst_dump_VFP_REGS(inst_str_ptr, &inst_str_size, &inst,
					inst.info->category);
			else if (arm_token_comp(fmt_str, "freg", &token_len))
				arm_inst_dump_FREG(inst_str_ptr, &inst_str_size, &inst,
					inst.info->category);
			else if (arm_token_comp(fmt_str, "fp", &token_len))
				arm_inst_dump_FP(inst_str_ptr, &inst_str_size, &inst,
					inst.info->category);

			else
				fatal("%s: token not recognized\n", fmt_str);

			fmt_str += token_len;
		}
		fprintf(f, "%s\n", inst_str);
	}
	else
	{
		fprintf (f,"???\n");
	}

}

unsigned int arm_rotl(unsigned int value, unsigned int shift)
{
	shift = shift * 2;
	if ((shift &= sizeof(value) * 8 - 1) == 0)
		return value;

	return (value << shift) | (value >> (sizeof(value) * 8 - shift));
}

unsigned int arm_rotr(unsigned int value, unsigned int shift)
{
	shift = shift * 2;
	if ((shift &= sizeof(value) * 8 - 1) == 0)
		return value;

	return (value >> shift) | (value << (sizeof(value) * 8 - shift));
}

void arm_inst_dump_RD(char **inst_str_ptr, int *inst_str_size,
	struct arm_inst_t *inst, enum arm_cat_enum cat)
{
	unsigned int rd;

	if (cat == ARM_CAT_DPR_REG)
		rd = inst->dword.dpr_ins.dst_reg;
	else if (cat == ARM_CAT_DPR_IMM)
		rd = inst->dword.dpr_ins.dst_reg;
	else if (cat == ARM_CAT_DPR_SAT)
		rd = inst->dword.dpr_sat_ins.dst_reg;
	else if (cat == ARM_CAT_PSR)
		rd = inst->dword.psr_ins.dst_reg;
	else if (cat == ARM_CAT_MULT)
		rd = inst->dword.mult_ins.dst_rd;
	else if (cat == ARM_CAT_MULT_SIGN)
		rd = inst->dword.mult_ins.dst_rd;
	else if (cat == ARM_CAT_MULT_LN)
		fatal("%d: rd fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT_LN_SIGN)
		fatal("%d: rd fmt not recognized", cat);
	else if (cat == ARM_CAT_HFWRD_REG)
		rd = inst->dword.hfwrd_reg_ins.dst_rd;
	else if (cat == ARM_CAT_HFWRD_IMM)
		rd = inst->dword.hfwrd_imm_ins.dst_rd;
	else if (cat == ARM_CAT_BAX)
		fatal("%d: rd fmt not recognized", cat);
	else if (cat == ARM_CAT_SDTR)
		rd = inst->dword.sdtr_ins.src_dst_rd;
	else if (cat == ARM_CAT_SDSWP)
		rd = inst->dword.sngl_dswp_ins.dst_rd;
	else if (cat == ARM_CAT_CPR_RTR)
		rd = inst->dword.cpr_rtr_ins.rd;
	else if (cat == ARM_CAT_CPR_DTR)
		rd = inst->dword.cpr_dtr_ins.cpr_sr_dst;
	else if (cat == ARM_CAT_BRNCH)
		fatal("%d: rd fmt not recognized", cat);

	/* TODO: destinations for BDTR CDTR CDO*/
	else
		fatal("%d: rd fmt not recognized", cat);

	switch (rd)
	{
	case (r13):
		str_printf(inst_str_ptr, inst_str_size, "sp");
	break;

	case (r14):
		str_printf(inst_str_ptr, inst_str_size, "lr");
	break;
	case (r15):

		str_printf(inst_str_ptr, inst_str_size, "pc");
	break;

	default:
		str_printf(inst_str_ptr, inst_str_size, "r%d", rd);
		break;
	}


}

void arm_inst_dump_RN(char **inst_str_ptr, int *inst_str_size,
	struct arm_inst_t *inst, enum arm_cat_enum cat)
{
	unsigned int rn;

	if (cat == ARM_CAT_DPR_REG)
		rn = inst->dword.dpr_ins.op1_reg;
	else if (cat == ARM_CAT_DPR_IMM)
		rn = inst->dword.dpr_ins.op1_reg;
	else if (cat == ARM_CAT_DPR_SAT)
		rn = inst->dword.dpr_sat_ins.op1_reg;
	else if (cat == ARM_CAT_PSR)
		fatal("%d: rn  fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT)
		rn = inst->dword.mult_ins.op2_rn;
	else if (cat == ARM_CAT_MULT_SIGN)
		rn = inst->dword.mult_ins.op2_rn;
	else if (cat == ARM_CAT_MULT_LN)
		fatal("%d: rn  fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT_LN_SIGN)
		fatal("%d: rn fmt not recognized", cat);
	else if (cat == ARM_CAT_HFWRD_REG)
		rn = inst->dword.hfwrd_reg_ins.base_rn;
	else if (cat == ARM_CAT_HFWRD_IMM)
		rn = inst->dword.hfwrd_imm_ins.base_rn;
	else if (cat == ARM_CAT_BAX)
		rn = inst->dword.bax_ins.op0_rn;
	else if (cat == ARM_CAT_SDTR)
		rn = inst->dword.sdtr_ins.base_rn;
	else if (cat == ARM_CAT_BDTR)
		rn = inst->dword.bdtr_ins.base_rn;
	else if (cat == ARM_CAT_SDSWP)
		rn = inst->dword.sngl_dswp_ins.base_rn;
	else if (cat == ARM_CAT_CPR_RTR)
		rn = inst->dword.cpr_rtr_ins.cpr_rn;
	else if (cat == ARM_CAT_BRNCH)
		fatal("%d: rn fmt not recognized", cat);
	else if (cat == ARM_CAT_VFP)
		rn = inst->dword.vfp_mv_ins.vfp_rn;

	/* TODO: destinations for BDTR CDTR CDO*/
	else
		fatal("%d: rn fmt not recognized", cat);

	switch (rn)
	{
	case (r12):
		if(cat == ARM_CAT_VFP)
		{
			if(inst->dword.vfp_mv_ins.w)
				str_printf(inst_str_ptr, inst_str_size, "ip!");
			else
				str_printf(inst_str_ptr, inst_str_size, "ip");
		}
		else
			str_printf(inst_str_ptr, inst_str_size, "ip");
		break;
	case (r13):
		if(cat != ARM_CAT_BDTR)
		{
		str_printf(inst_str_ptr, inst_str_size, "sp");
		}
		else if (cat == ARM_CAT_BDTR)
		{
		str_printf(inst_str_ptr, inst_str_size, " ");
		}
		break;
	case (r14):
		str_printf(inst_str_ptr, inst_str_size, "lr");
		break;
	case (r15):
		str_printf(inst_str_ptr, inst_str_size, "pc");
		break;
	default:
		str_printf(inst_str_ptr, inst_str_size, "r%d", rn);
		break;
	}



}

void arm_inst_dump_RM(char **inst_str_ptr, int *inst_str_size,
	struct arm_inst_t *inst, enum arm_cat_enum cat)
{
	unsigned int rm;

	if (cat == ARM_CAT_DPR_REG)
		fatal("%d: rm fmt not recognized", cat);
	else if (cat == ARM_CAT_DPR_IMM)
		fatal("%d: rm fmt not recognized", cat);
	else if (cat == ARM_CAT_DPR_SAT)
		fatal("%d: rm fmt not recognized", cat);
	else if (cat == ARM_CAT_PSR)
		fatal("%d: rm fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT)
		rm = inst->dword.mult_ins.op0_rm;
	else if (cat == ARM_CAT_MULT_SIGN)
		rm = inst->dword.mult_ins.op0_rm;
	else if (cat == ARM_CAT_MULT_LN)
		rm = inst->dword.mul_ln_ins.op0_rm;
	else if (cat == ARM_CAT_MULT_LN_SIGN)
		rm = inst->dword.mul_ln_ins.op0_rm;
	else if (cat == ARM_CAT_HFWRD_REG)
		rm = inst->dword.hfwrd_reg_ins.off_reg;
	else if (cat == ARM_CAT_HFWRD_IMM)
		fatal("%d: rm fmt not recognized", cat);
	else if (cat == ARM_CAT_BAX)
		fatal("%d: rm fmt not recognized", cat);
	else if (cat == ARM_CAT_SDTR)
		fatal("%d: rm fmt not recognized", cat);
	else if (cat == ARM_CAT_SDSWP)
		rm = inst->dword.sngl_dswp_ins.op0_rm;
	else if (cat == ARM_CAT_CPR_RTR)
		rm = inst->dword.cpr_rtr_ins.cpr_op_rm;
	else if (cat == ARM_CAT_BRNCH)
		fatal("%d: rm fmt not recognized", cat);

	/* TODO: destinations for BDTR CDTR CDO*/
	else
		fatal("%d: rm fmt not recognized", cat);

	switch (rm)
	{
	case (r13):
		str_printf(inst_str_ptr, inst_str_size, "sp");
		break;
	case (r14):
		str_printf(inst_str_ptr, inst_str_size, "lr");
		break;
	case (r15):
		str_printf(inst_str_ptr, inst_str_size, "pc");
		break;
	default:
		str_printf(inst_str_ptr, inst_str_size, "r%d", rm);
		break;
	}


}

void arm_inst_dump_RS(char **inst_str_ptr, int *inst_str_size,
	struct arm_inst_t *inst, enum arm_cat_enum cat)
{
	unsigned int rs;

	if (cat == ARM_CAT_DPR_REG)
		fatal("%d: rs fmt not recognized", cat);
	else if (cat == ARM_CAT_DPR_IMM)
		fatal("%d: rs fmt not recognized", cat);
	else if (cat == ARM_CAT_DPR_SAT)
		fatal("%d: rs fmt not recognized", cat);
	else if (cat == ARM_CAT_PSR)
		fatal("%d: rs fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT)
		rs = inst->dword.mult_ins.op1_rs;
	else if (cat == ARM_CAT_MULT_SIGN)
		rs = inst->dword.mult_ins.op1_rs;
	else if (cat == ARM_CAT_MULT_LN)
		rs = inst->dword.mul_ln_ins.op1_rs;
	else if (cat == ARM_CAT_MULT_LN_SIGN)
		rs = inst->dword.mul_ln_ins.op1_rs;
	else if (cat == ARM_CAT_HFWRD_REG)
		fatal("%d: rs fmt not recognized", cat);
	else if (cat == ARM_CAT_HFWRD_IMM)
		fatal("%d: rs fmt not recognized", cat);
	else if (cat == ARM_CAT_BAX)
		fatal("%d: rs fmt not recognized", cat);
	else if (cat == ARM_CAT_SDTR)
		fatal("%d: rs fmt not recognized", cat);
	else if (cat == ARM_CAT_SDSWP)
		fatal("%d: rs fmt not recognized", cat);
	else if (cat == ARM_CAT_CPR_RTR)
		fatal("%d: rs fmt not recognized", cat);
	else if (cat == ARM_CAT_BRNCH)
		fatal("%d: rs fmt not recognized", cat);

	/* TODO: destinations for BDTR CDTR CDO*/
	else
		fatal("%d: rs fmt not recognized", cat);

	switch (rs)
	{
	case (r13):
		str_printf(inst_str_ptr, inst_str_size, "sp");
		break;
	case (r14):
		str_printf(inst_str_ptr, inst_str_size, "lr");
		break;
	case (r15):
		str_printf(inst_str_ptr, inst_str_size, "pc");
		break;
	default:
		str_printf(inst_str_ptr, inst_str_size, "r%d", rs);
		break;
	}

}

void arm_inst_dump_OP2(char **inst_str_ptr, int *inst_str_size,
	struct arm_inst_t *inst, enum arm_cat_enum cat)
{
	unsigned int op2;
	unsigned int rm;
	unsigned int rs;
	unsigned int shift;
	unsigned int imm;
	unsigned int rotate;
	unsigned int imm_8r;

	if (cat == ARM_CAT_DPR_REG)
		op2 = inst->dword.dpr_ins.op2;
	else if (cat == ARM_CAT_DPR_IMM)
		op2 = inst->dword.dpr_ins.op2;
	else if (cat == ARM_CAT_DPR_SAT)
		op2 = inst->dword.dpr_sat_ins.op2;
	else if (cat == ARM_CAT_PSR)
		op2 = inst->dword.psr_ins.op2;
	else if (cat == ARM_CAT_MULT)
		fatal("%d: op2 fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT_SIGN)
		fatal("%d: op2 fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT_LN)
		fatal("%d: op2 fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT_LN_SIGN)
		fatal("%d: op2 fmt not recognized", cat);
	else if (cat == ARM_CAT_HFWRD_REG)
		fatal("%d: op2 fmt not recognized", cat);
	else if (cat == ARM_CAT_HFWRD_IMM)
		fatal("%d: op2 fmt not recognized", cat);
	else if (cat == ARM_CAT_BAX)
		fatal("%d: op2 fmt not recognized", cat);
	else if (cat == ARM_CAT_SDTR)
		fatal("%d: op2 fmt not recognized", cat);
	else if (cat == ARM_CAT_SDSWP)
		fatal("%d: op2 fmt not recognized", cat);
	else if (cat == ARM_CAT_CPR_RTR)
		fatal("%d: op2 fmt not recognized", cat);
	else if (cat == ARM_CAT_BRNCH)
		fatal("%d: op2 fmt not recognized", cat);

	/* TODO: destinations for BDTR CDTR CDO*/
	else
		fatal("%d: op2 fmt not recognized", cat);

	if (!inst->dword.dpr_ins.imm)
	{
		rm = (op2 & (0x0000000f));
		shift = ((op2 >> 4) & (0x000000ff));

		if (shift & 0x00000001)
		{
			rs = (shift >> 4);
			switch ((shift >> 1) & 0x00000003)
			{
			case (ARM_OPTR_LSL):
				str_printf(inst_str_ptr, inst_str_size, "r%d , LSL r%d", rm, rs);
			break;

			case (ARM_OPTR_LSR):
				str_printf(inst_str_ptr, inst_str_size, "r%d , LSR r%d", rm, rs);
			break;

			case (ARM_OPTR_ASR):
				str_printf(inst_str_ptr, inst_str_size, "r%d , ASR r%d", rm, rs);
			break;

			case (ARM_OPTR_ROR):
				str_printf(inst_str_ptr, inst_str_size, "r%d , ROR r%d", rm, rs);
			break;
			}
		}

		else
		{
			switch ((shift >> 1) & 0x00000003)
			{
			case (ARM_OPTR_LSL):
				str_printf(inst_str_ptr, inst_str_size, "r%d , LSL #%d   ;0x%x",
					rm, ((shift >> 3) & 0x0000001f),((shift >> 3) & 0x0000001f));
			break;

			case (ARM_OPTR_LSR):
				str_printf(inst_str_ptr, inst_str_size, "r%d , LSR #%d   ;0x%x",
					rm, ((shift >> 3) & 0x0000001f),((shift >> 3) & 0x0000001f));
			break;

			case (ARM_OPTR_ASR):
				str_printf(inst_str_ptr, inst_str_size, "r%d , ASR #%d   ;0x%x",
					rm, ((shift >> 3) & 0x0000001f),((shift >> 3) & 0x0000001f));
			break;

			case (ARM_OPTR_ROR):
				str_printf(inst_str_ptr, inst_str_size, "r%d , ROR #%d   ;0x%x",
					rm, ((shift >> 3) & 0x0000001f),((shift >> 3) & 0x0000001f));
			break;
			}
		}
	}
	else
	{
		imm = (op2 & (0x000000ff));
		rotate = ((op2 >> 8) & 0x0000000f);
		imm_8r = arm_rotr( imm , rotate);
		str_printf(inst_str_ptr, inst_str_size, "#%d   ;0x%x", imm_8r, imm_8r);
	}

}

void arm_inst_dump_COND(char **inst_str_ptr, int *inst_str_size,
	struct arm_inst_t *inst, enum arm_cat_enum cat)
{
	unsigned int cond;

	if (cat == ARM_CAT_DPR_REG)
		cond = inst->dword.dpr_ins.cond;
	else if (cat == ARM_CAT_DPR_IMM)
		cond = inst->dword.dpr_ins.cond;
	else if (cat == ARM_CAT_DPR_SAT)
		cond = inst->dword.dpr_sat_ins.cond;
	else if (cat == ARM_CAT_PSR)
		cond = inst->dword.psr_ins.cond;
	else if (cat == ARM_CAT_MULT)
		cond = inst->dword.mult_ins.cond;
	else if (cat == ARM_CAT_MULT_SIGN)
		cond = inst->dword.mult_ins.cond;
	else if (cat == ARM_CAT_MULT_LN)
		cond = inst->dword.mul_ln_ins.cond;
	else if (cat == ARM_CAT_MULT_LN_SIGN)
		cond = inst->dword.mul_ln_ins.cond;
	else if (cat == ARM_CAT_HFWRD_REG)
		cond = inst->dword.hfwrd_reg_ins.cond;
	else if (cat == ARM_CAT_HFWRD_IMM)
		cond = inst->dword.hfwrd_imm_ins.cond;
	else if (cat == ARM_CAT_BAX)
		cond = inst->dword.bax_ins.cond;
	else if (cat == ARM_CAT_SDTR)
		cond = inst->dword.sdtr_ins.cond;
	else if (cat == ARM_CAT_BDTR)
		cond = inst->dword.bdtr_ins.cond;
	else if (cat == ARM_CAT_SDSWP)
		cond = inst->dword.sngl_dswp_ins.cond;
	else if (cat == ARM_CAT_CPR_RTR)
		cond = inst->dword.cpr_rtr_ins.cond;
	else if (cat == ARM_CAT_CPR_DTR)
		cond = inst->dword.cpr_dtr_ins.cond;
	else if (cat == ARM_CAT_BRNCH)
		cond = inst->dword.brnch_ins.cond;
	else if (cat == ARM_CAT_SWI_SVC)
		cond = inst->dword.swi_svc_ins.cond;
	else if (cat == ARM_CAT_VFP)
		cond = inst->dword.vfp_mv_ins.cond;

	/* TODO: destinations for BDTR CDTR CDO*/
	else
		fatal("%d: cond fmt not recognized", cat);

	switch (cond)
	{
	case (EQ):
	str_printf(inst_str_ptr, inst_str_size, "EQ");
	break;

	case (NE):
	str_printf(inst_str_ptr, inst_str_size, "NE");
	break;

	case (CS):
	str_printf(inst_str_ptr, inst_str_size, "CS");
	break;

	case (CC):
	str_printf(inst_str_ptr, inst_str_size, "CC");
	break;

	case (MI):
	str_printf(inst_str_ptr, inst_str_size, "MI");
	break;

	case (PL):
	str_printf(inst_str_ptr, inst_str_size, "PL");
	break;

	case (VS):
	str_printf(inst_str_ptr, inst_str_size, "VS");
	break;

	case (VC):
	str_printf(inst_str_ptr, inst_str_size, "VC");
	break;

	case (HI):
	str_printf(inst_str_ptr, inst_str_size, "HI");
	break;

	case (LS):
	str_printf(inst_str_ptr, inst_str_size, "LS");
	break;

	case (GE):
	str_printf(inst_str_ptr, inst_str_size, "GE");
	break;

	case (LT):
	str_printf(inst_str_ptr, inst_str_size, "LT");
	break;

	case (GT):
	str_printf(inst_str_ptr, inst_str_size, "GT");
	break;

	case (LE):
	str_printf(inst_str_ptr, inst_str_size, "LE");
	break;

	case (AL):
	str_printf(inst_str_ptr, inst_str_size, " ");
	break;

	}
}

void arm_inst_dump_RDLO(char **inst_str_ptr, int *inst_str_size,
	struct arm_inst_t *inst, enum arm_cat_enum cat)
{
	unsigned int rdlo;

	if (cat == ARM_CAT_DPR_REG)
		fatal("%d: rdlo fmt not recognized", cat);
	else if (cat == ARM_CAT_DPR_IMM)
		fatal("%d: rdlo fmt not recognized", cat);
	else if (cat == ARM_CAT_DPR_SAT)
		fatal("%d: rdlo fmt not recognized", cat);
	else if (cat == ARM_CAT_PSR)
		fatal("%d: rdlo fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT)
		fatal("%d: rdlo fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT_SIGN)
		fatal("%d: rdlo fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT_LN)
		rdlo = inst->dword.mul_ln_ins.dst_lo;
	else if (cat == ARM_CAT_MULT_LN_SIGN)
		rdlo = inst->dword.mul_ln_ins.dst_lo;
	else if (cat == ARM_CAT_HFWRD_REG)
		fatal("%d: rdlo fmt not recognized", cat);
	else if (cat == ARM_CAT_HFWRD_IMM)
		fatal("%d: rdlo fmt not recognized", cat);
	else if (cat == ARM_CAT_BAX)
		fatal("%d: rdlo fmt not recognized", cat);
	else if (cat == ARM_CAT_SDTR)
		fatal("%d: rdlo fmt not recognized", cat);
	else if (cat == ARM_CAT_SDSWP)
		fatal("%d: rdlo fmt not recognized", cat);
	else if (cat == ARM_CAT_CPR_RTR)
		fatal("%d: rdlo fmt not recognized", cat);
	else if (cat == ARM_CAT_BRNCH)
		fatal("%d: rdlo fmt not recognized", cat);

	/* TODO: destinations for BDTR CDTR CDO*/
	else
		fatal("%d: rdlo fmt not recognized", cat);

	str_printf(inst_str_ptr, inst_str_size, "r%d", rdlo);

}

void arm_inst_dump_RDHI(char **inst_str_ptr, int *inst_str_size,
	struct arm_inst_t *inst, enum arm_cat_enum cat)
{
	unsigned int rdhi;

	if (cat == ARM_CAT_DPR_REG)
		fatal("%d: rdhi fmt not recognized", cat);
	else if (cat == ARM_CAT_DPR_IMM)
		fatal("%d: rdhi fmt not recognized", cat);
	else if (cat == ARM_CAT_DPR_SAT)
		fatal("%d: rdhi fmt not recognized", cat);
	else if (cat == ARM_CAT_PSR)
		fatal("%d: rdhi fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT)
		fatal("%d: rdhi fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT_SIGN)
		fatal("%d: rdhi fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT_LN)
		rdhi = inst->dword.mul_ln_ins.dst_hi;
	else if (cat == ARM_CAT_MULT_LN_SIGN)
		rdhi = inst->dword.mul_ln_ins.dst_hi;
	else if (cat == ARM_CAT_HFWRD_REG)
		fatal("%d: rdhi fmt not recognized", cat);
	else if (cat == ARM_CAT_HFWRD_IMM)
		fatal("%d: rdhi fmt not recognized", cat);
	else if (cat == ARM_CAT_BAX)
		fatal("%d: rdhi fmt not recognized", cat);
	else if (cat == ARM_CAT_SDTR)
		fatal("%d: rdhi fmt not recognized", cat);
	else if (cat == ARM_CAT_SDSWP)
		fatal("%d: rdhi fmt not recognized", cat);
	else if (cat == ARM_CAT_CPR_RTR)
		fatal("%d: rdhi fmt not recognized", cat);
	else if (cat == ARM_CAT_BRNCH)
		fatal("%d: rdhi fmt not recognized", cat);

	/* TODO: destinations for BDTR CDTR CDO*/
	else
		fatal("%d: rdhi fmt not recognized", cat);

	str_printf(inst_str_ptr, inst_str_size, "r%d", rdhi);

}

void arm_inst_dump_PSR(char **inst_str_ptr, int *inst_str_size,
	struct arm_inst_t *inst, enum arm_cat_enum cat)
{
	unsigned int psr;

	if (cat == ARM_CAT_DPR_REG)
		fatal("%d: psr fmt not recognized", cat);
	else if (cat == ARM_CAT_DPR_IMM)
		fatal("%d: psr fmt not recognized", cat);
	else if (cat == ARM_CAT_DPR_SAT)
		fatal("%d: psr fmt not recognized", cat);
	else if (cat == ARM_CAT_PSR)
		psr = inst->dword.psr_ins.psr_loc;
	else if (cat == ARM_CAT_MULT)
		fatal("%d: psr fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT_SIGN)
		fatal("%d: psr fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT_LN)
		fatal("%d: psr fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT_LN_SIGN)
		fatal("%d: psr fmt not recognized", cat);
	else if (cat == ARM_CAT_HFWRD_REG)
		fatal("%d: psr fmt not recognized", cat);
	else if (cat == ARM_CAT_HFWRD_IMM)
		fatal("%d: psr fmt not recognized", cat);
	else if (cat == ARM_CAT_BAX)
		fatal("%d: psr fmt not recognized", cat);
	else if (cat == ARM_CAT_SDTR)
		fatal("%d: psr fmt not recognized", cat);
	else if (cat == ARM_CAT_SDSWP)
		fatal("%d: psr fmt not recognized", cat);
	else if (cat == ARM_CAT_CPR_RTR)
		fatal("%d: psr fmt not recognized", cat);
	else if (cat == ARM_CAT_BRNCH)
		fatal("%d: psr fmt not recognized", cat);

	/* TODO: destinations for BDTR CDTR CDO*/
	else
		fatal("%d: psr fmt not recognized", cat);

	switch (psr)
	{
	case (CPSR):
	str_printf(inst_str_ptr, inst_str_size, "CPSR");
	break;

	case (SPSR):
	str_printf(inst_str_ptr, inst_str_size, "SPSR");
	break;
	}
}

void arm_inst_dump_OP2_PSR(char **inst_str_ptr, int *inst_str_size,
	struct arm_inst_t *inst, enum arm_cat_enum cat)
{
	unsigned int op2_psr;
	unsigned int rotate;
	unsigned int immd_8r;
	unsigned int rm;

	if (cat == ARM_CAT_DPR_REG)
		fatal("%d: op2 psr fmt not recognized", cat);
	else if (cat == ARM_CAT_DPR_IMM)
		fatal("%d: op2 psr fmt not recognized", cat);
	else if (cat == ARM_CAT_DPR_SAT)
		fatal("%d: op2 psr fmt not recognized", cat);
	else if (cat == ARM_CAT_PSR)
		op2_psr = inst->dword.psr_ins.op2;
	else if (cat == ARM_CAT_MULT)
		fatal("%d: op2 psr fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT_SIGN)
		fatal("%d: op2 psr fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT_LN)
		fatal("%d: op2 psr fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT_LN_SIGN)
		fatal("%d: op2 psr fmt not recognized", cat);
	else if (cat == ARM_CAT_HFWRD_REG)
		fatal("%d: op2 psr fmt not recognized", cat);
	else if (cat == ARM_CAT_HFWRD_IMM)
		fatal("%d: op2 psr fmt not recognized", cat);
	else if (cat == ARM_CAT_BAX)
		fatal("%d: op2 psr fmt not recognized", cat);
	else if (cat == ARM_CAT_SDTR)
		fatal("%d: op2 psr fmt not recognized", cat);
	else if (cat == ARM_CAT_SDSWP)
		fatal("%d: op2 psr fmt not recognized", cat);
	else if (cat == ARM_CAT_CPR_RTR)
		fatal("%d: op2 psr fmt not recognized", cat);
	else if (cat == ARM_CAT_BRNCH)
		fatal("%d: op2 psr fmt not recognized", cat);

	/* TODO: destinations for BDTR CDTR CDO*/
	else
		fatal("%d: psr fmt not recognized", cat);

	if (inst->dword.psr_ins.imm)
	{
		rotate = ((op2_psr & 0x00000f00) >> 8);
		immd_8r = arm_rotr( op2_psr , rotate);
		str_printf(inst_str_ptr, inst_str_size, "#%d   ;0x%x", immd_8r, immd_8r);
	}
	else
	{
		rm = (op2_psr & 0x0000000f);
		switch (rm)
		{
		case (r13):
			str_printf(inst_str_ptr, inst_str_size, "sp");
			break;
		case (r14):
			str_printf(inst_str_ptr, inst_str_size, "lr");
			break;
		case (r15):
			str_printf(inst_str_ptr, inst_str_size, "pc");
			break;
		default:
			str_printf(inst_str_ptr, inst_str_size, "r%d", rm);
			break;
		}
	}
}


void arm_amode2_disasm(char **inst_str_ptr, int *inst_str_size,
	struct arm_inst_t *inst, enum arm_cat_enum cat)
{
	unsigned int rn;
	unsigned int rm;
	unsigned int shift;
	unsigned int offset;

	offset = inst->dword.sdtr_ins.off;
	rn = inst->dword.sdtr_ins.base_rn;

	if(inst->dword.sdtr_ins.imm == 1)
	{
		rm = (offset & (0x0000000f));
		shift = ((offset >> 4) & (0x000000ff));

		if(inst->dword.sdtr_ins.up_dn)
		{
			switch ((shift >> 1) & 0x00000003)
			{
			case (ARM_OPTR_LSL):
				str_printf(inst_str_ptr, inst_str_size, "[r%d, r%d, lsl #%d]",
					rn, rm, ((shift >> 3) & 0x0000001f));
			break;

			case (ARM_OPTR_LSR):
				str_printf(inst_str_ptr, inst_str_size, "[r%d, r%d, lsr #%d]",
					rn, rm, ((shift >> 3) & 0x0000001f));
			break;

			case (ARM_OPTR_ASR):
				str_printf(inst_str_ptr, inst_str_size, "[r%d, r%d, asr #%d]",
					rn, rm, ((shift >> 3) & 0x0000001f));
			break;

			case (ARM_OPTR_ROR):
				str_printf(inst_str_ptr, inst_str_size, "[r%d, r%d, ror #%d]",
					rn, rm, ((shift >> 3) & 0x0000001f));
			break;
			}
		}
		else
		{
			switch ((shift >> 1) & 0x00000003)
			{
			case (ARM_OPTR_LSL):
				str_printf(inst_str_ptr, inst_str_size, "[r%d, r%d, lsl #-%d]",
					rn, rm, ((shift >> 3) & 0x0000001f));
			break;

			case (ARM_OPTR_LSR):
				str_printf(inst_str_ptr, inst_str_size, "[r%d, r%d, lsr #-%d]",
					rn, rm, ((shift >> 3) & 0x0000001f));
			break;

			case (ARM_OPTR_ASR):
				str_printf(inst_str_ptr, inst_str_size, "[r%d, r%d, asr #-%d]",
					rn, rm, ((shift >> 3) & 0x0000001f));
			break;

			case (ARM_OPTR_ROR):
				str_printf(inst_str_ptr, inst_str_size, "[r%d, r%d, ror #-%d]",
					rn, rm, ((shift >> 3) & 0x0000001f));
			break;
			}
		}
	}
	else if (inst->dword.sdtr_ins.imm == 0)
	{
		if(!offset)
		{
			str_printf(inst_str_ptr, inst_str_size, "[r%d]",
				rn);
		}
		else
		{
			if(inst->dword.sdtr_ins.up_dn)
				str_printf(inst_str_ptr, inst_str_size, "[r%d, #%d]",
					rn, offset);
			else
				str_printf(inst_str_ptr, inst_str_size, "[r%d, #-%d]",
					rn, offset);
		}
	}
	else
		fatal("%d: amode 2 fmt not recognized", cat);

}

void arm_amode3_disasm(char **inst_str_ptr, int *inst_str_size,
	struct arm_inst_t *inst, enum arm_cat_enum cat)
{
	unsigned int rn;
	unsigned int rm;
	unsigned int offset;
	if ( cat == ARM_CAT_HFWRD_REG)
	{
		rn = inst->dword.hfwrd_reg_ins.base_rn;
		rm = inst->dword.hfwrd_reg_ins.off_reg;
		if (rm)
			str_printf(inst_str_ptr, inst_str_size, "[r%d, #%d]", rn, rm);
		else
			str_printf(inst_str_ptr, inst_str_size, "[r%d]", rn);
	}
	else if (cat == ARM_CAT_HFWRD_IMM)
	{
		rn = inst->dword.hfwrd_imm_ins.base_rn;
		offset = (inst->dword.hfwrd_imm_ins.imm_off_hi << 4)
			| (inst->dword.hfwrd_imm_ins.imm_off_lo);
		if(offset)
			str_printf(inst_str_ptr, inst_str_size, "[r%d, #%d]", rn, offset);
		else
			str_printf(inst_str_ptr, inst_str_size, "[r%d]", rn);
	}
	else
		fatal("%d: amode 3 disasm fmt not recognized", cat);
}

void arm_inst_dump_AMODE_3(char **inst_str_ptr, int *inst_str_size,
	struct arm_inst_t *inst, enum arm_cat_enum cat)
{

	if (cat == ARM_CAT_DPR_REG)
		fatal("%d: amode 3 fmt not recognized", cat);
	else if (cat == ARM_CAT_DPR_IMM)
		fatal("%d: amode 3 fmt not recognized", cat);
	else if (cat == ARM_CAT_DPR_SAT)
		fatal("%d: amode 3 fmt not recognized", cat);
	else if (cat == ARM_CAT_PSR)
		fatal("%d: amode 3 fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT)
		fatal("%d: amode 3 fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT_SIGN)
		fatal("%d: amode 3 fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT_LN)
		fatal("%d: amode 3 fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT_LN_SIGN)
		fatal("%d: amode 3 fmt not recognized", cat);
	else if (cat == ARM_CAT_HFWRD_REG)
		arm_amode3_disasm(inst_str_ptr, inst_str_size, inst, cat);
	else if (cat == ARM_CAT_HFWRD_IMM)
		arm_amode3_disasm(inst_str_ptr, inst_str_size, inst, cat);
	else if (cat == ARM_CAT_BAX)
		fatal("%d: amode 3 fmt not recognized", cat);
	else if (cat == ARM_CAT_SDTR)
		fatal("%d: amode 3 fmt not recognized", cat);
	else if (cat == ARM_CAT_SDSWP)
		fatal("%d: amode 3 fmt not recognized", cat);
	else if (cat == ARM_CAT_CPR_RTR)
		fatal("%d: amode 3 fmt not recognized", cat);
	else if (cat == ARM_CAT_BRNCH)
		fatal("%d: amode 3 fmt not recognized", cat);

	/* TODO: destinations for BDTR CDTR CDO*/
	else
		fatal("%d: amode 3 fmt not recognized", cat);
}

void arm_inst_dump_AMODE_2(char **inst_str_ptr, int *inst_str_size,
	struct arm_inst_t *inst, enum arm_cat_enum cat)
{

	if (cat == ARM_CAT_DPR_REG)
		fatal("%d: amode 2 fmt not recognized", cat);
	else if (cat == ARM_CAT_DPR_IMM)
		fatal("%d: amode 2 fmt not recognized", cat);
	else if (cat == ARM_CAT_DPR_SAT)
		fatal("%d: amode 2 fmt not recognized", cat);
	else if (cat == ARM_CAT_PSR)
		fatal("%d: amode 2 fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT)
		fatal("%d: amode 2 fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT_SIGN)
		fatal("%d: amode 2 fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT_LN)
		fatal("%d: amode 2 fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT_LN_SIGN)
		fatal("%d: amode 2 fmt not recognized", cat);
	else if (cat == ARM_CAT_HFWRD_REG)
		fatal("%d: amode 2 fmt not recognized", cat);
	else if (cat == ARM_CAT_HFWRD_IMM)
		fatal("%d: amode 2 fmt not recognized", cat);
	else if (cat == ARM_CAT_BAX)
		fatal("%d: amode 2 fmt not recognized", cat);
	else if (cat == ARM_CAT_SDTR)
		arm_amode2_disasm(inst_str_ptr, inst_str_size, inst, cat);
	else if (cat == ARM_CAT_SDSWP)
		fatal("%d: amode 2 fmt not recognized", cat);
	else if (cat == ARM_CAT_CPR_RTR)
		fatal("%d: amode 2 fmt not recognized", cat);
	else if (cat == ARM_CAT_BRNCH)
		fatal("%d: amode 2 fmt not recognized", cat);

	/* TODO: destinations for BDTR CDTR CDO*/
	else
		fatal("%d: amode 2 fmt not recognized", cat);
}

void arm_inst_dump_IDX(char **inst_str_ptr, int *inst_str_size,
	struct arm_inst_t *inst, enum arm_cat_enum cat)
{
	unsigned int idx;

	if (cat == ARM_CAT_DPR_REG)
		fatal("%d: idx fmt not recognized", cat);
	else if (cat == ARM_CAT_DPR_IMM)
		fatal("%d: idx fmt not recognized", cat);
	else if (cat == ARM_CAT_DPR_SAT)
		fatal("%d: idx fmt not recognized", cat);
	else if (cat == ARM_CAT_PSR)
		fatal("%d: idx fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT)
		fatal("%d: idx fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT_SIGN)
		fatal("%d: idx fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT_LN)
		fatal("%d: idx fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT_LN_SIGN)
		fatal("%d: idx fmt not recognized", cat);
	else if (cat == ARM_CAT_HFWRD_REG)
		fatal("%d: idx fmt not recognized", cat);
	else if (cat == ARM_CAT_HFWRD_IMM)
		fatal("%d: idx fmt not recognized", cat);
	else if (cat == ARM_CAT_BAX)
		fatal("%d: idx fmt not recognized", cat);
	else if (cat == ARM_CAT_SDTR)
		idx = inst->dword.sdtr_ins.idx_typ;
	else if (cat == ARM_CAT_SDSWP)
		fatal("%d: idx fmt not recognized", cat);
	else if (cat == ARM_CAT_CPR_RTR)
		fatal("%d: idx fmt not recognized", cat);
	else if (cat == ARM_CAT_BRNCH)
		fatal("%d: idx fmt not recognized", cat);

	/* TODO: destinations for BDTR CDTR CDO*/
	else
		fatal("%d: idx fmt not recognized", cat);

	if (idx == 1)
	{
		if(inst->dword.sdtr_ins.off)
		str_printf(inst_str_ptr, inst_str_size, "!");
	}
	else
		str_printf(inst_str_ptr, inst_str_size, " ");
}

void arm_inst_dump_BADDR(char **inst_str_ptr, int *inst_str_size,
	struct arm_inst_t *inst, enum arm_cat_enum cat,
	unsigned int inst_addr)
{
	signed int offset;

	if (cat == ARM_CAT_DPR_REG)
		fatal("%d: brnch fmt not recognized", cat);
	else if (cat == ARM_CAT_DPR_IMM)
		fatal("%d: brnch fmt not recognized", cat);
	else if (cat == ARM_CAT_DPR_SAT)
		fatal("%d: brnch fmt not recognized", cat);
	else if (cat == ARM_CAT_PSR)
		fatal("%d: brnch fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT)
		fatal("%d: brnch fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT_SIGN)
		fatal("%d: brnch fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT_LN)
		fatal("%d: brnch fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT_LN_SIGN)
		fatal("%d: brnch fmt not recognized", cat);
	else if (cat == ARM_CAT_HFWRD_REG)
		fatal("%d: brnch fmt not recognized", cat);
	else if (cat == ARM_CAT_HFWRD_IMM)
		fatal("%d: brnch fmt not recognized", cat);
	else if (cat == ARM_CAT_BAX)
		fatal("%d: brnch fmt not recognized", cat);
	else if (cat == ARM_CAT_SDTR)
		fatal("%d: brnch fmt not recognized", cat);
	else if (cat == ARM_CAT_SDSWP)
		fatal("%d: brnch fmt not recognized", cat);
	else if (cat == ARM_CAT_CPR_RTR)
		fatal("%d: brnch fmt not recognized", cat);
	else if (cat == ARM_CAT_BRNCH)
		offset = (inst->dword.brnch_ins.off << 2);
	/* TODO: destinations for BDTR CDTR CDO*/
	else
		fatal("%d: brnch fmt not recognized", cat);

	str_printf(inst_str_ptr, inst_str_size, "%x",(inst_addr + offset + 8));
}

void arm_inst_dump_REGS(char **inst_str_ptr, int *inst_str_size,
	struct arm_inst_t *inst, enum arm_cat_enum cat)
{
	unsigned int reg_list;
	int i;

	if (cat == ARM_CAT_DPR_REG)
		fatal("%d: regs fmt not recognized", cat);
	else if (cat == ARM_CAT_DPR_IMM)
		fatal("%d: regs fmt not recognized", cat);
	else if (cat == ARM_CAT_DPR_SAT)
		fatal("%d: regs fmt not recognized", cat);
	else if (cat == ARM_CAT_PSR)
		fatal("%d: regs fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT)
		fatal("%d: regs fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT_SIGN)
		fatal("%d: regs fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT_LN)
		fatal("%d: regs fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT_LN_SIGN)
		fatal("%d: regs fmt not recognized", cat);
	else if (cat == ARM_CAT_HFWRD_REG)
		fatal("%d: regs fmt not recognized", cat);
	else if (cat == ARM_CAT_HFWRD_IMM)
		fatal("%d: regs fmt not recognized", cat);
	else if (cat == ARM_CAT_BAX)
		fatal("%d: regs fmt not recognized", cat);
	else if (cat == ARM_CAT_SDTR)
		fatal("%d: regs fmt not recognized", cat);
	else if (cat == ARM_CAT_BDTR)
		reg_list = inst->dword.bdtr_ins.reg_lst;
	else if (cat == ARM_CAT_SDSWP)
		fatal("%d: regs fmt not recognized", cat);
	else if (cat == ARM_CAT_CPR_RTR)
		fatal("%d: regs fmt not recognized", cat);
	else if (cat == ARM_CAT_BRNCH)
		fatal("%d: regs fmt not recognized", cat);
	/* TODO: destinations for CDTR CDO*/
	else
		fatal("%d: regs fmt not recognized", cat);

	str_printf(inst_str_ptr, inst_str_size, "{");
	for (i = 1; i < 65536; i *= 2)
	{
		if(reg_list & (i))
		{
			str_printf(inst_str_ptr, inst_str_size, "r%d ", log_base2(i));
		}
	}

	str_printf(inst_str_ptr, inst_str_size, "}");
}

void arm_inst_dump_IMMD24(char **inst_str_ptr, int *inst_str_size,
	struct arm_inst_t *inst, enum arm_cat_enum cat)
{
	unsigned int immd24;

	if (cat == ARM_CAT_DPR_REG)
		fatal("%d: swi_svc fmt not recognized", cat);
	else if (cat == ARM_CAT_DPR_IMM)
		fatal("%d: swi_svc fmt not recognized", cat);
	else if (cat == ARM_CAT_DPR_SAT)
		fatal("%d: swi_svc fmt not recognized", cat);
	else if (cat == ARM_CAT_PSR)
		fatal("%d: swi_svc fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT)
		fatal("%d: swi_svc fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT_SIGN)
		fatal("%d: swi_svc fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT_LN)
		fatal("%d: swi_svc fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT_LN_SIGN)
		fatal("%d: swi_svc fmt not recognized", cat);
	else if (cat == ARM_CAT_HFWRD_REG)
		fatal("%d: swi_svc fmt not recognized", cat);
	else if (cat == ARM_CAT_HFWRD_IMM)
		fatal("%d: swi_svc fmt not recognized", cat);
	else if (cat == ARM_CAT_BAX)
		fatal("%d: swi_svc fmt not recognized", cat);
	else if (cat == ARM_CAT_SDTR)
		fatal("%d: swi_svc fmt not recognized", cat);
	else if (cat == ARM_CAT_SDSWP)
		fatal("%d: swi_svc fmt not recognized", cat);
	else if (cat == ARM_CAT_CPR_RTR)
		fatal("%d: swi_svc fmt not recognized", cat);
	else if (cat == ARM_CAT_BRNCH)
		fatal("%d: swi_svc fmt not recognized", cat);
	else if (cat == ARM_CAT_SWI_SVC)
		immd24 = inst->dword.swi_svc_ins.cmnt;
	/* TODO: destinations for CDTR CDO*/
	else
		fatal("%d: swi_svc fmt not recognized", cat);

	str_printf(inst_str_ptr, inst_str_size, "0x%x",immd24);
}

void arm_inst_dump_IMMD16(char **inst_str_ptr, int *inst_str_size,
	struct arm_inst_t *inst, enum arm_cat_enum cat)
{
	unsigned int immd16;

	if (cat == ARM_CAT_DPR_REG)
		fatal("%d: movt_movw fmt not recognized", cat);
	else if (cat == ARM_CAT_DPR_IMM)
		immd16 = ((inst->dword.dpr_ins.op1_reg << 12)
			| inst->dword.dpr_ins.op2);
	else if (cat == ARM_CAT_DPR_SAT)
		fatal("%d: movt_movw fmt not recognized", cat);
	else if (cat == ARM_CAT_PSR)
		fatal("%d: movt_movw fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT)
		fatal("%d: movt_movw fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT_SIGN)
		fatal("%d: movt_movw fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT_LN)
		fatal("%d: movt_movw fmt not recognized", cat);
	else if (cat == ARM_CAT_MULT_LN_SIGN)
		fatal("%d: movt_movw fmt not recognized", cat);
	else if (cat == ARM_CAT_HFWRD_REG)
		fatal("%d: movt_movw fmt not recognized", cat);
	else if (cat == ARM_CAT_HFWRD_IMM)
		fatal("%d: movt_movw fmt not recognized", cat);
	else if (cat == ARM_CAT_BAX)
		fatal("%d: movt_movw fmt not recognized", cat);
	else if (cat == ARM_CAT_SDTR)
		fatal("%d: movt_movw fmt not recognized", cat);
	else if (cat == ARM_CAT_SDSWP)
		fatal("%d: movt_movw fmt not recognized", cat);
	else if (cat == ARM_CAT_CPR_RTR)
		fatal("%d: movt_movw fmt not recognized", cat);
	else if (cat == ARM_CAT_BRNCH)
		fatal("%d: movt_movw fmt not recognized", cat);
	else if (cat == ARM_CAT_SWI_SVC)
		fatal("%d: movt_movw fmt not recognized", cat);
	/* TODO: destinations for BDTR CDTR CDO*/
	else
		fatal("%d: movt_movw fmt not recognized", cat);

	str_printf(inst_str_ptr, inst_str_size, "#%d  ; 0x%x",immd16, immd16);
}

void arm_inst_dump_COPR(char **inst_str_ptr, int *inst_str_size,
	struct arm_inst_t *inst, enum arm_cat_enum cat)
{
	unsigned int copr;

	if (cat == ARM_CAT_CPR_RTR)
		copr = inst->dword.cpr_rtr_ins.cpr_num;
	else if (cat == ARM_CAT_CPR_DTR)
		copr = inst->dword.cpr_dtr_ins.cpr_num;
	/* TODO: destinations for BDTR CDTR CDO*/
	else
		fatal("%d: copr num fmt not recognized", cat);

	str_printf(inst_str_ptr, inst_str_size, "%d", copr);
}

void arm_inst_dump_AMODE_5(char **inst_str_ptr, int *inst_str_size,
	struct arm_inst_t *inst, enum arm_cat_enum cat)
{
	unsigned int offset;
	unsigned int rn;

	if (cat == ARM_CAT_CPR_RTR)
		fatal("%d: copr num fmt not recognized", cat);
	else if (cat == ARM_CAT_CPR_DTR)
		offset = inst->dword.cpr_dtr_ins.off;
	/* TODO: destinations for BDTR CDTR CDO*/
	else
		fatal("%d: amode5 fmt not recognized", cat);

	rn = inst->dword.cpr_dtr_ins.base_rn;
	if(offset)
	{
	str_printf(inst_str_ptr, inst_str_size, "[r%d], #%d", rn, offset*4);
	}
	else
		str_printf(inst_str_ptr, inst_str_size, "[r%d]", rn);
}

void arm_inst_dump_VFP1STM(char **inst_str_ptr, int *inst_str_size,
	struct arm_inst_t *inst, enum arm_cat_enum cat)
{
	unsigned int vfp1;

	if (cat == ARM_CAT_VFP)
		vfp1 = inst->dword.vfp_mv_ins.immd8;
	/* TODO: destinations for BDTR CDTR CDO*/
	else
		fatal("%d: vfp1 stm fmt not recognized", cat);

	if(vfp1 % 2)
		str_printf(inst_str_ptr, inst_str_size, "FSTMIAX");
	else
		str_printf(inst_str_ptr, inst_str_size, "VSTMIA");
}

void arm_inst_dump_VFP1LDM(char **inst_str_ptr, int *inst_str_size,
	struct arm_inst_t *inst, enum arm_cat_enum cat)
{
	unsigned int vfp1;

	if (cat == ARM_CAT_VFP)
		vfp1 = inst->dword.vfp_mv_ins.immd8;
	/* TODO: destinations for BDTR CDTR CDO*/
	else
		fatal("%d: vfp1 ldm fmt not recognized", cat);

	if(vfp1 % 2)
		str_printf(inst_str_ptr, inst_str_size, "FLDMIAX");
	else
		str_printf(inst_str_ptr, inst_str_size, "VLDMIA");
}

void arm_inst_dump_VFP_REGS(char **inst_str_ptr, int *inst_str_size,
	struct arm_inst_t *inst, enum arm_cat_enum cat)
{

	unsigned int immd8;
	unsigned int reg_start;
	if (cat == ARM_CAT_VFP)
	{
		immd8 = inst->dword.vfp_mv_ins.immd8;
		reg_start = ((inst->dword.vfp_mv_ins.d << 4)
			| (inst->dword.vfp_mv_ins.vd)) & (0x0000001f);
	}
	/* TODO: destinations for BDTR CDTR CDO*/
	else
		fatal("%d: vfp regs fmt not recognized", cat);

	str_printf(inst_str_ptr, inst_str_size, "{d%d-d%d}", reg_start,
		(reg_start + immd8/2 - 1));
}

void arm_inst_dump_FREG(char **inst_str_ptr, int *inst_str_size,
	struct arm_inst_t *inst, enum arm_cat_enum cat)
{
	unsigned int freg;


	if (cat == ARM_CAT_CPR_DTR)
		freg = inst->dword.cpr_dtr_ins.cpr_sr_dst;
	/* TODO: destinations for BDTR CDTR CDO*/
	else
		fatal("%d: freg fmt not recognized", cat);

	if(freg > 7)
		str_printf(inst_str_ptr, inst_str_size, "f%d", (freg-8));
	else
		str_printf(inst_str_ptr, inst_str_size, "f%d", freg);
}

void arm_inst_dump_FP(char **inst_str_ptr, int *inst_str_size,
	struct arm_inst_t *inst, enum arm_cat_enum cat)
{
	unsigned int freg;


	if (cat == ARM_CAT_CPR_DTR)
		freg = inst->dword.cpr_dtr_ins.cpr_sr_dst;
	/* TODO: destinations for BDTR CDTR CDO*/
	else
		fatal("%d: FP fmt not recognized", cat);

	if(freg > 7)
		str_printf(inst_str_ptr, inst_str_size, "P");
	else
		str_printf(inst_str_ptr, inst_str_size, "E");
}

void arm_inst_dump_RT(char **inst_str_ptr, int *inst_str_size,
	struct arm_inst_t *inst, enum arm_cat_enum cat)
{
	unsigned int rt;

	if (cat == ARM_CAT_VFP)
		rt = inst->dword.vfp_strreg_tr_ins.vfp_rt;
	/* TODO: destinations for BDTR CDTR CDO*/
	else
		fatal("%d: vfp rt fmt not recognized", cat);

	switch (rt)
		{
		case (r13):
			str_printf(inst_str_ptr, inst_str_size, "sp");
			break;
		case (r14):
			str_printf(inst_str_ptr, inst_str_size, "lr");
			break;
		case (r15):
			str_printf(inst_str_ptr, inst_str_size, "pc");
			break;
		default:
			str_printf(inst_str_ptr, inst_str_size, "r%d", rt);
			break;
		}
}

/*
 * Arm disassembler
 */

unsigned int arm_elf_function_symbol(struct elf_file_t *elf_file, unsigned int inst_addr, unsigned int prev_symbol)
{
	unsigned int i;
	struct elf_symbol_t *symbol;

	for ( i = 0; i < list_count(elf_file->symbol_table); i++)
	{
		symbol = (struct elf_symbol_t* )list_get(elf_file->symbol_table, i);
		if(symbol->value == inst_addr)
		{
			if((!strncmp(symbol->name, "$",1)))
			{
				continue;
			}
			else
			{
				//if(prev_symbol != symbol->value)
				{
					printf ("\n%08x <%s>\n", symbol->value, symbol->name);
					prev_symbol = symbol->value;
				}
				break;
			}
		}
	}
	return (prev_symbol);
}

unsigned int arm_dump_word_symbol(struct elf_file_t *elf_file, unsigned int inst_addr, void *inst_ptr)
{
	struct elf_symbol_t *symbol;
	unsigned int word_flag;
 	symbol = elf_symbol_get_by_address(elf_file, inst_addr,	NULL);

	if((!strncmp(symbol->name, "$d",2)))
	{
		printf (".word   0x%08x\n", *(unsigned int *)inst_ptr);
		word_flag = 1;
	}
	else
	{
		word_flag = 0;
	}

	return (word_flag);
}


void arm_emu_disasm(char *path)
{
	struct elf_file_t *elf_file;
	struct elf_section_t *section;

	char inst_str[MAX_STRING_SIZE];
	int i;
	unsigned int inst_index;
	unsigned int prev_symbol;
	void *inst_ptr;

	/* Initialization */
	arm_disasm_init();
	inst_index = 0;
	/* Find .text section which saves instruction bits */
	elf_file = elf_file_create_from_path(path);

	for (i = 0; i < list_count(elf_file->section_list); ++i)
	{
		section = (struct elf_section_t *)list_get(elf_file->section_list, i);
		if (!strncmp(section->name, ".text", 5))
			break;
	}
	if (i == list_count(elf_file->section_list))
		fatal(".text section not found!\n");

	/* Decode and dump instructions */
	for (inst_ptr = section->buffer.ptr; inst_ptr < section->buffer.ptr +
			section->buffer.size; inst_ptr += 4)
	{

		prev_symbol = arm_elf_function_symbol(elf_file, (section->header->sh_addr + inst_index), prev_symbol);

		arm_inst_hex_dump(stdout, inst_ptr, (section->header->sh_addr + inst_index));

		if (!arm_dump_word_symbol(elf_file, (section->header->sh_addr + inst_index),
			inst_ptr))
			arm_inst_dump(stdout, inst_str, MAX_STRING_SIZE, inst_ptr , inst_index,
				(section->header->sh_addr + inst_index));

		inst_index += 4;
	}

	/* Free external ELF */
	elf_file_free(elf_file);
}

/* Pointer to 'inst' is declared volatile to avoid optimizations when calling 'memset' */
void arm_disasm(void *buf, unsigned int ip, volatile struct arm_inst_t *inst)
{
	unsigned int byte_index;
	unsigned int arg1;
	unsigned int arg2;

	inst->addr = ip;
	for (byte_index = 0; byte_index < 4; ++byte_index)
		inst->dword.bytes[byte_index] = *(unsigned char *) (buf + byte_index);

	arg1 = ((inst->dword.bytes[3] & 0x0f) << 4) | ((inst->dword.bytes[2] & 0xf0) >> 4);

	arg2 = ((inst->dword.bytes[0] & 0xf0) >> 4);

	inst->info = &arm_inst_info[arg1 * 16 + arg2];

}

void arm_inst_debug_dump(struct arm_inst_t *inst, FILE *f )
{

	char inst_str[MAX_STRING_SIZE];
	void *inst_ptr;

	inst_ptr = &inst->dword.bytes;
	arm_inst_dump(f, inst_str, MAX_STRING_SIZE, inst_ptr, inst->addr, inst->addr);
}
