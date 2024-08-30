#pragma once

#include <raylib.h>

#include "node.h"


typedef struct {
    float dist_constraint; // dist to maintain between elems

    int chain_length; // how many elements in chain
    Node* chain_head; // array of nodes

    // directions must be normalized
    Vector2 current_direction; // used only when moving
    Vector2 direction; // when current_dir = 0 to maintain it to a value != 0 for the animations to keep working
    float velocity;
    float max_angle; // max angle it can turn at once

    // points to render body
    int n_border_vertices;
    Vector2* border_vertices;

} Chain;

// returns head of chain
Chain chain_create(const int elements, int dist_constraint,Vector2 direction, Vector2 starting_pos, const float* radiuses);
void chain_destroy(Chain* chain);

void chain_print_debug(Chain* chain);

void chain_render_skeleton(Chain* chain);

void chain_update_border_vertices(Chain* chain);
void chain_change_direction(Chain* chain, Vector2 target_direction);
void chain_update(Chain* chain, float dt);

// get direction node in nth position (0 indexed) of chain is facing
Vector2 chain_get_direction(Chain* chain, int node_pos);
