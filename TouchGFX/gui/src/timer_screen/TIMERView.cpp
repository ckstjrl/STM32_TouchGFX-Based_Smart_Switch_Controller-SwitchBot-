#include <gui/timer_screen/TIMERView.hpp>
#include <gui/common/TimerSchedule.hpp>

TimerSchedule gSchedule = { 0, 0, 1, 0 };

TIMERView::TIMERView()
	: hour(0), minute(0), isOnMode(1)
{

}

void TIMERView::setupScreen()
{
    TIMERViewBase::setupScreen();
    hour = 0;
    minute = 0;
    isOnMode = 1;
    updateDisplay();
}

void TIMERView::tearDownScreen()
{
    TIMERViewBase::tearDownScreen();
}

void TIMERView::plusHour()
{
	hour++;
	if (hour > 23) hour = 0;
	updateDisplay();
}

void TIMERView::minusHour()
{
	hour--;
	if (hour < 0) hour = 23;
	updateDisplay();
}

void TIMERView::plusMinute()
{
	minute++;
	if (minute > 59) minute = 0;
	updateDisplay();
}

void TIMERView::minusMinute()
{
	minute--;
	if (minute < 0) minute = 59;
	updateDisplay();
}

void TIMERView::onSet()
{
	isOnMode = 1;
	onMode.setVisible(true);
	offMode.setVisible(false);
	onMode.invalidate();
	offMode.invalidate();
}

void TIMERView::offSet()
{
	isOnMode = 0;
	onMode.setVisible(false);
	offMode.setVisible(true);
	onMode.invalidate();
	offMode.invalidate();
}

void TIMERView::setTimer()
{
	//RTC와 연동
	gSchedule.hour = (uint8_t)hour;
	gSchedule.minute = (uint8_t)minute;
	gSchedule.turnOn = isOnMode ? 1 : 0;
	gSchedule.active = 1;
}

void TIMERView::updateDisplay()
{
	Unicode::snprintf(hourBuf, 3, "%02d", hour);
	timerHour.setWildcard(hourBuf);
	timerHour.invalidate();

	Unicode::snprintf(minuteBuf, 6, "%02d", minute);
	timerMinute.setWildcard(minuteBuf);
	timerMinute.invalidate();

}

void TIMERView::updateClock(uint8_t h, uint8_t m, uint8_t s)
{
	Unicode::snprintf(clockHourBuf, 3, "%02d", h);
	Unicode::snprintf(clockMinuteBuf, 3, "%02d", m);
	Unicode::snprintf(clockSecBuf, 3, "%02d", s);

	clockHour.setWildcard(clockHourBuf);
	clockMinute.setWildcard(clockMinuteBuf);
	clockSec.setWildcard(clockSecBuf);

	clockHour.invalidate();
	clockMinute.invalidate();
	clockSec.invalidate();
}
