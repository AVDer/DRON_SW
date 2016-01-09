/*
 * DrvADC.cpp
 *
 *  Created on: 7 ñ³÷. 2016 ð.
 *      Author: Admin
 */

#include "DrvADC.h"

Drv_ADC::Drv_ADC() {
	GPIO_InitTypeDef io_init_struct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	io_init_struct.GPIO_Pin = GPIO_Pin_1;
	io_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
	io_init_struct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOB, &io_init_struct);

	ADC_InitTypeDef adc_init_struct;
	ADC_StructInit(&adc_init_struct);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	adc_init_struct.ADC_ContinuousConvMode = ENABLE;
	adc_init_struct.ADC_DataAlign = ADC_DataAlign_Right;
	adc_init_struct.ADC_Mode = ADC_Mode_Independent;
	adc_init_struct.ADC_NbrOfChannel = 1;
	adc_init_struct.ADC_ScanConvMode = DISABLE;
	ADC_Init(ADC1, &adc_init_struct);
	ADC_Cmd(ADC1, ENABLE);

	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1, ADC_SampleTime_55Cycles5);

	ADC_ResetCalibration(ADC1);
	while (ADC_GetResetCalibrationStatus(ADC1)) {
		continue;
	}
	ADC_StartCalibration(ADC1);
	while (ADC_GetCalibrationStatus(ADC1)) {
		continue;
	}
}

uint16_t Drv_ADC::get_adc_value() {

	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET) {
		continue;
	}

	return ADC_GetConversionValue(ADC1);
}

