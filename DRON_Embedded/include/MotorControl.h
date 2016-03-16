/**
 * @file   MotorControl.h
 * @Author Andrey Derevyanko <derandr@gmail.com>
 * @date   2016-01-23
 * @brief  DRON motor control commands
 *
 */

#ifndef MOTORCONTROL_H_
#define MOTORCONTROL_H_

#include "stm32f10x.h"

class MotorControl {
public:
	MotorControl();
	void forawrd();
	void bacward();
	void stop();
	void release();

	void open_damper();
	void close_damper();

private:
	GPIO_TypeDef* kForwardPort = GPIOA;
	GPIO_TypeDef* kBackwardPort = GPIOA;
	GPIO_TypeDef* kStopPort = GPIOB;
	GPIO_TypeDef* kDamperPort = GPIOB;

	uint16_t kForwardPin = GPIO_Pin_2;
	uint16_t kBackwardPin = GPIO_Pin_3;
	uint16_t kStopPin = GPIO_Pin_2;
	uint16_t kDamperPin = GPIO_Pin_3;
	void gpio_init();
};

#endif /* MOTORCONTROL_H_ */
