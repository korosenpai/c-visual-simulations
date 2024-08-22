#include "chain.h"
#include "constants.h"
#include "node.h"

#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>

Chain chain_create(int elements, int dist_constraint,Vector2 direction, Vector2 starting_pos) {
    Chain chain = (Chain){
        .dist_constraint = dist_constraint,
        .chain_length = elements,
        .chain_head = malloc(sizeof(Node) * elements),

        .direction = Vector2Normalize(direction),
        .velocity = 5,
        .max_angle = 90,

    };

    // fill chain
    for (int i = 0; i < elements; i++) {
        chain.chain_head[i] = node_create(starting_pos);

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

void chain_render(Chain *chain) {
    // line looking where chain is headed to
    DrawLine(
        chain->chain_head->position.x + chain->dist_constraint * chain->direction.x,
        chain->chain_head->position.y + chain->dist_constraint * chain->direction.y,
        chain->chain_head->position.x,
        chain->chain_head->position.y,
        RED 
    );

    for (int i = 0; i < chain->chain_length; i++) {
        node_render(chain->chain_head + i);
    }
}

void chain_change_direction(Chain* chain, Vector2 target_position) {
    // // TODO: max angle
    // https://www.cuemath.com/geometry/angle-between-vectors/
    //
    // float angle = Vector2Angle(target_position, chain->direction);
    // if (angle > chain->max_angle) angle = chain->max_angle;
    // if (angle < -chain->max_angle) angle = -chain->max_angle;


    // point to mouse position
    Vector2 direction = Vector2Subtract(target_position, chain->chain_head->position);
    if (Vector2Length(direction) > chain->dist_constraint)
        chain->direction = Vector2Normalize(direction);
    else {
        chain->direction = (Vector2){0};
    };
}

void chain_update(Chain* chain) {
    // move head
    chain->chain_head->position = Vector2Add(
        chain->chain_head->position,
        Vector2Scale(chain->direction, chain->velocity)
    );

    // move rest of body
    for (int i = 1; i < chain->chain_length; i++) {
        // direction of node looking at previous node
        Vector2 direction = Vector2Subtract(
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
