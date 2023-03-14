//
// Created by kefas on 26.2.23.
//

#include "CheckBox.hpp"
#include "IVGA.hpp"
#include "rp_core.hpp"

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
}

void rpgui::ui::CheckBox::Draw() const
{
    auto bounds = this->GetBounds();
    IVGA::IDrawRectangle(bounds, this->color);
    if (checked)
    {
        // TODO: Draw as polyline ?
        // Left top to bottom right
        IVGA::IDrawLine(IVGA::Point{bounds.x, bounds.y},
                        IVGA::Point{bounds.x + bounds.w, bounds.y + bounds.h},
                        this->tickColor);
        // Right top to bottom left
        IVGA::IDrawLine(IVGA::Point{bounds.x + bounds.w, bounds.y},
                        IVGA::Point{bounds.x, bounds.y + bounds.h},
                        this->tickColor);
    }
}

