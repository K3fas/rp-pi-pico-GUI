//
// Created by kefas on 26.2.23.
//

#include "Cursor.hpp"
#include "IVGA.hpp"

using namespace rpgui::type;

void rpgui::core::Cursor::Draw() const
{
    auto bounds = this->GetBounds();
    IVGA::IDrawLine(Point(bounds.x - _size, bounds.y),
                    Point(bounds.x + _size, bounds.y),
                    Color::White);
    IVGA::IDrawLine(Point(bounds.x, bounds.y - _size),
                    Point(bounds.x, bounds.y + _size),
                    Color::White);
}