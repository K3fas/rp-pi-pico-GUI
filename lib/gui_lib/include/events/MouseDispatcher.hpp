//
// Created by kefas on 27.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_MOUSEDISPATCHER_HPP
#define PICO_KIT_FRAMEWORK_MOUSEDISPATCHER_HPP

#include "include.hpp"
#include "MouseEvent.hpp"

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
        inline static uint16_t counter = 0;
        const uint16_t id;
        HandleFunc handler;
        Clickable *sender;

        Handler(const HandleFunc& func, Clickable* sender);
    };

    class MouseDispatcher
    {

    private:
        using PriorityListener = std::map<uint8_t,std::map<MouseEventType, std::vector<Handler>>>;
        PriorityListener _listeners;


    public:
        MouseDispatcher() = default;
        MouseDispatcher(const MouseDispatcher &) = default;
        ~MouseDispatcher();

        void Post(MouseEvent<MouseEventType> &event, ID activePage);

        void Subscribe(MouseEventType type, const Handler &handler, const uint8_t priority = 0);
    };

} // namespace rpgui::event

#endif // PICO_KIT_FRAMEWORK_MOUSEDISPATCHER_HPP