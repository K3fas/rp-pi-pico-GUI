//
// Created by kefas on 27.2.23.
//
#include "MouseDispatcher.hpp"
#include "Cursor.hpp"
#include "rp_core.hpp"

rpgui::event::MouseDispatcher::~MouseDispatcher()
{
    for (auto &priority : _listeners)
    {
        for (auto &listener : _listeners)
        {
            // Clear vector
            listener.second.clear();
        }
        // Clear map
        priority.second.clear();
    }
    // Clears top map
    _listeners.clear();
}

void rpgui::event::MouseDispatcher::Post(MouseEvent<MouseEventType> &event)
{
    for (auto const &priority : _listeners)
    {
        // No listeners
        if (priority.second.find(event.Type()) == priority.second.end())
            continue;

        for (auto const &handler : priority.second.at(event.Type()))
        {
            if (event.IsHandled())
                return;
            // Posts event to handling function of listener,
            // with information of sender objs
            auto view = (rpgui::common::VisualElement *)handler.sender;
            view->GetBounds();
            if (!view->IsInBounds(event.pos))
                continue;
            // Go to root
            // Check if element is in current page
            auto element = (rpgui::common::Element *)view;
            while (element->GetParrent() != nullptr)
            {
                element = const_cast<rpgui::common::Element *>(element->GetParrent());
            }
            if(element->GetId() != rpgui::core::MainApp::GetSelectedPageID())
                continue;
                
            // Post event if cursor is above element and that element is currently beeing drawn
            handler.handler(event, handler.sender);
        }
    }
}

void rpgui::event::MouseDispatcher::Subscribe(MouseEventType type, const Handler &handler, const uint8_t priority)
{
    _listeners[priority][type].push_back(handler);
}

rpgui::event::Handler::Handler(const HandleFunc &func, Clickable *sender)
    : id(counter++), handler(func), sender(sender)
{
}
