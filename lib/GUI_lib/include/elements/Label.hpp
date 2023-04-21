//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_LABEL_HPP
#define PICO_KIT_FRAMEWORK_LABEL_HPP

#include "include.hpp"
#include <string>

namespace rpgui::ui
{
    class Label : public rpgui::common::View
    {
    public:
        rpgui::common::BindableProperty<std::string> text;
        rpgui::colors::Color textColor;
        const void *font;
        uint8_t fontSize;

    public:
        Label() = delete;
        Label(const Label &) = default;
        ~Label() = default;

        Label(std::string &text, const Color textColor = Color::White, const Color backgroundColor = Color::Transparent, const void *font = nullptr, const uint8_t fontSize = 8);
        Label(const std::string &text, const Color textColor = Color::White, const Color backgroundColor = Color::Transparent, const void *font = nullptr, const uint8_t fontSize = 8);

        void Draw() const final;

        void SetText(const std::string& text);
    };

} // namespace rpgui::ui

#endif // PICO_KIT_FRAMEWORK_LABEL_HPP
