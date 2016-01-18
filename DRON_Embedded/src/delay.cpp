/**
 * @file   delay.cpp
 * @Author Andrey Derevyanko <derandr@gmail.com>
 * @date   2016-01-18
 * @brief  Implementation of simple Cortex delay class
 *
 */

#include "delay.h"

namespace Delay
{

uint32_t DWT_Get(void)
{
    return DWT_CYCCNT;
}
__inline
uint8_t DWT_Compare(int32_t tp)
{
    return (((int32_t)DWT_Get() - tp) < 0);
}

void init()
{
	if (!(DWT_CONTROL & 1))
	{
		SCB_DEMCR  |= 0x01000000;
		DWT_CYCCNT  = 0;
		DWT_CONTROL|= 1; // enable the counter
	}
}

void us(uint32_t usec)
{
	uint32_t tp = DWT_Get() + usec * (SystemCoreClock/1000000);
	while (DWT_Compare(tp));
}

void ms(uint32_t msec)
{
	us(msec * 1000);
}

}
