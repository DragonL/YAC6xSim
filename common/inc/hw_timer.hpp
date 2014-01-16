#ifndef COMMON_HW_TIMER_HPP
#define COMMON_HW_TIMER_HPP

class HwTimer
{
public:
  static void init();
  static void start(unsigned int timer_idx);
  static void end(unsigned int timer_idx);
  static double get_diff_seconds(unsigned int timer_idx);
  static double get_diff_us(unsigned int timer_idx);

  HwTimer():pfCounterAll(0),pfCounterStart(0){}

private:
  static double dFreq;
  long long pfCounterAll,pfCounterStart;
};

#endif