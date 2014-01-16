#ifndef CORE_M_UNIT_HPP
#define CORE_M_UNIT_HPP

#include "common/inc/def.hpp"
#include "core/inc/unit.hpp"

BEGIN_NS

// class MUnit ...
BEGIN_UNIT(M)
private:
  inline static void decode_32bit_ext_compound(Core *pCore,code_t code,Instruction *inst);
  inline static void decode_32bit_ext_unary(Core *pCore,code_t code,Instruction *inst);
  inline static void decode_32bit_mpy(Core *pCore,code_t code,Instruction *inst);

public:
  DEF_DE_FUNC(de_32bit_ext_compound,avg2);
  DEF_DE_FUNC(de_32bit_ext_compound,avgu4);
  DEF_DE_FUNC(de_32bit_ext_compound,dotp2_f1);
  DEF_DE_FUNC(de_32bit_ext_compound,dotp2_f2);
  DEF_DE_FUNC(de_32bit_ext_compound,dotpn2);
  DEF_DE_FUNC(de_32bit_ext_compound,dotpnrsu2);
  DEF_DE_FUNC(de_32bit_ext_compound,dotprsu2);
  DEF_DE_FUNC(de_32bit_ext_compound,dotpsu4);
  DEF_DE_FUNC(de_32bit_ext_compound,dotpu4);
  DEF_DE_FUNC(de_32bit_ext_compound,mpyhi);
  DEF_DE_FUNC(de_32bit_ext_compound,mpyhir);
  DEF_DE_FUNC(de_32bit_ext_compound,mpyli);
  DEF_DE_FUNC(de_32bit_ext_compound,mpylir);
  DEF_DE_FUNC(de_32bit_ext_compound,mpysu4);
  DEF_DE_FUNC(de_32bit_ext_compound,mpyu4);
  DEF_DE_FUNC(de_32bit_ext_compound,mpy2);
  DEF_DE_FUNC(de_32bit_ext_compound,rotl_f1);
  DEF_DE_FUNC(de_32bit_ext_compound,rotl_f2);
  DEF_DE_FUNC(de_32bit_ext_compound,sshvr);

  DEF_DE_FUNC(de_32bit_ext_unary,bitc4);
  DEF_DE_FUNC(de_32bit_ext_unary,bitr);
  DEF_DE_FUNC(de_32bit_ext_unary,deal);
  DEF_DE_FUNC(de_32bit_ext_unary,shfl);
  DEF_DE_FUNC(de_32bit_ext_unary,mvd);
  DEF_DE_FUNC(de_32bit_ext_unary,xpnd2);
  DEF_DE_FUNC(de_32bit_ext_unary,xpnd4);

  DEF_DE_FUNC(de_32bit_mpy,mpy_f1);
  DEF_DE_FUNC(de_32bit_mpy,mpy_f2); // scst5
  DEF_DE_FUNC(de_32bit_mpy,mpyh);
  DEF_DE_FUNC(de_32bit_mpy,mpyhl);
  DEF_DE_FUNC(de_32bit_mpy,mpyhlu);
  DEF_DE_FUNC(de_32bit_mpy,mpyhslu);
  DEF_DE_FUNC(de_32bit_mpy,mpyhsu);
  DEF_DE_FUNC(de_32bit_mpy,mpyhu);
  DEF_DE_FUNC(de_32bit_mpy,mpyhuls);
  DEF_DE_FUNC(de_32bit_mpy,mpyhus);

  DEF_DE_FUNC(de_32bit_mpy,mpylh_nc);
  DEF_DE_FUNC(de_32bit_mpy,mpylh_z0);
  DEF_DE_FUNC(de_32bit_mpy,mpylh_z1);

  DEF_DE_FUNC(de_32bit_mpy,mpylshu);
  DEF_DE_FUNC(de_32bit_mpy,mpyluhs);
  DEF_DE_FUNC(de_32bit_mpy,mpylhu);
  DEF_DE_FUNC(de_32bit_mpy,mpysu_f1);
  DEF_DE_FUNC(de_32bit_mpy,mpysu_f2);
  DEF_DE_FUNC(de_32bit_mpy,mpyus);
  DEF_DE_FUNC(de_32bit_mpy,mpyu);

  DEF_DE_FUNC(de_32bit_mpy,smpyh);
  DEF_DE_FUNC(de_32bit_mpy,smpy);
  DEF_DE_FUNC(de_32bit_mpy,smpylh);
  DEF_DE_FUNC(de_32bit_mpy,smpyhl);
END_UNIT(M)

END_NS
#endif // CORE_M_UNIT_HPP