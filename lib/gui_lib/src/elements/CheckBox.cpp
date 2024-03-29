//
// Created by kefas on 26.2.23.
//

#include "CheckBox.hpp"
#include "IVGA.hpp"
#include "rp_core.hpp"
#include "MouseEvent.hpp"
#include "MouseDispatcher.hpp"

using namespace rpgui::type;



rpgui::ui::CheckBox::CheckBox(const Width &width, const Height &height, const bool &value, const Color backgroundColor, const Color tickColor)
    :checked(value), tickColor(tickColor)
{
    this->color = backgroundColor;
    auto bounds = Bounds(0, 0, width.v, height.v);

    if (width.v < _minWidth)
        bounds.w = _minWidth;
    if (height.v < _minHeight)
        bounds.h = _minHeight;

    SetBounds(bounds);

    rpgui::core::MainApp::AddListener(MouseEventType::Clicked, Handler{changeState, this}, 1);
}

rpgui::ui::CheckBox::CheckBox(const Width &width, const Height &height, bool &value, const Color backgroundColor, const Color tickColor)
    :checked(value), tickColor(tickColor)
{
    this->color = backgroundColor;
    auto bounds = Bounds(0, 0, width.v, height.v);

    if (width.v < _minWidth)
        bounds.w = _minWidth;
    if (height.v < _minHeight)
        bounds.h = _minHeight;

    SetBounds(bounds);

    rpgui::core::MainApp::AddListener(MouseEventType::Clicked, Handler{changeState, this});
}

rpgui::ui::CheckBox::CheckBox(const Bounds &bounds, const Color &backgroundColor, const bool &value, const Color tickColor)
    :VisualElement(bounds,backgroundColor), checked(value), tickColor(tickColor)
{
}

rpgui::ui::CheckBox::CheckBox(const Bounds &bounds, const Color &backgroundColor, bool &value, const Color tickColor)
    :VisualElement(bounds,backgroundColor), checked(value), tickColor(tickColor)
{
}
void rpgui::ui::CheckBox::Draw() const
{
    #ifdef TRACKING
    auto start = time_us_32();
#endif
    auto bounds = this->GetBounds();
    
    if (checked.GetValue())
    {
        // TODO: Draw as polyline ?
        IVGA::IDrawFrame(bounds,this->tickColor);
        IVGA::IDrawFrame(bounds-1,this->tickColor);
        auto inner = bounds-2;
        IVGA::IDrawRectangle(inner, this->color);
        // Left top to bottom right
        IVGA::IDrawLine(Point(inner.x, inner.y),
                        Point(inner.x + inner.w, inner.y + inner.h),
                        this->tickColor);
        // Right top to bottom left
        IVGA::IDrawLine(Point(inner.x + inner.w, inner.y),
                        Point(inner.x, inner.y + inner.h),
                        this->tickColor);
    }
    else
    {
        IVGA::IDrawFrame(bounds,this->tickColor);
        IVGA::IDrawFrame(bounds-1,this->tickColor);
        IVGA::IDrawRectangle(bounds-2, this->color);
    }
#ifdef TRACKING
    printf("CheckBox Draw took %f\n",time_us_32()-start);
#endif
}

void rpgui::ui::CheckBox::changeState(rpgui::event::MouseEvent<MouseEventType> &event, Clickable *sender)
{
    auto box = (ui::CheckBox *)sender;
    box->checked.SetValue(!(box->checked.GetValue()));
}
