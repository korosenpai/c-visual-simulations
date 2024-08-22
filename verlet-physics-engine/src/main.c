#include <raylib.h>

#include "obj_spawner.h"
#include "solver.h"
#include "constants.h"


int main(void) {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "verlet engine");

    SetTargetFPS(FPS);

    Solver solver = solver_create();
    VOSpawner spawner = spawner_create(
        (Vector2) {200, 300},
        (Vector2){90000, 0},
        true,
        0.1
    );


    while (!WindowShouldClose()) {
        float time = GetTime();
        float deltaTime = GetFrameTime();

        solver_update(&solver, deltaTime);
        spawner_update(&spawner, &solver, time);

        BeginDrawing();

            ClearBackground(BLACK);

            // draw constraint
            DrawCircleV(CONSTRAINT_POSITION, CONSTRAINT_RADIUS, CONSTRAINT_COLOR);

            solver_render(&solver);

            DrawFPS(SCREEN_WIDTH - 100, 20);


        EndDrawing();

        // if (IsKeyPressed(KEY_SPACE)) solver_add_object(&solver);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            solver_add_object(&solver, GetMousePosition(), (Vector2){0});
        }
    }

    // De-Initialization
    solver_destroy(&solver);
    CloseWindow(); // close window and opengl

    return 0;
}


