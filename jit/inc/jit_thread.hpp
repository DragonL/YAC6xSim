#ifndef JIT_JIT_THREAD_HPP
#define JIT_JIT_THREAD_HPP

#include "jit/inc/jit_support.hpp"
#include "decode/inc/inst.hpp"

#include <list>
#include <vector>
#include <process.h>  
#include <Windows.h>

extern HANDLE jit_compile_req_event;
extern HANDLE jit_mutext;

class JITThread
{
public:
  static void init();
  static void push_compile_req(c6x::BasicBlock *bb);

public:
  static std::vector<c6x::BasicBlock*> compile_req_list;
};

#endif