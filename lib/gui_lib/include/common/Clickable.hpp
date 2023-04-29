//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_CLICKABLE_HPP
#define PICO_KIT_FRAMEWORK_CLICKABLE_HPP

#include "Types.hpp"
#include <functional>
#include <concepts>

namespace rpgui::event
{
    template <typename T>
    class MouseEvent;
}

namespace rpgui::common
{
    class Clickable;
}

namespace rpgui::type
{

    using HandleFunc = std::function<void(rpgui::event::MouseEvent<rpgui::type::MouseEventType> &, rpgui::common::Clickable *)>;
}

using namespace rpgui::type;

namespace rpgui::common
{
    class Clickable
    {

    public:
        Clickable() = default;
        Clickable(const Clickable &) = default;
        ~Clickable() = default;

        void SetOnClickHandler(const MouseEventType type, const HandleFunc &function, const uint8_t priority = 0);
    };

} // namespace rpgui::common

#endif // PICO_KIT_FRAMEWORK_CLICKABLE_HPP