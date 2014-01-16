#include "common/inc/hw_timer.hpp"

#ifdef _WIN32
#include <Windows.h>
#endif

double HwTimer::dFreq;
HwTimer timer_pool[10]; // support max 10 static timers

void HwTimer::init()
{
#ifdef _WIN32
  LARGE_INTEGER Freq;
  QueryPerformanceFrequency(&Freq);
  dFreq = (double)Freq.QuadPart; // query frequency
#endif
}

void HwTimer::start(unsigned int timer_idx)
{
  if(timer_idx > 10)
  {
    return;
  }
  LARGE_INTEGER PerfCounter;
  QueryPerformanceCounter(&PerfCounter);
  HwTimer &t = timer_pool[timer_idx];
  t.pfCounterStart = PerfCounter.QuadPart;
}

void HwTimer::end(unsigned int timer_idx)
{
  if(timer_idx > 10)
  {
    return;
  }
  LARGE_INTEGER PerfCounter;
  QueryPerformanceCounter(&PerfCounter);
  HwTimer &t = timer_pool[timer_idx];
  t.pfCounterAll += PerfCounter.QuadPart - t.pfCounterStart;
}

double HwTimer::get_diff_seconds(unsigned int timer_idx)
{
  if(timer_idx > 10)
  {
    return 0;
  }
  // dfTim/1000000
  HwTimer &t = timer_pool[timer_idx];
  return (double)(t.pfCounterAll/dFreq);
}

double HwTimer::get_diff_us(unsigned int timer_idx)
{
  if(timer_idx > 10)
  {
    return 0;
  }
  // dfTim/1000000
  HwTimer &t = timer_pool[timer_idx];
  return (double)(t.pfCounterAll/dFreq)*1000000;
}