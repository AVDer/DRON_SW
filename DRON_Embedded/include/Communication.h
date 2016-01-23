/*
 * Communication.h
 *
 *  Created on: 17 ñ³÷. 2016 ð.
 *      Author: Admin
 */

#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

#include <utility>

#include "Commands.h"
#include "UART.h"

class Communication;
Communication* get_communication();

using MessageReceiveFunc = void (*)(const std::pair<uint32_t, uint32_t>&);

class Communication {
public:
	Communication();
	// ----------------------------------------------------------------------------
	static void wrap_byte_received(uint8_t byte) {get_communication()->byte_received(byte);}

	void send_data(uint32_t data_type, uint32_t data_value);
	bool is_message_ready() const {return message_ready_;};
	void register_message_func(MessageReceiveFunc f);

	void byte_received(uint8_t byte);

private:
	// ----------------------------------------------------------------------------
	Message in_message_;
	Message out_message_;
	bool message_ready_ = false;
	bool is_sync_mode_ = false;
	uint8_t read_index_ = 0;

	MessageReceiveFunc f_ = nullptr;
};

#endif /* COMMUNICATION_H_ */
