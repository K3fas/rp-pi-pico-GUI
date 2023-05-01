//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_ENTRY_HPP
#define PICO_KIT_FRAMEWORK_ENTRY_HPP

#include "include.hpp"
#include <string>

using namespace rpgui::type;
using namespace rpgui::common;

namespace rpgui::ui
{
    class Entry : public VisualElement, virtual Activatable
    {
        private:
            char lastChar;
    public:
        BindableProperty<std::string> text;
        Color textColor;
    public:
        Entry() = delete;
        Entry(const Entry&) = default;
        ~Entry() = default;

        Entry(const std::string& text, const Color backgroundColor = Color::Transparent, const Color textColor = Color::White);
        Entry(std::string& text, const Color backgroundColor = Color::Transparent, const Color textColor = Color::White);

        void HandleActive() final;

        void Draw() const final;
    };
    

    
} // namespace rpgui::ui


#endif //PICO_KIT_FRAMEWORK_ENTRY_HPP
