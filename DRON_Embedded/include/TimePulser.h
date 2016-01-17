/*
 * TimePulser.h
 *
 *  Created on: 14 Jan 2016
 *      Author: ade
 */

#ifndef TIMEPULSER_H_
#define TIMEPULSER_H_

// ----------------------------------------------------------------------------

#include "stm32f10x.h"

#include "stm32f10x_tim.h"

// ----------------------------------------------------------------------------

class TimePulser;
extern TimePulser time_pulse;

using TimerFunc = void (*)(uint32_t);

class TimePulser {
public:
  TimePulser() = default;
  void init();
  void start();
  void stop();
  void set_timeout(uint16_t ms);
  void set_function(TimerFunc f);
  void trigger_function();

private:
  TIM_TypeDef *kTimer = TIM3;

  void timer_init();
  TimerFunc f_ = nullptr;
  uint32_t call_number_ = 0;
};


#endif /* TIMEPULSER_H_ */
