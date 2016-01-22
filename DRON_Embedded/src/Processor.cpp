/*
 * Processor.cpp
 *
 *  Created on: 18 ñ³÷. 2016 ð.
 *      Author: Admin
 */

#include "Processor.h"

#include "Communication.h"

Processor& get_processor() {
	static Processor processor_;
	return processor_;
}

Processor::Processor() {
	get_communication().register_message_func(wrap_message_received);
}

void Processor::message_received(const std::pair<uint32_t, uint32_t>& message) {
	switch (message.first) {
	case cmd_exposition:
		exposition_ = message.second;
		break;
	default:
		break;
	}
}

void Processor::run() {
	auto a = pulse_counter_.get_counter();
	exposition_ = a;
}
