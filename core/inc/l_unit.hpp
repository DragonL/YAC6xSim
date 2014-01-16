#ifndef CORE_L_UNIT_HPP
#define CORE_L_UNIT_HPP

#include "common/inc/def.hpp"
#include "core/inc/unit.hpp"

BEGIN_NS

// class LUnit ...
BEGIN_UNIT(L)
public:
  inline static void decode_32bit_unary(Core *core, code_t code, Instruction *inst);
  inline static void decode_32bit_1or2_src(Core *core, code_t code, Instruction *inst);

  DEF_DE_FUNC(de_32bit_unary,abs);
  DEF_DE_FUNC(de_32bit_unary,swap4);
  DEF_DE_FUNC(de_32bit_unary,unpklu4);
  DEF_DE_FUNC(de_32bit_unary,unpkhu4);
  DEF_DE_FUNC(de_32bit_unary,abs2);
  DEF_DE_FUNC(de_32bit_unary,mvk_nc); // mvk no-condition optimize
  DEF_DE_FUNC(de_32bit_unary,mvk_z0);
  DEF_DE_FUNC(de_32bit_unary,mvk_z1);

  DEF_DE_FUNC(de_32bit_1or2_src,cmpeq_f1);
  DEF_DE_FUNC(de_32bit_1or2_src,cmpeq_f2);
  DEF_DE_FUNC(de_32bit_1or2_src,cmpeq_f3);
  DEF_DE_FUNC(de_32bit_1or2_src,cmpeq_f4);

  DEF_DE_FUNC(de_32bit_1or2_src,cmpgtu_f1);
  DEF_DE_FUNC(de_32bit_1or2_src,cmpgtu_f2);
  DEF_DE_FUNC(de_32bit_1or2_src,cmpgtu_f3);
  DEF_DE_FUNC(de_32bit_1or2_src,cmpgtu_f4);

  DEF_DE_FUNC_NC_Z0_Z1(de_32bit_1or2_src,cmpltu_f1);
  DEF_DE_FUNC(de_32bit_1or2_src,cmpltu_f2);
  DEF_DE_FUNC(de_32bit_1or2_src,cmpltu_f3);
  DEF_DE_FUNC(de_32bit_1or2_src,cmpltu_f4);

  DEF_DE_FUNC(de_32bit_1or2_src,cmpgt_f1);
  DEF_DE_FUNC(de_32bit_1or2_src,cmpgt_f2);
  DEF_DE_FUNC(de_32bit_1or2_src,cmpgt_f3);
  DEF_DE_FUNC(de_32bit_1or2_src,cmpgt_f4);

  DEF_DE_FUNC(de_32bit_1or2_src,cmplt_f1);
  DEF_DE_FUNC(de_32bit_1or2_src,cmplt_f2);
  DEF_DE_FUNC(de_32bit_1or2_src,cmplt_f3);
  DEF_DE_FUNC(de_32bit_1or2_src,cmplt_f4);

  DEF_DE_FUNC(de_32bit_1or2_src,minu4);
  DEF_DE_FUNC(de_32bit_1or2_src,maxu4);

  DEF_DE_FUNC(de_32bit_1or2_src,min2);
  DEF_DE_FUNC(de_32bit_1or2_src,max2);

  DEF_DE_FUNC(de_32bit_1or2_src,lmbd_f1);
  DEF_DE_FUNC(de_32bit_1or2_src,lmbd_f2);

  DEF_DE_FUNC(de_32bit_1or2_src,norm_f1);
  DEF_DE_FUNC(de_32bit_1or2_src,norm_f2);

  DEF_DE_FUNC(de_32bit_1or2_src,or_f1);
  DEF_DE_FUNC(de_32bit_1or2_src,or_f2);
  DEF_DE_FUNC(de_32bit_1or2_src,or_f2_nc);

  DEF_DE_FUNC(de_32bit_1or2_src,pack2);
  DEF_DE_FUNC(de_32bit_1or2_src,packh2);

  DEF_DE_FUNC(de_32bit_1or2_src,shlmb);
  DEF_DE_FUNC(de_32bit_1or2_src,shrmb);

  DEF_DE_FUNC(de_32bit_1or2_src,packh4);
  DEF_DE_FUNC(de_32bit_1or2_src,packl4);

  DEF_DE_FUNC(de_32bit_1or2_src,packhl2);
  DEF_DE_FUNC(de_32bit_1or2_src,packlh2);

  DEF_DE_FUNC(de_32bit_1or2_src,sadd_f1);
  DEF_DE_FUNC(de_32bit_1or2_src,sadd_f2);
  DEF_DE_FUNC(de_32bit_1or2_src,sadd_f3);
  DEF_DE_FUNC(de_32bit_1or2_src,sadd_f4);

  DEF_DE_FUNC(de_32bit_1or2_src,ssub_f1);
  DEF_DE_FUNC(de_32bit_1or2_src,ssub_f2);
  DEF_DE_FUNC(de_32bit_1or2_src,ssub_f3);
  DEF_DE_FUNC(de_32bit_1or2_src,ssub_f4);

  DEF_DE_FUNC(de_32bit_1or2_src,sat);
  DEF_DE_FUNC(de_32bit_1or2_src,abs_slong);

  //DEF_DE_FUNC(de_32bit_1or2_src,sub_f1);
  DEF_DE_FUNC_NC_Z0_Z1(de_32bit_1or2_src,sub_f1);
  DEF_DE_FUNC(de_32bit_1or2_src,sub_f2);
  DEF_DE_FUNC(de_32bit_1or2_src,sub_f3);
  DEF_DE_FUNC(de_32bit_1or2_src,sub_f4);
  DEF_DE_FUNC(de_32bit_1or2_src,sub_f5);
  DEF_DE_FUNC(de_32bit_1or2_src,sub_f6);

  DEF_DE_FUNC(de_32bit_1or2_src,add_f1);
  DEF_DE_FUNC(de_32bit_1or2_src,add_f1_nc);
  DEF_DE_FUNC(de_32bit_1or2_src,add_f2_nc);
  DEF_DE_FUNC(de_32bit_1or2_src,add_f2_z0);
  DEF_DE_FUNC(de_32bit_1or2_src,add_f2_z1);
  DEF_DE_FUNC(de_32bit_1or2_src,add_f3);
  //DEF_DE_FUNC(de_32bit_1or2_src,add_f4);
  DEF_DE_FUNC(de_32bit_1or2_src,add_f4_nc);
  DEF_DE_FUNC(de_32bit_1or2_src,add_f4_z0);
  DEF_DE_FUNC(de_32bit_1or2_src,add_f4_z1);
  DEF_DE_FUNC(de_32bit_1or2_src,add_f5);

  DEF_DE_FUNC(de_32bit_1or2_src,addu_f1);
  DEF_DE_FUNC(de_32bit_1or2_src,addu_f2);
  DEF_DE_FUNC(de_32bit_1or2_src,add2);
  DEF_DE_FUNC(de_32bit_1or2_src,add4);

  DEF_DE_FUNC(de_32bit_1or2_src,andn);
  DEF_DE_FUNC(de_32bit_1or2_src,and_f1);
  DEF_DE_FUNC(de_32bit_1or2_src,and_f2);

  DEF_DE_FUNC(de_32bit_1or2_src,subabs4);

  DEF_DE_FUNC(de_32bit_1or2_src,subc);
  DEF_DE_FUNC(de_32bit_1or2_src,sub2);
  DEF_DE_FUNC(de_32bit_1or2_src,sub4);

  DEF_DE_FUNC(de_32bit_1or2_src,xor_f1);
  DEF_DE_FUNC(de_32bit_1or2_src,xor_f2);

  DEF_DE_FUNC(de_32bit_1or2_src,subu_f1);
  DEF_DE_FUNC(de_32bit_1or2_src,subu_f2);
END_UNIT(L)

END_NS
#endif // CORE_L_UNIT_HPP