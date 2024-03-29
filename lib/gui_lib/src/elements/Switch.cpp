//
// Created by kefas on 26.2.23.
//
#include "Switch.hpp"
#include "rp_core.hpp"
#include "MouseEvent.hpp"
#include "MouseDispatcher.hpp"
#include "IVGA.hpp"

rpgui::ui::Switch::Switch(const Width &width, const Height &height, const bool &value,
                          const Color backgroundColor,
                          const Color switchOnColor,
                          const Color switchOffColor,
                          const Color borderColor)
    : VisualElement(Bounds(0, 0, width.v, height.v), backgroundColor), isSwitched(value), switchOnColor(switchOnColor), switchOffColor(switchOffColor), borderColor(borderColor)
{
    rpgui::core::MainApp::AddListener(MouseEventType::Clicked, rpgui::event::Handler{changeState, this}, 1);
}

rpgui::ui::Switch::Switch(const Width &width, const Height &height, bool &value,
                          const Color backgroundColor,
                          const Color switchOnColor,
                          const Color switchOffColor,
                          const Color borderColor)
    : VisualElement(Bounds(0, 0, width.v, height.v), backgroundColor), isSwitched(value), switchOnColor(switchOnColor), switchOffColor(switchOffColor), borderColor(borderColor)
{
    rpgui::core::MainApp::AddListener(MouseEventType::Clicked, rpgui::event::Handler{changeState, this}, 1);
}

rpgui::ui::Switch::Switch(const Bounds &bounds, const bool &value,
                          const Color backgroundColor,
                          const Color switchOnColor,
                          const Color switchOffColor,
                          const Color borderColor)
    : VisualElement(bounds, backgroundColor), isSwitched(value), switchOnColor(switchOnColor), switchOffColor(switchOffColor), borderColor(borderColor)
{
    rpgui::core::MainApp::AddListener(MouseEventType::Clicked, rpgui::event::Handler{changeState, this}, 1);
}

rpgui::ui::Switch::Switch(const Bounds &bounds, bool &value,
                          const Color backgroundColor,
                          const Color switchOnColor,
                          const Color switchOffColor,
                          const Color borderColor)
    : VisualElement(bounds, backgroundColor), isSwitched(value), switchOnColor(switchOnColor), switchOffColor(switchOffColor), borderColor(borderColor)
{
    rpgui::core::MainApp::AddListener(MouseEventType::Clicked, rpgui::event::Handler{changeState, this}, 1);
}

void rpgui::ui::Switch::Draw() const
{
    auto bounds = GetBounds();
    IVGA::IDrawRectangle(bounds, color);

    // true -> right pos
    if (isSwitched.GetValue())
    {
        IVGA::IDrawRectangle(Bounds(bounds.x + bounds.w / 2, bounds.y, bounds.w / 2, bounds.h), switchOnColor);
    }
    else
    {
        IVGA::IDrawRectangle(Bounds(bounds.x, bounds.y, bounds.w / 2, bounds.h), switchOffColor);
    }
    
    IVGA::IDrawFrame(bounds, borderColor);
}

void rpgui::ui::Switch::changeState(rpgui::event::MouseEvent<MouseEventType> &event, Clickable *sender)
{
    auto sw = (Switch *)sender;
    if (sw)
    {
        sw->isSwitched.SetValue(!sw->isSwitched.GetValue());
    }
}
