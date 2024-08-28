#include <raylib.h>
#include <stdio.h>

#include "chain.h"
#include "constants.h"
#include "snake.h"


int main(void) {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "procedural animation demo");

    SetTargetFPS(FPS);

    // SNAKE SHADERS
    Shader shader = LoadShader(0, "shaders/fragmentShader.glsl");
    RenderTexture shaderTarget = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT); // where shader will be rendered on

    int timeLoc = GetShaderLocation(shader, "time");
    float time = 0; // frames passed since beginning of animation
    SetShaderValue(shader, timeLoc, &time, SHADER_UNIFORM_FLOAT);


    int resolutionLoc = GetShaderLocation(shader, "resolution");
    float resolution[2] = { SCREEN_WIDTH, SCREEN_HEIGHT };
    SetShaderValue(shader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2);
    // 



    // TODO: use formula to generate a lot of more points
    float SNAKE_BODY_ARRAY_RADIUSES[] = {43, 48, 40, 38, 36, 33, 30, 27, 25, 23, 20, 17, 15, 12 };
    int SNAKE_BODY_SIZE = sizeof(SNAKE_BODY_ARRAY_RADIUSES) / sizeof(SNAKE_BODY_ARRAY_RADIUSES[0]);

    Chain chain = chain_create(SNAKE_BODY_SIZE, DISTANCE_CONSTRAINT, (Vector2){ 1, 0 }, (Vector2){200, 200}, SNAKE_BODY_ARRAY_RADIUSES);
    Snake snake = snake_create(SNAKE_BODY_SIZE, SNAKE_BODY_ARRAY_RADIUSES, &chain);



    while (!WindowShouldClose()) {
        // float time = GetTime();
        float dt = GetFrameTime();

        BeginDrawing();

            ClearBackground(BLACK);

            // chain_render_skeleton(snake.chain);

            BeginShaderMode(shader);
                snake_render(&snake);
            EndShaderMode();

            DrawFPS(SCREEN_WIDTH - 100, 20);


        EndDrawing();


        chain_change_direction(&chain, GetMousePosition());

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            chain_update(snake.chain, dt);
        }

        time += 1.0 / FPS; // updates by one full digit every second
        SetShaderValue(shader, timeLoc, &time, SHADER_UNIFORM_FLOAT);

    }

    // De-Initialization
    CloseWindow(); // close window and opengl

    return 0;
}


