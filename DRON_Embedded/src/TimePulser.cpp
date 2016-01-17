/*
 * TimePulser.cpp
 *
 *  Created on: 14 Jan 2016
 *      Author: ade
 */

#include "TimePulser.h"

TimePulser time_pulse;

void TimePulser::init() {
  timer_init();
}

void TimePulser::start() {
  TIM_Cmd(kTimer, ENABLE);
}

void TimePulser::stop() {
  TIM_Cmd(kTimer, DISABLE);
}

void TimePulser::set_timeout(uint16_t ms) {
  TIM_TimeBaseInitTypeDef timer_init_struct;
  timer_init_struct.TIM_Prescaler = 0x8C9F; // 36000 - 1
  timer_init_struct.TIM_CounterMode = TIM_CounterMode_Down;
  timer_init_struct.TIM_Period = ms * 2;
  TIM_TimeBaseInit(kTimer, &timer_init_struct);
}

void TimePulser::timer_init() {
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  TIM_TimeBaseInitTypeDef timer_init_struct;
  timer_init_struct.TIM_Prescaler = 0x8C9F; // 36000 - 1
  timer_init_struct.TIM_CounterMode = TIM_CounterMode_Down;
  timer_init_struct.TIM_Period = 2000;
  TIM_TimeBaseInit(kTimer, &timer_init_struct);

  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  TIM_ITConfig(kTimer, TIM_IT_Update, ENABLE);
}

void TimePulser::set_function(TimerFunc f) {
  f_ = f;
}

void TimePulser::trigger_function() {
  if (f_) {
    f_(++call_number_);
  }
}

extern "C" {

void TIM3_IRQHandler(void) {
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    time_pulse.trigger_function();
  }
}

}
