#ifndef TIMERVIEW_HPP
#define TIMERVIEW_HPP

#include <gui_generated/timer_screen/TIMERViewBase.hpp>
#include <gui/timer_screen/TIMERPresenter.hpp>

class TIMERView : public TIMERViewBase
{
public:
    TIMERView();
    virtual ~TIMERView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void plusHour();
    virtual void minusHour();
    virtual void plusMinute();
    virtual void minusMinute();
    virtual void setTimer();
    virtual void onSet();
    virtual void offSet();

    void updateClock(uint8_t h, uint8_t m, uint8_t s);
protected:
    int hour;
    int minute;
    int isOnMode;

    Unicode::UnicodeChar hourBuf[3];
    Unicode::UnicodeChar minuteBuf[3];

    Unicode::UnicodeChar clockHourBuf[3];
    Unicode::UnicodeChar clockMinuteBuf[3];
    Unicode::UnicodeChar clockSecBuf[3];


    void updateDisplay();
};

#endif // TIMERVIEW_HPP
