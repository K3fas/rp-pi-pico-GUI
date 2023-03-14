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
    std::string text;
    rpgui::colors::Color textColor;
        
    public:
        // TODO: Add font type and size support
        Label(std::string text, const Color backgroundColor = Color::Transparent, const Color textColor = Color::White);
        Label(const Color backgroundColor = Color::Transparent, const Color textColor = Color::White);
        Label(const Label&) = default;
        ~Label() = default;

        void Draw() const final;
    };
    
} // namespace rpgui::ui


#endif //PICO_KIT_FRAMEWORK_LABEL_HPP
