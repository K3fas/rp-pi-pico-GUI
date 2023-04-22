#include "IVGA.hpp"

#include "Types.hpp"
#include "Base.hpp"
#include "Sprite.hpp"
#include <string>

#ifdef PICOVGA
#include "global.h" // global common definitions
#include "settings.hpp"

ALIGNED u8 Box[WIDTH * HEIGHT];

#define WIDTHBYTE WIDTH

extern sCanvas Canvas;

#endif

#ifndef PICOVGA

#include "qvga/draw.h" // draw
#include "qvga/qvga.h" // main lib

#endif

namespace IVGA
{

#ifdef PICOVGA
    void init()
    {
        Video(DEV_VGA, RES_EGA, FORM_8BIT, Box);
    }

    void IDrawRectangle(const Point &point, const Width &width, const Height &heigth, const Color &color)
    {
        DrawRect(&Canvas, point.x, point.y, width.v, heigth.v, color);
    }

    void IDrawRectangle(const rpgui::common::Bounds &coord, const Color &color)
    {
        DrawRect(&Canvas, coord.x, coord.y, coord.w, coord.h, color);
    }

    void IDrawFrame(const Bounds &bounds, const Color &color)
    {
        DrawFrame(&Canvas, bounds.x, bounds.y, bounds.w, bounds.h, color);
    }

    void IDrawPoint(const Point &point, const Color &color)
    {
        DrawPoint(&Canvas, point.x, point.y, color);
    }

    void IDrawClear()
    {
        DrawClear(&Canvas);
    }

    void IDrawLine(const Point &start, const Point &end, const Color &color)
    {
        DrawLine(&Canvas, start.x, start.y, end.x, end.y, color);
    }

    void IDrawCircle(const Point &point, const Radius &radius, const Color &color, bool isFilled)
    {
        if (isFilled)
        {
            DrawFillCircle(&Canvas, point.x, point.y, radius.v, color);
        }
        else
        {
            DrawCircle(&Canvas, point.x, point.y, radius.v, color);
        }
    }

    void IDrawText(const char *text, const Point &point, const Color &color, const void *font, uint8_t fontHeight, uint8_t scaleX, uint8_t scaleY)
    {
    }

    void IDrawText(const char *text, const Point &point, const Color &color, const Color &background, const void *font, uint8_t fontHeight, uint8_t scaleX, uint8_t scaleY)
    {
        if (Color::Transparent == background)
        {
            DrawText(&Canvas, text, point.x, point.y, color, font, fontHeight, scaleX, scaleY);
        }
        else
        {
            DrawTextBg(&Canvas, text, point.x, point.y, color, background, font, fontHeight, scaleX, scaleY);
        }
    }

    void IDrawImage(const rpgui::ui::Sprite &source, const Point &point)
    {
        auto img = source.GetCanvas(Canvas);
        DrawImg(&Canvas, &img, point.x, point.y, 1, 1, source.GetWidth(), source.GetHeight());
    }

    void ICore1Exec(void (*fnc)())
    {
        Core1Exec(fnc);
    }

    void IWaitVSync()
    {
        WaitVSync();
    }
#endif

#ifndef PICOVGA

    void init()
    {
    }

    void IDrawRectangle(const Point &point, const Width &width, const Height &heigth, const Color &color)
    {
        DrawRect(point.x, point.y, width.v, heigth.v, color);
    }

    void IDrawRectangle(const Bounds &coord, const Color &color)
    {
        DrawRect(coord.x, coord.y, coord.w, coord.h, color);
    }

    void IDrawFrame(const Bounds &coord, const Color &color)
    {
        DrawFrame(coord.x, coord.y, coord.w, coord.h, color);
    }

    void IDrawPoint(const Point &point, const Color &color)
    {
        DrawPoint(point.x, point.y, color);
    }

    void IDrawClear()
    {
        DrawClear();
    }

    void IDrawLine(const Point &start, const Point &end, const Color &color)
    {
        DrawLine(start.x, start.y, end.x, end.y, color);
    }

    void IDrawCircle(const Point &point, const Radius &radius, const Color &color, bool isFilled)
    {
        if (isFilled)
        {
            DrawFillCircle(point.x, point.y, radius.v, color);
        }
        else
        {
            DrawCircle(point.x, point.y, radius.v, color);
        }
    }

    void IDrawText(const char *text, const Point &point, const Color &color, const void *font, uint8_t fontHeight, uint8_t scaleX, uint8_t scaleY)
    {
        if (fontHeight > 8)
        {
            DrawText2(text, point.x, point.y, color);
        }
        else
        {
            DrawText(text, point.x, point.y, color);
        }
    }

    void IDrawText(const char *text, const Point &point, const Color &color, const Color &background, const void *font, uint8_t fontHeight, uint8_t scaleX, uint8_t scaleY)
    {
        DrawTextBg(text, point.x, point.y, color, background);
    }

    void IDrawImage(Sprite &source, const Point &point)
    {
        DrawImg(source.GetImage(), point.x, point.y, 1, 1, source.GetWidth(), source.GetHeight());
    }

    void ICore1Exec(void (*fnc)())
    {
        Core1Exec(fnc);
    }

    void IWaitVSync()
    {
        WaitVSync();
    }

#endif
}
