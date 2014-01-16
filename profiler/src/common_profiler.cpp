#include "common/inc/def.hpp"
#include "jit/inc/jit_support.hpp"
#include "common/inc/hw_timer.hpp"
#include "profiler/inc/common_profiler.hpp"
#include "core/inc/core.hpp"
#include "jit/inc/jit.hpp"
#include "jit/inc/jit_thread.hpp"

BEGIN_NS

//TODO dynamic inc
static BasicBlock bb_pool[10 * _1K];
st_table *Profiler::bb_tbl;
static word_t bb_pool_count = 0;
word_t Profiler::bb_jit_thresh_times = 6;
word_t Profiler::bb_jit_thresh_len = 4;
byte_t Profiler::bb_state = 0xFF;
md_addr_t Profiler::bb_start_addr = 0;
md_addr_t Profiler::bb_end_addr = 0;
BasicBlock *Profiler::bb_current = NULL;
Profiler::bb_map_t Profiler::bb_map;

inline BasicBlock* bb_alloc(md_addr_t addr)
{
  BasicBlock* bb = &bb_pool[bb_pool_count++];
  new (bb) BasicBlock(addr);
  return bb;
}

void Profiler::init()
{

}

void Profiler::set_jit_threshold_times(word_t thres)
{
  bb_jit_thresh_times = thres;
}

void Profiler::set_jit_threshold_len(word_t thres)
{
  bb_jit_thresh_len = thres;
}

void Profiler::log_event(word_t evt, md_addr_t addr)
{
#ifdef CORE_USE_INST_CACHE
  //half_t evt_id = evt >> 16;
  //if(evt_id == 0)
  {
    const word_t delay_cycles = evt;
    if(delay_cycles == 0)
    {
      if(bb_state == 0xFF)
      {// enter new bb
        bb_start_addr = bb_end_addr = addr;

        Instruction *inst = Core::fetch_cached_inst(addr);
        BasicBlock *bb = inst->get_bb();
        //bb_map_t::iterator it = bb_map.find(addr);
        //BasicBlock *bb;
        if(bb != NULL)
        //if(it != bb_map.end())
        {//find it
          //bb = it->second;
          bb_state = 0x1;

          // JIT BB more than X instructions
          if(bb->bytes_len >= bb_jit_thresh_len)
          { // DO NOT JIT CIO related code
            bb->call_times++;
            Core *core = Core::get();
            if(!bb->jit_sended && bb->call_times >= bb_jit_thresh_times &&(
              core->cio.cio_hook_addr > bb->end ||
              core->cio.cio_hook_addr < bb->start))
            {
                if(inst->get_jit_func() == NULL)
                {
#ifdef CORE_PERF
                  HwTimer::start(1);
#endif
#ifdef CORE_USE_LIBJIT
                  JIT2::compile_basic_block(Core::get(),bb);
#elif CORE_USE_LLVM
                  //JIT::compile_basic_block(Core::get(),bb);
                  ///*
                  {
                    WaitForSingleObject(jit_mutext,INFINITE);
                    JITThread::push_compile_req(bb);
                    ReleaseMutex(jit_mutext);
                    SetEvent(jit_compile_req_event);
                    bb->jit_sended = 1;
                  }
                  //*/
#endif
#ifdef CORE_PERF
                  HwTimer::end(1);
#endif
                }
            }
          }
        }
        else
        {// not find in bb_tbl;new bb
          bb_state = 0x2;
          bb_current = new BasicBlock(addr);
          //bb_current = bb_alloc(addr); // TODO
          //bb_map.insert(std::make_pair(addr,bb_current));
          inst->set_bb(bb_current);
        }
      }
      else if(bb_state == 0x2)
      { // update end_addr for new bb
        bb_end_addr = addr;
      }
      else
      {// do nothing

      }
    }
    else
    {
      if(bb_state == 0x02)
      {// end current new bb

        if(delay_cycles == VIRTUAL_INT_DELAY_CYCLES)
        {// BB breaked by an interrupt
          Core::get()->get_ofs() << "BB " << to_hex_str(bb_current->start) <<
            " breaked by interrupt\n";
        }
        // bb_end_addr is the first addr of EP
        // we need to find the real end addr of BB
        //bb_current->end = bb_end_addr;
        md_addr_t addr = bb_end_addr;

        Instruction *inst = Core::fetch_cached_inst(addr);
        while(inst->is_next_p())
        {
          addr += 4;
          inst = Core::fetch_cached_inst(addr);
        }
        bb_current->end = addr;
        bb_current->bytes_len = bb_current->end - bb_current->start;
      }
      bb_state = 0xFF;
    }
  }
#endif
}

void Profiler::dump_all_bb_info()
{
  bb_map_t::iterator it = bb_map.begin();
  for(;it != bb_map.end();++it)
  {
    BasicBlock *bb = it->second;
    Core::get()->get_ofs() << "BasicBlock:" << to_hex_str(bb->start)
      << "," << to_hex_str(bb->end) << ",times:" << bb->call_times << "\n";
  }
  Core::get()->get_ofs().flush();
}

void Profiler::dump_bb_info(Instruction* inst,BasicBlock* bb)
{
  Core::get()->get_ofs() << "BasicBlock:" << to_hex_str(bb->start)
    << "," << to_hex_str(bb->end) << ",times:" << bb->call_times <<
    ",JIT:" << to_yes_or_no(inst->get_jit_func()) << "\n";
}

void Profiler::dump_hot_bb_info(word_t thresh)
{
  std::list<Instruction*>::iterator it_heap = Core::inst_heap_list.begin();
  for(; Core::inst_heap_list.end() != it_heap; ++it_heap)
  {
    Instruction* heap = *it_heap;
    for(int i = 0;i < Core::inst_heap_size; ++i)
    {
      Instruction *inst = heap+i;
      if(inst->get_bb())
      {//have basic block
        dump_bb_info(inst,inst->get_bb());
      }
    }
  }
  Core::get()->get_ofs().flush();
}

END_NS