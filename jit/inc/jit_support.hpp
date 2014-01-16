#ifndef JIT_SUPPORT_HPP
#define JIT_SUPPORT_HPP

#ifdef CORE_USE_LLVM

#include "common/inc/def.hpp"

//LLVM-support
#include "llvm/LLVMContext.h"
#include "llvm/Module.h"
#include "llvm/Constants.h"
#include "llvm/DerivedTypes.h"
#include "llvm/Instructions.h"
#include "llvm/ExecutionEngine/JIT.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/IRBuilder.h"



BEGIN_NS

class Core;
class BasicBlock; // conflict with llvm::BasicBlock

class JIT
{
private:
  //LLVM-support
  static llvm::Module      llvm_module;
  static llvm::IRBuilder<> llvm_builder;
  static llvm::ExecutionEngine* llvm_ee;

public:
  static void init();
  static void init_jit_compile_func();
  static inline llvm::Module&       module();
  static inline llvm::IRBuilder<>&  builder();
  static inline llvm::ExecutionEngine& EE();
  static void compile_basic_block(Core *core, BasicBlock *bb);

private:
  //helper functions
  static void compile_addr(Core *core, md_addr_t addr);
  static inline void compile_native_call_void_uint(void *fp,word_t arg);
  static inline void compile_native_call_void_void(void *fp); 
  static inline void compile_native_call_de_func(void *fp,llvm::Value *arg1,llvm::Value *arg2); 
  static inline void compile_update_pc(word_t pc_diff);
  static inline void compile_update_inst_num();
  static inline void compile_current_inst();
  static inline llvm::Value* compile_const_u32(word_t val);
  static inline llvm::Value* compile_ptr(uint64_t ptr,llvm::Type* type);
  static inline void compile_bb_epilog_proc();
  static inline void compile_bb_prolog_proc();
  static inline void compile_bb_prolog_proc_multi_cycles(word_t nops);
  static inline void compile_bb_epilog_and_prolog_proc();
  static void compile_reg_ch_proc();
  static void compile_stw_proc();
  static inline llvm::Value* compile_core_reg_read(word_t side,word_t idx);
  static inline llvm::Value* compile_core_reg_read_abs_idx(word_t idx);
  static inline void compile_core_push_reg_ch(word_t side,word_t idx,llvm::Value* val);
  static inline void compile_core_push_reg_ch_abs_idx(word_t idx,llvm::Value* val);
  static inline void compile_core_save_reg_ch_abs_idx(word_t idx,llvm::Value* val);

  //JIT compile func
private:
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
  static void jit_compile_lu_de_32bit_1or2_src_cmpltu_f1_nc();
  static void jit_compile_lu_de_32bit_1or2_src_cmpltu_f1_z0();
  static void jit_compile_lu_de_32bit_1or2_src_cmpltu_f1_z1();
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
  static void jit_compile_du_de_32bit_ld_st_basci_stw(llvm::Value *jit_offset);
  static void jit_compile_du_de_32bit_ld_st_basic_stdw(llvm::Value *jit_offset,
    const word_t offset_factor);
};

llvm::Module& JIT::module()
{
  return llvm_module;
}

llvm::IRBuilder<>& JIT::builder()
{
  return llvm_builder;
}

llvm::ExecutionEngine& JIT::EE()
{
  return *llvm_ee;
}

END_NS

#endif //CORE_USE_LLVM

#endif