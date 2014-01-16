#include <string.h>
#include "core/inc/dbg.hpp"
#include "core/inc/core.hpp"
#include "decode/inc/fp.hpp"

BEGIN_NS

DbgDummy DbgDummy::dbgdummy;

dbg_cont_t DbgHelp::operator()(Core* core,debug_param_t& params)
{
  return DBG_HOLD;
}

dbg_cont_t DbgDummy::operator()(Core* core,debug_param_t& params)
{
  std::string& cmd = params.at(0);
  std::cout << "<warn>:" << "cmd \"" << cmd << "\" is not supported\n";
  return DBG_HOLD;
}

dbg_cont_t DbgShowGenRegs::operator()(Core* core,debug_param_t& params)
{
  for (int i=0;i<32;++i)
  {
    std::cout << "A" << i << ":" << to_hex_str(core->reg[i]) << " ";
    if ((i+1)% 5 == 0)
    {
      std::cout << "\n";
    }
  }
  std::cout << "\n";
  for (int i=0;i<32;++i)
  {
    std::cout << "B" << i << ":" << to_hex_str(core->reg[32 + i]) << " ";
    if ((i+1)% 5 == 0)
    {
      std::cout << "\n";
    }
  }
  std::cout << "\n";
  return DBG_HOLD;
}

dbg_cont_t DbgShowContext::operator()(Core* core,debug_param_t& params)
{
  std::stringstream ss;
  ss << "dis6x ";
  char buf[256];

  std::cout << "current jmp point:" << core->get_jmp_point() << "\n";
  for(int i = 0; i < 6; ++i)
  {
    if(core->jmp_req_list[i])
    {
      std::cout << "JMP " << i << " addr:" << to_hex_str(core->jmp_req_list[i]) << "\n";
    }
  }

  return DBG_HOLD;
}

dbg_cont_t DbgStep::operator()(Core* core,debug_param_t& params)
{
  if(0 != core->get_nop_remains())
  {
    std::cout << "chained NOPs:" <<  core->get_nop_remains() << "\n";
  }

  return DBG_STEP;
}

dbg_cont_t DbgGo::operator()(Core* core,debug_param_t& params)
{
  core->set_debug(false);
  return DBG_EXIT;
}

dbg_cont_t DbgSetBreakPoint::operator()(Core* core,debug_param_t& params)
{
  md_addr_t bp_addr = strtoul(params[1].c_str(),NULL,16);
  core->add_bp(bp_addr);

  return DBG_HOLD;
}

dbg_cont_t DbgSetCycleBreak::operator()(Core* core,debug_param_t& params)
{
  qword_t bp_cycle = _strtoui64(params[1].c_str(),NULL,10);
  //core->add_bp(bp_addr);
  core->add_cycle_bp(bp_cycle);

  return DBG_HOLD;
}

dbg_cont_t DbgListBreakPoint::operator()(Core* core,debug_param_t& params)
{
  std::vector<md_addr_t>::iterator it = core->bp_list.begin();
  std::cout << "Break Point List:\n";
  int index = 0;
  for(; it != core->bp_list.end(); ++it)
  {
    std::cout << "[" << index << "] : " << to_hex_str(*it) << "\n";
    index++;
  }

  return DBG_HOLD;
}

dbg_cont_t DbgRemoveBreakPoint::operator()(Core* core,debug_param_t& params)
{
  word_t idx = strtoul(params[1].c_str(),NULL,10);
  core->rmv_bp_by_index(idx);

  return DBG_HOLD;
}

dbg_cont_t DbgSetWord::operator()(Core* core,debug_param_t& params)
{
  if(params.size() <= 2)
  {
    return DBG_HOLD;
  }

  md_addr_t addr = strtoul(params[1].c_str(),NULL,16);
  word_t val = strtoul(params[2].c_str(),NULL,16);
  core->get_l2()->mem_write_word_xendian(addr,val);

  return DBG_HOLD;
}

dbg_cont_t DbgDumpWord::operator()(Core* core,debug_param_t& params)
{
  md_addr_t addr;
  if(params.size() == 1)
  {
    return DBG_HOLD;
  }
  addr = strtoul(params[1].c_str(),NULL,16);
  word_t dispaly_len = 3;
  if(params.size() >= 3)
  {
    dispaly_len = strtoul(params[2].c_str(),NULL,10);
    if(dispaly_len > 16)
    {
      dispaly_len = 16; // max 16
    }
  }
  word_t val = core->get_l2()->mem_read_word(addr);
  std::cout << ">>" << to_hex_str(addr) << " : " << to_hex_str(val) << "\n";

  for(word_t i = 0; i < dispaly_len; ++i)
  {
    val = core->get_l2()->mem_read_word(addr+4+4*i);
    std::cout << "  " << to_hex_str(addr+4+4*i) << " : " << to_hex_str(val) << "\n";
  }

  return DBG_HOLD;
}

dbg_cont_t DbgDumpString::operator()(Core* core,debug_param_t& params)
{
  md_addr_t addr;
  if(params.size() == 1)
  {
    return DBG_HOLD;
  }
  addr = strtoul(params[1].c_str(),NULL,16);
  word_t dispaly_len = 3;
  if(params.size() >= 3)
  {
    dispaly_len = strtoul(params[2].c_str(),NULL,10);
    if(dispaly_len > 16)
    {
      dispaly_len = 16; // max 16
    }
  }
  byte_t b1 = core->get_l2()->mem_read_byte(addr++);
  byte_t b2 = core->get_l2()->mem_read_byte(addr++);
  byte_t b3 = core->get_l2()->mem_read_byte(addr++);
  byte_t b4 = core->get_l2()->mem_read_byte(addr++);
  printf("\n>> 0x%08x : %c%c%c%c\n",addr - 4,b1,b2,b3,b4);

  for(word_t i = 0; i < dispaly_len; ++i)
  {
    b1 = core->get_l2()->mem_read_byte(addr++);
    b2 = core->get_l2()->mem_read_byte(addr++);
    b3 = core->get_l2()->mem_read_byte(addr++);
    b4 = core->get_l2()->mem_read_byte(addr++);
    printf("   0x%08x : %c%c%c%c\n",addr - 4,b1,b2,b3,b4);
  }
  return DBG_HOLD;
}

dbg_cont_t DbgListSymbol::operator()(Core* core,debug_param_t& params)
{
  std::string filter;
  if(params.size() > 1)
  {
    filter = params[1];
  }
  Core::sym_tbl_t::iterator it = core->get_sym_tbl().begin();
  for(; it != core->get_sym_tbl().end(); ++it)
  {
    if(!filter.empty())
    { // filter it
      if(NULL == strstr(it->second.c_str(),filter.c_str() ) )
      {
        continue;
      }
    }
    std::cout << it->second << " : " << to_hex_str(it->first) << "\n";
  }
  return DBG_HOLD;
}

dbg_cont_t DbgSetTraceFlag::operator()(Core* core,debug_param_t& params)
{
  if(params.size() < 2)
  {
    return DBG_HOLD;
  }
  word_t flag = strtoul(params[1].c_str(),NULL,10);
  core->set_trace_flag(flag);

  return DBG_HOLD;
}

dbg_cont_t DbgSetSkipJmp::operator()(Core* core,debug_param_t& params)
{
  if(params.size() < 2)
  {
    return DBG_HOLD;
  }
  md_addr_t addr = strtoul(params[1].c_str(),NULL,16);
  core->add_skip_jmp(addr);
  return DBG_HOLD;
}

dbg_cont_t DbgSetMemTrace::operator()(Core* core,debug_param_t& params)
{
  if(params.size() < 2)
  {
    return DBG_HOLD;
  }
  md_addr_t start = strtoul(params[1].c_str(),NULL,16);
  word_t len = 4; // default 1 word

  if(params.size() >= 3)
  {
    len = strtoul(params[2].c_str(),NULL,10);
  }

  core->add_mem_trace_range(start,len);
  return DBG_HOLD;
}

dbg_cont_t DbgSetWriteCheck::operator()(Core* core,debug_param_t& params)
{
  md_addr_t addr;
  if(params.size() == 1)
  {
    return DBG_HOLD;
  }
  addr = strtoul(params[1].c_str(),NULL,16);
  //core->get_l2()->set_write_check_addr(addr);

  return DBG_HOLD;
}

END_NS