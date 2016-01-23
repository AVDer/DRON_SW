/**
 * @file   Commands.h
 * @Author Andrey Derevyanko <derandr@gmail.com>
 * @date   2016-01-18
 * @brief  Generic data structures and definitions for DRON UART communication
 *
 */

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <cstdint>

const uint8_t kMessageSize = 8;

enum Commands {
	cmd_start = 0,
	cmd_stop,
	cmd_counts,
	cmd_step,
	cmd_direction,
	cmd_exposition,
	cmd_break_time,
	cmd_delay,
	cmd_sw_version,
	cmd_sync = 0xFF
};

enum Mode {
	mode_stop = 0,
	mode_points,
	mode_integral,
	mode_justice
};

enum Direction {
	dir_none = 0,
	dir_forward,
	dir_backward
};

using Message = union Message_{
	struct {
		uint32_t command;
		uint32_t data;
	} data;
	uint8_t raw_data[kMessageSize];
        char chars[kMessageSize];
};

#endif /* COMMANDS_H_ */
