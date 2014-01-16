#include "core/inc/n_unit.hpp"
#include "core/inc/core.hpp"

BEGIN_NS

void NoneUnit::decode(Core *core, Instruction *inst)
{
  op_code_t type = (op_code_t)inst->get_op_type();
  word_t code = inst->get_code();

  if(type == OP_N_UNIT_32BIT_IDLE_NOP)
  {
    word_t src = get_uint(code,13,4);
    inst->set_de_func(DE_FUNC_ADDR(NoneUnit,de_32bit,nop));
    inst->set_src1(src);
    inst->set_nop_count(src);
    //inst->set_de_func(JIT::gen_nu_de_32bit_nop(core,inst));
  }
  else
  {
    core->panic("NUnit");
  }
}

DE_FUNC(NoneUnit,de_32bit,nop)
{
  NO_CONDITION();
  if(src1 > core->get_nop_remains())
  {
    core->set_nop_remains(src1);
  }
}


END_NS