#pragma once

#include <cstdint>

namespace rpgui::common
{
    struct Margin
    {
        uint8_t l, t, r, b;

        Margin() : l(0), t(0), r(0), b(0) {}
        Margin(const Margin &) = default;
        ~Margin() = default;
        Margin(uint8_t l, uint8_t t, uint8_t r, uint8_t b)
            : l(l), t(t), r(r), b(b) {}
    };
} // namespace rpgui::type


