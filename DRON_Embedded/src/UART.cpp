/*
 * UART.cpp
 *
 *  Created on: 7 ��. 2016 �.
 *      Author: Admin
 */

#include "UART.h"

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
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; //�����
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //���������
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;//��������� ���������
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //�������� �����
	NVIC_Init(&NVIC_InitStructure); //��������������
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);  //�������� ������ ���������� ��� ��� �����

	USART_Cmd(USART1, ENABLE);
}

void UART::send_byte(uint8_t byte) {
	while(!(USART1->SR & USART_SR_TC));
	USART1->DR = byte;
}

void UART::receive_byte(uint8_t byte) {
	volatile uint8_t a;
	a = byte;
}

extern "C" {
void USART1_IRQHandler(void) {
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		UART::receive_byte(USART_ReceiveData(USART1));
	}

	/*
      if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET) {
        UsartInterruptFeature<1>::_usartInstance->UsartInterruptEventSender.raiseEvent(UsartEventType::EVENT_RECEIVE);
        USART_ClearITPendingBit(USART1,USART_IT_RXNE);
      }
      else if(USART_GetITStatus(USART1,USART_IT_TXE)!=RESET) {
        UsartInterruptFeature<1>::_usartInstance->UsartInterruptEventSender.raiseEvent(UsartEventType::EVENT_READY_TO_TRANSMIT);
        USART_ClearITPendingBit(USART1,USART_IT_TXE);
      }
      else if(USART_GetITStatus(USART1,USART_IT_TC)!=RESET) {
        UsartInterruptFeature<1>::_usartInstance->UsartInterruptEventSender.raiseEvent(UsartEventType::EVENT_TRANSMIT_COMPLETE);
        USART_ClearITPendingBit(USART1,USART_IT_TC);
      }
      else if(USART_GetITStatus(USART1,USART_IT_PE)!=RESET) {
        UsartInterruptFeature<1>::_usartInstance->UsartInterruptEventSender.raiseEvent(UsartEventType::EVENT_PARITY_ERROR);
        USART_ClearITPendingBit(USART1,USART_IT_PE);
      }
      else if(USART_GetITStatus(USART1,USART_IT_IDLE)!=RESET) {
        UsartInterruptFeature<1>::_usartInstance->UsartInterruptEventSender.raiseEvent(UsartEventType::EVENT_IDLE);
        USART_ClearITPendingBit(USART1,USART_IT_IDLE);
      }
      else if(USART_GetITStatus(USART1,USART_IT_LBD)!=RESET) {
        UsartInterruptFeature<1>::_usartInstance->UsartInterruptEventSender.raiseEvent(UsartEventType::EVENT_LINE_BREAK_DETECT);
        USART_ClearITPendingBit(USART1,USART_IT_LBD);
      }
      else if(USART_GetITStatus(USART1,USART_IT_CTS)!=RESET) {
        UsartInterruptFeature<1>::_usartInstance->UsartInterruptEventSender.raiseEvent(UsartEventType::EVENT_CLEAR_TO_SEND);
        USART_ClearITPendingBit(USART1,USART_IT_CTS);
      }
      else if(USART_GetITStatus(USART1,USART_IT_ERR)!=RESET) {
        UsartInterruptFeature<1>::_usartInstance->UsartInterruptEventSender.raiseEvent(UsartEventType::EVENT_ERROR);
        USART_ClearITPendingBit(USART1,USART_IT_ERR);
      }
      __DSB();      // prevent erroneous recall of this handler due to delayed memory write
	 */
}

}
