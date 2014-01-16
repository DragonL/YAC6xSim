#ifndef PROFILER_COMMON_PROFILER_HPP
#define PROFILER_COMMON_PROFILER_HPP

#include <fstream>
#include <map>
#include <Windows.h>
#include "common/inc/def.hpp"
#include "profiler/inc/basic_block.hpp"

#include "common/inc/st.h"

BEGIN_NS

enum ProfEvt
{
  PROF_EVENT_BR_DELAY_CYCLES = 0 // current branch delay cycles
};

#define VIRTUAL_INT_DELAY_CYCLES 55

inline word_t mk_evt(half_t evt_id, half_t extra)
{
  return (((word_t)evt_id) << 16) | extra;
}

class Profiler
{
public:
  static void log_event(word_t evt, md_addr_t addr);
  static void dump_all_bb_info();
  static void dump_hot_bb_info(word_t thresh = 50);
  static void init();
  static void set_jit_threshold_times(word_t thres);
  static void set_jit_threshold_len(word_t thres);
  static void dump_bb_info(Instruction* inst,BasicBlock* bb);

public:
  typedef std::map<md_addr_t,BasicBlock*> bb_map_t;

  // state of current basic block
  // 0x01 - IN BB, exist BB
  // 0x02 - IN new BB
  // 0xFF - OUT of BB
  static byte_t bb_state;

  static md_addr_t bb_start_addr;
  static md_addr_t bb_end_addr;
  static BasicBlock *bb_current;
  
  static bb_map_t bb_map;
  static st_table *bb_tbl;

  static word_t bb_jit_thresh_times;
  static word_t bb_jit_thresh_len;
};

END_NS

#endif