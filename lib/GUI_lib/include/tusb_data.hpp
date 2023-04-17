#pragma once

namespace HID
{
    inline static struct kbd_t
    {
        uint8_t pressedKeys[6] = {};
        uint64_t processTime;
    }kbd;

    inline static struct mouse_t
    {
        int16_t mousePos[2] = {};
        uint8_t mouseKeys[5] = {};
        uint64_t processTime;
        bool moved;
        bool clicked;
    }mouse;

}
