#include "raylib.h"

int main(void)
{
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 450;

    const int MAX_ITER = 256;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "default window with shaders");
    SetTargetFPS(60);

    // prepare shader
    Shader shader = LoadShader(0, "fragmentShader.glsl");
    RenderTexture target = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
    int resolutionLoc = GetShaderLocation(shader, "resolution");
    // int locationLoc = GetShaderLocation(shader, "location");
    int maxIterLoc = GetShaderLocation(shader, "maxIter");


    float resolution[2] = { SCREEN_WIDTH, SCREEN_HEIGHT };

    SetShaderValue(shader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2);
    SetShaderValue(shader, maxIterLoc, &MAX_ITER, SHADER_UNIFORM_INT);



    // Main game loop
    while (!WindowShouldClose()) { // esc to exit

        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginTextureMode(target);
                DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK);
            EndTextureMode();
            BeginShaderMode(shader);
                DrawTexture(target.texture, 0, 0, WHITE);
            EndShaderMode();

        EndDrawing();
    }

    UnloadShader(shader);
    CloseWindow();

    return 0;
}
