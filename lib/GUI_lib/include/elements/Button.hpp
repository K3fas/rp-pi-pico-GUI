//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_BUTTON_HPP
#define PICO_KIT_FRAMEWORK_BUTTON_HPP

#include "include.hpp"
#include "rp_core.hpp"

using namespace rpgui::type;
using namespace rpgui::common;
using namespace rpgui::event;

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
        ~Button() {}

        void Draw() const;
        void Draw(const Bounds &bounds) const;

        void AddHandler(const MouseEventType type, const SlotType<MouseEventType> &function)
        {
            rpgui::core::MainApp::AddListener(type, function);
        }
    };

} // namespace rpgui::ui

#endif // PICO_KIT_FRAMEWORK_BUTTON_HPP
