//
// Created by kefas on 27.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_MOUSEEVENT_HPP
#define PICO_KIT_FRAMEWORK_MOUSEDEVENT_HPP

#include "include.hpp"
#include "Event.hpp"
#include <string>


using namespace rpgui::type;

namespace rpgui::event
{
    class MouseEvent : public Event<MouseEventType>
    {
    private:
    public:
        MouseEvent(const MouseEventType &type, const std::string &name);
        virtual ~MouseEvent() = default;
    };

} // namespace rpgui::events

#endif // PICO_KIT_FRAMEWORK_MOUSEEVENT_HPP
