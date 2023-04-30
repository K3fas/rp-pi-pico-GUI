//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_CURSOR_HPP
#define PICO_KIT_FRAMEWORK_CURSOR_HPP

#include "include.hpp"

using namespace rpgui::common;

namespace rpgui::core
{
    class Cursor : public VisualElement
    {

    public:
        struct pos_t
        {
            float x = 0, y = 0;
        } pos;
        
        Cursor() = default;
        Cursor(const Cursor &) = delete;
        ~Cursor() = default;

        void SetBounds(const Bounds& bounds) final;

        void Draw() const final;
    };

} // namespace rpgui::core

#endif // PICO_KIT_FRAMEWORK_CURSOR_HPP
