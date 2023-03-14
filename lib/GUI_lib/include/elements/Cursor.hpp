//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_CURSOR_HPP
#define PICO_KIT_FRAMEWORK_CURSOR_HPP

#include "include.hpp"

namespace rpgui::common
{
    class VisualElement;
} // namespace rpgui::common

namespace rpgui::core
{
    class Cursor : public rpgui::common::VisualElement
    {
    private:
        const uint16_t _size = 2;

    public:
        Cursor() = default;
        Cursor(const Cursor &) = delete;
        ~Cursor() = default;

        void Draw() const final;
    };

} // namespace rpgui::core

#endif // PICO_KIT_FRAMEWORK_CURSOR_HPP
