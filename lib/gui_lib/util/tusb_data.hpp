#pragma once

namespace HID
{
    struct kbd
    {
        inline static uint8_t pressedKeys[6] = {};
        inline static uint64_t processTime = 0;
    };

    struct mouse
    {
        inline static int16_t mousePos[2] = {};
        inline static uint8_t mouseKeys[5] = {};
        inline static uint64_t processTime = 0;
        inline static bool moved = false;
        inline static bool clicked = false;
    };

}
