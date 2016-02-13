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
	GPIO_SetBits(kStopPort, kStopPin);
	GPIO_SetBits(kBackwardPort, kBackwardPin);
	GPIO_ResetBits(kForwardPort, kForwardPin);
}

void MotorControl::bacward() {
	GPIO_SetBits(kStopPort, kStopPin);
	GPIO_SetBits(kForwardPort, kForwardPin);
	GPIO_ResetBits(kBackwardPort, kBackwardPin);
}

void MotorControl::stop() {
	GPIO_SetBits(kForwardPort, kForwardPin);
	GPIO_SetBits(kBackwardPort, kBackwardPin);
	GPIO_ResetBits(kStopPort, kStopPin);
}

void MotorControl::release() {
	GPIO_SetBits(kStopPort, kStopPin);
	GPIO_SetBits(kForwardPort, kForwardPin);
	GPIO_SetBits(kBackwardPort, kBackwardPin);
}

void MotorControl::open_damper() {
	GPIO_SetBits(kDamperPort, kDamperPin);
}

void MotorControl::close_damper() {
	GPIO_ResetBits(kDamperPort, kDamperPin);
}

void MotorControl::gpio_init() {
	GPIO_InitTypeDef io_init_struct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	io_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
	io_init_struct.GPIO_Mode = GPIO_Mode_Out_OD;
	io_init_struct.GPIO_Pin = kForwardPin;
	GPIO_Init(kForwardPort, &io_init_struct);
	io_init_struct.GPIO_Pin = kBackwardPin;
	GPIO_Init(kBackwardPort, &io_init_struct);
	io_init_struct.GPIO_Pin = kStopPin;
	GPIO_Init(kStopPort, &io_init_struct);
	io_init_struct.GPIO_Mode = GPIO_Mode_Out_PP;
	io_init_struct.GPIO_Pin = kDamperPin;
	GPIO_Init(kDamperPort, &io_init_struct);

	release();
}
