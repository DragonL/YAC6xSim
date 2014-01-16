#include "common/inc/def.hpp"
#include "profiler/inc/exe_path_profiler.hpp"
#include "core/inc/core.hpp"


BEGIN_NS

StackFrame ExePathProfiler::_stack_frame[_stack_frame_len];

bool ExecutionPath::operator==(ExecutionPath& right)
{
  return (this->start == right.start) &&
    (this->end == right.end);
}

void ExePathProfiler::exec_jmp(Core *core,md_addr_t addr)
{
  Core::sym_tbl_t::iterator it = core->get_sym_tbl().find(addr);
  if(it != core->get_sym_tbl().end())
  {
    StackFrame sf(it->second.c_str(),addr,core->reg_read(A_SIDE,4),
      core->reg_read(B_SIDE,4),core->reg_read(B_SIDE,3),
      core->reg_read(A_SIDE,11),core->reg_read(B_SIDE,11));
    push_call_stack(sf);
  }
  if(addr == 0)
  {
    dump_call_stack();
  }
}

void ExePathProfiler::exec_addr(Core *core,md_addr_t addr)
{
  Core::sym_tbl_t::iterator it = core->get_sym_tbl().find(addr);
  if(it != core->get_sym_tbl().end())
  {
    StackFrame sf(it->second.c_str(),addr,core->reg_read(A_SIDE,4),
      core->reg_read(B_SIDE,4),core->reg_read(B_SIDE,3),
      core->reg_read(A_SIDE,11),core->reg_read(B_SIDE,11));
    push_call_stack(sf);
  }

  if(_verbose)
  {
    if(_current.start == 0xFFFFFFFF) // first inst
    {
      _current.start = _current.end = addr;
      return;
    }

    // CONT. path
    if(addr == _current.end + 4)
    {
      _current.end = addr;
      return;
    }

    if(_exe_path_list.empty())
    {
      _exe_path_list.push_back(_current);
    }
    else
    {
      ExecutionPath &last_path = _exe_path_list.at(_exe_path_list.size() - 1);
      if(_current == last_path)
      {
        last_path.loop++;
        if(_verbose)
        {
          *_pofs << "ExePath:<" << to_hex_str(last_path.start)
            << "," << to_hex_str(last_path.end) << ">"
            << " | loop " << last_path.loop << "\n";
        }
      }
      else
      { // a new path
        _exe_path_list.push_back(_current);
        // remove the first one
        _exe_path_list.erase(_exe_path_list.begin());
      }
    }

    {
      *_pofs << "End ExePath:<" << to_hex_str(_current.start)
        << "," << to_hex_str(_current.end) << ">"
        << " | loop " << _current.loop << "\n";
    }

    //new path
    _current.loop = 1;
    _current.start = _current.end = addr;
  }
}

void ExePathProfiler::write()
{

}

void ExePathProfiler::push_call_stack(const StackFrame& sf)
{
  _stack_frame[_stack_frame_pos++] = sf;
  if(_stack_frame_pos >= _stack_frame_len)
  {
    _stack_frame_pos = 0;
  }
}

void ExePathProfiler::dump_call_stack()
{
  int count = 0;
  for(int i = _stack_frame_pos; i < _stack_frame_len; ++i)
  {
    const StackFrame& sf = _stack_frame[i];
    if(sf.func_name)
    {
      get_ofs() << count << " : " << sf.func_name << 
        ",A4:" << to_hex_str(sf.a4) << ",B4:" << to_hex_str(sf.b4)<< 
        ",B3:" << to_hex_str(sf.b3) << ",ENTRY:" << to_hex_str(sf.entry_addr) << 
        ",A11:" << to_hex_str(sf.a11) << ",B11:" << to_hex_str(sf.b11)<< 
        "\n";
      ++count;
    }
  }

  for(int i = 0; i < _stack_frame_pos; ++i)
  {
    const StackFrame& sf = _stack_frame[i];
    if(sf.func_name)
    {
      get_ofs() << count << " : " << sf.func_name << 
        ",A4:" << to_hex_str(sf.a4) << ",B4:" << to_hex_str(sf.b4)<< 
        ",B3:" << to_hex_str(sf.b3) << ",ENTRY:" << to_hex_str(sf.entry_addr) << 
        ",A11:" << to_hex_str(sf.a11) << ",B11:" << to_hex_str(sf.b11)<< 
        "\n";
      ++count;
    }
  }
  get_ofs().flush();
}


END_NS