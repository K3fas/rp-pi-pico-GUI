#pragma once
namespace VColors
{
	// 8 Color bits of VGA output

	constexpr uint8_t b0 = 1 << 0;
	constexpr uint8_t b1 = 1 << 1;
	constexpr uint8_t b2 = 1 << 2;
	constexpr uint8_t b3 = 1 << 3;
	constexpr uint8_t b4 = 1 << 4;
	constexpr uint8_t b5 = 1 << 5;
	constexpr uint8_t b6 = 1 << 6;
	constexpr uint8_t b7 = 1 << 7;

	enum Color
	{

		DarkBlue = b0,
		SemiBlue = b1,
		Blue = b0 + b1,
		MoreBlue = Blue + b3 + b6,
		LightBlue = Blue + b4 + b7,

		DarkGreen = b3,
		SemiGreen = b4,
		Green = b2 + b3 + b4,
		MoreGreen = Green + b0 + b6,
		LightGreen = Green + b1 + b7,

		DarkRed = b6,
		SemiRed = b7,
		Red = b5 + b6 + b7,
		MoreRed = Red + b0 + b3,
		LightRed = Red + b1 + b4,

		DarkCyan = b0 + b3,
		SemiCyan = b1 + b4,
		Cyan = b0 + b1 + b2 + b3 + b4,

		DarkMagenta = b0 + b6,
		SemiMagenta = b1 + b7,
		Magenta = b0 + b1 + b5 + b6 + b7,

		DarkYellow = b3 + b6,
		SemiYellow = b4 + b7,
		Yellow = b2 + b3 + b4 + b5 + b6 + b7,

		DarkGray = b2 + b5,
		SemiGray = b0 + b3 + b6,
		Gray = b1 + b4 + b7,

		Black = (uint8_t)0,
		White = (uint8_t)255,

		Tranparent

	};

}