//
// Created by kefas on 26.2.23.
//
#include "Button.hpp"
#include "rp_core.hpp"
#include "IVGA.hpp"

void rpgui::ui::Button::SetText(const std::string &text)
{
    constexpr uint8_t fontSize = 8;
    _text.str = text;

    auto tWidth = text.length() * fontSize;
    // Put text to center of button
    _text.bounds = Bounds(0, 0,
                          tWidth,
                          fontSize);
}

void rpgui::ui::Button::Draw() const
{
    auto bounds = this->GetBounds();
    IVGA::IDrawRectangle(bounds, this->color);
    if (!_text.str.empty())
    {
        IVGA::IDrawText(_text.str.c_str(), IVGA::Point{bounds.x + (bounds.w - _text.bounds.w) / 2, bounds.y + (bounds.h - _text.bounds.h) / 2},
                        this->textColor);
    }
}
