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
    class Event;
}

namespace rpgui::common
{
    class Clickable;
}

namespace rpgui::type
{

    using HandleFunc = std::function<void(rpgui::event::Event<rpgui::type::MouseEventType> &, rpgui::common::Clickable *)>;
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

        void SetOnClickHandler(const MouseEventType type, const HandleFunc &function);
    };

} // namespace rpgui::common

#endif // PICO_KIT_FRAMEWORK_CLICKABLE_HPP