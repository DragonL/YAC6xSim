#include "core/inc/timer_32bit.hpp"

BEGIN_NS

word_t Timer32::read_ctl(void)
{
  /*
  word_t ctl = l2memctrl->mem_read_word(ctl_addr);
  return ctl;
  */
  //return ((word_t*)get_buf())[CTL];
  return MD_SWAPW(read<word_t>(ctl_addr));
}

word_t Timer32::read_prd(void)
{
  /*
  word_t prd = l2memctrl->mem_read_word(prd_addr);
  return prd;
  */
  //return ((word_t*)get_buf())[PRD];
  return MD_SWAPW(read<word_t>(prd_addr));
}

word_t Timer32::read_cnt(void)
{
  /*
  word_t cnt = l2memctrl->mem_read_word(cnt_addr);
  return cnt;
  */
  //return ((word_t*)get_buf())[CNT];
  return MD_SWAPW(read<word_t>(cnt_addr));
}

void Timer32::write_ctl(word_t val)
{
  //l2memctrl->mem_write_word_xendian(ctl_addr,val);
  ((word_t*)get_buf())[CTL] = MD_SWAPW(val);
}

void Timer32::write_prd(word_t val)
{
  //l2memctrl->mem_write_word_xendian(prd_addr,val);
  ((word_t*)get_buf())[PRD] = MD_SWAPW(val);
}

void Timer32::write_cnt(word_t val)
{
  //l2memctrl->mem_write_word_xendian(cnt_addr,val);
  ((word_t*)get_buf())[CNT] = MD_SWAPW(val);
}

void Timer32::cycle(void)
{
  word_t ctl = read_ctl();
  word_t hld,go,cnt;
  hld = (ctl & 0x80) >> 7;
  if(!hld)
  { // Counter is disabled and held in the current state.
    return;
  }

  if(next_clock_go)
  {// reset and start to count
    real_count = 0;
    write_cnt(0);
    next_clock_go = false;
  }

  go = (ctl & 0x40) >> 6;
  if(go)
  {//If HLD = 1, the counter register is zeroed and begins counting on the next clock.
    next_clock_go = true;

    //clr go
    ctl &= ~0x40;
    write_ctl(ctl);
  }

  real_count++;
  if(real_count % 8 == 0)
  {
    cnt = read_cnt();
    cnt++;
    write_cnt(cnt);
    word_t prd = read_prd();
    
    if(cnt == prd) // reach period
    {
      write_cnt(0);
      signal_event = true;
    }
  }
}



END_NS