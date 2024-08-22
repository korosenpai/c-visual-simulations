#include <raylib.h>

#include "chain.h"
#include "constants.h"


int main(void) {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "procedural animation demo");

    SetTargetFPS(FPS);

    Chain chain = chain_create(20, DISTANCE_CONSTRAINT, (Vector2){ 1, 0 }, (Vector2){200, 200});
    chain_print_debug(&chain);


    while (!WindowShouldClose()) {
        float time = GetTime();
        float deltaTime = GetFrameTime();

        BeginDrawing();

            ClearBackground(BLACK);

            chain_render(&chain);



            DrawFPS(SCREEN_WIDTH - 100, 20);


        EndDrawing();

        // only if furthjer away than velocity
        chain_change_direction(&chain, GetMousePosition());
        chain_update(&chain);

    }

    // De-Initialization
    CloseWindow(); // close window and opengl

    return 0;
}


