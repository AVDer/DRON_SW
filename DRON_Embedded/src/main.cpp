//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "DrvADC.h"
#include "BlinkLed.h"
#include "UART.h"
#include "Timer.h"

// ----------------------------------------------------------------------------
//
// Standalone STM32F1 led blink sample (trace via DEBUG).
//
// In debug configurations, demonstrate how to print a greeting message
// on the trace device. In release configurations the message is
// simply discarded.
//
// Then demonstrates how to blink a led with 1 Hz, using a
// continuous loop and SysTick delays.
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the DEBUG output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//
// The external clock frequency is specified as a preprocessor definition
// passed to the compiler via a command line option (see the 'C/C++ General' ->
// 'Paths and Symbols' -> the 'Symbols' tab, if you want to change it).
// The value selected during project creation was HSE_VALUE=8000000.
//
// Note: The default clock settings take the user defined HSE_VALUE and try
// to reach the maximum possible system clock. For the default 8 MHz input
// the result is guaranteed, but for other values it might not be possible,
// so please adjust the PLL settings in system/src/cmsis/system_stm32f10x.c
//

// Definitions visible only within this translation unit.
namespace
{
// ----- Timing definitions -------------------------------------------------

// Keep the LED on for 2/3 of a second.
constexpr Timer::ticks_t BLINK_ON_TICKS = Timer::FREQUENCY_HZ * 3 / 4;
constexpr Timer::ticks_t BLINK_OFF_TICKS = Timer::FREQUENCY_HZ
		- BLINK_ON_TICKS;
}

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int main(void) {
	Timer timer;
	timer.start();

	BlinkLed blinkLed;
	UART uart_1;
	Drv_ADC adc_1;
	adc_1.start();

	// Perform all necessary initialisations for the LED.
	blinkLed.powerUp();

	// Infinite loop
	while (true) {
		uint16_t adc_value = adc_1.get_adc_value();
		uart_1.send_byte(adc_value >> 8);
		uart_1.send_byte(adc_value);
		uart_1.send_byte('\n');
		uart_1.send_byte('\r');


		blinkLed.turnOn();
		timer.sleep(BLINK_ON_TICKS);

		blinkLed.turnOff();
		timer.sleep(BLINK_OFF_TICKS);
	}
	// Infinite loop, never return.
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
