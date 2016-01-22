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

PulseCounter::PulseCounter() {
	gpio_init();
	counter_init();
}

void PulseCounter::reset_counter() {
	TIM2->CNT = 0;
}

uint16_t PulseCounter::get_counter() {
	return TIM2->CNT;
}

void PulseCounter::gpio_init() {
	GPIO_InitTypeDef io_init_struct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	io_init_struct.GPIO_Pin = GPIO_Pin_1;
	io_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
	io_init_struct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &io_init_struct);
}


void PulseCounter::counter_init() {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICFilter = 0x0;

	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	TIM_Cmd(TIM2, ENABLE);
}
