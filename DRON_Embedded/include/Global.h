/**
 * @file   Global.h
 * @Author Andrey Derevyanko <derandr@gmail.com>
 * @date   2016-01-23
 * @brief  Global system settings
 *
 */

#ifndef VERSION_H_
#define VERSION_H_

const uint32_t kSWVersion = 0x00010100;

enum IPrio {
  ticks_prio = 0,
  pulses_prio = 1,
  uart_prio = 2,
  timer_prio = 8
};


#endif /* VERSION_H_ */
