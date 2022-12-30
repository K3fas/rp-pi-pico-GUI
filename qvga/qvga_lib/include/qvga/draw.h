// ****************************************************************************
//
//                                   Draw
//
// ****************************************************************************

#ifndef _DRAW_H
#define _DRAW_H

#include <stdint.h>
#include "mat2d.h"

#define TEXTWIDTH	(WIDTH/8)	// width of text buffer (=40)
#define TEXTHEIGHT	(HEIGHT/8)	// height of text buffer (=30)
#define TEXTSIZE	(TEXTWIDTH*TEXTHEIGHT) // size of mono text buffer (=1200)
#define FTEXTSIZE	(TEXTWIDTH*2*TEXTHEIGHT) // size of text buffer with foreground color (=2400)

// pointer to draw frame buffer
extern uint8_t *pDrawBuf;

// Draw rectangle
void DrawRect(int x, int y, int w, int h, uint8_t col);

// Draw frame
void DrawFrame(int x, int y, int w, int h, uint8_t col);

// clear canvas (fill with black color)
void DrawClear();

// Draw point
void DrawPoint(int x, int y, uint8_t col);

// Draw line
void DrawLine(int x1, int y1, int x2, int y2, uint8_t col);

// Draw filled circle
void DrawFillCircle(int x0, int y0, int r, uint8_t col);

// Draw circle
void DrawCircle(int x0, int y0, int r, uint8_t col);

// Draw text (transparent background)
void DrawText(const char *text, int x, int y, uint8_t col);

// Draw text double sized (transparent background)
void DrawText2(const char *text, int x, int y, uint8_t col);

// Draw text with background
void DrawTextBg(const char *text, int x, int y, uint8_t col, uint8_t bgcol);

// Draw text buffer (size TEXTSIZE)
void DrawTextBuf(const char *textbuf, uint8_t col, uint8_t bgcol);

// Draw text buffer with foreground color (size FTEXTSIZE)
void DrawFTextBuf(const char *textbuf, uint8_t bgcol);

// Draw image
void DrawImg(const uint8_t *src, int xd, int yd, int w, int h, int ws);

// Draw image with transparency (col = transparency key color)
void DrawBlit(const uint8_t *src, int xd, int yd, int w, int h, int ws, uint8_t col);

// DrawImgMat mode
enum {
	DRAWIMG_WRAP,		// wrap image
	DRAWIMG_NOBORDER,	// no border (transparent border)
	DRAWIMG_CLAMP,		// clamp image (use last pixel as border)
	DRAWING_COLOR,		// color border
	DRAWIMG_TRANSP,		// transparent image with key color
	DRAWIMG_PERSP,		// perspective floor
};

// draw 8-bit image with 2D transformation matrix
//  src ... source image
//  ws ... source image width
//  hs ... source image height
//  x ... destination coordinate X
//  y ... destination coordinate Y
//  w ... destination width
//  h ... destination height
//  m ... transformation matrix (should be prepared using PrepDrawImg or PrepDrawPersp function)
//  mode ... draw mode DRAWIMG_*
//  color ... key or border color (DRAWIMG_PERSP mode: horizon offset)
// Note to wrap and perspective mode: Width and height of source image must be power of 2!
void DrawImgMat(const uint8_t *src, int ws, int hs, int x, int y, int w, int h, const cMat2Df *m, uint8_t mode, uint8_t color);

// draw image line interpolated
//  src = source image
//  xd,yd = destination coordinates
//  wd = destination width
//  ws = source width
//  wbs = source line pitch in bytes
void DrawImgLine(const uint8_t *src, int xd, int yd, int wd, int ws, int wbs);

// generate gradient
void GenGrad(uint8_t *dst, int w);

// decode unsigned number into ASCIIZ text buffer (returns number of digits)
//  sep = thousand separator, 0=none
int DecUNum(char *buf, uint32_t num, char sep = 0);

// decode signed number into ASCIIZ text buffer (returns number of digits)
//  sep = thousand separator, 0=none
int DecNum(char *buf, int32_t num, char sep = 0);

// decode hex number (dig = number of digits)
void DecHexNum(char *buf, uint32_t num, uint8_t dig);

// decode 2 digits of number
void Dec2Dig(char *buf, uint8_t num);

// decode 2 digits of number with space character
void Dec2DigSpc(char *buf, uint8_t num);

// get ascii text length
int TextLen(const char *txt);

#endif // _DRAW_H
