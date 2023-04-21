#ifndef PICO_KIT_IVGA
#define PICO_KIT_IVGA

#include "VColors.hpp"

#include "font8x8.bmp.h"

namespace rpgui::type
{
    class Point;
    class Width;
    class Height;
    class Radius;
}

namespace rpgui::common
{
    class Bounds;
    class Sprite;
}

using namespace rpgui::type;
using namespace rpgui::common;
using namespace rpgui::colors;


namespace IVGA
{
    void init();

    void IDrawRectangle(const Point &point, const Width &width, const Height &heigth, const Color &color);

    void IDrawRectangle(const Bounds &coord, const Color &color);

    void IDrawFrame(const Bounds &coord, const Color &color);

    void IDrawPoint(const Point &point, const Color &color);

    void IDrawClear();

    void IDrawLine(const Point &start, const Point &end, const Color &color);

    void IDrawCircle(const Point &point, const Radius &radius, const Color &color, bool isFilled = true);

    void IDrawText(const char *text, const Point &point, const Color &color, const Color &background = Color::Transparent, const void* font = Font8x8.image, uint8_t fontHeight = 8, uint8_t scaleX = 1 , uint8_t scaleY = 1);

    void IDrawImage(Sprite& source, const Point& point);

    void ICore1Exec(void (*fnc)());

    void IWaitVSync();

}

#endif // PICO_KIT_IVGA