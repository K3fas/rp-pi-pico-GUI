//
// Created by kefas on 26.2.23.
//
#include "Button.hpp"
#include "rp_core.hpp"
#include "IVGA.hpp"

rpgui::ui::Button::Button(const Width &width, const Height &heigth, const Color &color, std::string &text)
    : View(Bounds(0, 0, width.v, heigth.v), color), _text(text)
{
}

rpgui::ui::Button::Button(const Width &width, const Height &heigth, const Color &color, const std::string &text)
    : View(Bounds(0, 0, width.v, heigth.v), color), _text(text)
{
}

rpgui::ui::Button::Button(const Bounds &bounds, const Color &color, std::string &text)
    : View(bounds, color), _text(text)
{
}

rpgui::ui::Button::Button(const Bounds &bounds, const Color &color, const std::string &text)
    : View(bounds, color), _text(text)
{
}

void rpgui::ui::Button::SetText(const std::string &text)
{
    constexpr uint8_t fontSize = 8;
    _text.str.SetValue(text);

    auto tWidth = text.length() * fontSize;
    _text.bounds = Bounds(0, 0,
                          tWidth,
                          fontSize);
}

void rpgui::ui::Button::SetBounds(const Bounds &bounds)
{
    this->rpgui::common::View::SetBounds(bounds);
    // Put text to center of button
    _text.bounds = Bounds(bounds.x + (bounds.w - _text.bounds.w) / 2,
                          bounds.y + (bounds.h - _text.bounds.h) / 2,
                          _text.bounds.w,
                          _text.bounds.h);
}

void rpgui::ui::Button::Draw() const
{
#ifdef TRACKING
    auto start = time_us_32();
#endif
    IVGA::IDrawRectangle(this->GetBounds(), this->color);
    if (!_text.str.GetValue().empty())
    {
        IVGA::IDrawText(_text.str.GetValue().c_str(), IVGA::Point{_text.bounds.x, _text.bounds.y},
                        this->textColor);
    }
#ifdef TRACKING
    printf("Button Draw took %f\n",time_us_32()-start);
#endif
}
