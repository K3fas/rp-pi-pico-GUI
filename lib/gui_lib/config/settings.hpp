#pragma once
#include "stdint.h"
#ifdef PICOVGA

#define WIDTH   512     // display width
#define HEIGHT  400     // display width

#else

#define WIDTH	320		// display width
#define HEIGHT	240		// display width

#endif

static constexpr float sensitivity = 2.0f;
static constexpr uint8_t cursorSize = 5;
static constexpr uint8_t cursorWidth = 1;

static constexpr bool drawOnCore1 = false;
static constexpr bool waitVSync = true;