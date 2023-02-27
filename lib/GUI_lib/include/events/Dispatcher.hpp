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
    class Dispatcher
    {
        using SlotType = std::function<void(const Event<T> &)>;

    private:
        std::map<T, std::vector<SlotType>> _observers;

    public:
        Dispatcher() = default;

        void Subscribe(T type, const SlotType &function) { _observers[type].push_back(function); }

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
