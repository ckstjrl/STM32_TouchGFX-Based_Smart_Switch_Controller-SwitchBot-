#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <gui/common/TimerSchedule.hpp>
#include "main.h"

extern RTC_HandleTypeDef hrtc;
extern "C" {
    extern volatile uint8_t gServoOn;
    extern volatile uint8_t gServoOff;
}


Model::Model() : modelListener(0)
{

}

void Model::tick()
{
	RTC_TimeTypeDef t;
	RTC_DateTypeDef d;

	HAL_RTC_GetTime(&hrtc, &t, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &d, RTC_FORMAT_BIN); // 반드시 호출

	static uint8_t lastSec = 255;

	if (t.Seconds != lastSec)
	{
		lastSec = t.Seconds;

		if (modelListener)
		{
			modelListener->updateClock(t.Hours, t.Minutes, t.Seconds);
		}

		// 예약시간 확인
		if (gSchedule.active)
		{
			if (t.Hours == gSchedule.hour && t.Minutes == gSchedule.minute)
			{
				if (gSchedule.turnOn)
				{
					gServoOn = 1;
				}
				else
				{
					gServoOff = 1;
				}
				gSchedule.active = 0;  // 1회 실행 후 비활성화
			}
		}
	}
}
