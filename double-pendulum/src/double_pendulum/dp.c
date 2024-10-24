#include "dp.h"
#include <math.h>
#include <raylib.h>
#include <raymath.h>


doublePendulum dp_create(
    float x, float y, float r1, float r2, float m1, float m2, float theta1, float theta2
) {
    return (doublePendulum) {
        .pendulum_origin = (Vector2){x, y},

        .r1 = r1,
        .r2 = r2,

        .m1 = m1,
        .m2 = m2,

        .theta1 = theta1,
        .theta2 = theta2,

        .p1 = (Vector2){0},
        .p2 = (Vector2){0},

        .a1_v = 0,
        .a2_v = 0,

    };

}

void dp_update(doublePendulum* dp, float* deltat) {

    float num1 = -G * (2 * dp->m1 + dp->m2) * sin(dp->theta1);
    float num2 = -dp->m2 * G * sin(dp->theta1 - 2 * dp->theta2);
    float num3 = -2 * sin(dp->theta1 - dp->theta2) * dp->m2;
    float num4 = dp->a2_v * dp->a2_v * dp->r2 + dp->a1_v * dp->a1_v * dp->r1 * cos(dp->theta1 - dp->theta2);
    float den = dp->r1 * (2 * dp->m1 + dp->m2 - dp->m2 * cos(2 * dp->theta1 - 2 * dp->theta2));
    float a1_a = (num1 + num2 + num3 * num4 ) / den;


    num1 = 2 * sin(dp->theta1 - dp->theta2);
    num2 = (dp->a1_v * dp->a1_v * dp->r1 * (dp->m1 + dp->m2));
    num3 = G * (dp->m1 + dp->m2) * cos(dp->theta1);
    num4 = dp->a2_v * dp->a2_v * dp->r2 * dp->m2 * cos(dp->theta1 - dp->theta2);
    den = dp->r2 * (2 * dp->m1 + dp->m2 - dp->m2 * cos(2 * dp->theta1 - 2 * dp->theta2));

    float a2_a = num1 * (num2 + num3 + num4) / den;

    // calculate new positions
    float x1 = dp->r1 * sin(dp->theta1);
    float y1 = dp->r1 * cos(dp->theta1);

    dp->p1 = Vector2Add(dp->pendulum_origin, (Vector2){x1, y1});

    // same calculations offset by p1
    float x2 = x1 + dp->r2 * sin(dp->theta2);
    float y2 = y1 + dp->r2 * cos(dp->theta2);

    dp->p2 = Vector2Add(dp->pendulum_origin, (Vector2){x2, y2});

    dp->a1_v += a1_a * *deltat;
    dp->a2_v += a2_a * *deltat;

    dp->theta1 += dp->a1_v;
    dp->theta2 += dp->a2_v;

    // friction
    dp->a1_v *= 0.999;
    dp->a2_v *= 0.999;
}


void dp_render(doublePendulum* dp) {

    DrawLineEx(dp->pendulum_origin, dp->p1, 5, WHITE);
    DrawCircleV(dp->p1, 5, RED);

    DrawLineEx(dp->p1, dp->p2, 5, BLUE);
    DrawCircleV(dp->p2, 5, RED);
}
