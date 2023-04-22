//
// Created by kefas on 26.2.23.
//
#include "Slider.hpp"
#include "IVGA.hpp"
#include "rp_core.hpp"

rpgui::ui::Slider::Slider(const Width &width, const Height &heigth, const Color &color, double &value)
    : View(Bounds(0, 0, width.v, heigth.v), color), value(value)
{
}

rpgui::ui::Slider::Slider(const Width &width, const Height &heigth, const Color &color, const double &value)
    : View(Bounds(0, 0, width.v, heigth.v), color), value(value)
{
}

rpgui::ui::Slider::Slider(const Bounds &bounds, const Color &color, double &value)
    : View(bounds, color), value(value)
{
}

rpgui::ui::Slider::Slider(const Bounds &bounds, const Color &color, const double &value)
    : View(bounds, color), value(value)
{
}

void rpgui::ui::Slider::Draw() const
{
    auto bounds = this->GetBounds();
    IVGA::IDrawFrame(bounds, leftColor);
    bounds = Bounds(bounds.x - pinSize, bounds.y, bounds.w - pinSize * 2, bounds.h);
    IVGA::IDrawRectangle(bounds, color);
    IVGA::IDrawCircle(Point(bounds.x + _pinOffset, bounds.y + bounds.h / 2), Radius(pinSize), pinColor, true);
}

void rpgui::ui::Slider::handlePressed(MouseEvent<MouseEventType> &event, Clickable *sender)
{
    this->SetActive(this);
}

void rpgui::ui::Slider::handleReleased(MouseEvent<MouseEventType> &event, Clickable *sender)
{
    
}
