#include "chain.h"
#include "node.h"

#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>

Chain chain_create(const int elements, int dist_constraint,Vector2 direction, Vector2 starting_pos, const float* radiuses) {
    Chain chain = (Chain){
        .dist_constraint = dist_constraint,
        .chain_length = elements,
        .chain_head = malloc(sizeof(Node) * elements),

        .direction = Vector2Normalize(direction),
        .velocity = 200,
        .max_angle = 40,

    };

    // fill chain
    for (int i = 0; i < elements; i++) {
        chain.chain_head[i] = node_create(starting_pos, radiuses[i]);

        // offset elements on opposite direction of vector direction
        starting_pos.x += dist_constraint * -direction.x;
    }

    return chain;
}

void chain_destroy(Chain* chain) {
    free(chain->chain_head);
}

void chain_print_debug(Chain* chain) {
    printf("CHAIN:\n");
    for (int i = 0; i < chain->chain_length; i++) {
        printf("%d: %f, %f\n", i, chain->chain_head[i].position.x, chain->chain_head[i].position.y);
    }
}

void chain_render_skeleton(Chain *chain) {
    // line looking where chain is headed to
    DrawLine(
        chain->chain_head->position.x + chain->chain_head->radius * chain->direction.x,
        chain->chain_head->position.y + chain->chain_head->radius * chain->direction.y,
        chain->chain_head->position.x,
        chain->chain_head->position.y,
        RED 
    );

    for (int i = 0; i < chain->chain_length; i++) {
        node_render_skeleton(chain->chain_head + i);
    }
}

// if some angles in the chain are too big or small, make them go in the middle
void chain_untangle(Chain* chain) {

}

void chain_change_direction(Chain* chain, Vector2 target_position) {
    // change angle instantlty(no smoothing)
    // point to mouse position
    Vector2 direction = Vector2Subtract(target_position, chain->chain_head->position);

    // update direction when current_dir is not 0
    if (Vector2Length(direction) > chain->dist_constraint) {
        chain->direction = chain->current_direction;
    }
    // if too close to mouse do not move
    else {
        // NOTE: when stopping, angles with direction give 0
        chain->current_direction = (Vector2){0};
        return;
    }

    chain->current_direction = Vector2Normalize(direction);

    // TODO:
    // // smoothing with max angle to turn
    // Vector2 direction = Vector2Subtract(target_position, chain->chain_head->position);
    // float angle = Vector2Angle(direction, chain->direction) * RAD2DEG;

    // if (fabsf(angle) < 10) return;
    // // if (angle > chain->max_angle) angle = chain->max_angle;
    // // if (angle < -chain->max_angle) angle = -chain->max_angle;
    // printf("%f\n", angle);
    // 
    // chain->direction = Vector2Rotate(chain->direction, angle * DEG2RAD);
    // chain->direction = Vector2Normalize(chain->direction);

}

void chain_update(Chain* chain, float dt) {

    chain_untangle(chain);

    Vector2 direction = chain->current_direction;

    // move head
    chain->chain_head->position = Vector2Add(
        chain->chain_head->position,
        Vector2Scale(direction, chain->velocity * dt)
    );

    // move rest of body to keep up with part of body before
    for (int i = 1; i < chain->chain_length; i++) {
        // direction of node looking at previous node
        direction = Vector2Subtract(
            (chain->chain_head + i - 1)->position, // position of precedent elem
            (chain->chain_head + i)->position
        );

        // get vector to reach length of "direction - dist_constraint"
        float len = Vector2Length(direction);
        float required_len = len - chain->dist_constraint;
        float scale_factor = required_len / len;
        direction = Vector2Scale(direction, scale_factor);

        (chain->chain_head + i)->position = Vector2Add((chain->chain_head + i)->position, direction);
    }
}
