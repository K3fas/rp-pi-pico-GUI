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
        
    public:
        // TODO: Add font type and size support
        Label() = delete;
        Label(const Label&) = default;
        ~Label() = default;

        Label(std::string& text, const Color backgroundColor = Color::Transparent, const Color textColor = Color::White);
        Label(const std::string& text, const Color backgroundColor = Color::Transparent, const Color textColor = Color::White);
        
        void Draw() const final;
    };
    
} // namespace rpgui::ui


#endif //PICO_KIT_FRAMEWORK_LABEL_HPP
