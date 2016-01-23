/**
 * @file   MotorControl.h
 * @Author Andrey Derevyanko <derandr@gmail.com>
 * @date   2016-01-23
 * @brief  DRON motor control commands
 *
 */

#ifndef MOTORCONTROL_H_
#define MOTORCONTROL_H_

class MotorControl {
public:
	MotorControl();
	void forawrd();
	void bacward();
	void stop();
	void release();

private:
	void gpio_init();
};

#endif /* MOTORCONTROL_H_ */
