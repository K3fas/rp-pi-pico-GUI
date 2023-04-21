//
// Created by kefas on 26.2.23.
//

#include "Label.hpp"
#include "IVGA.hpp"
#include "font8x8.bmp.h"

rpgui::ui::Label::Label(std::string &text, const Color textColor, const Color backgroundColor, const void *font, const uint8_t fontSize)
    : rpgui::common::View(rpgui::common::Bounds(0, 0, text.size() * 8, 8), backgroundColor),
      text(text),
      textColor(textColor),
      fontSize(fontSize)
{
    if (font != nullptr)
    {
        this->font = font;
    }
    else
    {
        this->font = Font8x8.image;
    }
}

rpgui::ui::Label::Label(const std::string &text, const Color textColor, const Color backgroundColor, const void *font, const uint8_t fontSize)
    : rpgui::common::View(rpgui::common::Bounds(0, 0, text.size() * fontSize, fontSize), backgroundColor),
      text(text),
      textColor(textColor),
      fontSize(fontSize)
{
    if (font != nullptr)
    {
        this->font = font;
    }
    else
    {
        this->font = Font8x8.image;
    }
}

void rpgui::ui::Label::Draw() const
{
    auto bounds = this->GetBounds();
    IVGA::IDrawText(text.GetValue().c_str(), rpgui::type::Point(bounds.x, bounds.y), textColor, color);
}

void rpgui::ui::Label::SetText(const std::string &text)
{
    auto bounds = this->GetBounds();
    bounds.w = text.size() * fontSize;
    bounds.h = fontSize;
    SetBounds(bounds);
}
