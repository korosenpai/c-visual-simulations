#pragma once

#include <raylib.h>
#include "constants.h"
#include "verlet_object.h"


// solver is the one in charge to manage the particles
typedef struct {
    int vobjects_number;
    VerletObject* vobjects;

} Solver;

Solver solver_create();
void solver_add_object(Solver *solver, Vector2 position, Vector2 acceleration);
void solver_destroy(Solver* solver);

void solver_update(Solver* solver, float dt);
void solver_render(Solver* solver);
