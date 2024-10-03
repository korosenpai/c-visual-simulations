#pragma once

#include <raylib.h>
#include <math.h>

void draw_lines(int array_size, Vector2* vertex_array, Color col, int border_size);
void DrawArc(Vector2 center, float radius, int startAngle, int endAngle, Color color, float thickness);

// from snake, points are in a anticlockwise fashion
void draw_polygon(int array_size, Vector2* vertex_array, Color col);

