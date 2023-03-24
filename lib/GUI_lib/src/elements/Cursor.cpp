//
// Created by kefas on 26.2.23.
//

#include "Cursor.hpp"
#include "IVGA.hpp"

using namespace rpgui::type;

void rpgui::core::Cursor::Draw() const
{
    auto bounds = this->GetBounds();
    IVGA::IDrawLine(Point(bounds.x + size, bounds.y),
                    Point(bounds.x + size, bounds.y + size * 2),
                    Color::White);
    IVGA::IDrawLine(Point(bounds.x, bounds.y + size),
                    Point(bounds.x + size * 2, bounds.y + size),
                    Color::White);
}