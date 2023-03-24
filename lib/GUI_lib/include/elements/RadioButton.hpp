//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_RADIOBUTTON_HPP
#define PICO_KIT_FRAMEWORK_RADIOBUTTON_HPP

#include "include.hpp"
#include <vector>
#include <string>

using namespace rpgui::common;
using namespace rpgui::colors;
using namespace rpgui::type;

namespace rpgui::ui
{
    class RadioButton : public View
    {
    private:

        
    public:
        RadioButton() = delete;
        RadioButton(const RadioButton&) = default;
        ~RadioButton() = default;

        RadioButton(const Point start, const Width& width, const Height& height);
        RadioButton(const Bounds& bounds,Color color);

        void AddItem(std::string text);

        void Draw() const final;
    };
    
    
} // namespace rpgui::ui


#endif //PICO_KIT_FRAMEWORK_RADIOBUTTON_HPP
