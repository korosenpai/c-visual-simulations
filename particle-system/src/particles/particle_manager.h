#pragma once

#include "particle.h"
#include <stddef.h>


#define PARTICLE_PREALLOC_N 1000


typedef struct {
    size_t particles_active;
    size_t arr_size;
    Particle* arr;

} ParticleCluster;



void manager_init();

void manager_render();

void manager_close();
