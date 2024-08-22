#include "obj_spawner.h"
#include "solver.h"
#include <raylib.h>
#include <raymath.h>
#include <math.h>


VOSpawner spawner_create(Vector2 position, Vector2 direction, bool oscillating, float delay) {
    return (VOSpawner){
        .position = position,
        .direction = direction,
        .angle = 0,
        .oscillating = oscillating,
        .delay = delay,
    };
}

void spawner_update(VOSpawner* spawner, Solver* solver, float time) {
    if (time < spawner->last_shot + spawner->delay) return;

    if (spawner->oscillating) {
        spawner->direction = Vector2Rotate(spawner->direction, -sin(spawner->angle) / 2);
        spawner->angle++;
    }

    spawner->last_shot = time;
    solver_add_object(solver, spawner->position, spawner->direction);
}
