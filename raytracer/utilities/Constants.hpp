#pragma once

/**
    This file caches common values and constants.

    Courtesy Kevin Suffern.
*/

#include <cstdlib>

#include "RGBColor.hpp"

// Precompute commonly used values.
const double PI = 3.1415926535897932384;
const double TWO_PI = 6.2831853071795864769;
const double PI_ON_180 = 0.0174532925199432957;
const double invPI = 0.3183098861837906715;
const double invTWO_PI = 0.1591549430918953358;

// Small and large values.
const double kEpsilon = 0.0001;
const double kHugeValue = 1.0E10;

// Some standard colors.
const RGBColor black(0.0);
const RGBColor white(1.0);
const RGBColor red(1.0, 0.0, 0.0);
const RGBColor green(0.0, 1.0, 0.0);
const RGBColor blue(0.0, 0.0, 1.0);

// Useful for scaling the output of rand() to [0,1].
const double invRAND_MAX = 1.0 / (double)RAND_MAX;
