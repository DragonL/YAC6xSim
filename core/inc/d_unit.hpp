#ifndef CORE_D_UNIT_HPP
#define CORE_D_UNIT_HPP

#include "common/inc/def.hpp"
#include "core/inc/unit.hpp"

BEGIN_NS

// class DUnit ...
BEGIN_UNIT(D)
private:
  //inline static void decode_32bit_1or2_src(Core *core, code_t code, Instruction *inst);
  //inline static void decode_32bit_ext_1or2_src(Core *core, code_t code, Instruction *inst);
  //inline static void decode_32bit_ld_st_basic(Core *core, code_t code, Instruction *inst);
  //inline static void decode_32bit_ld_st_long_immed(Core *core, code_t code, Instruction *inst);

  inline static void decode_32bit_1or2_src2(Core *core, code_t code, Instruction *inst);
  inline static void decode_32bit_ext_1or2_src2(Core *core, code_t code, Instruction *inst);
  inline static void decode_32bit_ld_st_basic2(Core *core, code_t code, Instruction *inst);
  inline static void decode_32bit_ld_st_long_immed2(Core *core, code_t code, Instruction *inst);

public:
  DEF_DE_FUNC(de_32bit,general);

  static void decode2(Core *core, Instruction *inst);

  DEF_DE_FUNC(de_32bit_1or2_src,add_f1);
  DEF_DE_FUNC(de_32bit_1or2_src,add_f2);
  DEF_DE_FUNC(de_32bit_1or2_src,mvk);
  DEF_DE_FUNC(de_32bit_1or2_src,sub_f1);
  DEF_DE_FUNC(de_32bit_1or2_src,sub_f2);
  DEF_DE_FUNC(de_32bit_1or2_src,addab_f1);
  DEF_DE_FUNC(de_32bit_1or2_src,addab_f2);
  DEF_DE_FUNC(de_32bit_1or2_src,subab_f1);
  DEF_DE_FUNC(de_32bit_1or2_src,subab_f2);
  DEF_DE_FUNC(de_32bit_1or2_src,addah_f1);
  DEF_DE_FUNC(de_32bit_1or2_src,addah_f2);
  DEF_DE_FUNC(de_32bit_1or2_src,subah_f1);
  DEF_DE_FUNC(de_32bit_1or2_src,subah_f2);
  DEF_DE_FUNC(de_32bit_1or2_src,addaw_f1);
  DEF_DE_FUNC(de_32bit_1or2_src,addaw_f2);
  DEF_DE_FUNC(de_32bit_1or2_src,subaw_f1);
  DEF_DE_FUNC(de_32bit_1or2_src,subaw_f2);
  DEF_DE_FUNC(de_32bit_1or2_src,addad_f1);
  DEF_DE_FUNC(de_32bit_1or2_src,addad_f2);

  DEF_DE_FUNC(de_32bit_ext_1or2_src,andn);
  DEF_DE_FUNC(de_32bit_ext_1or2_src,or_f1);
  DEF_DE_FUNC(de_32bit_ext_1or2_src,or_f2);
  DEF_DE_FUNC(de_32bit_ext_1or2_src,add2);
  DEF_DE_FUNC(de_32bit_ext_1or2_src,sub2);
  DEF_DE_FUNC(de_32bit_ext_1or2_src,and_f1);
  DEF_DE_FUNC(de_32bit_ext_1or2_src,and_f2);
  DEF_DE_FUNC(de_32bit_ext_1or2_src,add_f1);
  DEF_DE_FUNC(de_32bit_ext_1or2_src,add_f2);
  DEF_DE_FUNC(de_32bit_ext_1or2_src,sub);
  DEF_DE_FUNC(de_32bit_ext_1or2_src,xor_f1);
  DEF_DE_FUNC(de_32bit_ext_1or2_src,xor_f2);

  DEF_DE_FUNC(de_32bit_ld_st_long_immed,ldb);
  DEF_DE_FUNC(de_32bit_ld_st_long_immed,ldbu);
  DEF_DE_FUNC(de_32bit_ld_st_long_immed,ldh);
  DEF_DE_FUNC(de_32bit_ld_st_long_immed,ldhu);
  DEF_DE_FUNC(de_32bit_ld_st_long_immed,ldw);
  DEF_DE_FUNC(de_32bit_ld_st_long_immed,stb);
  DEF_DE_FUNC(de_32bit_ld_st_long_immed,sth);
  DEF_DE_FUNC(de_32bit_ld_st_long_immed,stw);

  DEF_DE_FUNC(de_32bit_ld_st_basic,ldb_f1);
  DEF_DE_FUNC(de_32bit_ld_st_basic,ldbu_f1);
  DEF_DE_FUNC(de_32bit_ld_st_basic,ldh_f1);
  DEF_DE_FUNC(de_32bit_ld_st_basic,ldhu_f1); 
  DEF_DE_FUNC(de_32bit_ld_st_basic,ldw_f1);
  DEF_DE_FUNC(de_32bit_ld_st_basic,ldnw_f1);
  DEF_DE_FUNC(de_32bit_ld_st_basic,lddw_f1);
  DEF_DE_FUNC(de_32bit_ld_st_basic,ldndw_f1);
  DEF_DE_FUNC(de_32bit_ld_st_basic,stb_f1);
  DEF_DE_FUNC(de_32bit_ld_st_basic,sth_f1);
  DEF_DE_FUNC(de_32bit_ld_st_basic,stw_f1);
  DEF_DE_FUNC(de_32bit_ld_st_basic,stnw_f1);
  DEF_DE_FUNC(de_32bit_ld_st_basic,stdw_f1);
  DEF_DE_FUNC(de_32bit_ld_st_basic,stndw_f1);

  DEF_DE_FUNC(de_32bit_ld_st_basic,ldb_f2);
  DEF_DE_FUNC(de_32bit_ld_st_basic,ldbu_f2);
  DEF_DE_FUNC(de_32bit_ld_st_basic,ldh_f2);
  DEF_DE_FUNC(de_32bit_ld_st_basic,ldhu_f2); 
  DEF_DE_FUNC(de_32bit_ld_st_basic,ldw_f2_nc);
  DEF_DE_FUNC(de_32bit_ld_st_basic,ldw_f2_z0);
  DEF_DE_FUNC(de_32bit_ld_st_basic,ldw_f2_z1);
  DEF_DE_FUNC(de_32bit_ld_st_basic,ldnw_f2);
  DEF_DE_FUNC(de_32bit_ld_st_basic,lddw_f2);
  DEF_DE_FUNC(de_32bit_ld_st_basic,ldndw_f2);
  DEF_DE_FUNC(de_32bit_ld_st_basic,stb_f2);
  DEF_DE_FUNC(de_32bit_ld_st_basic,sth_f2);

  DEF_DE_FUNC(de_32bit_ld_st_basic,stw_f2_nc);
  DEF_DE_FUNC(de_32bit_ld_st_basic,stw_f2_z0);
  DEF_DE_FUNC(de_32bit_ld_st_basic,stw_f2_z1);

  DEF_DE_FUNC(de_32bit_ld_st_basic,stnw_f2);
  DEF_DE_FUNC(de_32bit_ld_st_basic,stdw_f2);
  DEF_DE_FUNC(de_32bit_ld_st_basic,stndw_f2);

END_UNIT(D)

END_NS
#endif // CORE_D_UNIT_HPP