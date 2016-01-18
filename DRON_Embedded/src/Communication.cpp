/*
 * Communication.cpp
 *
 *  Created on: 17 ñ³÷. 2016 ð.
 *      Author: Admin
 */

#include "Communication.h"

#include <algorithm>

Communication& get_communication() {
	static Communication communication;
	return communication;
}

Communication::Communication() {
	get_uart_1().register_rx_func(Communication::wrap_byte_received);

}

void Communication::send_data(uint32_t data_type, uint32_t data_value) {
	out_message_.data.command = data_type;
	out_message_.data.data = data_value;
	for (uint8_t b : out_message_.raw_data)
		get_uart_1().send_byte(b);
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
	}
}
