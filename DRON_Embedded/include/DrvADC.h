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
#include "stm32f10x_adc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "misc.h"

// ----------------------------------------------------------------------------

class Drv_ADC {
public:
	Drv_ADC();

	uint16_t get_adc_value();
};

#endif /* DRVADC_H_ */
