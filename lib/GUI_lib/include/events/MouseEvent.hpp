//
// Created by kefas on 27.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_MOUSEEVENT_HPP
#define PICO_KIT_FRAMEWORK_MOUSEDEVENT_HPP

#include "Event.hpp"
#include <string>

namespace rpgui::event
{
    enum class MouseEventType
    {
        Clicked,
        Released,
        Pressed,
    };

    class MouseEvent : public Event<MouseEventType>
    {
    private:
        /* data */
    public:
        MouseEvent(const MouseEventType &type, const std::string &name) : Event<MouseEventType>(type, name){};
        virtual ~MouseEvent() = default;
    };

} // namespace rpgui::events

#endif // PICO_KIT_FRAMEWORK_MOUSEEVENT_HPP
