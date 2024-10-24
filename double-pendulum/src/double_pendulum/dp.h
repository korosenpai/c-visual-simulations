#pragma once

#include <raylib.h>

#include "../constants.h"

typedef struct {
    // this is the offset for the whole pendulum
    // pendulum starts in 0,0 + origin_point.
    // for calculations oriogin of pendulum is 0,0, this is only for rendering
    Vector2 pendulum_origin;

    float r1;
    float r2;

    float m1;
    float m2;

    // NOTE: in radians
    float theta1;
    float theta2;

    Vector2 p1;
    Vector2 p2;

    // velocity
    float a1_v;
    float a2_v;

} doublePendulum;

doublePendulum dp_create(
    float x, float y, float r1, float r2, float m1, float m2, float theta1, float theta2
);

void dp_update(doublePendulum* dp, float* deltat);

void dp_render(doublePendulum* dp);
