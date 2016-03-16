/*
 * Processor.h
 *
 *  Created on: 18 ñ³÷. 2016 ð.
 *      Author: Admin
 */

#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#include <cstdint>
#include <utility>

#include "Communication.h"
#include "DrvADC.h"
#include "MotorControl.h"
#include "PulseCounter.h"

class Processor;
Processor* get_processor();

class Processor {
public:
	Processor();
	static void wrap_message_received(const std::pair<uint32_t, uint32_t>& message) {
		get_processor()->message_received(message);
	}
	void message_received(const std::pair<uint32_t, uint32_t>& message);
	void run();
	void stop_event();
	inline void tick_event() {
	  if (mode_ == Mode::mode_points || mode_ == Mode::mode_integral) {
	    tick_event_ = true;
	  }
	}
	inline bool tick_processed() { return !tick_event_; }
	inline bool running() {return mode_ != mode_stop;}
private:
	const uint32_t kADC_Delay = 500;

	void move_motor();
	void gpio_init();
	void interrupt_init();

	Drv_ADC adc_;
	MotorControl motor_control_;
	PulseCounter pulse_counter_;

	bool tick_event_ {false};
	Direction direction_ {Direction::dir_none};
	uint8_t mode_ {};
	uint32_t counts_ {};
	uint32_t step_ {};
	uint32_t exposition_ {};
	uint32_t breaking_time_ {};
	uint32_t delay_ {};
	uint32_t angle_counter_ {};
	uint32_t step_counter_ {};
};

#endif /* PROCESSOR_H_ */
