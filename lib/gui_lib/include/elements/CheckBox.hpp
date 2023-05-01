//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_CHECKBOX_HPP
#define PICO_KIT_FRAMEWORK_CHECKBOX_HPP

#include "include.hpp"

namespace rpgui::type
{
    enum class MouseEventType;
}

namespace rpgui::event
{
    template <typename T>
    class MouseEvent;
}

using namespace rpgui::type;
using namespace rpgui::common;

namespace rpgui::ui
{
    class CheckBox : public VisualElement, public Clickable
    {
    private:
        const uint8_t _minHeight = 5;
        const uint8_t _minWidth = 5;

    public:
        BindableProperty<bool> checked;
        Color tickColor;

    public:
        CheckBox() = delete;
        CheckBox(const CheckBox &) = default;
        ~CheckBox() = default;

        CheckBox(const Width &width, const Height &height, const bool &value, const Color backgroundColor, const Color tickColor = Color::White);
        CheckBox(const Width &width, const Height &height, bool &value, const Color backgroundColor, const Color tickColor = Color::White);

        CheckBox(const Bounds &bounds, const Color &backgroundColor, const bool &value, const Color tickColor = Color::White);
        CheckBox(const Bounds &bounds, const Color &backgroundColor, bool &value, const Color tickColor = Color::White);

        void Draw() const final;

    private:
        static void changeState(rpgui::event::MouseEvent<MouseEventType> &event, Clickable *sender);
    };

} // namespace rpgui::element

#endif // PICO_KIT_FRAMEWORK_CHECKBOX_HPP
