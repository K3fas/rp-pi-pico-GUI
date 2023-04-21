//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_RADIOBUTTON_HPP
#define PICO_KIT_FRAMEWORK_RADIOBUTTON_HPP

#include "include.hpp"
#include "font8x8.bmp.h"
#include <vector>
#include <string>

using namespace rpgui::common;
using namespace rpgui::colors;
using namespace rpgui::type;

namespace rpgui::comon
{
    class Clickable;
}

namespace rpgui::ui
{
    class RadioButton : public View, public Clickable
    {
    private:
        const uint8_t _itemHeight;
        const uint8_t _itemWidth;
        const uint8_t _fontSize;
        const void *_font;
        uint8_t _delimiter;

        Point _circleCenter;

    public:
        std::vector<std::string> _items;
        uint8_t _checkedItem = 0;
        uint8_t circleRadius = 3;
        Color backgorundColor;

    public:
        RadioButton() = delete;
        RadioButton(const RadioButton &) = default;
        ~RadioButton() = default;

        RadioButton(const Width &itemWidth, const Height &itemHeight,
             Color color, Color bgColor = Color::Gray,
            const void *font = Font8x8.image, uint8_t fontSize = 8);

        void AddItem(std::string text);

        void SetBounds(const Bounds &bounds) override;

        void Draw() const final;

    private:
        static void clickHandler(rpgui::event::MouseEvent<MouseEventType> &event, Clickable *sender);
    };

} // namespace rpgui::ui

#endif // PICO_KIT_FRAMEWORK_RADIOBUTTON_HPP
