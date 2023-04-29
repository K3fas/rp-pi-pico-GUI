//
// Created by kefas on 27.2.23.
//
#include "MouseDispatcher.hpp"
#include "Cursor.hpp"

void rpgui::event::MouseDispatcher::Post(MouseEvent<MouseEventType> &event)
{
    // No subscribers found
    for (auto const &priority : _listeners)
    {
        if (priority.second.find(event.Type()) == priority.second.end())
            continue;
        
        for (auto const &handler : priority.second.at(event.Type()))
        {
            if (event.IsHandled())
                return;
            // Posts event to handling function of listener,
            // with information of sender objs
            auto view = (rpgui::common::View *)handler.sender;
            view->GetBounds();
            if (view->IsInBounds(event.pos))
            {
                handler.handler(event, handler.sender);
            }
        }
    }

    
}

void rpgui::event::MouseDispatcher::Subscribe(MouseEventType type, const Handler &handler, uint8_t priority)
{
    _listeners[priority][type].push_back(handler);
}

rpgui::event::Handler::Handler(const HandleFunc &func, Clickable *sender)
    : id(counter++),handler(func), sender(sender)
{
}
