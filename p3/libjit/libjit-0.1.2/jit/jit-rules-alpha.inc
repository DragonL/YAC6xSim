/* Automatically generated from ./jit-rules-alpha.ins - DO NOT EDIT */
/*
 * Copyright (C) 2004, 2006-2007  Southern Storm Software, Pty Ltd.
 *
 * This file is part of the libjit library.
 *
 * The libjit library is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * The libjit library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with the libjit library.  If not, see
 * <http://www.gnu.org/licenses/>.
*/

#if defined(JIT_INCLUDE_RULES)

case JIT_OP_TRUNC_SBYTE:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg;
	{
		_jit_regs_init(gen, &regs, 0);
		_jit_regs_init_dest(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		{
			alpha_slli(inst,reg,56,reg);
			alpha_srai(inst,reg,56,reg);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_TRUNC_UBYTE:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg;
	{
		_jit_regs_init(gen, &regs, 0);
		_jit_regs_init_dest(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		{
			_alpha_li8(inst,ALPHA_AT,0xff);
			alpha_and(inst,reg,ALPHA_AT,reg);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_TRUNC_SHORT:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg;
	{
		_jit_regs_init(gen, &regs, 0);
		_jit_regs_init_dest(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		{
			alpha_slli(inst,reg,56,reg);
			alpha_srai(inst,reg,56,reg);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_TRUNC_USHORT:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg;
	{
		_jit_regs_init(gen, &regs, 0);
		_jit_regs_init_dest(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		{
			alpha_slli(inst,reg,56,reg);
			alpha_srli(inst,reg,56,reg);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_IADD:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg, reg2, reg3;
	jit_nint imm_value;
	if(insn->value2->is_constant && (insn->value2->address == 0))
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_FREE_DEST);
		_jit_regs_init_dest(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_dest(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		imm_value = insn->value2->address;
		{
			alpha_mov(inst,reg2,reg);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
	else
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_FREE_DEST);
		_jit_regs_init_dest(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value2(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_dest(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		reg3 = _jit_reg_info[_jit_regs_get_value2(&regs)].cpu_reg;
		{
			alpha_addl(inst,reg3,reg2,reg);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_ISUB:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg, reg2, reg3;
	jit_nint imm_value;
	if(insn->value2->is_constant && (insn->value2->address == 0))
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_FREE_DEST);
		_jit_regs_init_dest(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_dest(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		imm_value = insn->value2->address;
		{
			alpha_mov(inst,reg2,reg);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
	else
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_FREE_DEST);
		_jit_regs_init_dest(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value2(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_dest(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		reg3 = _jit_reg_info[_jit_regs_get_value2(&regs)].cpu_reg;
		{
			alpha_subl(inst,reg3,reg2,reg);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_IMUL:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg, reg2, reg3;
	jit_nint imm_value;
	if(insn->value2->is_constant && (insn->value2->address == 1))
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_FREE_DEST);
		_jit_regs_init_dest(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_dest(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		imm_value = insn->value2->address;
		{
			alpha_mov(inst,reg2,reg);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
	else if(insn->value2->is_constant && (insn->value2->address == 0))
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_FREE_DEST);
		_jit_regs_init_dest(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_dest(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		imm_value = insn->value2->address;
		{
			alpha_clr(inst,reg);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
	else if(insn->value2->is_constant && (insn->value2->address == -1))
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_FREE_DEST);
		_jit_regs_init_dest(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_dest(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		imm_value = insn->value2->address;
		{
			alpha_subl(inst,reg,ALPHA_ZERO,reg2);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
	else
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_FREE_DEST);
		_jit_regs_init_dest(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value2(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_dest(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		reg3 = _jit_reg_info[_jit_regs_get_value2(&regs)].cpu_reg;
		{
			alpha_mull(inst,reg3,reg2,reg);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_INEG:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg;
	{
		_jit_regs_init(gen, &regs, 0);
		_jit_regs_init_dest(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		{
			/* Alpha has no neg operation, do reg = 0 - reg; instead */
			alpha_subl(inst,ALPHA_ZERO,reg,reg);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_LADD:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg, reg2, reg3;
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_FREE_DEST);
		_jit_regs_init_dest(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value2(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_dest(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		reg3 = _jit_reg_info[_jit_regs_get_value2(&regs)].cpu_reg;
		{
			alpha_addq(inst,reg3,reg2,reg);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_LSUB:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg, reg2, reg3;
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_FREE_DEST);
		_jit_regs_init_dest(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value2(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_dest(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		reg3 = _jit_reg_info[_jit_regs_get_value2(&regs)].cpu_reg;
		{
			alpha_subq(inst,reg3,reg2,reg);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_LMUL:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg, reg2, reg3;
	jit_nint imm_value;
	if(insn->value2->is_constant && (insn->value2->address == 1))
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_FREE_DEST);
		_jit_regs_init_dest(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_dest(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		imm_value = insn->value2->address;
		{
			alpha_mov(inst,reg2,reg);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
	else if(insn->value2->is_constant && (insn->value2->address == 0))
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_FREE_DEST);
		_jit_regs_init_dest(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_dest(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		imm_value = insn->value2->address;
		{
			alpha_clr(inst,reg);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
	else if(insn->value2->is_constant && (insn->value2->address == -1))
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_FREE_DEST);
		_jit_regs_init_dest(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_dest(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		imm_value = insn->value2->address;
		{
			alpha_subq(inst,reg,ALPHA_ZERO,reg2);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
	else
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_FREE_DEST);
		_jit_regs_init_dest(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value2(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_dest(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		reg3 = _jit_reg_info[_jit_regs_get_value2(&regs)].cpu_reg;
		{
			alpha_mulq(inst,reg3,reg2,reg);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_LNEG:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg;
	{
		_jit_regs_init(gen, &regs, 0);
		_jit_regs_init_dest(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		{
			/* Alpha has no neg operation, do reg = 0 - reg; instead */
			alpha_subq(inst,ALPHA_ZERO,reg,reg);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_IAND:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg, reg2, reg3;
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_FREE_DEST);
		_jit_regs_init_dest(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value2(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_dest(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		reg3 = _jit_reg_info[_jit_regs_get_value2(&regs)].cpu_reg;
		{
			alpha_and(inst,reg3,reg2,reg);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_IOR:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg, reg2, reg3;
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_FREE_DEST);
		_jit_regs_init_dest(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value2(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_dest(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		reg3 = _jit_reg_info[_jit_regs_get_value2(&regs)].cpu_reg;
		{
			alpha_or(inst,reg3,reg2,reg);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_IXOR:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg, reg2, reg3;
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_FREE_DEST);
		_jit_regs_init_dest(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value2(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_dest(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		reg3 = _jit_reg_info[_jit_regs_get_value2(&regs)].cpu_reg;
		{
			alpha_xor(inst,reg3,reg2,reg);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_INOT:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg;
	{
		_jit_regs_init(gen, &regs, 0);
		_jit_regs_init_dest(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		{
			_alpha_li32(inst,ALPHA_AT,0xffffffff);
			alpha_xor(inst,ALPHA_AT,reg,reg);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_LAND:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg, reg2, reg3;
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_FREE_DEST);
		_jit_regs_init_dest(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value2(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_dest(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		reg3 = _jit_reg_info[_jit_regs_get_value2(&regs)].cpu_reg;
		{
			alpha_and(inst,reg3,reg2,reg);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_LOR:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg, reg2, reg3;
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_FREE_DEST);
		_jit_regs_init_dest(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value2(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_dest(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		reg3 = _jit_reg_info[_jit_regs_get_value2(&regs)].cpu_reg;
		{
			alpha_or(inst,reg3,reg2,reg);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_LXOR:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg, reg2, reg3;
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_FREE_DEST);
		_jit_regs_init_dest(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value2(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_dest(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		reg3 = _jit_reg_info[_jit_regs_get_value2(&regs)].cpu_reg;
		{
			alpha_xor(inst,reg3,reg2,reg);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_LNOT:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg;
	{
		_jit_regs_init(gen, &regs, 0);
		_jit_regs_init_dest(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		{
			_alpha_li64(inst,ALPHA_AT,0xffffffff);
			alpha_xor(inst,ALPHA_AT,reg,reg);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_LSHL:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg, reg2, reg3;
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_FREE_DEST);
		_jit_regs_init_dest(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value2(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_dest(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		reg3 = _jit_reg_info[_jit_regs_get_value2(&regs)].cpu_reg;
		{
			alpha_sll(inst,reg3,reg2,reg);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_LSHR:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg, reg2, reg3;
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_FREE_DEST);
		_jit_regs_init_dest(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value2(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_dest(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		reg3 = _jit_reg_info[_jit_regs_get_value2(&regs)].cpu_reg;
		{
			alpha_srl(inst,reg3,reg2,reg);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_LSHR_UN:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg, reg2, reg3;
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_FREE_DEST);
		_jit_regs_init_dest(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value2(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_dest(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		reg3 = _jit_reg_info[_jit_regs_get_value2(&regs)].cpu_reg;
		{
			alpha_sra(inst,reg3,reg2,reg);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_BR:
{
	alpha_inst inst;
	{
		_jit_regs_spill_all(gen);
		jit_gen_load_inst_ptr(gen, inst);
		{
			/* branch if ALPHA_ZERO is zero (this is always true) */
			alpha_output_branch(func, inst, ALPHA_OP_BEQ, insn, ALPHA_ZERO);
		}
		jit_gen_save_inst_ptr(gen, inst);
	}
}
break;

case JIT_OP_BR_IFALSE:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg;
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_BRANCH);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		_jit_regs_clobber_all(gen, &regs);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		{
			/* banch if reg == 0 */
			alpha_output_branch(func, inst, ALPHA_OP_BEQ, insn, reg);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_BR_ITRUE:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg;
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_BRANCH);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		_jit_regs_clobber_all(gen, &regs);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		{
			/* branch if reg != 0 */
			alpha_output_branch(func, inst, ALPHA_OP_BNE, insn, reg);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_BR_IEQ:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg, reg2;
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_BRANCH);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value2(&regs, insn, 0, alpha_reg);
		_jit_regs_clobber_all(gen, &regs);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value2(&regs)].cpu_reg;
		{
			/* reg == reg2 -> $at */
			alpha_cmpeq(inst, reg, reg2, ALPHA_AT);
	
			/* branch if $at == 1 */
			alpha_output_branch(func, inst, ALPHA_OP_BEQ, insn, ALPHA_AT);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_BR_INE:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg, reg2;
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_BRANCH);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value2(&regs, insn, 0, alpha_reg);
		_jit_regs_clobber_all(gen, &regs);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value2(&regs)].cpu_reg;
		{
			/* reg == reg2 -> $at */
			alpha_cmpeq(inst, reg, reg2, ALPHA_AT);
	
			/* branch if $at == 0 */
			alpha_output_branch(func, inst, ALPHA_OP_BNE, insn, ALPHA_AT);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_BR_ILT:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg, reg2;
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_BRANCH);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value2(&regs, insn, 0, alpha_reg);
		_jit_regs_clobber_all(gen, &regs);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value2(&regs)].cpu_reg;
		{
			/* reg < reg2 -> $at */
			alpha_cmplt(inst, reg, reg2, ALPHA_AT);
	
			/* branch if $at == 1 */
			alpha_output_branch(func, inst, ALPHA_OP_BEQ, insn, ALPHA_AT);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_BR_ILT_UN:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg, reg2;
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_BRANCH);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value2(&regs, insn, 0, alpha_reg);
		_jit_regs_clobber_all(gen, &regs);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value2(&regs)].cpu_reg;
		{
			/* reg < reg2 -> $at */
			alpha_cmpult(inst, reg, reg2, ALPHA_AT);
	
			/* branch if $at == 1 */
			alpha_output_branch(func, inst, ALPHA_OP_BEQ, insn, ALPHA_AT);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_BR_ILE:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg, reg2;
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_BRANCH);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value2(&regs, insn, 0, alpha_reg);
		_jit_regs_clobber_all(gen, &regs);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value2(&regs)].cpu_reg;
		{
			/* reg <= reg2 -> $at */
			alpha_cmple(inst, reg, reg2, ALPHA_AT);
	
			/* branch if $at == 1 */
			alpha_output_branch(func, inst, ALPHA_OP_BEQ, insn, ALPHA_AT);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_BR_ILE_UN:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg, reg2;
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_BRANCH);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value2(&regs, insn, 0, alpha_reg);
		_jit_regs_clobber_all(gen, &regs);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value2(&regs)].cpu_reg;
		{
			/* reg <= reg2 -> $at */
			alpha_cmpule(inst, reg, reg2, ALPHA_AT);
	
			/* branch if $at == 1 */
			alpha_output_branch(func, inst, ALPHA_OP_BEQ, insn, ALPHA_AT);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_BR_IGT:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg, reg2;
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_BRANCH);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value2(&regs, insn, 0, alpha_reg);
		_jit_regs_clobber_all(gen, &regs);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value2(&regs)].cpu_reg;
		{
			/* reg <= reg2 -> $at */
			alpha_cmpgt(inst, reg, reg2, ALPHA_AT);
	
			/* branch if $at == 1 */
			alpha_output_branch(func, inst, ALPHA_OP_BEQ, insn, ALPHA_AT);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_BR_IGT_UN:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg, reg2;
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_BRANCH);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value2(&regs, insn, 0, alpha_reg);
		_jit_regs_clobber_all(gen, &regs);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value2(&regs)].cpu_reg;
		{
			/* reg > reg2 -> $at */
			alpha_cmpugt(inst, reg, reg2, ALPHA_AT);
	
			/* branch if $at == 1 */
			alpha_output_branch(func, inst, ALPHA_OP_BEQ, insn, ALPHA_AT);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_BR_IGE:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg, reg2;
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_BRANCH);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value2(&regs, insn, 0, alpha_reg);
		_jit_regs_clobber_all(gen, &regs);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value2(&regs)].cpu_reg;
		{
			/* reg >= reg2 -> $at */
			alpha_cmpge(inst, reg, reg2, ALPHA_AT);
	
			/* branch if $at == 1 */
			alpha_output_branch(func, inst, ALPHA_OP_BEQ, insn, ALPHA_AT);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_BR_IGE_UN:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg, reg2;
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_BRANCH);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value2(&regs, insn, 0, alpha_reg);
		_jit_regs_clobber_all(gen, &regs);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value2(&regs)].cpu_reg;
		{
			/* reg >= reg2 -> $at */
			alpha_cmpuge(inst, reg, reg2, ALPHA_AT);
	
			/* branch if $at == 1 */
			alpha_output_branch(func, inst, ALPHA_OP_BEQ, insn, ALPHA_AT);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_IEQ:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg, reg2, reg3;
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_FREE_DEST);
		_jit_regs_init_dest(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value2(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_dest(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		reg3 = _jit_reg_info[_jit_regs_get_value2(&regs)].cpu_reg;
		{
			alpha_cmpeq(inst,reg3,reg2,reg);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_INE:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg, reg2, reg3;
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_FREE_DEST);
		_jit_regs_init_dest(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value2(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_dest(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		reg3 = _jit_reg_info[_jit_regs_get_value2(&regs)].cpu_reg;
		{
			alpha_cmpeq(inst,reg3,reg2,reg);
			alpha_cmpeq(inst,reg,ALPHA_ZERO,reg);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_ILT:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg, reg2, reg3;
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_FREE_DEST);
		_jit_regs_init_dest(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value2(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_dest(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		reg3 = _jit_reg_info[_jit_regs_get_value2(&regs)].cpu_reg;
		{
			alpha_cmplt(inst,reg3,reg2,reg);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_ILT_UN:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg, reg2, reg3;
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_FREE_DEST);
		_jit_regs_init_dest(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value2(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_dest(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		reg3 = _jit_reg_info[_jit_regs_get_value2(&regs)].cpu_reg;
		{
			alpha_cmpult(inst,reg3,reg2,reg);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_ILE:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg, reg2, reg3;
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_FREE_DEST);
		_jit_regs_init_dest(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value2(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_dest(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		reg3 = _jit_reg_info[_jit_regs_get_value2(&regs)].cpu_reg;
		{
			alpha_cmple(inst,reg3,reg2,reg);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_ILE_UN:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg, reg2, reg3;
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_FREE_DEST);
		_jit_regs_init_dest(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		_jit_regs_init_value2(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_dest(&regs)].cpu_reg;
		reg2 = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		reg3 = _jit_reg_info[_jit_regs_get_value2(&regs)].cpu_reg;
		{
			alpha_cmpule(inst,reg3,reg2,reg);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_CALL:
{
	alpha_inst inst;
	{
		jit_gen_load_inst_ptr(gen, inst);
		{
			jit_function_t func = (jit_function_t)(insn->dest);
			alpha_call(inst, jit_function_to_closure(func));
		}
		jit_gen_save_inst_ptr(gen, inst);
	}
}
break;

case JIT_OP_RETURN:
{
	alpha_inst inst;
	{
		jit_gen_load_inst_ptr(gen, inst);
		{
			jump_to_epilog(gen, inst, block);
		}
		jit_gen_save_inst_ptr(gen, inst);
	}
}
break;

case JIT_OP_RETURN_INT:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg;
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_BRANCH);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		_jit_regs_clobber_all(gen, &regs);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		{
			alpha_mov(inst,reg,ALPHA_V0);
			jump_to_epilog(gen, inst, block);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_RETURN_LONG:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg;
	{
		_jit_regs_init(gen, &regs, _JIT_REGS_BRANCH);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		_jit_regs_clobber_all(gen, &regs);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		{
			alpha_mov(inst,reg,ALPHA_V0);
			jump_to_epilog(gen, inst, block);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_CALL_EXTERNAL:
{
	alpha_inst inst;
	{
		jit_gen_load_inst_ptr(gen, inst);
		{
			alpha_call(inst, (insn->dest));
		}
		jit_gen_save_inst_ptr(gen, inst);
	}
}
break;

case JIT_OP_RETURN_REG:
{
		{
			/* Nothing to do here */;
		}
}
break;

case JIT_OP_PUSH_INT:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg;
	jit_nint imm_value;
	if(insn->value1->is_constant)
	{
		jit_gen_load_inst_ptr(gen, inst);
		imm_value = insn->value1->address;
		{
			alpha_li(inst,ALPHA_AT,imm_value);
			alpha_stq(inst,ALPHA_AT,ALPHA_SP,0);
			alpha_lda(inst,ALPHA_SP,ALPHA_SP,-8);
		}
		jit_gen_save_inst_ptr(gen, inst);
	}
	else
	{
		_jit_regs_init(gen, &regs, 0);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		{
			alpha_stq(inst,reg,ALPHA_SP,0);
			alpha_lda(inst,ALPHA_SP,ALPHA_SP,-8);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_PUSH_LONG:
{
	alpha_inst inst;
	_jit_regs_t regs;
	int reg;
	jit_nint imm_value;
	if(insn->value1->is_constant)
	{
		jit_gen_load_inst_ptr(gen, inst);
		imm_value = insn->value1->address;
		{
			alpha_li(inst,ALPHA_AT,imm_value);
			alpha_stq(inst,ALPHA_AT,ALPHA_SP,0);
			alpha_lda(inst,ALPHA_SP,ALPHA_SP,-8);
		}
		jit_gen_save_inst_ptr(gen, inst);
	}
	else
	{
		_jit_regs_init(gen, &regs, 0);
		_jit_regs_init_value1(&regs, insn, 0, alpha_reg);
		if(!_jit_regs_assign(gen, &regs))
		{
			return;
		}
		if(!_jit_regs_gen(gen, &regs))
		{
			return;
		}
		jit_gen_load_inst_ptr(gen, inst);
		reg = _jit_reg_info[_jit_regs_get_value1(&regs)].cpu_reg;
		{
			alpha_stq(inst,reg,ALPHA_SP,0);
			alpha_lda(inst,ALPHA_SP,ALPHA_SP,-8);
		}
		jit_gen_save_inst_ptr(gen, inst);
		_jit_regs_commit(gen, &regs);
	}
}
break;

case JIT_OP_POP_STACK:
{
	alpha_inst inst;
	{
		jit_gen_load_inst_ptr(gen, inst);
		{
			alpha_lda(inst,ALPHA_SP,ALPHA_SP,insn->value1->address);
		}
		jit_gen_save_inst_ptr(gen, inst);
	}
}
break;

#elif defined(JIT_INCLUDE_SUPPORTED)

case JIT_OP_TRUNC_SBYTE:
case JIT_OP_TRUNC_UBYTE:
case JIT_OP_TRUNC_SHORT:
case JIT_OP_TRUNC_USHORT:
case JIT_OP_IADD:
case JIT_OP_ISUB:
case JIT_OP_IMUL:
case JIT_OP_INEG:
case JIT_OP_LADD:
case JIT_OP_LSUB:
case JIT_OP_LMUL:
case JIT_OP_LNEG:
case JIT_OP_IAND:
case JIT_OP_IOR:
case JIT_OP_IXOR:
case JIT_OP_INOT:
case JIT_OP_LAND:
case JIT_OP_LOR:
case JIT_OP_LXOR:
case JIT_OP_LNOT:
case JIT_OP_LSHL:
case JIT_OP_LSHR:
case JIT_OP_LSHR_UN:
case JIT_OP_BR:
case JIT_OP_BR_IFALSE:
case JIT_OP_BR_ITRUE:
case JIT_OP_BR_IEQ:
case JIT_OP_BR_INE:
case JIT_OP_BR_ILT:
case JIT_OP_BR_ILT_UN:
case JIT_OP_BR_ILE:
case JIT_OP_BR_ILE_UN:
case JIT_OP_BR_IGT:
case JIT_OP_BR_IGT_UN:
case JIT_OP_BR_IGE:
case JIT_OP_BR_IGE_UN:
case JIT_OP_IEQ:
case JIT_OP_INE:
case JIT_OP_ILT:
case JIT_OP_ILT_UN:
case JIT_OP_ILE:
case JIT_OP_ILE_UN:
case JIT_OP_CALL:
case JIT_OP_RETURN:
case JIT_OP_RETURN_INT:
case JIT_OP_RETURN_LONG:
case JIT_OP_CALL_EXTERNAL:
case JIT_OP_RETURN_REG:
case JIT_OP_PUSH_INT:
case JIT_OP_PUSH_LONG:
case JIT_OP_POP_STACK:
	return 1;

#endif
