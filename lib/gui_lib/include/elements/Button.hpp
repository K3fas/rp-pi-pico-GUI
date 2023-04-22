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
    class Label;
}

namespace rpgui::ui
{
    class Button : public View, public Clickable
    {
    private:
        Label* _text;

    public:

    public:

        Button() = delete;
        Button(const Button&) = default;
        ~Button();
        
        Button(const Width &width, const Height &heigth, const Color &color, 
            std::string& text, const Color& textColor = Color::White, uint8_t fontSize = 8, void* font = nullptr);
        Button(const Width &width, const Height &heigth, const Color &color,
         const std::string& text = "",const Color& textColor = Color::White, uint8_t fontSize = 8, void* font = nullptr);

        Button(const Bounds &bounds, const Color &color, 
            std::string& text, const Color& textColor = Color::White, uint8_t fontSize = 8, void* font = nullptr);
        Button(const Bounds &bounds, const Color &color,
             const std::string& text = "", const Color& textColor = Color::White, uint8_t fontSize = 8, void* font = nullptr);

        void SetText(const std::string& text);

        void SetBounds(const Bounds& bounds);

        void Draw() const final;
    };

} // namespace rpgui::ui

#endif // PICO_KIT_FRAMEWORK_BUTTON_HPP
