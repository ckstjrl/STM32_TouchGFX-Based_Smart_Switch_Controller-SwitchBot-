#include <gui/timer_screen/TIMERView.hpp>
#include <gui/timer_screen/TIMERPresenter.hpp>

TIMERPresenter::TIMERPresenter(TIMERView& v)
    : view(v)
{

}

void TIMERPresenter::activate()
{

}

void TIMERPresenter::deactivate()
{

}

void TIMERPresenter::updateClock(uint8_t h, uint8_t m, uint8_t s)
{
    view.updateClock(h, m, s);
}
