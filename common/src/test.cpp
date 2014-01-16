#include "decode/inc/fp.hpp"
#include "core/inc/core.hpp"
#include <stdlib.h>
#include <iostream>

#include "core/inc/l2_mem_ctrl.hpp"
#include "coff/inc/coff_parser.hpp"
#include "profiler/inc/common_profiler.hpp"

USING_NS

extern void verif_m_unit(void);

int AA[32];
int BB[32];

int main(int argc, char** argv){
  // verif M unit
#ifdef CORE_DBG
  verif_m_unit();
#endif

  if(argc < 2)
  {
    return 0;
  }

  Core *pCore = Core::start();
  pCore->init();
  COFF_parser parser(argv[1]);
  pCore->set_mode(BK_AT_MAIN);

  if(argc >= 3)
  {
    core_mode_t mode = (core_mode_t)strtoul(argv[2],NULL,10);
    pCore->set_mode(mode);
  }

  if(argc >= 4)
  {
    word_t thres = strtoul(argv[3],NULL,10);
    Profiler::set_jit_threshold_times(thres);
  }

  if(argc >= 5)
  {
    word_t thres = strtoul(argv[4],NULL,10);
    Profiler::set_jit_threshold_len(thres);
  }

  parser.connect(pCore);
  parser.set_reverse(false);
  parser.parse();
  
  pCore->init();
#if 0
  pCore->reg_write(0,0,2); // A0 = 2
  pCore->reg_write(1,0,3); // B0 = 3

  llvm::Function *func = llvm::cast<llvm::Function>(Core::get_llvm_module().getOrInsertFunction("func",
    Type::getInt32Ty(getGlobalContext()),(Type*)0));
  llvm::BasicBlock* bb = llvm::BasicBlock::Create(getGlobalContext(),"entry",func);
  Core::get_llvm_builder().SetInsertPoint(bb);
  llvm::Constant* a_side_addr = llvm::ConstantInt::get(llvm::Type::getInt32Ty(getGlobalContext())
    ,(uint64_t)pCore->get_reg_a());
  llvm::Constant* b_side_addr = llvm::ConstantInt::get(llvm::Type::getInt32Ty(getGlobalContext())
    ,(uint64_t)pCore->get_reg_b());
  llvm::Constant* dst_addr = llvm::ConstantInt::get(llvm::Type::getInt32Ty(getGlobalContext())
    ,(uint64_t)(pCore->get_reg_b()+1)); // B1
  llvm::Value* a_side = llvm::ConstantExpr::getIntToPtr(a_side_addr,
    llvm::PointerType::getUnqual(llvm::Type::getInt32Ty(getGlobalContext())));
  llvm::Value* b_side = llvm::ConstantExpr::getIntToPtr(b_side_addr,
    llvm::PointerType::getUnqual(llvm::Type::getInt32Ty(getGlobalContext())));

  llvm::Value* b1 = llvm::ConstantExpr::getIntToPtr(dst_addr,
    llvm::PointerType::getUnqual(llvm::Type::getInt32Ty(getGlobalContext())));

  llvm::Value* left = Core::get_llvm_builder().CreateLoad(a_side);
  llvm::Value* right = Core::get_llvm_builder().CreateLoad(b_side);
  llvm::Value* re = Core::get_llvm_builder().CreateAdd(left,right);
  Core::get_llvm_builder().CreateStore(re,b1,true);

  Core::get_llvm_builder().CreateRet(re);

  ExecutionEngine* EE = EngineBuilder(&Core::get_llvm_module()).create();

  // Call the `foo' function with no arguments:
  //std::vector<GenericValue> noargs;
  //GenericValue gv = EE->runFunction(func, noargs);
  void* FPtr = EE->getPointerToFunction(func);
  int (*FP)() = (int (*)())(intptr_t)FPtr;
  FP();

  // Import result of execution:
  std::cout << "Result: " << pCore->reg_read(B_SIDE,1) << "\n";
  //outs() << "re: " << gv.IntVal << "\n";
#endif

#if 0
  pCore->reg_write(A_SIDE,3,0xFF);
  de_func_t de_func = JIT::gen_su_de_32bit_1or2_src_shl_f2_nc(pCore,0x018d0ca0);

  c6x::Instruction inst;

  pCore->reg_ch_num = 1;
  de_func(pCore,&inst);
  pCore->step();

  std::cout << to_hex_str(pCore->reg_read(A_SIDE,3)) << "\n";

  system("pause");
#endif
  pCore->run();

  return 0;
} 