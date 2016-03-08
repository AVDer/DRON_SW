/**
 * @file   PulseCounter.h
 * @Author Andrey Derevyanko <derandr@gmail.com>
 * @date   2016-01-22
 * @brief  DRON pulses counter header
 *
 */

#ifndef PULSECOUNTER_H_
#define PULSECOUNTER_H_

#include "stm32f10x.h"

class PulseCounter {
public:
	PulseCounter();
	void reset_counter();
	uint32_t get_counter();

private:
	void gpio_init();
	void counter_init();
};

#endif /* PULSECOUNTER_H_ */
