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

class UART;
UART& get_uart_1();

using ByteReceiveFunc = void (*)(uint8_t);

class UART {
public:
	UART();

	void send_byte(uint8_t byte);
	void register_rx_func(ByteReceiveFunc f);
	void receive_byte(uint8_t byte);
private:
	ByteReceiveFunc f_ = nullptr;
};

#endif /* UART_H_ */
