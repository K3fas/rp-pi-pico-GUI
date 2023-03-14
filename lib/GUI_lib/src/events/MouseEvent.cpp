//
// Created by kefas on 26.2.23.
//

#include "MouseEvent.hpp"

using namespace rpgui::type;

rpgui::event::MouseEvent::MouseEvent(const MouseEventType &type, const std::string &name)
     : Event<MouseEventType>(type, name){};

