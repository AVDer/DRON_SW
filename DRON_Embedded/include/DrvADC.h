/*
 * DrvADC.h
 *
 *  Created on: 7 ñ³÷. 2016 ð.
 *      Author: Admin
 */

#ifndef DRVADC_H_
#define DRVADC_H_

// ----------------------------------------------------------------------------

#include "stm32f10x.h"

// ----------------------------------------------------------------------------

class Drv_ADC {
public:
	Drv_ADC();
	void start();
	void stop();
	uint16_t get_adc_value();
private:
	static const uint32_t kADC1_Data_Address = 0x4001244C;
	static const uint8_t kADC_Buffer_Size = 10;

	void gpio_init();
	void adc_init();
	void dma_config();

	uint16_t adc_data[kADC_Buffer_Size] = {};
};

#endif /* DRVADC_H_ */
