#ifndef TIMER_SCHEDULE_HPP
#define TIMER_SCHEDULE_HPP

#include <stdint.h>

struct TimerSchedule {
	uint8_t hour;
	uint8_t minute;
	uint8_t turnOn;
	uint8_t active;
};

extern TimerSchedule gSchedule;

#endif
