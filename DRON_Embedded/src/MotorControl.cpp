/**
 * @file   MotorControl.cpp
 * @Author Andrey Derevyanko <derandr@gmail.com>
 * @date   2016-01-23
 * @brief  DRON motor control commands
 *
 */

#include "MotorControl.h"

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

MotorControl::MotorControl() {
	gpio_init();
}

void MotorControl::forawrd() {
	GPIO_ResetBits(GPIOA, GPIO_Pin_3);
	GPIO_ResetBits(GPIOB, GPIO_Pin_2);
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
}

void MotorControl::bacward() {
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOB, GPIO_Pin_2);
	GPIO_SetBits(GPIOA, GPIO_Pin_3);
}

void MotorControl::stop() {
	GPIO_ResetBits(GPIOA, GPIO_Pin_3);
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_SetBits(GPIOB, GPIO_Pin_2);
}

void MotorControl::release() {
	GPIO_ResetBits(GPIOA, GPIO_Pin_3);
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOB, GPIO_Pin_2);
}

void MotorControl::gpio_init() {
	GPIO_InitTypeDef io_init_struct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	io_init_struct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	io_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
	io_init_struct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &io_init_struct);
	io_init_struct.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOB, &io_init_struct);

	release();
}
