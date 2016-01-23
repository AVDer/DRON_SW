/*
 * Communication.cpp
 *
 *  Created on: 17 ñ³÷. 2016 ð.
 *      Author: Admin
 */

#include "Communication.h"

#include <algorithm>

Communication* get_communication() {
	static Communication communication;
	return &communication;
}

Communication::Communication() {
	uart_1.register_rx_func(Communication::wrap_byte_received);
	uart_1.dma_config(reinterpret_cast<uint32_t>(out_message_.raw_data), kMessageSize);
}

void Communication::register_message_func(MessageReceiveFunc f) {
	f_ = f;
}

void Communication::send_data(uint32_t data_type, uint32_t data_value) {
	out_message_.data.command = data_type;
	out_message_.data.data = data_value;
	uart_1.fire_dma();
}

void Communication::byte_received(uint8_t byte) {
	if (is_sync_mode_ && byte == cmd_sync) {
		return;
	}
	if (byte != cmd_sync) {
		is_sync_mode_ = false;
	}
	in_message_.raw_data[read_index_] = byte;
	if (++read_index_ >= kMessageSize) {
		read_index_ = 0;
		if (std::all_of(std::begin(in_message_.raw_data), std::end(in_message_.raw_data), [](uint8_t b){return b == cmd_sync;})) {
			is_sync_mode_ = true;
		}
		else {
			if (f_) {
				f_(std::make_pair(in_message_.data.command, in_message_.data.data));
			}
		}
	}
}
