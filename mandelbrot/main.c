#include "raylib.h"

int main(void) {

    const int SCREEN_WIDTH = 1100;
    const int SCREEN_HEIGHT = 900;

    const float DEFAULT_LOCATION[2] = { -0.85, 0 };
    const float DEFAULT_ZOOM = 1.7;
    const int DEFAULT_COLORSCHEME = 1;
    const int DEFAULT_MAX_ITER = 100;

    const int N_COLOR_SCHEMES = 2;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "mandelbrot explorer");
    SetTargetFPS(60);

    // prepare shader
    Shader shader = LoadShader(0, "mandelbrot.glsl");
    RenderTexture target = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT); // where shader will be rendered on
    int resolutionLoc = GetShaderLocation(shader, "resolution");
    int locationLoc = GetShaderLocation(shader, "location");
    int zoomLoc = GetShaderLocation(shader, "zoom");
    int maxIterLoc = GetShaderLocation(shader, "maxIter");
    int colorizedLoc = GetShaderLocation(shader, "colorScheme");


    float resolution[2] = { SCREEN_WIDTH, SCREEN_HEIGHT };
    float location[2] = { DEFAULT_LOCATION[0], DEFAULT_LOCATION[1] };
    float zoom = DEFAULT_ZOOM;
    int maxIter = DEFAULT_MAX_ITER;
    int colorScheme = DEFAULT_COLORSCHEME;


    SetShaderValue(shader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2);
    SetShaderValue(shader, locationLoc, &location, SHADER_UNIFORM_VEC2);
    SetShaderValue(shader, zoomLoc, &zoom, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, maxIterLoc, &maxIter, SHADER_UNIFORM_INT);
    SetShaderValue(shader, colorizedLoc, &colorScheme, SHADER_UNIFORM_INT);



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

            // DrawFPS(SCREEN_WIDTH - 100, 20);

        EndDrawing();

        // modify uniforms
        if(IsKeyDown(KEY_W)) location[1] += 1.0 / zoom * 0.05f;
        if(IsKeyDown(KEY_S)) location[1] -= 1.0 / zoom * 0.05f;
        if(IsKeyDown(KEY_D)) location[0] += 1.0 / zoom * 0.05f;
        if(IsKeyDown(KEY_A)) location[0] -= 1.0 / zoom * 0.05f;

        if (IsKeyDown(KEY_UP)) zoom += zoom * 0.01f;
        if (IsKeyDown(KEY_DOWN)) zoom -= zoom * 0.01f;

        if (IsKeyPressed(KEY_LEFT)) colorScheme = (colorScheme + 1) % N_COLOR_SCHEMES;

        // absolutely beautiful effect
        if (IsKeyDown(KEY_J)) maxIter = maxIter - 1 > 0 ? maxIter - 1: maxIter;
        if (IsKeyDown(KEY_K)) maxIter++;

        if (IsKeyPressed(KEY_ENTER)) { // reset
            location[0] = DEFAULT_LOCATION[0];
            location[1] = DEFAULT_LOCATION[1];
            zoom = DEFAULT_ZOOM;
            colorScheme = DEFAULT_COLORSCHEME;
            maxIter = DEFAULT_MAX_ITER;
        }

        // update uniforms
        SetShaderValue(shader, zoomLoc, &zoom, SHADER_UNIFORM_FLOAT);
        SetShaderValue(shader, locationLoc, &location, SHADER_UNIFORM_VEC2);
        SetShaderValue(shader, maxIterLoc, &maxIter, SHADER_UNIFORM_INT);
        SetShaderValue(shader, colorizedLoc, &colorScheme, SHADER_UNIFORM_INT);
    }

    UnloadShader(shader);
    CloseWindow();

    return 0;
}
