#pragma once

#include <stddef.h>
#include <raylib.h>


typedef struct {
    Vector2 position;
    size_t radius;
    Color color;

} Particle;


Particle particle_create(Vector2 position);

void particle_render(Particle* p);
