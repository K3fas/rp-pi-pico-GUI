//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_CLICKABLE_HPP
#define PICO_KIT_FRAMEWORK_CLICKABLE_HPP

#include <functional>
#include "Dispatcher.hpp"
#include "include.hpp"

using namespace rpgui::type;
using namespace rpgui::event;

namespace rpgui::common
{
    class Clickable
    {
    protected:
        SlotType<MouseEventType> _clicked;

    public:
        Clickable() = default;
        Clickable(const Clickable&) = default;
        ~Clickable() = default;

        virtual void SetOnClickHandler(const MouseEventType type, const SlotType<MouseEventType> &function);
    };
} // namespace rpgui::common

#endif // PICO_KIT_FRAMEWORK_CLICKABLE_HPP