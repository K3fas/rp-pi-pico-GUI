//
// Created by kefas on 26.2.23.
//

#include "Clickable.hpp"
#include "rp_core.hpp"

namespace rpgui::common
{
    void rpgui::common::Clickable::SetOnClickHandler(const MouseEventType type, const SlotType<MouseEventType> &function)
    {
        rpgui::core::MainApp::AddListener(type,function,this);
    }

} // namespace rpgui::common
