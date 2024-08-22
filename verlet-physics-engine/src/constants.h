#pragma once

// NOTE: use make clean after updating these to be sure everything gets updated

#define FPS  60

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 900


// verlet objects
#define VO_MAX_OBJ_NUMBER 256
#define VO_GRAVITY CLITERAL(Vector2){0.0f, 1000.0f}

// circular constraint
#define CONSTRAINT_POSITION CLITERAL(Vector2){(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2}
#define CONSTRAINT_RADIUS 400.0f
#define CONSTRAINT_COLOR CLITERAL(Color){30, 30, 30, 255}
