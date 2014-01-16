#ifdef CORE_USE_LLVM

#pragma comment(lib, "LLVMJIT.lib")
#pragma comment(lib, "LLVMInterpreter.lib")
#pragma comment(lib, "LLVMX86CodeGen.lib")
#pragma comment(lib, "LLVMRuntimeDyld.lib")
#pragma comment(lib, "LLVMExecutionEngine.lib")
#pragma comment(lib, "LLVMAsmPrinter.lib")
#pragma comment(lib, "LLVMSelectionDAG.lib")
#pragma comment(lib, "LLVMX86Desc.lib")
#pragma comment(lib, "LLVMX86Utils.lib")
#pragma comment(lib, "LLVMCodeGen.lib")
#pragma comment(lib, "LLVMX86AsmPrinter.lib")
#pragma comment(lib, "LLVMX86Info.lib")
#pragma comment(lib, "LLVMScalarOpts.lib")
#pragma comment(lib, "LLVMInstCombine.lib")
#pragma comment(lib, "LLVMTransformUtils.lib")
#pragma comment(lib, "LLVMAnalysis.lib")
#pragma comment(lib, "LLVMTarget.lib")
#pragma comment(lib, "LLVMCore.lib")
#pragma comment(lib, "LLVMMC.lib")
#pragma comment(lib, "LLVMObject.lib")
#pragma comment(lib, "LLVMSupport.lib")

#include <unordered_map>
#include "jit/inc/jit_support.hpp"
#include "jit/inc/jit_thread.hpp"
#include "decode/inc/inst.hpp"
#include "core/inc/core.hpp"
#include "core/inc/l2_mem_ctrl.hpp"
#include "profiler/inc/basic_block.hpp"

using namespace llvm;
BEGIN_NS

typedef void (*jit_compile_t)(void);
typedef std::unordered_map<uint,jit_compile_t> jit_compile_map_t;
static jit_compile_map_t jit_compile_map;

  // init JIT compile function map
#define INSERT_JIT_FUNC(de_func,jit_func)\
  jit_compile_map.insert(std::make_pair((uint)de_func,jit_func))

#define SIDE  current_inst->get_side()
#define XSIDE current_inst->get_xside()
#define SRC1  current_inst->get_src1()
#define SRC2  current_inst->get_src2()
#define DST   current_inst->get_dst()

#define GGC getGlobalContext()

Module      JIT::llvm_module("c64x",GGC);
IRBuilder<> JIT::llvm_builder(GGC);
ExecutionEngine* JIT::llvm_ee = NULL;

struct reg_wb_t2
{
  uint* reg_addr;
  uint  val;
};

uint regs[32];
uint stw_req_num = 0;
reg_wb_t2 reg_wb_list[8];

Type *type_of_regs_ary;
Type *type_of_struct_reg_wb_t;
Value *ptr_to_regs_ary;
Value *ptr_to_core_reg;

Constant *val_core;
Constant *const_of_reg_wb_list;
Constant *const_of_ptr_to_regs_ary;
Constant *const_five;
Constant *const_four;
Constant *const_one;
Constant *const_zero;

Value *ptr_to_pc_e1;
Value *ptr_to_total_inst;

Value *ptr_to_reg_ch_num;
Value *ptr_to_reg_wb_list;
Value *ptr_to_stw_req_num;

static BasicBlock *current_bb;
static Core *current_core;
static llvm::Function *current_func;
static word_t jit_bb_inst_nums;
static word_t jit_remain_nops;
static word_t jit_bb_cycles;
static word_t prolog_epilog_flag;
static Instruction *current_inst;
static Instruction *prev_inst;

FunctionType *llvm_de_func_t;
FunctionType *llvm_void_void_ft;
FunctionType *llvm_void_uint_ft;
llvm::Function *su_de_func_mvk_f1;
llvm::Function *su_de_func_mvk_f2;

Value* JIT::compile_ptr(uint64_t ptr,llvm::Type* type)
{
  return ConstantExpr::getIntToPtr(ConstantInt::get(Type::getInt32Ty(GGC),ptr),
    llvm::PointerType::getUnqual(type));
}

Value* JIT::compile_const_u32(word_t val)
{
  return ConstantInt::get(Type::getInt32Ty(GGC),val);
}

void JIT::init_jit_compile_func()
{
  //LUnit
  INSERT_JIT_FUNC(LUnit::de_32bit_1or2_src_or_f2_nc,
    jit_compile_lu_de_32bit_1or2_src_or_f2_nc);
  INSERT_JIT_FUNC(LUnit::de_32bit_1or2_src_cmpltu_f1_nc,
    jit_compile_lu_de_32bit_1or2_src_cmpltu_f1_nc);
  INSERT_JIT_FUNC(LUnit::de_32bit_1or2_src_add_f1_nc,
    jit_compile_lu_de_32bit_1or2_src_add_f1_nc);
}

void JIT::init()
{
  init_jit_compile_func();
  current_core = Core::get();
  InitializeNativeTarget();
  JITThread::init();

  if(llvm_ee == NULL)
  {
    llvm_ee = EngineBuilder(&JIT::module()).setOptLevel(CodeGenOpt::None).create();
  }

  val_core = ConstantInt::get(Type::getInt32Ty(GGC),(uint64_t)Core::get());
  Constant *const_tmp = ConstantInt::get(Type::getInt32Ty(GGC),(uint64_t)&current_core->pce1);
  ptr_to_pc_e1 = llvm::ConstantExpr::getIntToPtr(const_tmp,
   llvm::PointerType::getUnqual(Type::getInt32Ty(GGC)));

  const_tmp = ConstantInt::get(Type::getInt32Ty(GGC),(uint64_t)&current_core->total_inst);
  ptr_to_total_inst = llvm::ConstantExpr::getIntToPtr(const_tmp,
   llvm::PointerType::getUnqual(Type::getInt32Ty(GGC)));

  llvm::Type *func_args[2] = {Type::getInt32Ty(GGC),Type::getInt32Ty(GGC)};
  llvm::Type *func_arg_1[1] = {Type::getInt32Ty(GGC)};
  llvm_de_func_t = FunctionType::get(Type::getVoidTy(GGC),func_args);
  llvm_void_void_ft = FunctionType::get(Type::getVoidTy(GGC),false);
  llvm_void_uint_ft = FunctionType::get(Type::getVoidTy(GGC),func_arg_1);

  llvm::Type *elems[2] = {llvm::PointerType::getUnqual(Type::getInt32Ty(GGC)),Type::getInt32Ty(GGC)};
  type_of_struct_reg_wb_t = llvm::StructType::create(elems);

  ptr_to_reg_ch_num = compile_ptr((uint64_t)&(Core::reg_ch_num),Type::getInt32Ty(GGC));
  ptr_to_reg_wb_list = compile_ptr((uint64_t)&(Core::reg_wb_list),type_of_struct_reg_wb_t);
  ptr_to_stw_req_num = compile_ptr((uint64_t)&(Core::stw_req_num),Type::getInt32Ty(GGC));
  ptr_to_core_reg = compile_ptr((uint64_t)&(Core::reg),Type::getInt32Ty(GGC));

  const_five = ConstantInt::get(Type::getInt32Ty(GGC),5);
  const_four = ConstantInt::get(Type::getInt32Ty(GGC),4);
  const_one = ConstantInt::get(Type::getInt32Ty(GGC),1);
  const_zero = ConstantInt::get(Type::getInt32Ty(GGC),0);
}

static void wrap_bb_epilog_proc()
{
  current_core->bb_epilog_proc();
}

void JIT::compile_bb_epilog_and_prolog_proc()
{
  //compile_bb_epilog_proc();
  //compile_bb_prolog_proc();
  compile_native_call_void_void(bb_prolog_and_epilog_proc);
}

void JIT::compile_bb_prolog_proc()
{
  compile_native_call_void_void(bb_prolog_proc);
}

void JIT::compile_bb_prolog_proc_multi_cycles(word_t nops)
{
  compile_native_call_void_uint(bb_prolog_proc_multi_cycles,nops);
}

void JIT::compile_bb_epilog_proc()
{
  //compile_native_call_void_void(wrap_bb_epilog_proc);
  compile_reg_ch_proc();
  compile_stw_proc();
}

void JIT::compile_basic_block(Core *core, c6x::BasicBlock *bb)
{
  void *entry;
  word_t pc_diff = 0;

  //first Instruction in BasicBlock
  current_bb = bb;
  Instruction *first_inst = Core::fetch_cached_inst(bb->start);

  // Add a basic block to the function. As before, it automatically inserts
  // because of the last argument.
  //Twine &block_name = "EntryBlock_" + Twine(bb->start);

  Twine &func_name = "FUNC_" + Twine(bb->start);
  current_func = 
    (llvm::Function*)(JIT::module().getOrInsertFunction(func_name.str(),
    Type::getVoidTy(GGC),(Type*)0));

  llvm::BasicBlock* enter_bb = llvm::BasicBlock::Create(GGC, "",current_func);

  // Create a basic block builder with default parameters.  The builder will
  // automatically append instructions to the basic block `BB'.
  JIT::builder().SetInsertPoint(enter_bb);

  jit_bb_inst_nums = 0;
  jit_remain_nops = 0;
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
  JIT::builder().CreateRetVoid();
  entry = JIT::EE().getPointerToFunction(current_func);

  first_inst->set_jit_func((jit_func_t)entry);
  current_inst = NULL;
  prev_inst = NULL;
}

void JIT::compile_update_pc(word_t pc_diff)
{
  Value* val_of_pc_e1 = JIT::builder().CreateLoad(ptr_to_pc_e1);
  Constant *const_pc_diff = ConstantInt::get(Type::getInt32Ty(GGC),(uint64_t)pc_diff);
  val_of_pc_e1 = JIT::builder().CreateAdd(const_pc_diff,val_of_pc_e1);
  JIT::builder().CreateStore(val_of_pc_e1,ptr_to_pc_e1);
}

void JIT::compile_update_inst_num()
{
  Value* val_of_total_inst = JIT::builder().CreateLoad(ptr_to_total_inst);
  Constant *const_diff = ConstantInt::get(Type::getInt32Ty(GGC),(uint64_t)jit_bb_inst_nums);
  val_of_total_inst = JIT::builder().CreateAdd(const_diff,val_of_total_inst);
  JIT::builder().CreateStore(val_of_total_inst,ptr_to_total_inst);
}

void JIT::compile_addr(Core *core, md_addr_t addr)
{
  current_inst = Core::fetch_cached_inst(addr); // should always hit
  compile_current_inst();

  if(!current_inst->is_next_p())
  {
    // prolog for next EP
    if(addr != current_bb->end)
    {
      prolog_epilog_flag |= 0x2;
    }

    if(prolog_epilog_flag == 1)
    {
      compile_bb_epilog_proc();
    }
    else if(prolog_epilog_flag == 2)
    {
      compile_bb_prolog_proc();
    }
    else if(prolog_epilog_flag == 3)
    {
      compile_bb_epilog_and_prolog_proc();
    }

    // process remain NOPs
    if(jit_remain_nops > 0)
    {
      if(jit_remain_nops == 1)
      {
        compile_bb_prolog_proc();
      }
      else
      {
        compile_bb_prolog_proc_multi_cycles(jit_remain_nops);
      }
      jit_bb_inst_nums += jit_remain_nops;
      jit_remain_nops = 0;
    }

    prolog_epilog_flag = 0;
  }

  prev_inst = current_inst;
}

llvm::Value* JIT::compile_core_reg_read(word_t side,word_t idx)
{
  const word_t abs_idx = (side << 5) + idx;
  return compile_core_reg_read_abs_idx(abs_idx);
}

Value* JIT::compile_core_reg_read_abs_idx(word_t idx)
{
  Value *reg_addr = JIT::builder().CreateGEP(ptr_to_core_reg,compile_const_u32(idx));
  return JIT::builder().CreateLoad(reg_addr);
}

void JIT::compile_core_push_reg_ch(word_t side,word_t idx,Value* val)
{
  const word_t abs_idx = (side << 5) + idx;
  compile_core_push_reg_ch_abs_idx(abs_idx,val);
}

void JIT::compile_core_save_reg_ch_abs_idx(word_t idx,Value* val)
{
  Value *reg_addr = JIT::builder().CreateGEP(ptr_to_core_reg,compile_const_u32(idx));
  JIT::builder().CreateStore(val,reg_addr);
}

void JIT::compile_core_push_reg_ch_abs_idx(word_t idx,Value* val)
{
  Value *val_reg_ch_num = JIT::builder().CreateLoad(ptr_to_reg_ch_num);
  Value *plus_one = JIT::builder().CreateAdd(val_reg_ch_num,const_one);
  JIT::builder().CreateStore(plus_one,ptr_to_reg_ch_num);

  Value *ptr_to_reg_ch_req = JIT::builder().CreateGEP(ptr_to_reg_wb_list,val_reg_ch_num);
  Value *reg_addr = JIT::builder().CreateGEP(ptr_to_core_reg,compile_const_u32(idx));
  
  JIT::builder().CreateStore(reg_addr,JIT::builder().CreateStructGEP(ptr_to_reg_ch_req,0));
  JIT::builder().CreateStore(val,JIT::builder().CreateStructGEP(ptr_to_reg_ch_req,1));
}

/*
  NO_CONDITION();
  word_t src2_val = core->reg_read_abs_idx(src2);
  word_t dst_val = src1 | src2_val;
  core->push_reg_ch_abs_idx(dst,dst_val);
*/
void JIT::jit_compile_lu_de_32bit_1or2_src_or_f2_nc()
{
  Value* src2_val = compile_core_reg_read_abs_idx(current_inst->get_src2());
  Value* dst_val = JIT::builder().CreateOr(src2_val,(uint64_t)current_inst->get_src1());
  compile_core_push_reg_ch_abs_idx(current_inst->get_dst(),dst_val);
}

/*
  NO_CONDITION();
  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = (src1_val < src2_val);
  core->push_reg_ch(side,dst,dst_val);
*/
void JIT::jit_compile_lu_de_32bit_1or2_src_cmpltu_f1_nc()
{
  Value* src1_val = compile_core_reg_read(SIDE,SRC1);
  Value* src2_val = compile_core_reg_read(XSIDE,SRC2);
  Value* dst_val = JIT::builder().CreateICmpULT(src1_val,src2_val);
  dst_val = JIT::builder().CreateZExt(dst_val,Type::getInt32Ty(GGC));
  compile_core_push_reg_ch(SIDE,DST,dst_val);
}

/*
  NO_CONDITION();
  word_t src1_val = core->reg_read(side,src1);
  word_t src2_val = core->reg_read(xside,src2);
  word_t dst_val = src1_val + src2_val;
  core->push_reg_ch(side,dst,dst_val);
*/
void JIT::jit_compile_lu_de_32bit_1or2_src_add_f1_nc()
{
  Value* src1_val = compile_core_reg_read(SIDE,SRC1);
  Value* src2_val = compile_core_reg_read(XSIDE,SRC2);
  Value* dst_val = JIT::builder().CreateAdd(src1_val,src2_val);
  compile_core_push_reg_ch(SIDE,DST,dst_val);
}

void JIT::compile_current_inst()
{
  if(current_inst->get_de_func() == NoneUnit::de_32bit_nop)
  {
    if(current_inst->get_src1() > jit_remain_nops)
    {
      jit_remain_nops = current_inst->get_src1();
    }
    //NOP do not need epilog
  }
  else
  {
    //find if we have special jit compile functions
    jit_compile_map_t::iterator it = jit_compile_map.find(
      (uint)current_inst->get_de_func());
    if(it != jit_compile_map.end())
    {
      jit_compile_t compile_func = it->second;
      compile_func();
    }
    else
    { // use general compile function
      Constant *val_inst = ConstantInt::get(Type::getInt32Ty(GGC),(uint64_t)current_inst);
      compile_native_call_de_func(current_inst->get_de_func(),val_core,val_inst);
    }
    prolog_epilog_flag |= 0x1;
  }
}

void JIT::compile_native_call_void_uint(void *fp,word_t arg)
{
  llvm::Function *func = (llvm::Function*)JIT::EE().getGlobalValueAtAddress(fp);
  if(NULL == func)
  {
    func = Function::Create(llvm_void_uint_ft,llvm::GlobalVariable::LinkageTypes::ExternalLinkage);
    JIT::EE().addGlobalMapping(func,fp);
  }
  JIT::builder().CreateCall(func,compile_const_u32(arg));
}

// compile native call to void(*fp)(void) function type
void JIT::compile_native_call_void_void(void *fp)
{
  llvm::Function *func = (llvm::Function*)JIT::EE().getGlobalValueAtAddress(fp);
  if(NULL == func)
  {
    func = Function::Create(llvm_void_void_ft,llvm::GlobalVariable::LinkageTypes::ExternalLinkage);
    JIT::EE().addGlobalMapping(func,fp);
  }
  JIT::builder().CreateCall(func);
}

// compile native call to de_func(core,inst);
void JIT::compile_native_call_de_func(void *fp,llvm::Value *arg1,llvm::Value *arg2)
{
  llvm::Function *func = (llvm::Function*)JIT::EE().getGlobalValueAtAddress(fp);
  if(NULL == func)
  {//the 1st time
    func = Function::Create(llvm_de_func_t,llvm::GlobalVariable::LinkageTypes::ExternalLinkage);
    JIT::EE().addGlobalMapping(func,fp);
  }
#ifdef DE_FUNC_FASTCALL
  CallInst *call = JIT::builder().CreateCall2(func,arg1,arg2);
  call->setCallingConv(CallingConv::X86_FastCall);
#else
  JIT::builder().CreateCall2(func,arg1,arg2);
#endif
}

/*
BR (stw_req_num == 0) ? end_if : if;
if:
{
  CALL bb_stw_proc();
  BR end_if;
}
end_if:
*/
void JIT::compile_stw_proc()
{
  llvm::BasicBlock* if_block = llvm::BasicBlock::Create(GGC, "if", current_func);
  llvm::BasicBlock* end_if = llvm::BasicBlock::Create(GGC, "end_if", current_func);

  Value* val_of_stw_req_num = JIT::builder().CreateLoad(ptr_to_stw_req_num);
  Value* cond = JIT::builder().CreateICmpEQ(val_of_stw_req_num,const_zero);
  JIT::builder().CreateCondBr(cond,end_if,if_block);
  JIT::builder().SetInsertPoint(if_block);
  compile_native_call_void_void(bb_stw_proc);
  JIT::builder().CreateBr(end_if);
  JIT::builder().SetInsertPoint(end_if);
}

/*
BR (reg_ch_num == 0) ? end_loop : loop;
loop:
{
  --reg_ch_num;
  req = reg_wb_list[reg_ch_num];
  *req.reg_phy_addr = req.val;
  BR (reg_ch_num == 0) ? end_loop : loop;
}
end_loop:
*/
void JIT::compile_reg_ch_proc()
{
  llvm::BasicBlock* loop = llvm::BasicBlock::Create(GGC, "loop", current_func);
  llvm::BasicBlock* end_loop = llvm::BasicBlock::Create(GGC, "end_loop", current_func);

  Value* val_of_reg_ch_num = JIT::builder().CreateLoad(ptr_to_reg_ch_num);
  Value *cond = JIT::builder().CreateICmpEQ(val_of_reg_ch_num,const_zero);
  JIT::builder().CreateCondBr(cond,end_loop,loop);

  JIT::builder().SetInsertPoint(loop);
  val_of_reg_ch_num = JIT::builder().CreateLoad(ptr_to_reg_ch_num);
  Value *minus_one = JIT::builder().CreateSub(val_of_reg_ch_num,const_one);
  JIT::builder().CreateStore(minus_one,ptr_to_reg_ch_num);

  // get addr of reg_wb_list[reg_ch_num];
  Value *ptr_to_reg_ch_req = JIT::builder().CreateGEP(ptr_to_reg_wb_list,minus_one);

  Value *ptr_to_reg_phy_addr = JIT::builder().CreateStructGEP(ptr_to_reg_ch_req,0);
  Value *ptr_to_reg_val = JIT::builder().CreateStructGEP(ptr_to_reg_ch_req,1);

  Value *val_reg_phy_addr = JIT::builder().CreateLoad(ptr_to_reg_phy_addr);
  Value *val_reg_val = JIT::builder().CreateLoad(ptr_to_reg_val);

  // *req.reg_phy_addr = req.val;
  JIT::builder().CreateStore(val_reg_val,val_reg_phy_addr);

  val_of_reg_ch_num = JIT::builder().CreateLoad(ptr_to_reg_ch_num);
  cond = JIT::builder().CreateICmpEQ(val_of_reg_ch_num,const_zero);
  JIT::builder().CreateCondBr(cond,end_loop,loop);

  JIT::builder().SetInsertPoint(end_loop);

}

END_NS

#endif