#pragma once

#include <raylib.h>

typedef struct hsl {
  float h, s, l;
} HSL;


void col_shift_hue(Color* col, float angle);
