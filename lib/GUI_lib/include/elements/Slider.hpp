//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_SLIDER_HPP
#define PICO_KIT_FRAMEWORK_SLIDER_HPP

#include "include.hpp"

namespace rpgui::event
{
    template<typename T>
    class MouseEvent;
}

using namespace rpgui::colors;
using namespace rpgui::common;
using namespace rpgui::event;

namespace rpgui::ui
{
    class Slider : public View, public Clickable
    {
    private:
        uint8_t _pinOffset;
    public:
        BindableProperty<double> value;
        Color pinColor = Color::Red, leftColor = Color::Gray, doneColor = Color::DarkBlue;
        uint8_t pinSize = 4;

    public:
        Slider() = delete;
        Slider(const Slider &) = default;
        ~Slider() = default;

        Slider(const Width &width, const Height &heigth, const Color &color, double &value);
        Slider(const Width &width, const Height &heigth, const Color &color, const double &value = 0.0);

        Slider(const Bounds &bounds, const Color &color, double &value);
        Slider(const Bounds &bounds, const Color &color, const double &value = 0.0);

        void Draw() const final;

    private:
        void handlePressed(MouseEvent<MouseEventType> &event, Clickable *sender);
        void handleReleased(MouseEvent<MouseEventType> &event, Clickable *sender);
    };

} // namespace rpgui::ui

#endif // PICO_KIT_FRAMEWORK_SLIDER_HPP
