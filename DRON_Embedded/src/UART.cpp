/*
 * UART.cpp
 *
 *  Created on: 7 січ. 2016 р.
 *      Author: Admin
 */

#include "UART.h"

UART& get_uart_1() {
	static UART uart_1;
	return uart_1;
}

UART::UART() {
	GPIO_InitTypeDef PORTA_init_struct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
	PORTA_init_struct.GPIO_Pin = GPIO_Pin_9;
	PORTA_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
	PORTA_init_struct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &PORTA_init_struct);
	PORTA_init_struct.GPIO_Pin = GPIO_Pin_10;
	PORTA_init_struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &PORTA_init_struct);

	USART_InitTypeDef USART1_init_struct;
	USART1_init_struct.USART_BaudRate = 115200;
	USART1_init_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART1_init_struct.USART_Mode = (USART_Mode_Rx | USART_Mode_Tx);
	USART1_init_struct.USART_Parity = USART_Parity_No;
	USART1_init_struct.USART_StopBits = USART_StopBits_1;
	USART1_init_struct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART1_init_struct);

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; //канал
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //приоритет
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;//приоритет субгруппы
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //включаем канал
	NVIC_Init(&NVIC_InitStructure); //инициализируем
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);  //включаем нужное прерывание щас нам прием

	USART_Cmd(USART1, ENABLE);
}

void UART::send_byte(uint8_t byte) {
	while(!(USART1->SR & USART_SR_TC));
	USART1->DR = byte;
}

void UART::register_rx_func(ByteReceiveFunc f) {
	f_ = f;
}

void UART::receive_byte(uint8_t byte) {
	if (f_) {
		f_(byte);
	}
}

extern "C" {
void USART1_IRQHandler(void) {
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		get_uart_1().receive_byte(USART_ReceiveData(USART1));
	}
}

}
