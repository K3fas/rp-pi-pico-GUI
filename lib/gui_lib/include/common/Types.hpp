//
// Created by kefas on 26.2.23.
//

#ifndef PICO_KIT_FRAMEWORK_TYPES_HPP
#define PICO_KIT_FRAMEWORK_TYPES_HPP

#include "stdint.h"
#include <cstring>
#include <utility>

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

    struct Margin
    {
        uint8_t l, t, r, b;

        Margin() : l(0), t(0), r(0), b(0) {}
        Margin(const Margin &) = default;
        ~Margin() = default;
        Margin(uint8_t l, uint8_t t, uint8_t r, uint8_t b)
            : l(l), t(t), r(r), b(b) {}
    };

    struct sprite_data
    {
        uint8_t *image;
        const int16_t size;
        const int16_t width;
        const int16_t height;
        const int16_t pitch;

        // Rule of 5
        sprite_data() : image(nullptr), size(0), width(0), height(0), pitch(0) {}
        sprite_data(const sprite_data &s) : image(s.image), size(s.size), width(s.width), height(s.height), pitch(s.pitch) {}

        sprite_data(sprite_data &&s) noexcept : image(std::exchange(s.image, nullptr)),
                                                size(s.size),
                                                width(s.width),
                                                height(s.height),
                                                pitch(s.pitch)
        {
        }
        ~sprite_data() = default;

        sprite_data(uint8_t *img, const int16_t size, const int16_t width, const int16_t height, const int16_t pitch)
            : image(img), size(size), width(width), height(height), pitch(pitch) {}

        // Copy assignment
        sprite_data &operator=(const sprite_data &rhs)
        {
            if (this == &rhs)
                return *this;

            image = rhs.image;
            const_cast<int16_t &>(size) = rhs.size;
            const_cast<int16_t &>(width) = rhs.width;
            const_cast<int16_t &>(height) = rhs.height;
            const_cast<int16_t &>(pitch) = rhs.pitch;

            return *this;
        }
        // Move assignment
        sprite_data &operator=(sprite_data &&rhs) noexcept
        {
            if (this == &rhs)
                return *this;

            delete[] image;
            image = std::exchange(rhs.image, nullptr);
            const_cast<int16_t &>(size) = rhs.size;
            const_cast<int16_t &>(width) = rhs.width;
            const_cast<int16_t &>(height) = rhs.height;
            const_cast<int16_t &>(pitch) = rhs.pitch;

            return *this;
        }
    };

} // namespace rpgui::type

#endif // PICO_KIT_FRAMEWORK_TYPES_HPPT