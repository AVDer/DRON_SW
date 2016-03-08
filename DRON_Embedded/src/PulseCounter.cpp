/**
 * @file   PulseCounter.h
 * @Author Andrey Derevyanko <derandr@gmail.com>
 * @date   2016-01-22
 * @brief  DRON pulses counter implementation
 *
 */

#include "PulseCounter.h"

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"

#include "Global.h"

static uint16_t pulse_msb;

PulseCounter::PulseCounter() {
	gpio_init();
	counter_init();
}

void PulseCounter::reset_counter() {
	TIM2->CNT = 0;
	pulse_msb = 0;
}

uint32_t PulseCounter::get_counter() {
  uint32_t counter_value = pulse_msb;
  counter_value <<= 16;
	counter_value += TIM2->CNT;
	TIM2->CNT = 0;
	pulse_msb = 0;
	return counter_value;
}

void PulseCounter::gpio_init() {
	GPIO_InitTypeDef io_init_struct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	io_init_struct.GPIO_Pin = GPIO_Pin_1;
	io_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
	io_init_struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &io_init_struct);
}


void PulseCounter::counter_init() {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseInitTypeDef timer_init_struct;

	timer_init_struct.TIM_Prescaler = 0;
	timer_init_struct.TIM_CounterMode = TIM_CounterMode_Up;
	timer_init_struct.TIM_Period = 0xFFFF;
	timer_init_struct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM2, &timer_init_struct);

	TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0);
	TIM_SelectInputTrigger(TIM2, TIM_TS_ETRF);

  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = IPrio::pulses_prio;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	reset_counter();

	TIM_Cmd(TIM2, ENABLE);

}

extern "C" {

void TIM2_IRQHandler(void) {
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    ++pulse_msb;
  }
}

}
