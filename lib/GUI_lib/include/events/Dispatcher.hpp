//
// Created by kefas on 27.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_DISPATCHER_HPP
#define PICO_KIT_FRAMEWORK_DISPATCHER_HPP

#include "Event.hpp"

#include <map>
#include <functional>
#include <vector>
#include <algorithm>

namespace rpgui::event
{
    template <typename T>
    using SlotType = std::function<void(const Event<T> &)>;

    template <typename T>
    class Dispatcher
    {
    public:
    private:
        std::map<T, std::vector<rpgui::event::SlotType<T>>> _observers;

    public:
        Dispatcher() = default;

        void Subscribe(T type, const SlotType<T> &function) { _observers[type].push_back(function); }

        void Post(Event<T> &event)
        {
            // No subscribers found
            if (_observers.find(event.Type()) == _observers.end())
                return;

            for (auto &&observer : _observers.at(event.Type()))
            {
                if (!event.IsHandled())
                    observer(event);
            }
        }
    };

} // namespace rpgui::events

#endif // PICO_KIT_FRAMEWORK_DISPATCHER_HPP
