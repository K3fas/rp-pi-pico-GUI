#pragma once

#include <cstdint>
#include "Margin.hpp"

namespace rpgui::common
{
    struct Bounds
    {
        int16_t x, y;
        uint16_t w, h;

        Bounds() : x(0), y(0), w(0), h(0) {}
        Bounds(int16_t x, int16_t y, uint16_t w, uint32_t h)
            : x(x), y(y), w(w), h(h) {}

        Bounds(const Bounds &) = default;
        ~Bounds() = default;

        Bounds operator-(const uint8_t rhs)
        {
            return Bounds(x + rhs, y + rhs, w - rhs * 2, h - rhs * 2);
        }

        Bounds operator+(const Bounds rhs)
        {
            return Bounds(x + rhs.x, y + rhs.y, w, h);
        }

        friend Bounds operator-(const Bounds &lhs, const uint8_t rhs)
        {
            return Bounds(lhs.x + rhs, lhs.y + rhs, lhs.w - rhs * 2, lhs.h - rhs * 2);
        }

        static const Bounds GetAdjustedBounds(const Bounds &bounds, const Margin &margin)
        {
            return Bounds(
                bounds.x + margin.l,
                bounds.y + margin.t,
                bounds.w - margin.l - margin.r,
                bounds.h - margin.t - margin.b);
        }
    };
} // namespace rpgui::type
