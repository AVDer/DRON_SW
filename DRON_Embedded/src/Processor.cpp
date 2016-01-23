/*
 * Processor.cpp
 *
 *  Created on: 18 ñ³÷. 2016 ð.
 *      Author: Admin
 */

#include "Processor.h"

#include "stm32f10x_exti.h"

#include "Communication.h"
#include "delay.h"
#include "Version.h"

Processor* get_processor() {
	static Processor processor_;
	return &processor_;
}

Processor::Processor() {
	gpio_init();
	interrupt_init();
	get_communication()->register_message_func(wrap_message_received);
	adc_.start();
}

void Processor::gpio_init() {
	GPIO_InitTypeDef io_init_struct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	io_init_struct.GPIO_Pin = GPIO_Pin_0;
	io_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
	io_init_struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &io_init_struct);
}

void Processor::interrupt_init() {
	EXTI_InitTypeDef exti_init_struct;
	EXTI_StructInit(&exti_init_struct);
	exti_init_struct.EXTI_Line = EXTI_Line1;
	exti_init_struct.EXTI_Mode = EXTI_Mode_Interrupt;
	exti_init_struct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	exti_init_struct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&exti_init_struct);

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void Processor::message_received(const std::pair<uint32_t, uint32_t>& message) {
	switch (message.first) {
	case cmd_start:
		mode_ = message.second;
		angle_counter_ = 0;
		move_motor();
		break;
	case cmd_stop:
		mode_ = mode_stop;
		break;
	case cmd_counts:
		counts_ = message.second;
		break;
	case cmd_step:
		step_ = message.second;
		break;
	case cmd_direction:
		if (message.second == 1) {
			direction_ = Direction::dir_forward;
		}
		else if (message.second == 2) {
			direction_ = Direction::dir_backward;
		}
		else {
			direction_ = Direction::dir_none;
		}
		break;
	case cmd_exposition:
		exposition_ = message.second;
		break;
	case cmd_break_time:
		breaking_time_ = message.second;
		break;
	case cmd_delay:
		delay_ = message.second;
		break;
	case cmd_sw_version:
		if (!running()) {
			get_communication()->send_data(cmd_sw_version, kSWVersion);
		}
		break;
	default:
		break;
	}
}

void Processor::move_motor() {
	if (direction_ == Direction::dir_forward) {
		motor_control_.forawrd();
	}
	else if (direction_ == Direction::dir_backward) {
		motor_control_.bacward();
	}
	else {
		motor_control_.release();
	}
}

void Processor::run() {
	if (!tick_event_ || !running()) {
		return;
	}
	tick_event_ = false;
	if (mode_ == mode_points) { // Point scan
		motor_control_.stop();
		Delay::ms(breaking_time_);
		motor_control_.release();
		Delay::ms(delay_);
		pulse_counter_.reset_counter();
		Delay::ms(exposition_);
		get_communication()->send_data(angle_counter_, pulse_counter_.get_counter());
		move_motor();

	}
	else if (mode_ == mode_integral || mode_ == mode_justice) {
		get_communication()->send_data(angle_counter_, adc_.get_adc_value());
	}
	if (++angle_counter_ >= counts_) {
		mode_ = mode_stop;
	}
}

extern "C" void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1) != RESET) {
		get_processor()->tick_event();
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}
