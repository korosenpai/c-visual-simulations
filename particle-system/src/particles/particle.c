#include "particle.h"

#include <raylib.h>
#include <time.h>
#include <stdlib.h>

size_t get_random_size(int min, int max) {
    srand(time(NULL));
    return (size_t)(min + rand() % (max + 1 - min));

}

Particle particle_create(Vector2 position) {
    return (Particle) {
        .position = position,
        .radius = get_random_size(1, 2),
        .color = BLACK,

    };

}


void particle_render(Particle* p) {
    DrawCircleV(p->position, p->radius, p->color);
}
