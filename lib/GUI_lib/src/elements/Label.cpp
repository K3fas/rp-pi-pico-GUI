//
// Created by kefas on 26.2.23.
//

#include "Label.hpp"
#include "IVGA.hpp"


rpgui::ui::Label::Label(std::string& text, const Color backgroundColor, const Color textColor)
    : rpgui::common::View(rpgui::common::Bounds(0, 0, text.size()*8, 8), backgroundColor),
      text(text),
      textColor(textColor)
{
}

rpgui::ui::Label::Label(const std::string& text, const Color backgroundColor, const Color textColor)
    : rpgui::common::View(rpgui::common::Bounds(0, 0, text.size()*8, 8), backgroundColor),
      text(text),
      textColor(textColor)
{
}

void rpgui::ui::Label::Draw() const
{
      #ifdef TRACKING
    auto start = time_us_32();
#endif

    auto bounds = this->GetBounds();
    IVGA::IDrawRectangle(bounds, Color::Black);
    IVGA::IDrawText(text.GetValue().c_str(), rpgui::type::Point(bounds.x,bounds.y),textColor,color);
    #ifdef TRACKING
    printf("Button Draw took %f\n",time_us_32()-start);
#endif
}
