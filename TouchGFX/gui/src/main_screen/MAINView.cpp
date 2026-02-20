#include <gui/main_screen/MAINView.hpp>

extern "C" {
    extern volatile uint8_t gServoOn;
    extern volatile uint8_t gServoOff;
}

MAINView::MAINView()
{

}

void MAINView::setupScreen()
{
	MAINViewBase::setupScreen();

}

void MAINView::tearDownScreen()
{
    MAINViewBase::tearDownScreen();
}

void MAINView::turnOn()
{
	onGroup.setVisible(true);
	offGroup.setVisible(false);
	onGroup.invalidate();
	offGroup.invalidate();
	if (gServoOn == 0 && gServoOff == 0)
	{
		gServoOn = 1;
	}
}

void MAINView::turnOff()
{
	onGroup.setVisible(false);
	offGroup.setVisible(true);
	onGroup.invalidate();
	offGroup.invalidate();
	if (gServoOn == 0 && gServoOff == 0)
	{
		gServoOff = 1;
	}
}

void MAINView::updateClock(uint8_t h, uint8_t m, uint8_t s)
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
