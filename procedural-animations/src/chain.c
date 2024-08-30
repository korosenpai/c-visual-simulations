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

        .n_border_vertices = elements * 2,
        .border_vertices = malloc(sizeof(Vector2) * elements * 2),

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
    free(chain->border_vertices);
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

// NOTE: assumes n_border_vertices = chain length * 2
void chain_update_border_vertices(Chain* chain) {

    Vector2 direction;

    // two points of whole body_color
    Node* node;
    for (int i = 0; i < chain->chain_length; i++) {
        node = chain->chain_head + i;

        if (i == 0) direction = chain->direction; // head already has direction
        else direction = Vector2Normalize(Vector2Subtract((node - 1)->position, node->position)); // direction looking at previous node in chain

        // two points on borders of screen
        Vector2 rotated_90_deg = Vector2Rotate(direction, PI / 2);
        Vector2 new_dir = Vector2Add(node->position, Vector2Scale(rotated_90_deg, node->radius));
        // DrawCircleV(new_dir, 5 + i, RED);
        chain->border_vertices[i] = new_dir;

        rotated_90_deg = Vector2Rotate(direction, -PI / 2);
        new_dir = Vector2Add(node->position, Vector2Scale(rotated_90_deg, node->radius));
        // DrawCircleV(new_dir, 5 + i, GREEN);
        chain->border_vertices[chain->n_border_vertices- i - 1] = new_dir;
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

Vector2 chain_get_direction(Chain* chain, int node_pos) {
    Node* node = chain->chain_head + node_pos;
    return Vector2Normalize(Vector2Subtract((node - 1)->position, node->position)); // direction looking at previous node in chain
}
