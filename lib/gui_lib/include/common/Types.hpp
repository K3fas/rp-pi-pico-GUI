//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_TYPES_HPP
#define PICO_KIT_FRAMEWORK_TYPES_HPP

#include <cstdint>

namespace rpgui::type
{
    typedef uint16_t ID;

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

    struct sCircle
    {
        Point start;
        Radius r;
    };

    enum class MouseEventType
    {
        Clicked,
        Released,
        Pressed,
    };

    


} // namespace rpgui::type

#endif // PICO_KIT_FRAMEWORK_TYPES_HPPT