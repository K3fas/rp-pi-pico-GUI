//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_SWITCH_HPP
#define PICO_KIT_FRAMEWORK_SWITCH_HPP

#include "include.hpp"

using namespace rpgui::common;
using namespace rpgui::colors;
using namespace rpgui::type;

namespace rpgui::ui
{
    class Switch : public View, public Clickable
    {
    public:
        BindableProperty<bool> isSwitched;
        Color switchOnColor, switchOffColor, borderColor;

    public:
        Switch() = delete;
        Switch(const Switch &) = delete;
        ~Switch() = default;

        Switch(const Width &width, const Height &height, const bool &value,
               const Color backgroundColor = Color::SemiGray,
               const Color switchOnColor = Color::Green,
               const Color switchOffColor = Color::Red,
               const Color borderColor = Color::Gray);

        Switch(const Width &width, const Height &height, bool &value,
               const Color backgroundColor = Color::SemiGray,
               const Color switchOnColor = Color::Green,
               const Color switchOffColor = Color::Red,
               const Color borderColor = Color::Gray);

        Switch(const Bounds &bounds, const bool &value,
               const Color backgroundColor = Color::SemiGray,
               const Color switchOnColor = Color::Green,
               const Color switchOffColor = Color::Red,
               const Color borderColor = Color::Gray);
               
        Switch(const Bounds &bounds, bool &value,
               const Color backgroundColor = Color::SemiGray,
               const Color switchOnColor = Color::Green,
               const Color switchOffColor = Color::Red,
               const Color borderColor = Color::Gray);

        void Draw() const final;

    private:
        static void changeState(rpgui::event::MouseEvent<MouseEventType> &event, Clickable *sender);
    };

} // namespace rpgui::ui

#endif // PICO_KIT_FRAMEWORK_SWITCH_HPP
