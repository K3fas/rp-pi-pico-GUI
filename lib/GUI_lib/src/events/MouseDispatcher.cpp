//
// Created by kefas on 27.2.23.
//
#include "MouseDispatcher.hpp"
#include "Cursor.hpp"



void rpgui::event::MouseDispatcher::Post(Event<MouseEventType> &event, uint16_t x, uint16_t y)
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
        auto view = (rpgui::common::View*)listener.sender;
        view->GetBounds();
        if(view->IsInBounds(Point{x,y})){
            listener.handler(event,listener.sender);
        }
    }
}

void rpgui::event::MouseDispatcher::Subscribe(MouseEventType type, const Handler &handler)
{
    _listeners[type].push_back(handler);
}

