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
        struct textBounds
        {
            BindableProperty<std::string> str;
            Bounds bounds;

            textBounds(const std::string& text)
                :str(text){}
            textBounds(std::string& text)
                :str(text){}
        } _text;

    public:
        Color textColor = Color::White;

    public:

        Button() = delete;
        Button(const Button&) = default;
        ~Button() = default;
        
        Button(const Width &width, const Height &heigth, const Color &color, std::string& text);
        Button(const Width &width, const Height &heigth, const Color &color, const std::string& text = "");

        Button(const Bounds &bounds, const Color &color, std::string& text);
        Button(const Bounds &bounds, const Color &color, const std::string& text = "");

        void SetText(const std::string& text);

        void SetBounds(const Bounds& bounds);

        void Draw() const final;
    };

} // namespace rpgui::ui

#endif // PICO_KIT_FRAMEWORK_BUTTON_HPP
