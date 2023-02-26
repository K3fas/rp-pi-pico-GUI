//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_TYPES_HPP
#define PICO_KIT_FRAMEWORK_TYPES_HPP

#include "stdint.h"

namespace rpgui::types
{
    struct Width
    {
        uint16_t v;
    };
    struct Height
    {
        uint16_t v;
    };
    struct Radius
    {
        uint16_t v;
    };

    struct Point
    {
        int16_t x, y;
    };

    struct Rect
    {
        Point start;
        Width w;
        Height h;
    };

    struct Circle
    {
        Point start;
        Radius r;
    };

} // namespace rpgui::types

#endif // PICO_KIT_FRAMEWORK_TYPES_HPP