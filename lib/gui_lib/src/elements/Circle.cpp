#include "Circle.hpp"
#include "IVGA.hpp"

rpgui::ui::Circle::Circle(const Radius &radius, Color color)
    : View(Bounds(0, 0, radius.v * 2, radius.v * 2), color)
{
}

void rpgui::ui::Circle::Draw() const
{
    IVGA::IDrawCircle(center, radius, color);
}

void rpgui::ui::Circle::SetCenter(const Point &center)
{
    this->center = center;
    auto b = Bounds(center.x - radius.v, center.y - radius.v,
                    radius.v * 2, radius.v * 2);
    SetBounds(b);
}

const Point &rpgui::ui::Circle::GetCenter()
{
    return center;
}

