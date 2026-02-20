#include <gui/main_screen/MAINView.hpp>
#include <gui/main_screen/MAINPresenter.hpp>

MAINPresenter::MAINPresenter(MAINView& v)
    : view(v)
{

}

void MAINPresenter::activate()
{

}

void MAINPresenter::deactivate()
{

}

void MAINPresenter::updateClock(uint8_t h, uint8_t m, uint8_t s)
{
    view.updateClock(h, m, s);
}
