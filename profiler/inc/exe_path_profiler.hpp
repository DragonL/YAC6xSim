#ifndef PROFILER_EXE_PATH_PROFILER_HPP
#define PROFILER_EXE_PATH_PROFILER_HPP

#include "common/inc/def.hpp"
#include <vector>
#include <fstream>

BEGIN_NS

class Core;
struct ExecutionPath
{
  md_addr_t  start;
  md_addr_t  end;
  word_t     loop;

  ExecutionPath():start(-1),end(-1),loop(1){}

  bool operator==(ExecutionPath& right);
};

struct StackFrame
{
  const char* func_name;
  md_addr_t entry_addr;
  word_t a4;
  word_t b4;
  word_t b3;
  word_t a11;
  word_t b11;

  StackFrame():func_name(NULL){}

  explicit StackFrame(const char* fname,md_addr_t addr,
    word_t a4_val, word_t b4_val, word_t b3_val, 
    word_t a11_val, word_t b11_val):func_name(fname),
    entry_addr(addr),a4(a4_val),b4(b4_val),b3(b3_val),a11(a11_val),b11(b11_val){}
};

class ExePathProfiler
{
private:
  std::vector<ExecutionPath> _exe_path_list;
  ExecutionPath _current;
  bool _verbose;
  std::ofstream *_pofs;

  static const word_t _stack_frame_len = 50;
  static StackFrame _stack_frame[_stack_frame_len];
  word_t _stack_frame_pos;

  std::ofstream& get_ofs();
  void push_call_stack(const StackFrame& sf);

public:
  ExePathProfiler(std::ofstream *pofs,bool v = true):_verbose(v),_pofs(pofs),
    _stack_frame_pos(0)
  {
    for(int i = 0; i < _stack_frame_len; ++i)
    {
      _stack_frame[i].func_name = NULL;
    }
  }
  void exec_addr(Core *core,md_addr_t addr);
  void exec_jmp(Core *core,md_addr_t addr);
  void write();
  void dump_call_stack();
};

inline std::ofstream& ExePathProfiler::get_ofs()
{
  return *_pofs;
}

END_NS
#endif // PROFILER_EXE_PATH_PROFILER_HPP