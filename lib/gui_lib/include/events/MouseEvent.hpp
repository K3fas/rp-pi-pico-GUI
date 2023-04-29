//
// Created by kefas on 27.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_EVENT_HPP
#define PICO_KIT_FRAMEWORK_EVENT_HPP

#include <string>
#include <functional>
#include "include.hpp"

using namespace rpgui::type;

namespace rpgui::event
{
    template <typename T>
    class MouseEvent
    {
    private:
        T _type;
        bool _handled = false;

    public:
        const Point pos;

    public:
        MouseEvent() = delete;
        MouseEvent(const MouseEvent&) = default;
        virtual ~MouseEvent() = default;
        MouseEvent(T type, const Point& position) : _type(type), pos(position)  {}

        inline const T Type() const { return _type; }
        virtual bool IsHandled() { return _handled; }
        void SetHandled() { _handled = true; }
    };

} // namespace rpgui::event

#endif // PICO_KIT_FRAMEWORK_EVENT_HPP
