#include "solver.h"
#include "constants.h"
#include "verlet_object.h"


#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>

Solver solver_create() {
    return (Solver) {
        .vobjects_number = 0,
        .vobjects = malloc(sizeof(VerletObject) * VO_MAX_OBJ_NUMBER)
    };
}

void solver_add_object(Solver *solver, Vector2 position, Vector2 acceleration) {
    // TODO: make if loop around
    if (solver->vobjects_number > VO_MAX_OBJ_NUMBER - 1) {
        printf("max objects number reached\n");
        return;
    }

    // add new solver in last place of array for now populated
    solver->vobjects[solver->vobjects_number] = vobject_create(
        solver->vobjects_number,
        position,
        acceleration
    );
    solver->vobjects_number++;
}

void solver_destroy(Solver* solver) {
    free(solver->vobjects);
}

// on every object
void solver_apply_gravity(Solver* solver) {
    for (int i = 0; i < solver->vobjects_number; i++) {
        vobject_accelerate(solver->vobjects + i, VO_GRAVITY);
    }
};

void solver_update_positions(Solver* solver, float dt) {
    for (int i = 0; i < solver->vobjects_number; i++) {
        vobject_update_position(solver->vobjects + i, dt);
    }
}

void solver_apply_constraints(Solver* solver) {

    for (int i = 0; i < solver->vobjects_number; i++) {
        VerletObject* obj = solver->vobjects + i;
        Vector2 to_obj = Vector2Subtract(obj->position_current, CONSTRAINT_POSITION); // vector from obj to center
        float dist = Vector2Length(to_obj); // distance of obj from center

        if (dist > CONSTRAINT_RADIUS - obj->size) {
            // normalized vector of distance from center to obj
            Vector2 n = to_obj;
            n.x /= dist;
            n.y /= dist;
            // reput in circle with same vector of distance (just inside the constraint) (gives effect of sliding)
            // xn+1 = center + n * (radius - obj size)
            obj->position_current = Vector2Add(
                CONSTRAINT_POSITION,
                Vector2Scale(n, (CONSTRAINT_RADIUS - obj->size))
            );
        }
    }

}

void solver_solve_collisions(Solver* solver) {
    // brute force On^2 algo
    for (int i = 0; i < solver->vobjects_number; i++) {
        VerletObject* obj1 = solver->vobjects + i;

        for (int j = i + 1; j < solver->vobjects_number; j++) {
            VerletObject* obj2 = solver->vobjects + j;

            Vector2 collision_axis = Vector2Subtract(obj1->position_current, obj2->position_current);
            float dist = Vector2Length(collision_axis);
            if (dist < obj1->size + obj2->size) {
                // objs are colliding (overlapping)
                // move them along collision axis so they dont overlap anymore
                Vector2 n = collision_axis; // normalize vector of collision axis
                n.x /= dist;
                n.y /= dist;
                float delta = obj1->size + obj2->size - dist;
                obj1->position_current = Vector2Add(obj1->position_current, Vector2Scale(n, 0.5f * delta));
                obj2->position_current = Vector2Subtract(obj2->position_current, Vector2Scale(n, 0.5f * delta));

            }
        }

    }
}

void solver_update(Solver* solver, float dt) {
    // calculate more than once a frame to have results more precise
    int sub_steps = 8;
    float sub_dt = dt / (float)sub_steps; // time for each step

    for (int i = 0; i < sub_steps; i++) {
        solver_apply_gravity(solver);
        solver_update_positions(solver, sub_dt);
        solver_solve_collisions(solver);
        solver_apply_constraints(solver);
    }

}

void solver_render(Solver* solver) {
    for (int i = 0; i < solver->vobjects_number; i++) {
        vobject_render(solver->vobjects + i);
    }
}
