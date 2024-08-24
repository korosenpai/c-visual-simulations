#include <raylib.h>

#include "chain.h"
#include "constants.h"
#include "snake.h"


int main(void) {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "procedural animation demo");

    SetTargetFPS(FPS);

    int SNAKE_BODY_SIZE = 14;
    float SNAKE_BODY_ARRAY_RADIUSES[] = {43, 48, 40, 38, 36, 33, 30, 27, 25, 23, 20, 17, 15, 12 };

    Chain chain = chain_create(SNAKE_BODY_SIZE, DISTANCE_CONSTRAINT, (Vector2){ 1, 0 }, (Vector2){200, 200}, SNAKE_BODY_ARRAY_RADIUSES);
    Snake snake = snake_create(SNAKE_BODY_SIZE, SNAKE_BODY_ARRAY_RADIUSES, &chain);



    while (!WindowShouldClose()) {
        // float time = GetTime();
        float dt = GetFrameTime();

        BeginDrawing();

            ClearBackground(BLACK);

            // chain_render_skeleton(snake.chain);
            snake_render(&snake);

            DrawFPS(SCREEN_WIDTH - 100, 20);


        EndDrawing();


        chain_change_direction(&chain, GetMousePosition());

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            chain_update(snake.chain, dt);
        }

    }

    // De-Initialization
    CloseWindow(); // close window and opengl

    return 0;
}


