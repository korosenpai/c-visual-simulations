#include "constants.h"
#include "particles/particle_manager.h"
#include <raylib.h>

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
    SetTargetFPS(120);

    manager_init();


    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        BeginDrawing();

            ClearBackground(RAYWHITE);

            manager_render();
        EndDrawing();
    }

    manager_close();
    CloseWindow();

    return 0;
}
