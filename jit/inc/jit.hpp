#ifndef JIT_JIT_HPP
#define JIT_JIT_HPP

#include "jit/jit.h"
#include "common/inc/def.hpp"

BEGIN_NS

struct BasicBlock;
class Instruction;
class JIT2
{
public:
  static void compile_basic_block(Core *core,BasicBlock *bb);
  static void compile_addr(Core *core,md_addr_t addr);
  static void init(Core*);

public:
  static jit_context_t jit_context;
  static jit_function_t jit_current_func;
  static Instruction *current_inst;
  static Instruction *prev_inst;

private:
  static void compile_reg_ch();
  static void compile_stw_proc();
  static void compile_stw();

  static void compile_inst_with_cond(Core *core,word_t creg_z);

  static void compile_push_reg_ch(word_t side,word_t idx,jit_value_t jit_val);
  static void compile_push_stw_req(jit_value_t jit_mem_addr,jit_value_t jit_mem_type,jit_value_t jit_val);

  static void compile_du_32bit_ld_st_basic();
  
  static void compile_prolog_proc();
  static void compile_bb_combined_prolog_proc();
  static void compile_epilog_proc();
  static void compile_prolog_and_epilog_proc();
  static void compile_update_pc(word_t pc_diff);
  static void compile_update_inst_num();

  static jit_value_t compile_cond_val(Core *core,word_t creg_z);
  static void compile_current_inst();

  static jit_value_t compile_int(jit_nint int_val);
  static jit_value_t compile_uint(jit_nint uint_val);
  static jit_value_t compile_ulong(jit_ulong ul_val);
  static jit_value_t compile_ptr(word_t *ptr);
  static jit_value_t compile_byte_ptr(byte_t *ptr);
  static void jit_push_stw_req(jit_value_t jit_addr,jit_value_t jit_val,mem_type_t type);
  static void jit_push_reg_ch(word_t side,word_t idx,jit_value_t jit_val);
  static void jit_push_reg_ch2(jit_value_t jit_val);
  static void jit_push_reg_pair_ch(word_t side,word_t idx,jit_value_t jit_val);
  static void jit_compile_push_reg_delay_ch(word_t side,word_t idx,jit_value_t jit_val,word_t delay);
  static void jit_compile_push_reg_delay_ch2(jit_value_t jit_val,word_t delay);

private:
  //helper functions
  static jit_value_t compile_reg_read(word_t side,word_t idx);
  static jit_value_t compile_reg_read_src1();
  static jit_value_t compile_reg_read_dst();
  static jit_value_t compile_reg_read_xsrc1();
  static jit_value_t compile_reg_read_xsrc2();
  static jit_value_t compile_type_convert(jit_value_t jit_val,jit_type_t jit_type);

  static jit_value_t jit_compile_get_uint(jit_value_t,word_t,word_t);
  static jit_value_t jit_compile_clr(jit_value_t,jit_value_t,jit_value_t);
  static jit_value_t jit_compile_get_sign_ext_lsb16(jit_value_t);
  static jit_value_t jit_compile_get_sign_ext_msb16(jit_value_t);
  static jit_value_t jit_compile_get_lsb16(jit_value_t);
  static jit_value_t jit_compile_get_msb16(jit_value_t);
  static jit_value_t jit_compile_get_sign_ext_lsb5(jit_value_t);

  static jit_value_t jit_compile_du_mode_proc(word_t mode,word_t offset_factor,
    jit_value_t jit_offset,jit_value_t jit_base_addr);

  static jit_value_t jit_compile_l2_mem_read_word(jit_value_t jit_addr);
  static void jit_compile_l2_mem_write_byte(jit_value_t jit_addr,jit_value_t jit_val);
  static void jit_compile_l2_mem_write_xhalf(jit_value_t jit_addr,jit_value_t jit_val);
  static void jit_compile_l2_mem_write_xword(jit_value_t jit_addr,jit_value_t jit_val);
  static void jit_compile_l2_mem_write_xqword(jit_value_t jit_addr,jit_value_t jit_val);
  static jit_value_t jit_compile_bswap_uint(jit_value_t jit_val);

  static void jit_compile_de_func_general();

  //JIT compile func

  //SUnit
  static void jit_compile_su_de_32bit_1or2_src_clr();
  static void jit_compile_su_de_32bit_1or2_src_set();
  static void jit_compile_su_de_32bit_1or2_src_shr_f1();
  static void jit_compile_su_de_32bit_1or2_src_shr_f2();
  static void jit_compile_su_de_32bit_1or2_src_shr_f3();
  static void jit_compile_su_de_32bit_1or2_src_shr_f4();
  static void jit_compile_su_de_32bit_1or2_src_shl_f1();
  static inline void jit_compile_su_de_32bit_1or2_src_shl_f2_general(); // helper
  static void jit_compile_su_de_32bit_1or2_src_shl_f2();
  static void jit_compile_su_de_32bit_1or2_src_shl_f2_nc();
  static void jit_compile_su_de_32bit_1or2_src_shl_f3();
  static void jit_compile_su_de_32bit_1or2_src_shl_f4();
  static void jit_compile_su_de_32bit_1or2_src_ext();
  static void jit_compile_su_de_32bit_1or2_src_extu();
  static void jit_compile_su_de_32bit_1or2_src_shru_f1();
  static void jit_compile_su_de_32bit_1or2_src_shru_f2();
  static void jit_compile_su_de_32bit_1or2_src_shru_f3();
  static void jit_compile_su_de_32bit_1or2_src_shru_f4();
  static void jit_compile_su_de_32bit_1or2_src_sshl_f1();
  static void jit_compile_su_de_32bit_1or2_src_sshl_f2();
  static void jit_compile_su_de_32bit_1or2_src_sadd();
  static void jit_compile_su_de_32bit_1or2_src_and_f1();
  static void jit_compile_su_de_32bit_1or2_src_and_f2();
  static void jit_compile_su_de_32bit_1or2_src_cmpeq2();
  static void jit_compile_su_de_32bit_1or2_src_cmpeq4();
  static void jit_compile_su_de_32bit_1or2_src_or_f1();
  static void jit_compile_su_de_32bit_1or2_src_or_f2();
  static void jit_compile_su_de_32bit_1or2_src_sub_f1();
  static void jit_compile_su_de_32bit_1or2_src_sub_f2();
  static void jit_compile_su_de_32bit_1or2_src_cmpgtu4();
  static void jit_compile_su_de_32bit_1or2_src_cmpgt2();
  static void jit_compile_su_de_32bit_1or2_src_shl_f5();
  static void jit_compile_su_de_32bit_1or2_src_shl_f6();
  static void jit_compile_su_de_32bit_1or2_src_sub2();
  static void jit_compile_su_de_32bit_1or2_src_packlh2();
  static void jit_compile_su_de_32bit_1or2_src_mvc_f1();
  static void jit_compile_su_de_32bit_1or2_src_mvc_f2();
  static void jit_compile_su_de_32bit_1or2_src_xor_f1();
  static void jit_compile_su_de_32bit_1or2_src_xor_f2();
  static void jit_compile_su_de_32bit_1or2_src_packh2();
  static void jit_compile_su_de_32bit_1or2_src_packhl2();
  static void jit_compile_su_de_32bit_1or2_src_add_f1();
  static void jit_compile_su_de_32bit_1or2_src_add_f2();
  static void jit_compile_su_de_32bit_1or2_src_add2();
  
  static void jit_compile_su_de_32bit_addk();
  static void jit_compile_su_de_32bit_addkpc();
  static void jit_compile_su_de_32bit_mvk();
  static void jit_compile_su_de_32bit_mvkh();
  // NO Bxx instruction

  static void jit_compile_su_de_32bit_unary_unpkhu4();
  static void jit_compile_su_de_32bit_unary_unpklu4();

  static void jit_compile_su_de_32bit_fop_clr();
  static void jit_compile_su_de_32bit_fop_ext();
  static void jit_compile_su_de_32bit_fop_extu();
  static void jit_compile_su_de_32bit_fop_set();

  static void jit_compile_su_de_32bit_ext_1or2_src_andn();
  static void jit_compile_su_de_32bit_ext_1or2_src_sub();
  static void jit_compile_su_de_32bit_ext_1or2_src_shlmb();

  static void jit_compile_su_de_32bit_ext_1or2_src_shr2();
  static void jit_compile_su_de_32bit_ext_1or2_src_shrmb();
  static void jit_compile_su_de_32bit_ext_1or2_src_shru2();
  static void jit_compile_su_de_32bit_ext_1or2_src_pack2();
  static void jit_compile_su_de_32bit_ext_1or2_src_sadd2();
  static void jit_compile_su_de_32bit_ext_1or2_src_saddu4();
  static void jit_compile_su_de_32bit_ext_1or2_src_saddsu2();

  //NUnit
  static void jit_compile_nu_de_32bit_nop();

  //LUnit
  static void jit_compile_lu_de_32bit_unary_abs();
  static void jit_compile_lu_de_32bit_unary_swap4();
  static void jit_compile_lu_de_32bit_unary_unpklu4();
  static void jit_compile_lu_de_32bit_unary_unpkhu4();
  static void jit_compile_lu_de_32bit_unary_abs2();
  static void jit_compile_lu_de_32bit_unary_mvk();
  static void jit_compile_lu_de_32bit_unary_mvk_nc(); // mvk no-condition optimize

  static void jit_compile_lu_de_32bit_1or2_src_cmpeq_f1();
  static void jit_compile_lu_de_32bit_1or2_src_cmpeq_f2();
  static void jit_compile_lu_de_32bit_1or2_src_cmpeq_f3();
  static void jit_compile_lu_de_32bit_1or2_src_cmpeq_f4();
  static void jit_compile_lu_de_32bit_1or2_src_cmpgtu_f1();
  static void jit_compile_lu_de_32bit_1or2_src_cmpgtu_f2();
  static void jit_compile_lu_de_32bit_1or2_src_cmpgtu_f3();
  static void jit_compile_lu_de_32bit_1or2_src_cmpgtu_f4();
  static void jit_compile_lu_de_32bit_1or2_src_cmpltu_f1();
  static void jit_compile_lu_de_32bit_1or2_src_cmpltu_f2();
  static void jit_compile_lu_de_32bit_1or2_src_cmpltu_f3();
  static void jit_compile_lu_de_32bit_1or2_src_cmpltu_f4();
  static void jit_compile_lu_de_32bit_1or2_src_cmpgt_f1();
  static void jit_compile_lu_de_32bit_1or2_src_cmpgt_f2();
  static void jit_compile_lu_de_32bit_1or2_src_cmpgt_f3();
  static void jit_compile_lu_de_32bit_1or2_src_cmpgt_f4();
  static void jit_compile_lu_de_32bit_1or2_src_cmplt_f1();
  static void jit_compile_lu_de_32bit_1or2_src_cmplt_f2();
  static void jit_compile_lu_de_32bit_1or2_src_cmplt_f3();
  static void jit_compile_lu_de_32bit_1or2_src_cmplt_f4();
  static void jit_compile_lu_de_32bit_1or2_src_minu4();
  static void jit_compile_lu_de_32bit_1or2_src_maxu4();
  static void jit_compile_lu_de_32bit_1or2_src_min2();
  static void jit_compile_lu_de_32bit_1or2_src_max2();
  static void jit_compile_lu_de_32bit_1or2_src_lmbd_f1();
  static void jit_compile_lu_de_32bit_1or2_src_lmbd_f2();
  static void jit_compile_lu_de_32bit_1or2_src_norm_f1();
  static void jit_compile_lu_de_32bit_1or2_src_norm_f2();
  static void jit_compile_lu_de_32bit_1or2_src_or_f1();
  static void jit_compile_lu_de_32bit_1or2_src_or_f2();
  static void jit_compile_lu_de_32bit_1or2_src_or_f2_nc();
  static void jit_compile_lu_de_32bit_1or2_src_pack2();
  static void jit_compile_lu_de_32bit_1or2_src_packh2();
  static void jit_compile_lu_de_32bit_1or2_src_shlmb();
  static void jit_compile_lu_de_32bit_1or2_src_shrmb();
  static void jit_compile_lu_de_32bit_1or2_src_packh4();
  static void jit_compile_lu_de_32bit_1or2_src_packl4();
  static void jit_compile_lu_de_32bit_1or2_src_packhl2();
  static void jit_compile_lu_de_32bit_1or2_src_packlh2();
  static void jit_compile_lu_de_32bit_1or2_src_sadd_f1();
  static void jit_compile_lu_de_32bit_1or2_src_sadd_f2();
  static void jit_compile_lu_de_32bit_1or2_src_sadd_f3();
  static void jit_compile_lu_de_32bit_1or2_src_sadd_f4();
  static void jit_compile_lu_de_32bit_1or2_src_ssub_f1();
  static void jit_compile_lu_de_32bit_1or2_src_ssub_f2();
  static void jit_compile_lu_de_32bit_1or2_src_ssub_f3();
  static void jit_compile_lu_de_32bit_1or2_src_ssub_f4();
  static void jit_compile_lu_de_32bit_1or2_src_sat();
  static void jit_compile_lu_de_32bit_1or2_src_abs_slong();
  static void jit_compile_lu_de_32bit_1or2_src_sub_f1();
  static void jit_compile_lu_de_32bit_1or2_src_sub_f2();
  static void jit_compile_lu_de_32bit_1or2_src_sub_f3();
  static void jit_compile_lu_de_32bit_1or2_src_sub_f4();
  static void jit_compile_lu_de_32bit_1or2_src_sub_f5();
  static void jit_compile_lu_de_32bit_1or2_src_sub_f6();
  static void jit_compile_lu_de_32bit_1or2_src_add_f1();
  static void jit_compile_lu_de_32bit_1or2_src_add_f1_nc();
  static void jit_compile_lu_de_32bit_1or2_src_add_f2();
  static void jit_compile_lu_de_32bit_1or2_src_add_f3();
  static void jit_compile_lu_de_32bit_1or2_src_add_f4();
  static void jit_compile_lu_de_32bit_1or2_src_add_f5();
  static void jit_compile_lu_de_32bit_1or2_src_addu_f1();
  static void jit_compile_lu_de_32bit_1or2_src_addu_f2();
  static void jit_compile_lu_de_32bit_1or2_src_add2();
  static void jit_compile_lu_de_32bit_1or2_src_add4();
  static void jit_compile_lu_de_32bit_1or2_src_andn();
  static void jit_compile_lu_de_32bit_1or2_src_and_f1();
  static void jit_compile_lu_de_32bit_1or2_src_and_f2();
  static void jit_compile_lu_de_32bit_1or2_src_subabs4();
  static void jit_compile_lu_de_32bit_1or2_src_subc();
  static void jit_compile_lu_de_32bit_1or2_src_sub2();
  static void jit_compile_lu_de_32bit_1or2_src_sub4();
  static void jit_compile_lu_de_32bit_1or2_src_xor_f1();
  static void jit_compile_lu_de_32bit_1or2_src_xor_f2();
  static void jit_compile_lu_de_32bit_1or2_src_subu_f1();
  static void jit_compile_lu_de_32bit_1or2_src_subu_f2();

  //MUnit
  static void jit_compile_mu_de_32bit_ext_compound_avg2();
  static void jit_compile_mu_de_32bit_ext_compound_avgu4();
  static void jit_compile_mu_de_32bit_ext_compound_dotp2_f1();
  static void jit_compile_mu_de_32bit_ext_compound_dotp2_f2();
  static void jit_compile_mu_de_32bit_ext_compound_dotpn2();
  static void jit_compile_mu_de_32bit_ext_compound_dotpnrsu2();
  static void jit_compile_mu_de_32bit_ext_compound_dotprsu2();
  static void jit_compile_mu_de_32bit_ext_compound_dotpsu4();
  static void jit_compile_mu_de_32bit_ext_compound_dotpu4();
  static void jit_compile_mu_de_32bit_ext_compound_mpyhi();
  static void jit_compile_mu_de_32bit_ext_compound_mpyhir();
  static void jit_compile_mu_de_32bit_ext_compound_mpyli();
  static void jit_compile_mu_de_32bit_ext_compound_mpylir();
  static void jit_compile_mu_de_32bit_ext_compound_mpysu4();
  static void jit_compile_mu_de_32bit_ext_compound_mpyu4();
  static void jit_compile_mu_de_32bit_ext_compound_mpy2();
  static void jit_compile_mu_de_32bit_ext_compound_rotl_f1();
  static void jit_compile_mu_de_32bit_ext_compound_rotl_f2();
  static void jit_compile_mu_de_32bit_ext_compound_sshvr();

  static void jit_compile_mu_de_32bit_ext_unary_bitc4();
  static void jit_compile_mu_de_32bit_ext_unary_bitr();
  static void jit_compile_mu_de_32bit_ext_unary_deal();
  static void jit_compile_mu_de_32bit_ext_unary_shfl();
  static void jit_compile_mu_de_32bit_ext_unary_mvd();
  static void jit_compile_mu_de_32bit_ext_unary_xpnd2();
  static void jit_compile_mu_de_32bit_ext_unary_xpnd4();

  static void jit_compile_mu_de_32bit_mpy_mpy_f1();
  static void jit_compile_mu_de_32bit_mpy_mpy_f2(); // scst5
  static void jit_compile_mu_de_32bit_mpy_mpyh();
  static void jit_compile_mu_de_32bit_mpy_mpyhl();
  static void jit_compile_mu_de_32bit_mpy_mpyhlu();
  static void jit_compile_mu_de_32bit_mpy_mpyhslu();
  static void jit_compile_mu_de_32bit_mpy_mpyhsu();
  static void jit_compile_mu_de_32bit_mpy_mpyhu();
  static void jit_compile_mu_de_32bit_mpy_mpyhuls();
  static void jit_compile_mu_de_32bit_mpy_mpyhus();
  static void jit_compile_mu_de_32bit_mpy_mpylh();
  static void jit_compile_mu_de_32bit_mpy_mpylshu();
  static void jit_compile_mu_de_32bit_mpy_mpyluhs();
  static void jit_compile_mu_de_32bit_mpy_mpylhu();
  static void jit_compile_mu_de_32bit_mpy_mpysu_f1();
  static void jit_compile_mu_de_32bit_mpy_mpysu_f2();
  static void jit_compile_mu_de_32bit_mpy_mpyus();
  static void jit_compile_mu_de_32bit_mpy_mpyu();

  static void jit_compile_mu_de_32bit_mpy_smpyh();
  static void jit_compile_mu_de_32bit_mpy_smpy();
  static void jit_compile_mu_de_32bit_mpy_smpylh();
  static void jit_compile_mu_de_32bit_mpy_smpyhl();

  //DUnit
  static void jit_compile_du_general();

  static void jit_compile_du_de_32bit_1or2_src_add_f1();
  static void jit_compile_du_de_32bit_1or2_src_add_f2();
  static void jit_compile_du_de_32bit_1or2_src_mvk();
  static void jit_compile_du_de_32bit_1or2_src_sub_f1();
  static void jit_compile_du_de_32bit_1or2_src_sub_f2();
  static void jit_compile_du_de_32bit_1or2_src_addab_f1();
  static void jit_compile_du_de_32bit_1or2_src_addab_f2();
  static void jit_compile_du_de_32bit_1or2_src_subab_f1();
  static void jit_compile_du_de_32bit_1or2_src_subab_f2();
  static void jit_compile_du_de_32bit_1or2_src_addah_f1();
  static void jit_compile_du_de_32bit_1or2_src_addah_f2();
  static void jit_compile_du_de_32bit_1or2_src_subah_f1();
  static void jit_compile_du_de_32bit_1or2_src_subah_f2();
  static void jit_compile_du_de_32bit_1or2_src_addaw_f1();
  static void jit_compile_du_de_32bit_1or2_src_addaw_f2();
  static void jit_compile_du_de_32bit_1or2_src_subaw_f1();
  static void jit_compile_du_de_32bit_1or2_src_subaw_f2();
  static void jit_compile_du_de_32bit_1or2_src_addad_f1();
  static void jit_compile_du_de_32bit_1or2_src_addad_f2();

  static void jit_compile_du_de_32bit_ext_1or2_src_andn();
  static void jit_compile_du_de_32bit_ext_1or2_src_or_f1();
  static void jit_compile_du_de_32bit_ext_1or2_src_or_f2();
  static void jit_compile_du_de_32bit_ext_1or2_src_add2();
  static void jit_compile_du_de_32bit_ext_1or2_src_sub2();
  static void jit_compile_du_de_32bit_ext_1or2_src_and_f1();
  static void jit_compile_du_de_32bit_ext_1or2_src_and_f2();
  static void jit_compile_du_de_32bit_ext_1or2_src_add_f1();
  static void jit_compile_du_de_32bit_ext_1or2_src_add_f2();
  static void jit_compile_du_de_32bit_ext_1or2_src_sub();
  static void jit_compile_du_de_32bit_ext_1or2_src_xor_f1();
  static void jit_compile_du_de_32bit_ext_1or2_src_xor_f2();

  static void jit_compile_du_de_32bit_ld_st_long_immed_ldb();
  static void jit_compile_du_de_32bit_ld_st_long_immed_ldbu();
  static void jit_compile_du_de_32bit_ld_st_long_immed_ldh();
  static void jit_compile_du_de_32bit_ld_st_long_immed_ldhu();
  static void jit_compile_du_de_32bit_ld_st_long_immed_ldw();
  static void jit_compile_du_de_32bit_ld_st_long_immed_stb();
  static void jit_compile_du_de_32bit_ld_st_long_immed_sth();
  static void jit_compile_du_de_32bit_ld_st_long_immed_stw();

  static void jit_compile_du_de_32bit_ld_st_basic_ldb_f1();
  static void jit_compile_du_de_32bit_ld_st_basic_ldbu_f1();
  static void jit_compile_du_de_32bit_ld_st_basic_ldh_f1();
  static void jit_compile_du_de_32bit_ld_st_basic_ldhu_f1(); 
  static void jit_compile_du_de_32bit_ld_st_basic_ldw_f1();
  static void jit_compile_du_de_32bit_ld_st_basic_ldnw_f1();
  static void jit_compile_du_de_32bit_ld_st_basic_lddw_f1();
  static void jit_compile_du_de_32bit_ld_st_basic_ldndw_f1();
  static void jit_compile_du_de_32bit_ld_st_basic_stb_f1();
  static void jit_compile_du_de_32bit_ld_st_basic_sth_f1();
  static void jit_compile_du_de_32bit_ld_st_basic_stw_f1();
  static void jit_compile_du_de_32bit_ld_st_basic_stnw_f1();
  static void jit_compile_du_de_32bit_ld_st_basic_stdw_f1();
  static void jit_compile_du_de_32bit_ld_st_basic_stndw_f1();

  static void jit_compile_du_de_32bit_ld_st_basic_ldb_f2();
  static void jit_compile_du_de_32bit_ld_st_basic_ldbu_f2();
  static void jit_compile_du_de_32bit_ld_st_basic_ldh_f2();
  static void jit_compile_du_de_32bit_ld_st_basic_ldhu_f2(); 
  static void jit_compile_du_de_32bit_ld_st_basic_ldw_f2();
  static void jit_compile_du_de_32bit_ld_st_basic_ldw_f2_nc();
  static void jit_compile_du_de_32bit_ld_st_basic_ldnw_f2();
  static void jit_compile_du_de_32bit_ld_st_basic_lddw_f2();
  static void jit_compile_du_de_32bit_ld_st_basic_ldndw_f2();
  static void jit_compile_du_de_32bit_ld_st_basic_stb_f2();
  static void jit_compile_du_de_32bit_ld_st_basic_sth_f2();
  static void jit_compile_du_de_32bit_ld_st_basic_stw_f2();
  static void jit_compile_du_de_32bit_ld_st_basic_stnw_f2();
  static void jit_compile_du_de_32bit_ld_st_basic_stdw_f2();
  static void jit_compile_du_de_32bit_ld_st_basic_stndw_f2();

  //DUnit helper
  static void jit_compile_du_de_32bit_ld_st_basci_stw(jit_value_t jit_offset);
  static void jit_compile_du_de_32bit_ld_st_basic_stdw(jit_value_t jit_offset,
    const word_t offset_factor);
};



END_NS

#endif