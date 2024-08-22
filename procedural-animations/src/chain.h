#pragma once

#include <raylib.h>

#include "node.h"


typedef struct {
    float dist_constraint; // dist to maintain between elems
    int chain_length; // how many elements in chain
    Node* chain_head; // array of nodes

    Vector2 direction; // must be a normalized vector
    float velocity;
    float max_angle; // max angle it can turn at once

} Chain;

// returns head of chain
Chain chain_create(int elements, int dist_constraint,Vector2 direction, Vector2 starting_pos);
void chain_destroy(Chain* chain);

void chain_print_debug(Chain* chain);

void chain_render(Chain* chain);

void chain_change_direction(Chain* chain, Vector2 target_direction);
void chain_update(Chain* chain);
