#pragma once

#include "verlet_object.h"
#include <raylib.h>

// put this together to create a chain
typedef struct {
    VerletObject* obj1;
    VerletObject* obj2;
    float target_dist;
} Link;

Link* chain_create(Vector2 start, Vector2 end, float target_dist);

void apply_link(Link* link);
