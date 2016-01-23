/*
 * Processor.cpp
 *
 *  Created on: 18 ñ³÷. 2016 ð.
 *      Author: Admin
 */

#include "Processor.h"

#include "Communication.h"

Processor* get_processor() {
	static Processor processor_;
	return &processor_;
}

Processor::Processor() {
	get_communication()->register_message_func(wrap_message_received);
	adc_.start();
}

void Processor::message_received(const std::pair<uint32_t, uint32_t>& message) {
	switch (message.first) {
	case cmd_start:
		mode_ = message.second;
		angle_counter_ = 0;
		break;
	case cmd_stop:
		mode_ = 0;
		break;
	case cmd_exposition:
		exposition_ = message.second;
		break;
	default:
		break;
	}
}

void Processor::run() {
	if (mode_ == 1) {
		get_communication()->send_data(angle_counter_, pulse_counter_.get_counter());
	}
	else if (mode_ == 2) {
		get_communication()->send_data(angle_counter_, adc_.get_adc_value());
	}
	angle_counter_++;
}
