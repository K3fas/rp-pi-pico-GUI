//
// Created by kefas on 26.2.23.
//

#include "Entry.hpp"
#include "IVGA.hpp"
#include "rp_core.hpp"

rpgui::ui::Entry::Entry(const std::string &text, const Color backgroundColor, const Color textColor)
: rpgui::common::VisualElement(rpgui::common::Bounds(0, 0, text.size()*8, 8), backgroundColor),
      text(text),
      textColor(textColor)
{
}

rpgui::ui::Entry::Entry(std::string &text, const Color backgroundColor, const Color textColor)
: rpgui::common::VisualElement(rpgui::common::Bounds(0, 0, text.size()*8, 8), backgroundColor),
      text(text),
      textColor(textColor)
{
}

void rpgui::ui::Entry::HandleActive()
{
    if(lastChar != HID::kbd::pressedKeys[0])
    {
        lastChar = HID::kbd::pressedKeys[0];
        if(lastChar)
        {
            auto old = text.GetValue();
            text.SetValue(old+lastChar);
        }
    }
}

void rpgui::ui::Entry::Draw() const
{
    auto bounds = this->GetBounds();
    IVGA::IDrawRectangle(bounds, Color::Black);
    IVGA::IDrawText(text.GetValue().c_str(), rpgui::type::Point(bounds.x,bounds.y),textColor,color);
}
