#include "particle_manager.h"
#include "particle.h"
#include "../constants.h"

#include <raylib.h>
#include <stdlib.h>


static ParticleCluster _particles;

void manager_init() {
    _particles = (ParticleCluster){
        .particles_active = 0,
        .arr_size = PARTICLE_PREALLOC_N,
        .arr = malloc(sizeof(Particle) * PARTICLE_PREALLOC_N),
    };


    // fill particles array
    for (int i = 0; i < _particles.arr_size; i++) {
        _particles.arr[i] = particle_create(
            (Vector2) {
                GetRandomValue(0, SCREEN_WIDTH),
                GetRandomValue(0, SCREEN_HEIGHT)
            }
        );

    }
    _particles.particles_active = _particles.arr_size;
}




void manager_render() {
    for (int i = 0; i < _particles.arr_size; i++) {
        particle_render(_particles.arr + i);
    }
    
}

void manager_close() {

}
