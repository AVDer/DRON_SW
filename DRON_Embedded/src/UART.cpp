/*
 * UART.cpp
 *
 *  Created on: 7 ñ³÷. 2016 ð.
 *      Author: Admin
 */

#include "UART.h"

UART uart_1;

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
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	USART_Cmd(USART1, ENABLE);
	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
}

void UART::dma_config(uint32_t buffer_address, uint8_t buffer_size) {
	dma_buffer_address_ = buffer_address;
	dma_buffer_size_ = buffer_size;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	DMA_InitTypeDef dma_init_struct;
	DMA_StructInit(&dma_init_struct);
	dma_init_struct.DMA_PeripheralBaseAddr = (uint32_t)&(USART1->DR);
	dma_init_struct.DMA_MemoryBaseAddr = buffer_address;
	dma_init_struct.DMA_DIR = DMA_DIR_PeripheralDST;
	dma_init_struct.DMA_BufferSize = buffer_size;
	dma_init_struct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	dma_init_struct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dma_init_struct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	dma_init_struct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	dma_init_struct.DMA_Priority = DMA_Priority_High;
	DMA_Init(DMA1_Channel4, &dma_init_struct);
}

void UART::send_byte(uint8_t byte) {
	while(!(USART1->SR & USART_SR_TC));
	USART1->DR = byte;
}

void UART::fire_dma() {
	DMA1_Channel4->CCR &= (uint16_t)(~DMA_CCR1_EN);
	DMA1_Channel4->CMAR = dma_buffer_address_;
	DMA1_Channel4->CNDTR = dma_buffer_size_;
	DMA1_Channel4->CCR |= DMA_CCR1_EN;
}

void UART::register_rx_func(ByteReceiveFunc f) {
	f_ = f;
}

void UART::receive_byte(uint8_t byte) {
	if (f_ != nullptr) {
		f_(byte);
	}
}

extern "C" {
void USART1_IRQHandler(void) {
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		uart_1.receive_byte(USART_ReceiveData(USART1));
	}
}

}
