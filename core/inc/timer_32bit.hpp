#ifndef CORE_TIMER32_HPP
#define CORE_TIMER32_HPP

#include "common/inc/def.hpp"
#include "core/inc/core.hpp"
#include "core/inc/mem_block.hpp"
#include "core/inc/l2_mem_ctrl.hpp"

BEGIN_NS

class L2MemCtroller;

class Timer32 : public MemBlock
{
private:
  md_addr_t ctl_addr;
  md_addr_t prd_addr;
  md_addr_t cnt_addr;
  qword_t real_count;
  L2MemCtroller *l2memctrl;
  bool next_clock_go;
  bool signal_event;

  enum
  {
    CTL = 0,
    PRD = 1,
    CNT = 2
  } timer_reg_t;

public:
  Timer32():MemBlock(0,0)
  {}

  Timer32(md_addr_t ctl,md_addr_t prd,md_addr_t cnt,L2MemCtroller *mem_,word_t event_id_):
    MemBlock(ctl,12),
    ctl_addr(ctl),prd_addr(prd),cnt_addr(cnt),real_count(0),l2memctrl(mem_),next_clock_go(false),
    signal_event(false),event_id(event_id_)
  {}

  static const word_t internal_clksrc = 0x200;

  word_t read_ctl(void);
  word_t read_prd(void);
  word_t read_cnt(void);
  void write_ctl(word_t val);
  void write_prd(word_t val);
  void write_cnt(word_t val);

  void cycle(void);

  void clr_signal(void)
  {
    signal_event = false;
  }

  ATTR_RW(word_t,event_id)

  inline bool have_pending_signal(void)
  {
    return signal_event;
  }

  inline word_t read_hld(void)
  {
    word_t ctl = read_ctl();
    return (ctl & 0x80) >> 7;
  }

  inline void clr_hld(void)
  {
    word_t ctl = read_ctl();
    ctl &= ~0x80;
    write_ctl(ctl);
  }

  inline void set_hld(void)
  {
    word_t ctl = read_ctl();
    ctl |= 0x80;
    write_ctl(ctl);
  }

  inline word_t read_go(void)
  {
    word_t ctl = read_ctl();
    return (ctl & 0x40) >> 6;
  }


};


END_NS

#endif // CORE_TIMER_32BIT_HPP