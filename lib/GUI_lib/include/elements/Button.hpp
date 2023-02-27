//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_BUTTON_HPP
#define PICO_KIT_FRAMEWORK_BUTTON_HPP

#include "../include.hpp"

using namespace rpgui::type;
using namespace rpgui::common;

namespace rpgui::ui
{
    class Button : public View, public Clickable
    {
    private:
    public:
        Button(const Width &width, const Height &heigth, const Color &color)
            : View(Bounds{0, 0, width.v, heigth.v}, color) {}
        Button(const Bounds &bounds, const Color &color)
            : View(bounds, color) {}
        ~Button();

        void Draw() const { IVGA::IDrawRectangle(this->GetBounds(), this->color); }
        void Draw(const Bounds &bounds) const { IVGA::IDrawRectangle(bounds, this->color); }
    };

} // namespace rpgui::ui

#endif // PICO_KIT_FRAMEWORK_BUTTON_HPP
