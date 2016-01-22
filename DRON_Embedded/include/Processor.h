/*
 * Processor.h
 *
 *  Created on: 18 ��. 2016 �.
 *      Author: Admin
 */

#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#include <cstdint>
#include <utility>

#include "Communication.h"
#include "PulseCounter.h"

class Processor;
Processor& get_processor();

enum class Mode {
	Fast_Scan,
	Point_Scan
};

class Processor {
public:
	Processor();
	static void wrap_message_received(const std::pair<uint32_t, uint32_t>& message) {
		get_processor().message_received(message);
	}
	void message_received(const std::pair<uint32_t, uint32_t>& message);
	void run();
private:
	uint32_t exposition_ {};
	PulseCounter pulse_counter_;
};

#endif /* PROCESSOR_H_ */
