//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_BUTTON_HPP
#define PICO_KIT_FRAMEWORK_BUTTON_HPP

#include "include.hpp"
#include <string>

using namespace rpgui::type;
using namespace rpgui::common;
using namespace rpgui::event;

namespace rpgui::ui
{
    class Button : public View, public Clickable
    {
    private:
        struct
        {
            std::string str;
            Bounds bounds;
        } _text;

    public:
        Color textColor = Color::White;

    public:
        Button(const Width &width, const Height &heigth, const Color &color)
            : View(Bounds{0, 0, width.v, heigth.v}, color) {}
        Button(const Bounds &bounds, const Color &color)
            : View(bounds, color) {}
        ~Button() {}

        void SetText(const std::string& text);

        void SetBounds(const Bounds& bounds);

        void Draw() const final;
    };

} // namespace rpgui::ui

#endif // PICO_KIT_FRAMEWORK_BUTTON_HPP
