//
// Created by kefas on 26.2.23.
//

#include "Label.hpp"
#include "IVGA.hpp"

rpgui::ui::Label::Label(std::string text, const Color backgroundColor, const Color textColor)
    : rpgui::common::View(rpgui::common::Bounds(0, 0, 0, 0), backgroundColor),
      text(text),
      textColor(textColor)
{
}

rpgui::ui::Label::Label(const Color backgroundColor, const Color textColor)
    : rpgui::common::View(rpgui::common::Bounds(0, 0, 0, 0), backgroundColor),
      textColor(textColor)
{
}

void rpgui::ui::Label::Draw() const
{
    auto bounds = this->GetBounds();
    IVGA::IDrawText(text.c_str(), IVGA::Point(bounds.x,bounds.y),textColor,color);
}
