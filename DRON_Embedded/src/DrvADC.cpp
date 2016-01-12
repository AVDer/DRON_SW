/*
 * DrvADC.cpp
 *
 *  Created on: 7 ñ³÷. 2016 ð.
 *      Author: Admin
 */

#include "DrvADC.h"

#include <algorithm>

#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "misc.h"

Drv_ADC::Drv_ADC() {
  gpio_init();
  adc_init();
  dma_config();
}

void Drv_ADC::start() {
  ADC_Cmd(ADC1, ENABLE);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1, ADC_SampleTime_1Cycles5);
  ADC_ResetCalibration(ADC1);
  while (ADC_GetResetCalibrationStatus(ADC1)) {
    continue;
  }
  ADC_StartCalibration(ADC1);
  while (ADC_GetCalibrationStatus(ADC1)) {
    continue;
  }
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

void Drv_ADC::stop() {
  ADC_Cmd(ADC1, DISABLE);
}

uint16_t Drv_ADC::get_adc_value() {
  uint32_t temp_value = std::accumulate(adc_data, adc_data + kADC_Buffer_Size, 0);
  auto minmax = std::minmax_element(adc_data, adc_data + kADC_Buffer_Size);
  temp_value -= (*(minmax.first) + *(minmax.second));
  return temp_value / (kADC_Buffer_Size - 2);
}

void Drv_ADC::gpio_init() {
  GPIO_InitTypeDef io_init_struct;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  io_init_struct.GPIO_Pin = GPIO_Pin_1;
  io_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
  io_init_struct.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOB, &io_init_struct);
}


void Drv_ADC::adc_init() {
  ADC_InitTypeDef adc_init_struct;
  ADC_StructInit(&adc_init_struct);
  RCC_ADCCLKConfig(RCC_PCLK2_Div6);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  ADC_DeInit(ADC1);
  adc_init_struct.ADC_ContinuousConvMode = ENABLE;
  adc_init_struct.ADC_DataAlign = ADC_DataAlign_Right;
  adc_init_struct.ADC_Mode = ADC_Mode_Independent;
  adc_init_struct.ADC_NbrOfChannel = 1;
  adc_init_struct.ADC_ScanConvMode = DISABLE;
  adc_init_struct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_Init(ADC1, &adc_init_struct);
  ADC_DMACmd(ADC1, ENABLE);
}

void Drv_ADC::dma_config() {
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
  DMA_InitTypeDef DMA_InitStructure;

  DMA_InitStructure.DMA_PeripheralBaseAddr = kADC1_Data_Address;
  DMA_InitStructure.DMA_MemoryBaseAddr = reinterpret_cast<uint32_t>(&adc_data);
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = kADC_Buffer_Size;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  DMA_Cmd(DMA1_Channel1, ENABLE);
}
