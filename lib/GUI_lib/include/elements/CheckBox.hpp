//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_CHECKBOX_HPP
#define PICO_KIT_FRAMEWORK_CHECKBOX_HPP

#include "include.hpp"

using namespace rpgui::type;
using namespace rpgui::common;

namespace rpgui::ui
{
    class CheckBox : public View, public Clickable
    {
    private:
        const uint8_t _minHeight = 5;
        const uint8_t _minWidth = 5;

    public:
        bool checked;
        Color tickColor;

    public:
        CheckBox(const Width &width, const Height &heigth, const Color backgroundColor, const Color tickColor = Color::White);

        CheckBox(const Bounds &bounds, const Color &backgroundColor, const Color tickColor = Color::White)
            : View(bounds, backgroundColor), tickColor(tickColor) {}
        ~CheckBox() {}

        void Draw() const final;
    };

} // namespace rpgui::element

#endif // PICO_KIT_FRAMEWORK_CHECKBOX_HPP
