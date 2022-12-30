#pragma once

namespace HID
{
    struct KBD_t
    {
        uint8_t pressedKeys[6] = {};
        uint64_t processTime;
    };

    struct MOUSE_t
    {
        int8_t mousePos[3] = {};
        uint8_t mouseKeys[5] = {};
        uint64_t processTime;
    };

}
