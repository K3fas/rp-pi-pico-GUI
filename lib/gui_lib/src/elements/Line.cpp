//
// Created by kefas on 26.2.23.
//

#include "Line.hpp"
#include "IVGA.hpp"

rpgui::ui::Line::Line(const Point &start, const Point &end, Color color)
    : VisualElement(Bounds(), color), start(start), end(end)
{
}

void rpgui::ui::Line::Draw() const
{
    IVGA::IDrawLine(start, end, color);
}
