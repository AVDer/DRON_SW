/*
 * UART.h
 *
 *  Created on: 7 ñ³÷. 2016 ð.
 *      Author: Admin
 */

#ifndef UART_H_
#define UART_H_

// ----------------------------------------------------------------------------

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "misc.h"

// ----------------------------------------------------------------------------

class UART {
public:
	UART();

	void send_byte(uint8_t byte);
	static void receive_byte(uint8_t byte);
};

#endif /* UART_H_ */
