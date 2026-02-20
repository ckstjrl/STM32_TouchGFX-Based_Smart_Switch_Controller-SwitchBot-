#ifndef TIMERPRESENTER_HPP
#define TIMERPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class TIMERView;

class TIMERPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    TIMERPresenter(TIMERView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~TIMERPresenter() {}

    virtual void updateClock(uint8_t h, uint8_t m, uint8_t s);
private:
    TIMERPresenter();

    TIMERView& view;
};

#endif // TIMERPRESENTER_HPP
