#include "jit/inc/jit_thread.hpp"
#include "jit/inc/jit_support.hpp"
#include "core/inc/core.hpp"

using namespace c6x;
HANDLE jit_compile_req_event;
HANDLE jit_mutext;

bool inited = false;

void jit_compile_thread(void* param)
{
  for(;;)
  {
    c6x::BasicBlock *bb;
    {
      WaitForSingleObject(jit_mutext,INFINITE);
      if(JITThread::compile_req_list.empty())
      {
        while(JITThread::compile_req_list.empty())
        {//wait for compile request
          ResetEvent(jit_compile_req_event);
          SignalObjectAndWait(jit_mutext,jit_compile_req_event,INFINITE,false);
        }
        WaitForSingleObject(jit_mutext,INFINITE);// re-acquire mutex
      }
      bb = JITThread::compile_req_list.back();
      JITThread::compile_req_list.pop_back();
      ReleaseMutex(jit_mutext);
    }
#ifdef CORE_USE_LLVM
    JIT::compile_basic_block(Core::get(),bb);
#endif
  }
}

std::vector<c6x::BasicBlock*> JITThread::compile_req_list;

void JITThread::init()
{
  if(!inited)
  {
    jit_compile_req_event = CreateEvent(NULL,true,false,NULL);
    jit_mutext = CreateMutex(NULL,false,NULL);
    CreateThread( 
                  NULL,       // default security attributes
                  0,          // default stack size
                  (LPTHREAD_START_ROUTINE) jit_compile_thread, 
                  NULL,       // no thread function arguments
                  0,          // default creation flags
                  NULL); // receive thread identifier
    inited = true;
  }
}

void JITThread::push_compile_req(c6x::BasicBlock *bb)
{
  compile_req_list.push_back(bb);
}