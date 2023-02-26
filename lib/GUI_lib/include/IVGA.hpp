#pragma once
#include "VColors.hpp" // colors

#define PICOVGA 0 // choose between PicoVGA and PicoQVGA lib

#if PICOVGA

#include "util/canvas.h"

#define WIDTH 512
#define HEIGHT 400
#define WIDTHBYTE WIDTH

#else

#include "qvga/draw.h"	 // draw
#include "qvga/qvga.h"	 // main lib
#include "qvga/config.h" // configs

#endif

#include "common/Types.hpp"
#include "common/Base.hpp"
#include <string>

// #include "cursor8.bmp.h"

namespace IVGA
{
	using namespace rpgui::colors;

#if PICOVGA

	static sCanvas can;

#endif

	struct Point
	{
		int x, y;
		Point() = default;
		Point(const Point &) = default;
		Point(int x, int y) : x(x), y(y) {}
	};
	struct Width
	{
		int v;
	};
	struct Height
	{
		int v;
	};
	struct Radius
	{
		int v;
	};
	struct Rectangle
	{
		Point start;
		Width width;
		Height height;

		Rectangle() = default;
		Rectangle(Rectangle &rect)
			: start(rect.start), width(rect.width), height(rect.height) {}

		Rectangle(Point start, Width width, Height heigth)
			: start(start), width(width), height(heigth) {}

		Rectangle(Point start, Point end)
			: start(start), width(Width{end.x - start.x}), height(Height{end.y - start.y}) {}

		// return shrinked rectangle
		Rectangle operator-(const uint8_t &rhs) const
		{
			return Rectangle(Point{start.x + rhs, start.y + rhs},
							 Width{width.v - rhs * 2},
							 Height{height.v - rhs * 2});
		}
	};

	struct Circle
	{
		Point center;
		Radius radius;
		Circle() = default;
		Circle(Circle &) = default;
		Circle(Point center, Radius radius)
			: center(center), radius(radius) {}
	};

#if PICOVGA

	void IDrawRectangle(const Point &point, const Width &width, const Height &heigth, const Color &color)
	{
		DrawRect(&can, point.x, point.y, width.v, heigth.v, color);
	}

	void IDrawRectangle(const Rectangle &rect, const Color &color)
	{
		DrawRect(&can, rect.start.x, rect.start.y, rect.width.v, rect.height.v, color);
	}

	void IDrawFrame(const Rectangle &rect, const Color &color)
	{
		DrawFrame(&can, rect.start.x, rect.start.y, rect.width.v, rect.height.v, color);
	}

	void IDrawPoint(const Point &point, const Color &color)
	{
		DrawPoint(&can, point.x, point.y, color);
	}

	void IDrawClear()
	{
		DrawClear(&can);
	}

	void IDrawLine(const Point &start, const Point &end, const Color &color)
	{
		DrawLine(&can, start.x, start.y, end.x, end.y, color);
	}

	void IDrawCircle(const Point &point, const Radius &radius, const Color &color, bool isFilled = true)
	{
		if (isFilled)
		{
			DrawFillCircle(&can, point.x, point.y, radius.v, color);
		}
		else
		{
			DrawCircle(&can, point.x, point.y, radius.v, color);
		}
	}

	void IDrawText(const char *text, const Point &point, const Color &color, uint8_t textSize = 1)
	{
		// DrawText(&can, text, point.x, point.y, color);
	}

	void IDrawText(const char *text, const Point &point, const Color &color, const Color &backgorund)
	{
		// DrawTextBg(text, point.x, point.y, color, backgorund);
	}

	void IDrawImage(sCanvas *source, const Rectangle coords, int ws)
	{
		// DrawImg(&can, source, coords.start.x, coords.start.y, coords.width.v, coords.width.v, ws);
	}

	void ICore1Exec(void (*fnc)())
	{
		Core1Exec(fnc);
	}

#else
	// To be deprecated
	void IDrawRectangle(const Point &point, const Width &width, const Height &heigth, const Color &color)
	{
		DrawRect(point.x, point.y, width.v, heigth.v, color);
	}
	// To be deprecated
	void IDrawRectangle(const Rectangle &rect, const Color &color)
	{
		DrawRect(rect.start.x, rect.start.y, rect.width.v, rect.height.v, color);
	}

	void IDrawRectangle(const rpgui::common::Coord &coord, const Color &color)
	{
		DrawRect(coord.x, coord.y, coord.w, coord.h, color);
	}

	void IDrawFrame(const Rectangle &rect, const Color &color)
	{
		DrawFrame(rect.start.x, rect.start.y, rect.width.v, rect.height.v, color);
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

	void IDrawCircle(const Point &point, const Radius &radius, const Color &color, bool isFilled = true)
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

	void IDrawText(const char *text, const Point &point, const Color &color, int textSize = 1)
	{
		if (textSize > 1)
		{
			DrawText2(text, point.x, point.y, color);
		}
		else
		{
			DrawText(text, point.x, point.y, color);
		}
	}

	void IDrawText(const char *text, const Point &point, const Color &color, const Color &backgorund)
	{
		DrawTextBg(text, point.x, point.y, color, backgorund);
	}

	void IDrawImage(const uint8_t *source, const Rectangle coords, int ws)
	{
		DrawImg(source, coords.start.x, coords.start.y, coords.width.v, coords.width.v, ws);
	}

	void ICore1Exec(void (*fnc)())
	{
		Core1Exec(fnc);
	}

#endif
}
