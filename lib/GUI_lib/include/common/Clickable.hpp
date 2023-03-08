//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_CLICKABLE_HPP
#define PICO_KIT_FRAMEWORK_CLICKABLE_HPP

#include <functional>
#include "events/Dispatcher.hpp"

namespace rpgui::event
{
    enum class MouseEventType;
}

namespace rpgui::common
{
    class Clickable
    {
    protected:
        // rpgui::event::SlotType<rpgui::event::MouseEventType::Clicked> _clicked;
        // rpgui::event::SlotType<rpgui::event::MouseEventType::Pressed> _pressed;
        // rpgui::event::SlotType<rpgui::event::MouseEventyType::Released> _released;

    public:
        Clickable() = default;
        ~Clickable() = default;
    };
} // namespace rpgui::common

#endif // PICO_KIT_FRAMEWORK_CLICKABLE_HPP