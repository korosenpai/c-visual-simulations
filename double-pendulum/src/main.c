#include <raylib.h>
#include <math.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "double_pendulum/dp.h"


int main(void) {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] example - basic window");

    SetTargetFPS(60);

    ////////////////////// SETUP //////////////////////

    int dps_count = 10;
    doublePendulum* dps = malloc(sizeof(*dps) * dps_count);


    for (float i = 0; i < dps_count; i++) {
        dps[(int)i] = dp_create(
            SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 200, 200, 20, 20, PI * 0.99 + i / 10000, PI * 0.99
        );
    }

    ////////////////////// START //////////////////////
    while (!WindowShouldClose()) {
        float deltat = GetFrameTime();

        ////////////////////// CALC NEW VALUES //////////////////////
        for (int i = 0; i < dps_count; i++) {
            dp_update(dps + i, &deltat);
        }

        ////////////////////// DRAW //////////////////////
        BeginDrawing();

            ClearBackground(BLACK);


            for (int i = 0; i < dps_count; i++) {
                dp_render(dps + i);
            }

            DrawFPS(SCREEN_WIDTH- 100, 20);


        EndDrawing();


    }

    CloseWindow();
    free(dps);

    return 0;
}
