#pragma once

// get chain to draw snake on screen

#include "chain.h"
#include <raylib.h>

typedef struct {
    int SNAKE_BODY_LENGTH;
    float* SNAKE_BODY_ARRAY_RADIUSES;
    Chain* chain;

    Color border_color;
    Color body_color;
    float border_size;
} Snake;

// float* snake_create_sizes(int len, int starting_size); // to create snake_body_array
Snake snake_create(int snake_body_size, float* snake_body_array, Chain* chain);


void snake_render_body_border(Snake* snake);
void snake_render_body(Snake* snake);

// for when to create snake of bigger size
// float* create_snake_array();
// void destroy_snake_array(float* snake_array);


// static float* snake_body_vertices;
// 
// void create_snake_vertices_array();
// void destroy_snake_vertices_array();
// 
// // get points of border of body for rendering body
// void snake_calculate_body_vertices(Chain* chain); // seys snake_body:_vertices
// void snake_render(Vector2 points, Chain* chain);
