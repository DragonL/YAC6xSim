#ifndef CORE_UNIT_HPP
#define CORE_UNIT_HPP

#include "common/inc/def.hpp"
#include "decode/inc/inst.hpp"

BEGIN_NS
class Core;

class Unit
{
protected:
  int _id;
public:
  Unit(int id):_id(id){}
  inline int get_id()
  {
    return _id;
  }
  static bool not_cond(Core *core, Instruction *inst);
  static bool not_cond2(Core *core, Instruction *inst);
  static bool not_cond_z0(Core *core, Instruction *inst);
  static bool not_cond_z1(Core *core, Instruction *inst);
  static word_t* get_cond_reg_addr(Core *core, word_t creg_z);
};

#define BEGIN_UNIT(U) \
class U##Unit : public Unit{\
public:\
  U##Unit(int id):Unit(id){}\
  static void decode(Core*,Instruction*);\
private:\
  U##Unit();

#define END_UNIT(U) \
};

#define DEF_DE_FUNC(prefix,name) \
  static void DE_FUNC_CALL_TYPE  prefix##_##name(Core*,Instruction*)

#define DEF_DE_FUNC_NC_Z0_Z1(prefix,name) \
  static void DE_FUNC_CALL_TYPE  prefix##_##name##_##nc(Core*,Instruction*);\
  static void DE_FUNC_CALL_TYPE  prefix##_##name##_##z0(Core*,Instruction*);\
  static void DE_FUNC_CALL_TYPE  prefix##_##name##_##z1(Core*,Instruction*)

#define DE_FUNC(klass,prefix,name) \
  void DE_FUNC_CALL_TYPE klass::prefix##_##name(Core* core,Instruction* inst)

#define DE_FUNC_ADDR(klass,prefix,name) \
  klass::prefix##_##name

#define SET_DE_FUNC_NC_Z0_Z1(cregz,klass,prefix,name)\
{\
  if(cregz == 0)\
  {\
    de_func = DE_FUNC_ADDR(klass,prefix,name##_##nc);\
  }\
  else if((cregz & 0x1) == 0)\
  {\
    de_func = DE_FUNC_ADDR(klass,prefix,name##_##z0);\
  }\
  else\
  {\
    de_func = DE_FUNC_ADDR(klass,prefix,name##_##z1);\
  }\
}

#define SET_DE_FUNC_NC_Z(cregz,klass,prefix,name)\
{\
  if(cregz == 0)\
  {\
    de_func = DE_FUNC_ADDR(klass,prefix,name##_##nc);\
  }\
  else\
  {\
    de_func = DE_FUNC_ADDR(klass,prefix,name);\
  }\
}

#define SET_DE_FUNC(cregz,klass,prefix,name)\
{\
  de_func = DE_FUNC_ADDR(klass,prefix,name);\
}

#define NO_CONDITION() \
  const word_t cregz = inst->get_cregz();\
  const word_t src1 = inst->get_src1();\
  const word_t src2 = inst->get_src2();\
  const word_t dst = inst->get_dst();\
  const word_t side = inst->get_side();\
  const word_t xside = inst->get_xside();

inline bool Unit::not_cond(Core *core, Instruction *inst)
{
  const byte_t creg_z = inst->get_cregz();
  if(creg_z == 0)
  {
    return false;
  }
  return (creg_z & 0x1) ^ (*inst->get_cond_reg_phy_addr() == 0);
} // z == 0 && reg == 0

inline bool Unit::not_cond_z0(Core *core, Instruction *inst)
{
  return (*inst->get_cond_reg_phy_addr() == 0);
}

inline bool Unit::not_cond_z1(Core *core, Instruction *inst)
{
  return (*inst->get_cond_reg_phy_addr() != 0);
}

//(creg_z & 0x1)
inline bool Unit::not_cond2(Core *core, Instruction *inst)
{
  const byte_t creg_z = inst->get_cregz();
  return (creg_z & 0x1) ^ (*inst->get_cond_reg_phy_addr() == 0);
}

#define DE_CONDITION(core,cregz) \
  if(not_cond(core,inst)) \
  {\
    return;\
  }\
  const word_t src1 = inst->get_src1();\
  const word_t src2 = inst->get_src2();\
  const word_t dst = inst->get_dst();\
  const word_t side = inst->get_side();\
  const word_t xside = inst->get_xside();

#define DE_CONDITION_Z0(core) \
  if(not_cond_z0(core,inst)) \
  {\
    return;\
  }\
  const word_t src1 = inst->get_src1();\
  const word_t src2 = inst->get_src2();\
  const word_t dst = inst->get_dst();\
  const word_t side = inst->get_side();\
  const word_t xside = inst->get_xside();

#define DE_CONDITION_Z1(core) \
  if(not_cond_z1(core,inst)) \
  {\
    return;\
  }\
  const word_t src1 = inst->get_src1();\
  const word_t src2 = inst->get_src2();\
  const word_t dst = inst->get_dst();\
  const word_t side = inst->get_side();\
  const word_t xside = inst->get_xside();

#define DE_CONDITION_BRANCH(core,cregz) \
  Core::dummy_or_real_jmp_delay_cycles = 6;\
  if(not_cond(core,inst)) \
  {\
    return;\
  }\
  const word_t src1 = inst->get_src1();\
  const word_t src2 = inst->get_src2();\
  const word_t dst = inst->get_dst();\
  const word_t side = inst->get_side();\
  const word_t xside = inst->get_xside();

#define DE_CONDITION_BRANCH_NC(core,cregz) \
  Core::dummy_or_real_jmp_delay_cycles = 6;\
  const word_t src1 = inst->get_src1();\
  const word_t src2 = inst->get_src2();\
  const word_t dst = inst->get_dst();\
  const word_t side = inst->get_side();\
  const word_t xside = inst->get_xside();

#define DE_CONDITION_BRANCH2(core,cregz) \
  Core::dummy_or_real_jmp_delay_cycles = 6;\
  if(not_cond2(core,inst)) \
  {\
    return;\
  }\
  const word_t src1 = inst->get_src1();\
  const word_t src2 = inst->get_src2();\
  const word_t dst = inst->get_dst();\
  const word_t side = inst->get_side();\
  const word_t xside = inst->get_xside();

#define DE_CONDITION_BRANCH_Z0(core,cregz) \
  Core::dummy_or_real_jmp_delay_cycles = 6;\
  if(not_cond_z0(core,inst)) \
  {\
    return;\
  }\
  const word_t src1 = inst->get_src1();\
  const word_t src2 = inst->get_src2();\
  const word_t dst = inst->get_dst();\
  const word_t side = inst->get_side();\
  const word_t xside = inst->get_xside();

#define DE_CONDITION_BRANCH_Z1(core,cregz) \
  Core::dummy_or_real_jmp_delay_cycles = 6;\
  if(not_cond_z1(core,inst)) \
  {\
    return;\
  }\
  const word_t src1 = inst->get_src1();\
  const word_t src2 = inst->get_src2();\
  const word_t dst = inst->get_dst();\
  const word_t side = inst->get_side();\
  const word_t xside = inst->get_xside();

#define DE_CONDITION2(core,cregz) \
  if(not_cond2(core,inst)) \
  {\
    return;\
  }\
  const word_t src1 = inst->get_src1();\
  const word_t src2 = inst->get_src2();\
  const word_t dst = inst->get_dst();\
  const word_t side = inst->get_side();\
  const word_t xside = inst->get_xside();

#define DE_UPDATE_REG2(side,dst,dst_qval) \
  do \
  {\
    word_t dst_val = dst_qval & 0xFFFFFFFF;\
    word_t dst2_val = dst_qval >> 32;\
    core->push_reg_ch(side,dst,dst_val);\
    core->push_reg_ch(side,dst+1,dst2_val);\
  }\
  while(0)

#define DE_UPDATE_DELAY_REG2(side,dst,dst_qval,delay) \
  do \
  {\
    word_t dst_val = dst_qval & 0xFFFFFFFF;\
    word_t dst2_val = dst_qval >> 32;\
    core->push_reg_delay_ch(side,dst,dst_val,delay);\
    core->push_reg_delay_ch(side,dst+1,dst2_val,delay);\
  }\
  while(0)

END_NS

#endif // OCRE_UNIT_HPP