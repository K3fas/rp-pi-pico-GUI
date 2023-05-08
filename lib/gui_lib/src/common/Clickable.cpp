//
// Created by kefas on 26.2.23.
//

#include "Clickable.hpp"
#include "rp_core.hpp"
#include "Types.hpp"
#include "MouseDispatcher.hpp"

using namespace rpgui::type;

namespace rpgui::common
{
    void Clickable::SetOnClickHandler(const rpgui::type::MouseEventType type, const rpgui::type::HandleFunc &function, const uint8_t priority)
    {
        rpgui::core::MainApp::AddListener(type,Handler(function,this), priority);
    }

} // namespace rpgui::common
