#pragma once

#define NOTRACKING
#ifdef TRACKING
#include <stdio.h>
#include "pico/stdlib.h"
#endif

#include "stdint.h"

#include "Base.hpp"
#include "View.hpp"
#include "Types.hpp"
#include "Bounds.hpp"
#include "Margin.hpp"
#include "Clickable.hpp"
#include "BindableProperty.hpp"
#include "Activatable.hpp"
#include "settings.hpp"

