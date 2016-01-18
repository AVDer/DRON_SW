/**
 * @file   delay.h
 * @Author Andrey Derevyanko <derandr@gmail.com>
 * @date   2016-01-18
 * @brief  Header file of simple Cortex delay class
 *
 */

#ifndef __ARMJISHU_EVAL_H
#define __ARMJISHU_EVAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

#define    DWT_CYCCNT    *(volatile uint32_t *)0xE0001004
#define    DWT_CONTROL   *(volatile uint32_t *)0xE0001000
#define    SCB_DEMCR     *(volatile uint32_t *)0xE000EDFC

namespace Delay
{
void init();
void us(uint32_t usec);
void ms(uint32_t msec);
}

#ifdef __cplusplus
}
#endif

#endif /* __STM3210B_EVAL_H */

