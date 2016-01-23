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
extern UART uart_1;

using ByteReceiveFunc = void (*)(uint8_t);

class UART {
public:
	UART();

	void send_byte(uint8_t byte);
	void fire_dma();
	void register_rx_func(ByteReceiveFunc f);
	void dma_config(uint32_t buffer_address, uint8_t buffer_size);
	void receive_byte(uint8_t byte);
private:
	ByteReceiveFunc f_ = nullptr;
	uint32_t dma_buffer_address_ = 0;
	uint8_t dma_buffer_size_ = 0;
};

#endif /* UART_H_ */
