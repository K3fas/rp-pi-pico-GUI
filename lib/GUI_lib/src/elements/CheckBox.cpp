//
// Created by kefas on 26.2.23.
//

#include "CheckBox.hpp"
#include "IVGA.hpp"
#include "rp_core.hpp"
#include "Event.hpp"
#include "MouseDispatcher.hpp"

rpgui::ui::CheckBox::CheckBox(const Width &width, const Height &height, const Color backgroundColor, const Color tickColor)
    : tickColor(tickColor)
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

void rpgui::ui::CheckBox::Draw() const
{
    auto bounds = this->GetBounds();
    
    if (checked)
    {
        // TODO: Draw as polyline ?
        IVGA::IDrawFrame(bounds,this->tickColor);
        IVGA::IDrawFrame(bounds-1,this->tickColor);
        auto inner = bounds-2;
        IVGA::IDrawRectangle(inner, this->color);
        // Left top to bottom right
        IVGA::IDrawLine(IVGA::Point{inner.x, inner.y},
                        IVGA::Point{inner.x + inner.w, inner.y + inner.h},
                        this->tickColor);
        // Right top to bottom left
        IVGA::IDrawLine(IVGA::Point{inner.x + inner.w, inner.y},
                        IVGA::Point{inner.x, inner.y + inner.h},
                        this->tickColor);
    }
    else
    {
        IVGA::IDrawFrame(bounds,this->color);
        IVGA::IDrawFrame(bounds-1,this->color);
        IVGA::IDrawRectangle(bounds-2, this->tickColor);
    }
}

void rpgui::ui::CheckBox::changeState(rpgui::event::Event<MouseEventType> &event, Clickable *sender)
{
    auto box = (ui::CheckBox *)sender;
    box->checked = !(box->checked);
}
