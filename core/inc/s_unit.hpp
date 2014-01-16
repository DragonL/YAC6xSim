#ifndef CORE_S_UNIT_HPP
#define CORE_S_UNIT_HPP

#include "common/inc/def.hpp"
#include "core/inc/unit.hpp"

BEGIN_NS

// class SUnit ...
BEGIN_UNIT(S)
public:
  inline static void decode_32bit_1or2_src(Core *core, code_t code, Instruction *inst);
  inline static void decode_32bit_addk(Core *core, code_t code, Instruction *inst);
  inline static void decode_32bit_addkpc(Core *core, code_t code, Instruction *inst);
  inline static void decode_32bit_ext_1or2_src(Core *core, code_t code, Instruction *inst);
  inline static void decode_32bit_b_disp(Core *core, code_t code, Instruction *inst);
  inline static void decode_32bit_b_reg(Core *core, code_t code, Instruction *inst);
  inline static void decode_32bit_b_ptr(Core *core, code_t code, Instruction *inst);
  inline static void decode_32bit_bdec_or_bpos(Core *core, code_t code, Instruction *inst);
  inline static void decode_32bit_bnop_disp(Core *core, code_t code, Instruction *inst);
  inline static void decode_32bit_bnop_reg(Core *core, code_t code, Instruction *inst);
  inline static void decode_32bit_mvk_mvkh(Core *core, code_t code, Instruction *inst);
  inline static void decode_32bit_unary(Core *core, code_t code, Instruction *inst);
  inline static void decode_32bit_field_op(Core *core, code_t code, Instruction *inst);

  DEF_DE_FUNC(de_32bit_1or2_src,clr);
  DEF_DE_FUNC(de_32bit_1or2_src,set);
  DEF_DE_FUNC(de_32bit_1or2_src,shr_f1);
  DEF_DE_FUNC(de_32bit_1or2_src,shr_f2);
  DEF_DE_FUNC(de_32bit_1or2_src,shr_f3);
  DEF_DE_FUNC(de_32bit_1or2_src,shr_f4);
  DEF_DE_FUNC(de_32bit_1or2_src,shl_f1);
  DEF_DE_FUNC(de_32bit_1or2_src,shl_f2);
  DEF_DE_FUNC(de_32bit_1or2_src,shl_f2_nc); // none-condition opt
  DEF_DE_FUNC(de_32bit_1or2_src,shl_f3);
  DEF_DE_FUNC(de_32bit_1or2_src,shl_f4);
  DEF_DE_FUNC(de_32bit_1or2_src,shl_f5);
  DEF_DE_FUNC(de_32bit_1or2_src,shl_f6);
  DEF_DE_FUNC(de_32bit_1or2_src,ext);
  DEF_DE_FUNC(de_32bit_1or2_src,extu);
  DEF_DE_FUNC(de_32bit_1or2_src,shru_f1);
  DEF_DE_FUNC(de_32bit_1or2_src,shru_f2);
  DEF_DE_FUNC(de_32bit_1or2_src,shru_f3);
  DEF_DE_FUNC(de_32bit_1or2_src,shru_f4);
  DEF_DE_FUNC(de_32bit_1or2_src,sshl_f1);
  DEF_DE_FUNC(de_32bit_1or2_src,sshl_f2);
  DEF_DE_FUNC(de_32bit_1or2_src,sadd);
  DEF_DE_FUNC(de_32bit_1or2_src,and_f1);
  DEF_DE_FUNC(de_32bit_1or2_src,and_f2);
  DEF_DE_FUNC(de_32bit_1or2_src,packlh2);
  DEF_DE_FUNC(de_32bit_1or2_src,packhl2);
  DEF_DE_FUNC(de_32bit_1or2_src,packh2);
  DEF_DE_FUNC(de_32bit_1or2_src,xor_f1);
  DEF_DE_FUNC(de_32bit_1or2_src,xor_f2);
  DEF_DE_FUNC(de_32bit_1or2_src,cmpeq2);
  DEF_DE_FUNC(de_32bit_1or2_src,cmpeq4);
  DEF_DE_FUNC(de_32bit_1or2_src,or_f1);
  DEF_DE_FUNC(de_32bit_1or2_src,or_f2);
  DEF_DE_FUNC(de_32bit_1or2_src,sub_f1);
  DEF_DE_FUNC(de_32bit_1or2_src,sub_f2);
  DEF_DE_FUNC(de_32bit_1or2_src,cmpgtu4);
  DEF_DE_FUNC(de_32bit_1or2_src,cmpgt2);
  DEF_DE_FUNC(de_32bit_1or2_src,sub2);
  DEF_DE_FUNC(de_32bit_1or2_src,mvc_f1);
  DEF_DE_FUNC(de_32bit_1or2_src,mvc_f2);
  DEF_DE_FUNC(de_32bit_1or2_src,add_f1);
  DEF_DE_FUNC(de_32bit_1or2_src,add_f2_nc);
  DEF_DE_FUNC(de_32bit_1or2_src,add_f2_z0);
  DEF_DE_FUNC(de_32bit_1or2_src,add_f2_z1);
  DEF_DE_FUNC(de_32bit_1or2_src,add2);

  DEF_DE_FUNC(de_32bit,addk);
  DEF_DE_FUNC(de_32bit,addkpc);

  DEF_DE_FUNC(de_32bit,b_disp_nc);
  DEF_DE_FUNC(de_32bit,b_disp_z0);
  DEF_DE_FUNC(de_32bit,b_disp_z1);

  DEF_DE_FUNC(de_32bit,b_reg);
  DEF_DE_FUNC(de_32bit,b_ptr);
  DEF_DE_FUNC(de_32bit,b_dec);
  DEF_DE_FUNC(de_32bit,b_pos); // TODO

  DEF_DE_FUNC(de_32bit,bnop_disp_nc);
  DEF_DE_FUNC(de_32bit,bnop_disp_z0);
  DEF_DE_FUNC(de_32bit,bnop_disp_z1);

  DEF_DE_FUNC(de_32bit,bnop_reg);
  DEF_DE_FUNC(de_32bit,mvk_nc);
  DEF_DE_FUNC(de_32bit,mvk_z0);
  DEF_DE_FUNC(de_32bit,mvk_z1);
  DEF_DE_FUNC(de_32bit,mvkh);

  DEF_DE_FUNC(de_32bit_unary,unpkhu4);
  DEF_DE_FUNC(de_32bit_unary,unpklu4);

  DEF_DE_FUNC(de_32bit_fop,clr);
  DEF_DE_FUNC(de_32bit_fop,ext);
  DEF_DE_FUNC(de_32bit_fop,extu);
  DEF_DE_FUNC(de_32bit_fop,set);

  DEF_DE_FUNC(de_32bit_ext_1or2_src,andn);
  DEF_DE_FUNC(de_32bit_ext_1or2_src,sub);
  DEF_DE_FUNC(de_32bit_ext_1or2_src,shlmb);
  DEF_DE_FUNC(de_32bit_ext_1or2_src,shr2);
  DEF_DE_FUNC(de_32bit_ext_1or2_src,shrmb);
  DEF_DE_FUNC(de_32bit_ext_1or2_src,shru2);
  DEF_DE_FUNC(de_32bit_ext_1or2_src,pack2);
  DEF_DE_FUNC(de_32bit_ext_1or2_src,sadd2);
  DEF_DE_FUNC(de_32bit_ext_1or2_src,saddu4);
  DEF_DE_FUNC(de_32bit_ext_1or2_src,saddsu2);
END_UNIT(S)

END_NS
#endif // CORE_S_UNIT_HPP