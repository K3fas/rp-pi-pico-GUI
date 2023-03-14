//
// Created by kefas on 27.2.23.
//
#include "MouseDispatcher.hpp"

void rpgui::event::MouseDispatcher::Post(Event<MouseEventType> &event)
{
    // No subscribers found
    if (_listeners.find(event.Type()) == _listeners.end())
        return;

    for (auto &&listener : _listeners.at(event.Type()))
    {
        if (event.IsHandled())
            return;
        // Posts event to handling function of listener,
        // with information of sender objs
        listener.handler(event,listener.sender);
    }
}

void rpgui::event::MouseDispatcher::Subscribe(MouseEventType type, const Handler &handler)
{
    _listeners[type].push_back(handler);
}
