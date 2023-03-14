//
// Created by kefas on 26.2.23.
//

#include "Cursor.hpp"
#include "IVGA.hpp"

void rpgui::core::Cursor::Draw() const
{
    auto bounds = this->GetBounds();
    IVGA::IDrawLine(IVGA::Point{bounds.x - _size, bounds.y},
                    IVGA::Point{bounds.x + _size, bounds.y},
                    Color::White);
    IVGA::IDrawLine(IVGA::Point{bounds.x, bounds.y - _size},
                    IVGA::Point{bounds.x, bounds.y + _size},
                    Color::White);
}