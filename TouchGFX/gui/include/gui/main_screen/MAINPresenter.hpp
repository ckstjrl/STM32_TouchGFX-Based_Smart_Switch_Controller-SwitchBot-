#ifndef MAINPRESENTER_HPP
#define MAINPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class MAINView;

class MAINPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    MAINPresenter(MAINView& v);

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

    virtual ~MAINPresenter() {}

    void updateClock(uint8_t h, uint8_t m, uint8_t s);
private:
    MAINPresenter();

    MAINView& view;
};

#endif // MAINPRESENTER_HPP
