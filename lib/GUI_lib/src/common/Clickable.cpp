//
// Created by kefas on 26.2.23.
//

#include "Clickable.hpp"
#include "Types.hpp"
#include "rp_core.hpp"

using namespace rpgui::type;

namespace rpgui::common
{
    void Clickable::SetOnClickHandler(const rpgui::type::MouseEventType type, const rpgui::type::HandleFunc &function)
    {
        rpgui::core::MainApp::AddListener(type,Handler{function,this});
    }

} // namespace rpgui::common
