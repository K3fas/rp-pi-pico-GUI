//
// Created by kefas on 27.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_MOUSEDISPATCHER_HPP
#define PICO_KIT_FRAMEWORK_MOUSEDISPATCHER_HPP

#include "include.hpp"
#include "Event.hpp"

#include <map>
#include <functional>
#include <vector>
#include <algorithm>

using namespace rpgui::type;
using namespace rpgui::common;

namespace rpgui::event
{

    struct Handler
    {
        HandleFunc handler;
        Clickable *sender;
    };

    class MouseDispatcher
    {

    private:
        std::map<MouseEventType, std::vector<Handler>> _listeners;

    public:
        MouseDispatcher() = default;
        MouseDispatcher(const MouseDispatcher &) = default;
        ~MouseDispatcher() = default;

        void Post(Event<MouseEventType> &event);

        void Subscribe(MouseEventType type, const Handler &handler);
    };

} // namespace rpgui::event

#endif // PICO_KIT_FRAMEWORK_MOUSEDISPATCHER_HPP