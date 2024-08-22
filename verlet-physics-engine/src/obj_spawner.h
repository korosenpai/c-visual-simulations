#pragma once

#include "solver.h"
#include <raylib.h>
#include <time.h>

typedef struct {
    Vector2 position;

    Vector2 direction; // of shooting
    float angle;
    bool oscillating;

    float last_shot; // time since last shot
    float delay; // between each ball shot

} VOSpawner;

VOSpawner spawner_create(Vector2 position, Vector2 direction, bool oscillating, float delay);

void spawner_update(VOSpawner* spawner, Solver* solver, float time);
