//
// Created by kefas on 26.2.23.
//

#include "Cursor.hpp"
#include "IVGA.hpp"
#include "IVGA.hpp"

using namespace rpgui::type;

void rpgui::core::Cursor::SetBounds(const Bounds &bounds)
{
    // Horizontal
    IVGA::IDrawRectangle(Point(_bounds.x - cursorSize, _bounds.y - cursorWidth),
                    Width(cursorSize * 2 + 1),
                    Height(cursorWidth * 2 + 1),
                    Color::Black);
    // Vertical
    IVGA::IDrawRectangle(Point(_bounds.x - cursorWidth, _bounds.y - cursorSize),
                    Width(cursorWidth * 2 + 1),
                    Height(cursorSize *2 + 1),
                    Color::Black);
                    
    _bounds = bounds;
    
}

void rpgui::core::Cursor::Draw() const
{
    auto bounds = this->GetBounds();

    // Horizontal
    IVGA::IDrawRectangle(Point(bounds.x - cursorSize, bounds.y - cursorWidth),
                    Width(cursorSize * 2 + 1),
                    Height(cursorWidth * 2 + 1),
                    Color::White);
    // Vertical
    IVGA::IDrawRectangle(Point(bounds.x - cursorWidth, bounds.y - cursorSize),
                    Width(cursorWidth * 2 + 1),
                    Height(cursorSize *2 + 1),
                    Color::White);
}