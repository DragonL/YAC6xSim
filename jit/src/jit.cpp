#ifdef USE_LIBJIT
#include <map>
#include "jit/inc/jit.hpp"
#include "decode/inc/inst.hpp"
#include "core/inc/core.hpp"
#include "core/inc/l2_mem_ctrl.hpp"
#include "profiler/inc/basic_block.hpp"


BEGIN_NS

jit_context_t JIT2::jit_context;
jit_function_t JIT2::jit_current_func;
Instruction *JIT2::current_inst = NULL;
Instruction *JIT2::prev_inst = NULL;

static word_t jit_remain_nops = 0;
static jit_type_t jit_reg_ch_t;
static jit_type_t jit_stw_req_t;
static jit_type_t jit_reg_wb_t;
static jit_type_t jit_signature_de_func;
static jit_type_t jit_signature_void_void;
static jit_type_t jit_signature_void_uint;
static jit_type_t jit_signature_uint_uint;
static jit_type_t jit_signature_void_uint4;
static jit_type_t jit_signature_void_uint_ubyte;
static jit_type_t jit_signature_void_uint_uhalf;
static jit_type_t jit_signature_void_uint2;
static jit_type_t jit_signature_fastcall_void_uint2;
static jit_type_t jit_signature_void_uint_ulong;

static bool use_cond = false;


static cycle_t jit_bb_cycles = 0;
static word_t jit_bb_inst_nums = 0;

static BasicBlock* current_bb;
static Core* current_core;
static L2MemCtroller* l2;


struct jit_reg_change_req_t
{
  word_t side;
  word_t reg;
  jit_value_t jit_val;
  jit_value_t jit_cond;
};

struct bb_stw_req_t
{
  jit_value_t jit_addr;
  jit_value_t jit_stw_val;
  mem_type_t type;
};

static jit_reg_change_req_t jit_reg_wb_list[8];
static word_t jit_reg_ch_num = 0;

// 0 : NEED NOTHING
// 1 : NEED PROLOG
// 2 : NEED EPILOG
// 3 : BOTH
static uint prolog_epilog_flag = 0;

// max 4 U32 stw
static bb_stw_req_t jit_stw_req_lst[4];
static word_t jit_stw_num = 0;

struct reg_idx_t
{
  word_t side;
  word_t idx;
};

static reg_idx_t cond_tbl[16] = 
{
  {3,0}, // not use
  {3,0}, // not use
  {1,0}, // B0
  {1,0}, // B0
  {1,1}, // B1
  {1,1}, // B1
  {1,2}, // B2
  {1,2}, // B2
  {0,1}, // A1
  {0,1}, // A1
  {0,2}, // A2
  {0,2}, // A2
  {0,0}, // A0
  {0,0}, // A0
  {3,0}, // not use
  {3,0}, // not use
};

typedef void (*jit_compile_t)(void);
typedef std::map<uint,jit_compile_t> jit_compile_map_t;
static jit_compile_map_t jit_compile_map;

#define DBG_JIT_FUNC \
{\
  current_core->get_ofs() << __FUNCTION__ << \
    to_hex_str(current_inst->get_code_addr()) << "\n";\
}

void wrap_bb_prolog_proc()
{
  //current_core->bb_prolog_proc();
}

static void wrap_bb_epilog_proc()
{
  current_core->bb_epilog_proc();
}

void wrap_bb_stw_proc()
{
  current_core->stw_proc();
}

void wrap_bb_prolog_and_epilog_proc()
{
  current_core->bb_epilog_proc();
  bb_prolog_proc();
}

//TODO remove it
void wrap_du_general(Instruction* inst)
{
  /*
  de_func_t de_func = DE_FUNC_ADDR(DUnit,de_32bit,general);
  de_func(current_core,inst);
  */
}

word_t wrap_mem_read_word(md_addr_t addr)
{
  return current_core->get_l2()->mem_read_word(addr);
}

void wrap_mem_write_byte(md_addr_t addr, byte_t val)
{
  current_core->get_l2()->mem_write_byte(addr,val);
}

void wrap_mem_write_xhalf(md_addr_t addr, half_t val)
{
  current_core->get_l2()->mem_write_half_xendian(addr,val);
}

void wrap_mem_write_xword(md_addr_t addr, word_t val)
{
  current_core->get_l2()->mem_write_word_xendian(addr,val);
}

void wrap_mem_write_xqword(md_addr_t addr, qword_t qval)
{
  current_core->get_l2()->mem_write_qword_xendian(addr,qval);
}

void wrap_push_reg_delay_ch(word_t side,word_t idx,word_t delay,word_t val)
{
  current_core->push_reg_delay_ch(side,idx,val,delay);
}

void wrap_bb_combined_prolog_proc(word_t inc_cycles,word_t inst_nums)
{
  //current_core->bb_combined_prolog_proc(inc_cycles,inst_nums);
}

void wrap_general_de_func(Core *core,Instruction *inst)
{
  inst->de_func(core,inst);
}
  
void JIT2::init(Core* core)
{
  current_core = core;
  l2 = L2MemCtroller::get();
  jit_context = jit_context_create();
  jit_type_t reg_ch_t[3] = {
    jit_type_uint,
    jit_type_uint,
    jit_type_uint
  };
  jit_reg_ch_t = jit_type_create_struct(reg_ch_t,3,1);

  jit_type_t tmp_stw_req_t[4] = {
    jit_type_uint,
    jit_type_uint,
    jit_type_uint,
    jit_type_ulong
  };

  jit_type_t tmp_reg_wb_t[2] = {
    jit_type_uint,
    jit_type_uint
  };

  jit_stw_req_t = jit_type_create_struct(tmp_stw_req_t,4,1);
  jit_reg_wb_t = jit_type_create_struct(tmp_reg_wb_t,2,1);

  jit_type_t params[4];
	/* Build the function signature */
	params[0] = jit_type_uint;
	params[1] = jit_type_uint;
  params[2] = jit_type_uint;
  params[3] = jit_type_uint;
	jit_signature_de_func = jit_type_create_signature
		(jit_abi_cdecl, jit_type_uint, NULL, 0, 1);

  jit_signature_void_void = jit_type_create_signature
    (jit_abi_cdecl, jit_type_void, NULL, 0, 1);

  jit_signature_void_uint = jit_type_create_signature
    (jit_abi_cdecl, jit_type_void, params, 1, 1);

  jit_signature_uint_uint = jit_type_create_signature
    (jit_abi_cdecl, jit_type_uint, params, 1, 1);

  jit_signature_void_uint4 = jit_type_create_signature
    (jit_abi_cdecl, jit_type_void, params, 4, 1);

  jit_signature_void_uint2 = jit_type_create_signature
    (jit_abi_cdecl, jit_type_void, params, 2, 1);

  jit_signature_fastcall_void_uint2 = jit_type_create_signature
    (jit_abi_fastcall, jit_type_void, params, 2, 1);

	params[1] = jit_type_ubyte;
  jit_signature_void_uint_ubyte = jit_type_create_signature
    (jit_abi_cdecl, jit_type_void, params, 2, 1);

	params[1] = jit_type_ushort;
  jit_signature_void_uint_uhalf = jit_type_create_signature
    (jit_abi_cdecl, jit_type_void, params, 2, 1);

	params[1] = jit_type_ulong;
  jit_signature_void_uint_ulong = jit_type_create_signature
    (jit_abi_cdecl, jit_type_void, params, 2, 1);

  // init JIT compile function map
#define INSERT_JIT_FUNC(de_func,jit_func)\
  jit_compile_map.insert(std::make_pair((uint)de_func,jit_func))

  
  //SUnit
  /*
  INSERT_JIT_FUNC(DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,clr),
    jit_compile_su_de_32bit_1or2_src_clr);
  INSERT_JIT_FUNC(DE_FUNC_ADDR(SUnit,de_32bit,mvk),
    jit_compile_su_de_32bit_mvk);
  INSERT_JIT_FUNC(DE_FUNC_ADDR(SUnit,de_32bit,mvkh),
    jit_compile_su_de_32bit_mvkh);
    */
  /*
  INSERT_JIT_FUNC(DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,shl_f1),
    jit_compile_su_de_32bit_1or2_src_shl_f1);
  INSERT_JIT_FUNC(DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,shl_f2),
    jit_compile_su_de_32bit_1or2_src_shl_f2);
  INSERT_JIT_FUNC(DE_FUNC_ADDR(SUnit,de_32bit_1or2_src,shl_f2_nc),
    jit_compile_su_de_32bit_1or2_src_shl_f2_nc);
    */

  //DUnit
  //INSERT_JIT_FUNC(DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,ldw_f2_nc),
  //  jit_compile_du_de_32bit_ld_st_basic_ldw_f2_nc);
  //INSERT_JIT_FUNC(DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,stw_f1),
  //  jit_compile_du_de_32bit_ld_st_basic_stw_f1);
  //INSERT_JIT_FUNC(DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,stw_f2),
  //  jit_compile_du_de_32bit_ld_st_basic_stw_f2);
  /*
  INSERT_JIT_FUNC(DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,stnw_f1),
    jit_compile_du_de_32bit_ld_st_basic_stnw_f1);
  INSERT_JIT_FUNC(DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,stnw_f2),
    jit_compile_du_de_32bit_ld_st_basic_stnw_f2);
    */
  /*
  INSERT_JIT_FUNC(DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,stdw_f1),
    jit_compile_du_de_32bit_ld_st_basic_stdw_f1);
  INSERT_JIT_FUNC(DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,stdw_f2),
    jit_compile_du_de_32bit_ld_st_basic_stdw_f2);
  INSERT_JIT_FUNC(DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,stndw_f1),
    jit_compile_du_de_32bit_ld_st_basic_stndw_f1);
  INSERT_JIT_FUNC(DE_FUNC_ADDR(DUnit,de_32bit_ld_st_basic,stndw_f2),
    jit_compile_du_de_32bit_ld_st_basic_stndw_f2);
    */
  /*
  //MUnit
  INSERT_JIT_FUNC(DE_FUNC_ADDR(MUnit,de_32bit_mpy,mpylh),
    jit_compile_mu_de_32bit_mpy_mpylh);
  INSERT_JIT_FUNC(DE_FUNC_ADDR(MUnit,de_32bit_mpy,mpyu),
    jit_compile_mu_de_32bit_mpy_mpyu);

  //LUnit
  INSERT_JIT_FUNC(DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,add_f1),
    jit_compile_lu_de_32bit_1or2_src_add_f1);
  INSERT_JIT_FUNC(DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,add_f1_nc),
    jit_compile_lu_de_32bit_1or2_src_add_f1_nc);
  INSERT_JIT_FUNC(DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,add_f2),
    jit_compile_lu_de_32bit_1or2_src_add_f2);
  INSERT_JIT_FUNC(DE_FUNC_ADDR(LUnit,de_32bit_1or2_src,cmpeq_f2),
    jit_compile_lu_de_32bit_1or2_src_cmpeq_f2);
    */
  
  //NUnit
  INSERT_JIT_FUNC(DE_FUNC_ADDR(NoneUnit,de_32bit,nop),
    jit_compile_nu_de_32bit_nop);
}

void JIT2::compile_basic_block(Core *core, BasicBlock *bb)
{
  void *entry;
  word_t pc_diff = 0;

  //first Instruction in BasicBlock
  current_bb = bb;
  Instruction *first_inst = Core::fetch_cached_inst(bb->start);

  jit_context_build_start(jit_context);
  jit_current_func = jit_function_create(jit_context, jit_signature_de_func);

  jit_bb_inst_nums = 0;
  jit_remain_nops = 0;
  jit_bb_cycles = 0;
  prolog_epilog_flag = 0;

  for(md_addr_t addr = bb->start; addr <= bb->end; addr += 4)
  {//compile each instruction
    // first EP do not need prolog_proc()
    compile_addr(core,addr);
    pc_diff += 4;
    ++jit_bb_inst_nums;
  }
  compile_update_pc(pc_diff);
  compile_update_inst_num();
  //compile_bb_combined_prolog_proc();
  jit_insn_return(jit_current_func,NULL); // return
  jit_function_compile_entry(jit_current_func,&entry);
  jit_function_setup_entry(jit_current_func,entry);
  jit_context_build_end(jit_context);

  //first_inst->set_unit_type(UNIT_COMPILED_BB);
  first_inst->set_jit_func((jit_func_t)entry);
  current_inst = NULL;
  prev_inst = NULL;
}

void JIT2::compile_addr(Core *core, md_addr_t addr)
{
  current_inst = Core::fetch_cached_inst(addr); // should always hit
  compile_inst_with_cond(core,current_inst->get_cregz());

  if(!current_inst->is_next_p())
  {
    // prolog for next EP
    if(addr != current_bb->end)
    {
      prolog_epilog_flag |= 0x2;
      ++jit_bb_cycles;
    }

    if(prolog_epilog_flag == 1)
    {
      jit_insn_call_native(jit_current_func,NULL,wrap_bb_epilog_proc,jit_signature_void_void,NULL,0,0);
      //compile_epilog_proc();
    }
    else if(prolog_epilog_flag == 2)
    {
      compile_prolog_proc();
    }
    else if(prolog_epilog_flag == 3)
    {
      //compile_prolog_and_epilog_proc();
      //jit_insn_call_native(jit_current_func,NULL,wrap_bb_prolog_and_epilog_proc,jit_signature_void_void,NULL,0,0);
      jit_insn_call_native(jit_current_func,NULL,bb_prolog_and_epilog_proc,jit_signature_void_void,NULL,0,0);
    }

    // process remain NOPs
    if(jit_remain_nops > 0)
    {
      for(int i = 0; i < jit_remain_nops; ++i)
      {
        compile_prolog_proc();
        ++jit_bb_cycles;
        ++jit_bb_inst_nums;
      }
      jit_remain_nops = 0;
    }

    prolog_epilog_flag = 0;
  }

  prev_inst = current_inst;
}

inline void JIT2::jit_compile_push_reg_delay_ch2(jit_value_t jit_val,word_t delay)
{
  jit_compile_push_reg_delay_ch(current_inst->get_side(),
    current_inst->get_dst(),
    jit_val,
    delay);
}

void JIT2::jit_compile_push_reg_delay_ch(word_t side,word_t idx,jit_value_t jit_val,word_t delay)
{
  //wrap_push_reg_delay_ch  

  jit_value_t jit_side = compile_uint(side);
  jit_value_t jit_idx = compile_uint(idx);
  jit_value_t jit_delay = compile_uint(delay);
  jit_value_t jit_params[4] = {jit_side,jit_idx,jit_delay,jit_val};
  jit_insn_call_native(jit_current_func,
    NULL,
    wrap_push_reg_delay_ch,
    jit_signature_void_uint4,
    jit_params,
    4,
    0);
}

void JIT2::compile_push_stw_req(jit_value_t jit_mem_addr,jit_value_t jit_mem_type,jit_value_t jit_val)
{
  // const 0
  jit_value_t jit_const_zero = jit_value_create_nint_constant(jit_current_func,
    jit_type_uint,0);

  // const 1
  jit_value_t jit_const_one = jit_value_create_nint_constant(jit_current_func,
    jit_type_uint,1);

  jit_value_t jit_stw_req_num_addr = jit_value_create_nint_constant(jit_current_func,
    jit_type_uint,(word_t)&current_core->stw_req_num);
  jit_value_t jit_stw_req_num_val = jit_insn_load_relative(jit_current_func,
    jit_stw_req_num_addr,0,jit_type_uint);
  jit_value_t jit_stw_req_num_val_new = jit_insn_add(jit_current_func,
    jit_stw_req_num_val,
    jit_const_one);// ++stw_req_num
  jit_insn_store_relative(jit_current_func,
    jit_stw_req_num_addr,
    0,
    jit_stw_req_num_val_new);//store back

  jit_value_t jit_addr_of_stw_req_list = jit_value_create_nint_constant(jit_current_func,
    jit_type_uint,(word_t)&current_core->stw_req_list);
  jit_value_t jit_addr_of_stw_req = jit_insn_load_elem_address (jit_current_func,
    jit_addr_of_stw_req_list,
    jit_stw_req_num_val,
    jit_stw_req_t);

  jit_insn_store_elem(jit_current_func,
    jit_addr_of_stw_req,
    jit_const_zero,
    jit_mem_addr);
  jit_insn_store_elem(jit_current_func,
    jit_addr_of_stw_req,
    jit_const_one,
    jit_mem_type);

  //TYPE_U64
  if(jit_value_get_type(jit_val) == jit_type_ulong)
  {
    // const 3
    jit_value_t jit_const_three = jit_value_create_nint_constant(jit_current_func,
      jit_type_uint,3);
    jit_insn_store_elem(jit_current_func,
      jit_addr_of_stw_req,
      jit_const_three,
      jit_val);
  }
  else
  {//OTHER
    // const 2
    jit_value_t jit_const_two = jit_value_create_nint_constant(jit_current_func,
      jit_type_uint,2);
    jit_insn_store_elem(jit_current_func,
      jit_addr_of_stw_req,
      jit_const_two,
      jit_val);
  }
}

void JIT2::compile_push_reg_ch(word_t side,word_t idx,jit_value_t jit_val)
{
  prolog_epilog_flag |= 0x1;

  // const 0
  jit_value_t jit_const_zero = jit_value_create_nint_constant(jit_current_func,
    jit_type_uint,0);

  // const 1
  jit_value_t jit_const_one = jit_value_create_nint_constant(jit_current_func,
    jit_type_uint,1);

  // const 2
  jit_value_t jit_const_two = jit_value_create_nint_constant(jit_current_func,
    jit_type_uint,2);

  //reg_ch_num++
  jit_value_t jit_reg_ch_num_addr = jit_value_create_nint_constant(jit_current_func,
    jit_type_uint,(word_t)&current_core->reg_ch_num);
  jit_value_t jit_reg_ch_num_val = jit_insn_load_relative(jit_current_func,
    jit_reg_ch_num_addr,0,jit_type_uint);
  jit_value_t jit_reg_ch_num_val_new = jit_insn_add(jit_current_func,
    jit_reg_ch_num_val,
    jit_const_one);
  jit_insn_store_relative(jit_current_func,
    jit_reg_ch_num_addr,
    0,
    jit_reg_ch_num_val_new);

  // side,idx
  jit_value_t jit_side = compile_uint(side);
  jit_value_t jit_idx = compile_uint(idx);

  jit_value_t jit_addr_of_reg_wb_list = jit_value_create_nint_constant(jit_current_func,
    jit_type_uint,(word_t)&current_core->reg_wb_list);
  jit_value_t jit_addr_of_reg_ch = jit_insn_load_elem_address (jit_current_func,
    jit_addr_of_reg_wb_list,
    jit_reg_ch_num_val,
    jit_reg_ch_t);


  jit_insn_store_elem(jit_current_func,
    jit_addr_of_reg_ch,
    jit_const_zero,
    jit_side);
  jit_insn_store_elem(jit_current_func,
    jit_addr_of_reg_ch,
    jit_const_one,
    jit_idx);
  jit_insn_store_elem(jit_current_func,
    jit_addr_of_reg_ch,
    jit_const_two,
    jit_val);
}

inline void JIT2::jit_push_reg_ch2(jit_value_t jit_val)
{
  jit_push_reg_ch(current_inst->get_side(),
    current_inst->get_dst(),
    jit_val);
}

void JIT2::jit_push_stw_req(jit_value_t jit_addr,jit_value_t jit_val,mem_type_t type)
{
  bb_stw_req_t &jit_stw = jit_stw_req_lst[jit_stw_num++];
  jit_stw.type = type;
  jit_stw.jit_addr = jit_addr;
  jit_stw.jit_stw_val = jit_val;
}

void JIT2::jit_push_reg_ch(word_t side,word_t idx,jit_value_t jit_val)
{
    compile_push_reg_ch(side,idx,jit_val);
}

void JIT2::jit_push_reg_pair_ch(word_t side,word_t idx,jit_value_t jit_val)
{
  jit_value_t jit_const_0xFFFFFFFF = compile_ulong(0xFFFFFFFF);
  jit_value_t jit_const_32 = compile_uint(32);
  jit_value_t jit_dst_val = jit_insn_and(jit_current_func,
    jit_val,
    jit_const_0xFFFFFFFF);
  jit_dst_val = jit_insn_convert(jit_current_func,
    jit_dst_val,
    jit_type_uint,
    0);
  jit_push_reg_ch(current_inst->get_side(),
    current_inst->get_dst(),
    jit_dst_val);

  jit_value_t jit_dst2_val = jit_insn_shr(jit_current_func,
    jit_val,
    jit_const_32);
  jit_dst2_val = jit_insn_convert(jit_current_func,
    jit_dst_val,
    jit_type_uint,
    0);
  jit_push_reg_ch(current_inst->get_side(),
    current_inst->get_dst() + 1,
    jit_dst2_val);
}

void JIT2::compile_stw_proc()
{
  jit_label_t jit_lb_end_if = jit_label_undefined;

  // const 0
  jit_value_t jit_const_zero = jit_value_create_nint_constant(jit_current_func,
    jit_type_uint,0);

  jit_value_t jit_stw_req_num_addr = jit_value_create_nint_constant(jit_current_func,
    jit_type_uint,(word_t)&Core::get()->stw_req_num);

  jit_value_t jit_stw_req_num_tmp = jit_insn_load_relative(jit_current_func,
    jit_stw_req_num_addr,0,jit_type_uint);

  jit_value_t jit_cond = jit_insn_gt(jit_current_func,
    jit_stw_req_num_tmp,jit_const_zero);
  jit_insn_branch_if_not(jit_current_func,jit_cond,&jit_lb_end_if);

  //call native
  jit_insn_call_native(jit_current_func,NULL,wrap_bb_stw_proc,jit_signature_void_void,NULL,0,0);

  jit_insn_label(jit_current_func,&jit_lb_end_if);
}

/*
  while(reg_ch_num > 0)
  {
    reg_wb_t& req = reg_wb_list[--reg_ch_num];
    *req.reg_phy_addr = req.val;
  }
*/
void JIT2::compile_reg_ch()
{
  jit_label_t jit_lb_test_while = jit_label_undefined;
  jit_label_t jit_lb_end_while = jit_label_undefined;
  jit_label_t jit_lb_exe_while = jit_label_undefined;

  // const 0
  jit_value_t jit_const_zero = jit_value_create_nint_constant(jit_current_func,
    jit_type_uint,0);

  // const 1
  jit_value_t jit_const_one = jit_value_create_nint_constant(jit_current_func,
    jit_type_uint,1);

  jit_value_t jit_reg_ch_num_addr = jit_value_create_nint_constant(jit_current_func,
    jit_type_uint,(word_t)&Core::get()->reg_ch_num);

  jit_value_t jit_reg_ch_num_local = jit_value_create(jit_current_func,jit_type_uint);

  jit_value_t jit_reg_ch_num_tmp = jit_insn_load_relative(jit_current_func,
    jit_reg_ch_num_addr,0,jit_type_uint);
  jit_insn_store(jit_current_func,jit_reg_ch_num_local,jit_reg_ch_num_tmp);

  jit_value_t jit_addr_of_reg_wb_list = jit_value_create_nint_constant(jit_current_func,
    jit_type_uint,(word_t)&Core::get()->reg_wb_list);

  // test reg_ch_num > 0 ?
  jit_insn_label(jit_current_func,&jit_lb_test_while);

  jit_value_t jit_cond = jit_insn_gt(jit_current_func,
    jit_reg_ch_num_local,jit_const_zero);

  // if(reg_ch_num <= 0) JMP end_of_while
  jit_insn_branch_if_not(jit_current_func,jit_cond,&jit_lb_end_while);
  jit_insn_label(jit_current_func,&jit_lb_exe_while);

  // --reg_ch_num
  jit_value_t jit_reg_ch_num_tmp2 = jit_insn_sub(jit_current_func,jit_reg_ch_num_local,jit_const_one);
  jit_insn_store(jit_current_func,jit_reg_ch_num_local,jit_reg_ch_num_tmp2);

  jit_value_t jit_addr_of_reg_ch = jit_insn_load_elem_address(jit_current_func,
    jit_addr_of_reg_wb_list,
    jit_reg_ch_num_local,
    jit_reg_wb_t);

  jit_value_t jit_reg_phy_addr = jit_insn_load_elem(jit_current_func,
    jit_addr_of_reg_ch,
    jit_const_zero,
    jit_type_uint);

  jit_value_t jit_wb_val = jit_insn_load_elem(jit_current_func,
    jit_addr_of_reg_ch,
    jit_const_one,
    jit_type_uint);

  // *reg_phy_addr = reg_wb_val;
  jit_insn_store_relative(jit_current_func,
    jit_reg_phy_addr,
    0,
    jit_wb_val);

  jit_insn_branch(jit_current_func,&jit_lb_test_while);

  jit_insn_label(jit_current_func,&jit_lb_end_while);

  // reg_ch_num = 0;
  jit_insn_store_relative(jit_current_func,
    jit_reg_ch_num_addr,
    0,
    jit_const_zero);
}

void JIT2::compile_stw()
{
  /*
  for(int i = 0; i < jit_stw_num; ++i)
  {
    bb_stw_req_t &jit_stw_req = jit_stw_req_lst[i];
    switch(jit_stw_req.type)
    {
    case TYPE_U8:
      {
        jit_compile_l2_mem_write_byte(jit_stw_req.jit_addr,
          jit_stw_req.jit_stw_val);
      }
      break;

    case TYPE_U16:
      {
        jit_compile_l2_mem_write_xhalf(jit_stw_req.jit_addr,
          jit_stw_req.jit_stw_val);
      }
      break;

    case TYPE_U32:
      {
        jit_compile_l2_mem_write_xword(jit_stw_req.jit_addr,
          jit_stw_req.jit_stw_val);
      }
      break;

    case TYPE_U64:
      {
        jit_compile_l2_mem_write_xqword(jit_stw_req.jit_addr,
          jit_stw_req.jit_stw_val);
      }
      break;

    default:
      break;
    }
  }
  */
}

void JIT2::compile_current_inst()
{
  jit_compile_map_t::iterator it = jit_compile_map.find((uint)current_inst->get_de_func());
  if(it != jit_compile_map.end())
  {
    jit_compile_t jit_compile_func = it->second;
    jit_compile_func();
  }
  else
  {//general compile function
    jit_compile_de_func_general();
  }
}

inline void JIT2::compile_du_32bit_ld_st_basic()
{
  jit_compile_du_general();
}

void JIT2::compile_inst_with_cond(Core *core,word_t creg_z)
{
  if(creg_z != 0)
  {//condition
    jit_label_t label_end_of_if = jit_label_undefined;
    jit_label_t label_if_branch = jit_label_undefined;
    jit_value_t jit_cond_val = compile_cond_val(core,creg_z);
    jit_insn_branch_if_not(jit_current_func,jit_cond_val,&label_end_of_if);
    //jit_insn_branch(jit_current_func,&label_end_of_if);

    compile_current_inst();

    //end of if branch
    jit_insn_label(jit_current_func,&label_end_of_if);
  }
  else
  {// no condition
    compile_current_inst();
  }
}

jit_value_t JIT2::compile_cond_val(Core *core,word_t creg_z)
{
  jit_value_t jit_z_val = compile_uint(creg_z & 0x01);
  reg_idx_t *reg_idx = &cond_tbl[creg_z];
  jit_value_t jit_reg_val = compile_reg_read(reg_idx->side,reg_idx->idx);
  jit_value_t jit_const_zero = compile_uint(0);
  jit_value_t jit_reg_eq_zero = jit_insn_eq(jit_current_func,jit_reg_val,jit_const_zero);
  jit_value_t jit_cond_val = jit_insn_eq(jit_current_func,jit_z_val,jit_reg_eq_zero);
  return jit_cond_val;
}

inline jit_value_t JIT2::compile_uint(jit_nint uint_val)
{
  return jit_value_create_nint_constant(jit_current_func,jit_type_uint,uint_val);
}

inline jit_value_t JIT2::compile_int(jit_nint int_val)
{
  return jit_value_create_nint_constant(jit_current_func,jit_type_int,int_val);
}

inline jit_value_t JIT2::compile_ulong(jit_ulong ul_val)
{
  return jit_value_create_long_constant(jit_current_func,jit_type_ulong,ul_val);
}

inline jit_value_t JIT2::compile_ptr(word_t *ptr)
{
  return jit_value_create_nint_constant(jit_current_func,jit_type_uint,(jit_nint)ptr);
}

inline jit_value_t JIT2::compile_byte_ptr(byte_t *ptr)
{
  return jit_value_create_nint_constant(jit_current_func,jit_type_uint,(jit_nint)ptr);
}

inline void JIT2::compile_prolog_and_epilog_proc()
{
  compile_prolog_proc();
  compile_epilog_proc();
}

inline void JIT2::compile_epilog_proc()
{
  /*
  if(jit_stw_num > 0)
  {// none-condtion stw
    compile_stw();
    jit_stw_num = 0;
  }
  */

  /*
  if(jit_reg_ch_num > 0)
  {// none-condtion register change
    compile_reg_ch();
    jit_reg_ch_num = 0;
  }
  */
  compile_reg_ch();
  compile_stw_proc();
}

inline void JIT2::compile_prolog_proc()
{
  //jit_insn_call_native(jit_current_func,NULL,wrap_bb_prolog_proc,jit_signature_void_void,NULL,0,0);
  jit_insn_call_native(jit_current_func,NULL,bb_prolog_proc,jit_signature_void_void,NULL,0,0);
}

inline void JIT2::compile_bb_combined_prolog_proc()
{
  jit_value_t jit_cycles = compile_uint(jit_bb_cycles);
  jit_value_t jit_inst_nums = compile_uint(jit_bb_inst_nums);
  jit_value_t jit_params[2] = {jit_cycles,jit_inst_nums};
  jit_insn_call_native(jit_current_func,NULL,
    wrap_bb_combined_prolog_proc,jit_signature_void_uint2,jit_params,2,0);
}

inline void JIT2::compile_update_pc(word_t pc_diff)
{
  jit_value_t jit_pc_addr = compile_ptr(&current_core->pce1);
  jit_value_t jit_pc_val = jit_insn_load_relative(jit_current_func,
    jit_pc_addr,0,jit_type_uint);
  jit_value_t jit_pc_diff = compile_uint(pc_diff);
  jit_value_t jit_pc_new_val = jit_insn_add(jit_current_func,jit_pc_val,jit_pc_diff);
  jit_insn_store_relative(jit_current_func,
    jit_pc_addr,0,jit_pc_new_val);
}

inline void JIT2::compile_update_inst_num()
{
  jit_value_t jit_addr_of_total_inst = compile_ptr((word_t*)&current_core->total_inst);
  jit_value_t jit_total_inst = jit_insn_load_relative(jit_current_func,
    jit_addr_of_total_inst,0,jit_type_ulong);
  jit_value_t jit_diff = compile_uint(jit_bb_inst_nums);
  jit_value_t jit_new_total_inst = jit_insn_add(jit_current_func,jit_total_inst,jit_diff);
  jit_insn_store_relative(jit_current_func,
    jit_addr_of_total_inst,0,jit_new_total_inst);

}

/*****Helper*****/
inline jit_value_t JIT2::compile_reg_read_src1()
{
  return compile_reg_read(current_inst->get_side(),current_inst->get_src1());
}

inline jit_value_t JIT2::compile_reg_read_dst()
{
  return compile_reg_read(current_inst->get_side(),current_inst->get_dst());
}

inline jit_value_t JIT2::compile_reg_read_xsrc1()
{
  return compile_reg_read(current_inst->get_xside(),current_inst->get_src1());
}

inline jit_value_t JIT2::compile_reg_read_xsrc2()
{
  return compile_reg_read(current_inst->get_xside(),current_inst->get_src2());
}

inline jit_value_t JIT2::compile_type_convert(jit_value_t jit_val,jit_type_t jit_type)
{
  return jit_insn_convert(jit_current_func,jit_val,jit_type,0);
}

inline jit_value_t JIT2::jit_compile_get_lsb16(jit_value_t jit_val)
{
  jit_value_t jit_const_0xFFFF = compile_uint(0xFFFF);
  return jit_insn_and(jit_current_func,jit_val,jit_const_0xFFFF);
}

inline jit_value_t JIT2::jit_compile_get_msb16(jit_value_t jit_val)
{
  jit_value_t jit_const_16 = compile_uint(16);
  return jit_insn_shr(jit_current_func,jit_val,jit_const_16);
}

jit_value_t JIT2::jit_compile_get_sign_ext_lsb5(jit_value_t jit_val)
{
  jit_label_t jit_lb_if = jit_label_undefined;
  jit_label_t jit_lb_else = jit_label_undefined;
  jit_label_t jit_lb_endif = jit_label_undefined;
  jit_value_t jit_ret = jit_value_create(jit_current_func,jit_type_uint);

  jit_value_t jit_const_0x10 = compile_uint(0x10);
  jit_value_t jit_is_minus = jit_insn_and(jit_current_func,
    jit_const_0x10,
    jit_val);

  jit_insn_branch_if(jit_current_func,jit_is_minus,&jit_lb_if);

  // if branch
  jit_insn_label(jit_current_func,&jit_lb_if);
  jit_value_t jit_const_0xFFFFFFE0 = compile_uint(0xFFFFFFE0);
  jit_value_t jit_sign_ext = jit_insn_or(jit_current_func,
    jit_val,
    jit_const_0xFFFFFFE0);
  jit_insn_store(jit_current_func,jit_ret,jit_sign_ext);
  jit_insn_branch(jit_current_func,&jit_lb_endif);

  // else branch
  jit_insn_label(jit_current_func,&jit_lb_else);
  jit_insn_store(jit_current_func,jit_ret,jit_val);

  // endif
  jit_insn_label(jit_current_func,&jit_lb_endif);

  return jit_ret;
}

jit_value_t JIT2::jit_compile_get_sign_ext_lsb16(jit_value_t jit_val)
{
  jit_value_t jit_const_0xFFFF = compile_uint(0xFFFF);
  jit_value_t jit_lsb = jit_insn_and(jit_current_func,jit_val,jit_const_0xFFFF);
  jit_value_t jit_ret = jit_insn_convert(jit_current_func,
    jit_lsb,
    jit_type_short,
    0);
  return jit_ret;
}

jit_value_t JIT2::jit_compile_get_sign_ext_msb16(jit_value_t jit_val)
{
  jit_value_t jit_const_16 = compile_uint(16);
  jit_value_t jit_msb = jit_insn_shr(jit_current_func,jit_val,jit_const_16);
  jit_value_t jit_ret = jit_insn_convert(jit_current_func,
    jit_msb,
    jit_type_short,
    0);
  return jit_ret;
}

jit_value_t JIT2::compile_reg_read(word_t side,word_t idx)
{
  word_t* reg_addr = current_core->get_reg_addr(side,idx);
  jit_value_t jit_reg_addr = compile_ptr(reg_addr);
  jit_value_t jit_reg_val = jit_insn_load_relative(jit_current_func,jit_reg_addr,0,jit_type_uint);
  return jit_reg_val;
}

jit_value_t JIT2::jit_compile_get_uint(jit_value_t jit_val,word_t start,word_t len)
{
  jit_value_t jit_ret = jit_val;
  word_t mask = (1 << len) - 1;
  if(start > 0)
  {// shift right
    jit_ret = jit_insn_shr(jit_current_func,
      jit_val,
      compile_uint(start));
  }
  jit_ret = jit_insn_and(jit_current_func,
    jit_ret,
    compile_uint(mask));
  return jit_ret;
}

//mask = ~(( (1 << (cstb - csta + 1)) - 1) << csta)
jit_value_t JIT2::jit_compile_clr(jit_value_t jit_val,jit_value_t jit_csta,jit_value_t jit_cstb)
{
  jit_value_t mask_len = jit_insn_sub(jit_current_func,jit_cstb,jit_csta);
  jit_value_t jit_const_one = compile_uint(1);
  mask_len = jit_insn_add(jit_current_func,mask_len,jit_const_one);
  jit_value_t mask = jit_insn_shl(jit_current_func,jit_const_one,mask_len);
  mask = jit_insn_sub(jit_current_func,mask,jit_const_one);
  mask = jit_insn_shl(jit_current_func,mask,jit_csta);
  mask = jit_insn_not(jit_current_func,mask);
  jit_value_t jit_ret = jit_insn_and(jit_current_func,
    jit_val,
    mask);
  return jit_ret;
}

jit_value_t JIT2::jit_compile_du_mode_proc(word_t mode,word_t offset_factor,
    jit_value_t jit_offset,jit_value_t jit_base_addr)
{
  jit_value_t jit_offset_byte = jit_insn_mul(jit_current_func,
    jit_offset,
    compile_uint(offset_factor));
  jit_value_t jit_mem_addr = jit_value_create(jit_current_func,jit_type_uint);
  switch (mode)
  {
  case 0x8:
  case 0xC:
    {
      jit_value_t jit_new_base = jit_insn_sub(jit_current_func,
        jit_base_addr,
        jit_offset_byte);
      jit_mem_addr = jit_new_base;
      compile_push_reg_ch(current_inst->get_xside(),
        current_inst->get_src1(),
        jit_new_base);
    }
    break;

  case 0x9:
  case 0xD:
    {
      jit_value_t jit_new_base = jit_insn_add(jit_current_func,
        jit_base_addr,
        jit_offset_byte);
      jit_mem_addr = jit_new_base;
      compile_push_reg_ch(current_inst->get_xside(),
        current_inst->get_src1(),
        jit_new_base);
    }
    break;

  case 0x0:
  case 0x4:
    {
      jit_mem_addr = jit_insn_sub(jit_current_func,
          jit_base_addr,
          jit_offset_byte);
    }
    break;

  case 0x1:
  case 0x5:
    {
      jit_mem_addr = jit_insn_add(jit_current_func,
          jit_base_addr,
          jit_offset_byte);
    }
    break;

  case 0xA:
  case 0xE:
    {
      jit_value_t jit_new_base = jit_insn_sub(jit_current_func,
        jit_base_addr,
        jit_offset_byte);
      jit_mem_addr = jit_base_addr;
      compile_push_reg_ch(current_inst->get_xside(),
        current_inst->get_src1(),
        jit_new_base);
    }
    break;

  case 0xB:
  case 0xF:
    {
      jit_value_t jit_new_base = jit_insn_add(jit_current_func,
        jit_base_addr,
        jit_offset_byte);
      jit_mem_addr = jit_base_addr;
      compile_push_reg_ch(current_inst->get_xside(),
        current_inst->get_src1(),
        jit_new_base);
    }
    break;

  default:
    break;
  }
  return jit_mem_addr;
}

//TODO extern libjit , jit_insn_bswap_xxx
jit_value_t JIT2::jit_compile_bswap_uint(jit_value_t jit_val)
{
  jit_value_t jit_const_24 = compile_uint(24);
  jit_value_t jit_const_8 = compile_uint(8);
  jit_value_t jit_const_0x00FF0000 = compile_uint(0x00FF0000);
  jit_value_t jit_const_0x0000FF00 = compile_uint(0x0000FF00);
  jit_value_t jit_const_0x000000FF = compile_uint(0x000000FF);
  jit_value_t jit_part1 = jit_insn_shl(jit_current_func,jit_val,jit_const_24);
  jit_value_t jit_part2 = jit_insn_shl(jit_current_func,jit_val,jit_const_8);
  jit_value_t jit_part3 = jit_insn_shr(jit_current_func,jit_val,jit_const_8);
  jit_value_t jit_part4 = jit_insn_shr(jit_current_func,jit_val,jit_const_24);
  jit_part2 = jit_insn_and(jit_current_func,jit_part2,jit_const_0x00FF0000);
  jit_part3 = jit_insn_and(jit_current_func,jit_part3,jit_const_0x0000FF00);
  jit_part4 = jit_insn_and(jit_current_func,jit_part4,jit_const_0x000000FF);

  jit_value_t jit_re = jit_insn_or(jit_current_func,
    jit_part1,
    jit_part2);
  jit_part3 = jit_insn_or(jit_current_func,
    jit_part3,
    jit_part4);
  jit_re = jit_insn_or(jit_current_func,
    jit_re,
    jit_part3);
  return jit_re;
}

void JIT2::jit_compile_de_func_general()
{
  jit_value_t jit_params[2] = {compile_ptr((word_t*)current_core),
    compile_ptr((word_t*)current_inst)};

#ifdef DE_FUNC_FASTCALL
  jit_insn_call_native(jit_current_func,
    NULL,
    current_inst->get_de_func(),
    jit_signature_fastcall_void_uint2,
    jit_params,
    2,
    0);
#else
  jit_insn_call_native(jit_current_func,
    NULL,
    current_inst->get_de_func(),
    jit_signature_void_uint2,
    jit_params,
    2,
    0);
#endif

  prolog_epilog_flag |= 0x1;
}

void JIT2::jit_compile_l2_mem_write_byte(jit_value_t jit_addr,jit_value_t jit_val)
{
  jit_value_t jit_params[2] = {jit_addr,jit_val};
  jit_insn_call_native(jit_current_func,
    NULL,
    wrap_mem_write_byte,
    jit_signature_void_uint_ubyte,
    jit_params,
    2,
    0);
}

void JIT2::jit_compile_l2_mem_write_xhalf(jit_value_t jit_addr,jit_value_t jit_val)
{
  jit_value_t jit_params[2] = {jit_addr,jit_val};
  jit_insn_call_native(jit_current_func,
    NULL,
    wrap_mem_write_xhalf,
    jit_signature_void_uint_uhalf,
    jit_params,
    2,
    0);
}

void JIT2::jit_compile_l2_mem_write_xqword(jit_value_t jit_addr,jit_value_t jit_val)
{
  jit_value_t jit_params[2] = {jit_addr,jit_val};
  jit_insn_call_native(jit_current_func,
    NULL,
    wrap_mem_write_xqword,
    jit_signature_void_uint_ulong,
    jit_params,
    2,
    0);
}

void JIT2::jit_compile_l2_mem_write_xword(jit_value_t jit_addr,jit_value_t jit_val)
{
  jit_value_t jit_params[2] = {jit_addr,jit_val};
  jit_insn_call_native(jit_current_func,
    NULL,
    wrap_mem_write_xword,
    jit_signature_void_uint2,
    jit_params,
    2,
    0);

  /*
  jit_value_t jit_CIPRL_addr = compile_uint(0x01A0FFE4);
  jit_value_t jit_is_CIPRL = jit_insn_eq(jit_current_func,jit_addr,jit_CIPRL_addr);
  jit_value_t jit_xendian_val = jit_compile_bswap_uint(jit_val);
  jit_value_t jit_write_val = jit_value_create(jit_current_func,jit_type_uint);

  jit_insn_branch_if(jit_current_func,jit_is_CIPRL,&jit_lb_if);
  // else branch
  jit_insn_label(jit_current_func,&jit_lb_else);
  jit_insn_store(jit_current_func,jit_write_val,jit_xendian_val);
  jit_insn_branch(jit_current_func,&jit_lb_endif);

  jit_insn_label(jit_current_func,&jit_lb_if);

  // if branch
  jit_value_t jit_old_ciprl = jit_compile_l2_mem_read_word(jit_addr);
  jit_value_t jit_not_xendian_val = jit_insn_not(jit_current_func,jit_xendian_val);
  jit_value_t jit_new_ciprl = jit_insn_and(jit_current_func,
    jit_old_ciprl,
    jit_not_xendian_val);
  jit_insn_store(jit_current_func,jit_write_val,jit_new_ciprl);
  jit_insn_branch(jit_current_func,&jit_lb_endif);

  // endif
  jit_insn_label(jit_current_func,&jit_lb_endif);

  jit_value_t jit_tag = jit_insn_shr(jit_current_func,jit_addr,compile_uint(18));
  jit_value_t jit_offset = jit_insn_and(jit_current_func,
    jit_addr,
    compile_uint(L2MemCtroller::page_size - 1));

  jit_value_t jit_ptable_addr = compile_byte_ptr((byte_t*)&l2->ptable);
  jit_value_t jit_page = jit_insn_load_elem(jit_current_func,
    jit_ptable_addr,
    jit_tag,
    jit_type_create_pointer(jit_type_ubyte,1));

  jit_value_t jit_mem_addr = jit_insn_add(jit_current_func,
    jit_page,
    jit_offset);

  jit_insn_store_relative(jit_current_func,
    jit_mem_addr,
    0,
    jit_xendian_val);
    */
}

jit_value_t JIT2::jit_compile_l2_mem_read_word(jit_value_t jit_addr)
{
  jit_value_t jit_tag = jit_insn_shr(jit_current_func,
    jit_addr,
    compile_uint(18)); // (addr >> 18);

  jit_value_t jit_offset = jit_insn_and(jit_current_func,
    jit_addr,
    compile_uint(L2MemCtroller::page_size - 1));

  jit_value_t jit_ptable_addr = compile_byte_ptr((byte_t*)&l2->ptable);
  jit_value_t jit_page = jit_insn_load_elem(jit_current_func,
    jit_ptable_addr,
    jit_tag,
    jit_type_create_pointer(jit_type_ubyte,1));

  jit_value_t jit_mem_addr = jit_insn_add(jit_current_func,
    jit_page,
    jit_offset);

  jit_value_t jit_val = jit_insn_load_relative(jit_current_func,
    jit_mem_addr,
    0,
    jit_type_uint);

#ifdef MD_CROSS_ENDIAN
  jit_val = jit_compile_bswap_uint(jit_val);
#endif
 
  return jit_val;
}

/*****LUnit*****/
void JIT2::jit_compile_lu_de_32bit_1or2_src_add_f1()
{
  jit_value_t jit_src1_val = compile_reg_read_src1();
  jit_value_t jit_src2_val = compile_reg_read_xsrc2();

  // FIXME. convert to signed type?
  jit_value_t jit_dst_val = jit_insn_add(jit_current_func,
    jit_src1_val,
    jit_src2_val);
  jit_push_reg_ch(current_inst->get_side(),
    current_inst->get_dst(),
    jit_dst_val);
}

//TODO remove it
//same as jit_compile_lu_de_32bit_1or2_src_add_f1
void JIT2::jit_compile_lu_de_32bit_1or2_src_add_f1_nc()
{
  jit_value_t jit_src1_val = compile_reg_read_src1();
  jit_value_t jit_src2_val = compile_reg_read_xsrc2();

  // FIXME. convert to signed type?
  jit_value_t jit_dst_val = jit_insn_add(jit_current_func,
    jit_src1_val,
    jit_src2_val);
  jit_push_reg_ch(current_inst->get_side(),
    current_inst->get_dst(),
    jit_dst_val);
}

void JIT2::jit_compile_lu_de_32bit_1or2_src_add_f2()
{
  jit_value_t jit_src1_val = compile_reg_read_src1();
  jit_value_t jit_src2_val = compile_reg_read_xsrc2();

  jit_src1_val = jit_insn_convert(jit_current_func,
    jit_src1_val,
    jit_type_int,
    0); // convert to sign int
  jit_src1_val = jit_insn_convert(jit_current_func,
    jit_src1_val,
    jit_type_long,
    0); // convert to long long

  jit_src2_val = jit_insn_convert(jit_current_func,
    jit_src2_val,
    jit_type_int,
    0); // convert to sign int
  jit_src2_val = jit_insn_convert(jit_current_func,
    jit_src2_val,
    jit_type_long,
    0); // convert to long long

  //jit_dst_val is long long type
  jit_value_t jit_dst_val = jit_insn_add(jit_current_func,
    jit_src1_val,
    jit_src2_val);

  jit_push_reg_pair_ch(current_inst->get_side(),
    current_inst->get_dst(),
    jit_dst_val);
}

/*
  word_t src1_val = get_sign_ext_lsb5_quick(src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = (src1_val == src2_val);
  core->push_reg_ch(side,dst,dst_val);
  */
void JIT2::jit_compile_lu_de_32bit_1or2_src_cmpeq_f2()
{
  word_t src1_val = get_sign_ext_lsb5_quick(current_inst->get_src1());

  //jit_value_t jit_const_src1 = compile_uint(current_inst->get_src1());
  //jit_value_t jit_src1_val = jit_compile_get_sign_ext_lsb5(jit_const_src1);

  jit_value_t jit_const_src1 = compile_uint(src1_val);
  jit_value_t jit_src2_val = compile_reg_read_xsrc2();
  jit_value_t jit_dst_val = jit_insn_eq(jit_current_func,
    jit_const_src1,
    jit_src2_val);
  jit_push_reg_ch(current_inst->get_side(),
    current_inst->get_dst(),
    jit_dst_val);
}

void JIT2::jit_compile_lu_de_32bit_1or2_src_add_f3()
{
  jit_value_t jit_src1_val = compile_reg_read_src1();
  jit_value_t jit_src2_val = compile_reg_read_xsrc2();

  // FIXME. convert to signed type?
  jit_value_t jit_dst_val = jit_insn_add(jit_current_func,
    jit_src1_val,
    jit_src2_val);
  jit_push_reg_ch(current_inst->get_side(),
    current_inst->get_dst(),
    jit_dst_val);
}

void JIT2::jit_compile_lu_de_32bit_1or2_src_add_f4()
{
  jit_value_t jit_src1_val = compile_reg_read_src1();
  jit_value_t jit_src2_val = compile_reg_read_xsrc2();

  // FIXME. convert to signed type?
  jit_value_t jit_dst_val = jit_insn_add(jit_current_func,
    jit_src1_val,
    jit_src2_val);
  jit_push_reg_ch(current_inst->get_side(),
    current_inst->get_dst(),
    jit_dst_val);
}

void JIT2::jit_compile_lu_de_32bit_1or2_src_add_f5()
{
  jit_value_t jit_src1_val = compile_reg_read_src1();
  jit_value_t jit_src2_val = compile_reg_read_xsrc2();

  // FIXME. convert to signed type?
  jit_value_t jit_dst_val = jit_insn_add(jit_current_func,
    jit_src1_val,
    jit_src2_val);
  jit_push_reg_ch(current_inst->get_side(),
    current_inst->get_dst(),
    jit_dst_val);
}


/*****SUnit*****/
void JIT2::jit_compile_su_de_32bit_1or2_src_shl_f1()
{
  jit_label_t jit_lb_if = jit_label_undefined;
  jit_label_t jit_lb_else = jit_label_undefined;
  jit_label_t jit_lb_endif = jit_label_undefined;
  jit_value_t jit_const_0x3F = compile_uint(0x3F);
  jit_value_t jit_const_0x20 = compile_uint(0x20);
  jit_value_t jit_src1_val = compile_reg_read_src1();
  jit_src1_val = jit_insn_and(jit_current_func,jit_const_0x3F,jit_src1_val);
  jit_value_t jit_dst_val = jit_value_create(jit_current_func,jit_type_uint);

  jit_value_t jit_is_sht_ovf = jit_insn_ge(jit_current_func,
    jit_src1_val,
    jit_const_0x20);

  jit_insn_branch_if(jit_current_func,jit_is_sht_ovf,&jit_lb_if);

  //else branch
  jit_insn_label(jit_current_func,&jit_lb_else);
  jit_value_t jit_src2_val = compile_reg_read_xsrc2();
  jit_value_t jit_ret = jit_insn_shl(jit_current_func,
    jit_src2_val,
    jit_src1_val);
  jit_insn_store(jit_current_func,jit_dst_val,jit_ret);
  jit_insn_branch(jit_current_func,&jit_lb_endif);

  //if branch
  jit_insn_label(jit_current_func,&jit_lb_if);
  jit_insn_store(jit_current_func,jit_dst_val,compile_uint(0));
  //jit_insn_branch(jit_current_func,&jit_lb_endif);

  // endif
  jit_insn_label(jit_current_func,&jit_lb_endif);

  compile_push_reg_ch(current_inst->get_side(),current_inst->get_dst(),jit_dst_val);
}

void JIT2::jit_compile_su_de_32bit_1or2_src_shl_f2_general()
{
  jit_value_t jit_const_src1 = compile_uint(current_inst->get_src1());
  jit_value_t jit_src2_val = compile_reg_read_xsrc2();
  jit_value_t jit_dst_val = jit_insn_shl(jit_current_func,
    jit_src2_val,
    jit_const_src1);
  compile_push_reg_ch(current_inst->get_side(),current_inst->get_dst(),jit_dst_val);
}

void JIT2::jit_compile_su_de_32bit_1or2_src_shl_f2()
{
  jit_compile_su_de_32bit_1or2_src_shl_f2_general();
}

void JIT2::jit_compile_su_de_32bit_1or2_src_shl_f2_nc()
{
  jit_compile_su_de_32bit_1or2_src_shl_f2_general();
}

void JIT2::jit_compile_su_de_32bit_1or2_src_clr()
{
  jit_value_t jit_src1_val = compile_reg_read(current_inst->get_side(),
    current_inst->get_src1());
  jit_value_t jit_src2_val = compile_reg_read(current_inst->get_xside(),
    current_inst->get_src2());
  jit_value_t jit_cstb = jit_compile_get_uint(jit_src1_val,0,5);
  jit_value_t jit_csta = jit_compile_get_uint(jit_src1_val,5,5);
  jit_value_t jit_dst_val = jit_compile_clr(jit_src2_val,jit_csta,jit_cstb);
  compile_push_reg_ch(current_inst->get_side(),
    current_inst->get_dst(),
    jit_dst_val);
}

void JIT2::jit_compile_su_de_32bit_mvk()
{
  jit_value_t src1_val = compile_uint(current_inst->get_src1());
  compile_push_reg_ch(current_inst->get_side(),
    current_inst->get_dst(),
    src1_val);
}

void JIT2::jit_compile_su_de_32bit_mvkh()
{
  jit_value_t jit_reg_val = compile_reg_read(current_inst->get_side(),
    current_inst->get_dst());
  word_t src1_hi = current_inst->get_src1() << 16;
  jit_value_t jit_const_ffff = compile_uint(0xFFFF);
  jit_value_t jit_tmp1 = jit_insn_and(jit_current_func,jit_reg_val,jit_const_ffff);
  jit_value_t jit_const_16 = compile_uint(16);
  jit_value_t jit_src1_hi = compile_uint(src1_hi);
  jit_value_t jit_dst_val = jit_insn_or(jit_current_func,jit_src1_hi,jit_tmp1);
  compile_push_reg_ch(current_inst->get_side(),
    current_inst->get_dst(),
    jit_dst_val);
}

/*****MUnit*****/
void JIT2::jit_compile_mu_de_32bit_mpy_mpyu()
{
  jit_value_t jit_src1_val = compile_reg_read(current_inst->get_side(),
    current_inst->get_src1());
  jit_value_t jit_src2_val = compile_reg_read(current_inst->get_xside(),
    current_inst->get_src2());

  jit_value_t jit_ua = jit_compile_get_lsb16(jit_src1_val);
  jit_value_t jit_ub = jit_compile_get_lsb16(jit_src2_val);
  jit_value_t jit_dst_val = jit_insn_mul(jit_current_func,jit_ua,jit_ub);
  jit_compile_push_reg_delay_ch(current_inst->get_side(),
    current_inst->get_dst(),
    jit_dst_val,
    1);
}

void JIT2::jit_compile_mu_de_32bit_mpy_mpylh()
{
  jit_value_t jit_src1_val = compile_reg_read(current_inst->get_side(),
    current_inst->get_src1());
  jit_value_t jit_src2_val = compile_reg_read(current_inst->get_xside(),
    current_inst->get_src2());

  jit_value_t jit_sa = jit_compile_get_sign_ext_lsb16(jit_src1_val);
  jit_value_t jit_sb = jit_compile_get_sign_ext_msb16(jit_src2_val);
  jit_value_t jit_dst_val = jit_insn_mul(jit_current_func,
    jit_sa,
    jit_sb);

  jit_compile_push_reg_delay_ch(current_inst->get_side(),
    current_inst->get_dst(),
    jit_dst_val,
    1);
}

/*****NUnit*****/
void JIT2::jit_compile_nu_de_32bit_nop()
{
  if(current_inst->get_src1() > jit_remain_nops)
  {
    jit_remain_nops = current_inst->get_src1();
  }
}

/*****DUnit*****/
void JIT2::jit_compile_du_general()
{
  jit_value_t jit_inst = compile_ptr((word_t*)current_inst);
  jit_value_t jit_params[1] = {jit_inst};
  jit_insn_call_native(jit_current_func,NULL,wrap_du_general,jit_signature_void_uint,jit_params,1,0);
  prolog_epilog_flag |= 0x1;
}

void JIT2::jit_compile_du_de_32bit_ld_st_basic_ldw_f2_nc()
{
  const word_t code = current_inst->get_code();
  word_t mode = get_uint(code,9,4);
  jit_value_t jit_base_addr = compile_reg_read_xsrc1();
  word_t offset = current_inst->get_src2();
  const word_t offset_factor = 4;

  //MODE_PROC;
  jit_value_t jit_mem_addr = jit_compile_du_mode_proc(mode,
    offset_factor,
    compile_int(offset),
    jit_base_addr);

  jit_value_t jit_ld_result = jit_compile_l2_mem_read_word(jit_mem_addr);

  jit_compile_push_reg_delay_ch2(jit_ld_result,4);
}

void JIT2::jit_compile_du_de_32bit_ld_st_basci_stw(jit_value_t jit_offset)
{
  const word_t code = current_inst->get_code();
  word_t mode = get_uint(code,9,4);
  jit_value_t jit_base_addr = compile_reg_read_xsrc1();
  const word_t offset_factor = 4;
  jit_value_t jit_stw_val = compile_reg_read(current_inst->get_side(),
    current_inst->get_dst());

  jit_value_t jit_mem_addr = jit_compile_du_mode_proc(mode,
    offset_factor,
    jit_offset,
    jit_base_addr);

  //jit_push_stw_req(jit_mem_addr,jit_stw_val,TYPE_U32);
  compile_push_stw_req(jit_mem_addr,compile_uint(TYPE_U32),jit_stw_val);
}

void JIT2::jit_compile_du_de_32bit_ld_st_basic_stdw(jit_value_t jit_offset,const word_t offset_factor)
{
  const word_t code = current_inst->get_code();
  const word_t dst = current_inst->get_dst();
  word_t mode = get_uint(code,9,4);
  jit_value_t jit_base_addr = compile_reg_read_xsrc1();
  jit_value_t jit_stw_val = compile_reg_read_dst();
  jit_value_t jit_stw_qval = jit_value_create(jit_current_func,jit_type_ulong);

  jit_value_t jit_mem_addr = jit_compile_du_mode_proc(mode,
    offset_factor,
    jit_offset,
    jit_base_addr);

  if(is_reg_even(dst))
  {
    jit_value_t jit_tmp1 = compile_reg_read(current_inst->get_side(),current_inst->get_dst()+1);
    jit_value_t jit_qval = compile_type_convert(jit_tmp1,jit_type_ulong);
    jit_qval = jit_insn_shl(jit_current_func,jit_qval,compile_uint(32));
    jit_qval = jit_insn_or(jit_current_func,jit_qval,jit_stw_val);

    bb_stw_req_t stw_req;
    stw_req.jit_stw_val = jit_qval;
    stw_req.jit_addr = jit_mem_addr;
    stw_req.type = TYPE_U64;
  }
  else
  {
    current_core->panic("<WARN> dst is odd register in STDW");
  }
}

void JIT2::jit_compile_du_de_32bit_ld_st_basic_stw_f1()
{
  jit_value_t jit_offset = compile_reg_read_xsrc2();
  jit_compile_du_de_32bit_ld_st_basci_stw(jit_offset);
}

//FIXME. error?
void JIT2::jit_compile_du_de_32bit_ld_st_basic_stw_f2()
{
  jit_value_t jit_offset = compile_uint(current_inst->get_src2());
  jit_compile_du_de_32bit_ld_st_basci_stw(jit_offset);
  DBG_JIT_FUNC;
}

void JIT2::jit_compile_du_de_32bit_ld_st_basic_stnw_f1()
{
  jit_value_t jit_offset = compile_reg_read_xsrc2();
  jit_compile_du_de_32bit_ld_st_basci_stw(jit_offset);
}

void JIT2::jit_compile_du_de_32bit_ld_st_basic_stnw_f2()
{
  jit_value_t jit_offset = compile_int(current_inst->get_src2());
  jit_compile_du_de_32bit_ld_st_basci_stw(jit_offset);
}

void JIT2::jit_compile_du_de_32bit_ld_st_basic_stdw_f1()
{
  const word_t offset_factor = 8;
  jit_value_t jit_offset = compile_reg_read_xsrc2();
  jit_compile_du_de_32bit_ld_st_basic_stdw(jit_offset,offset_factor);
}

void JIT2::jit_compile_du_de_32bit_ld_st_basic_stdw_f2()
{
  const word_t offset_factor = 8;
  jit_value_t jit_offset = compile_uint(current_inst->get_src2());
  jit_compile_du_de_32bit_ld_st_basic_stdw(jit_offset,offset_factor);
}

void JIT2::jit_compile_du_de_32bit_ld_st_basic_stndw_f1()
{
  const word_t sc = get_uint(current_inst->get_code(),23,1);
  const word_t offset_factor = (sc == 1) ? 8 : 1;
  jit_value_t jit_offset = compile_reg_read_xsrc2();
  jit_compile_du_de_32bit_ld_st_basic_stdw(jit_offset,offset_factor);
}

void JIT2::jit_compile_du_de_32bit_ld_st_basic_stndw_f2()
{
  const word_t sc = get_uint(current_inst->get_code(),23,1);
  const word_t offset_factor = (sc == 1) ? 8 : 1;
  jit_value_t jit_offset = compile_uint(current_inst->get_src2());
  jit_compile_du_de_32bit_ld_st_basic_stdw(jit_offset,offset_factor);
}


END_NS

#endif
