#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP

#include <gui_generated/main_screen/MAINViewBase.hpp>
#include <gui/main_screen/MAINPresenter.hpp>

class MAINView : public MAINViewBase
{
public:
    MAINView();
    virtual ~MAINView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void turnOn();
    virtual void turnOff();
    void updateClock(uint8_t h, uint8_t m, uint8_t s);
protected:
    Unicode::UnicodeChar clockHourBuf[3];
    Unicode::UnicodeChar clockMinuteBuf[3];
    Unicode::UnicodeChar clockSecBuf[3];

};

#endif // MAINVIEW_HPP
