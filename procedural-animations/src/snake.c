#include "snake.h"
#include "chain.h"
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <raymath.h>

// max number of vertices to draw on singular node
const int snake_vertices_per_node = 8;

Snake snake_create(int snake_body_size, float* snake_body_array, Chain* chain) {


    return (Snake) {
        .SNAKE_BODY_LENGTH = snake_body_size,
        .SNAKE_BODY_ARRAY_RADIUSES = snake_body_array,
        .chain = chain
    };

}


// from snake, points are in a anticlockwise fashion
void draw_polygon(int array_size, Vector2* vertex_array, Color body, Color border) {
    for (int i = 0; i < (array_size - 2) / 2; i++) {
        DrawTriangle(vertex_array[array_size - 1 - i], vertex_array[1 + i], vertex_array[i], body);
        DrawTriangle(vertex_array[array_size - 1 - i], vertex_array[array_size - 2 - i], vertex_array[1 + i], body);

        // borders
        // TODO: make it ease
        DrawLineEx(vertex_array[i], vertex_array[i + 1], 5, border);
        DrawLineEx(vertex_array[array_size - 1 - i], vertex_array[array_size - 2 - i], 5, border);
    }
}


void snake_render(Snake* snake) {
    // draw vertices

    Chain* chain = snake->chain;
    Node* chain_head= snake->chain->chain_head;

    Vector2 direction;
    int n_vertices = chain->chain_length * 2;
    Vector2* vertices = malloc(sizeof(Vector2) * n_vertices);

    Color border_color = WHITE;
    Color body_color = BLUE;

    // two points of whole body_color
    Node* node;
    for (int i = 0; i < chain->chain_length; i++) {
        node = snake->chain->chain_head + i;

        if (i == 0) direction = chain->direction; // head already has direction
        else direction = Vector2Normalize(Vector2Subtract((node - 1)->position, node->position)); // direction looking at previous node in chain

        // two points on borders of screen
        Vector2 rotated_90_deg = Vector2Rotate(direction, PI / 2);
        Vector2 new_dir = Vector2Add(node->position, Vector2Scale(rotated_90_deg, node->radius));
        // DrawCircleV(new_dir, 5, RED);
        vertices[i] = new_dir;

        rotated_90_deg = Vector2Rotate(direction, -PI / 2);
        new_dir = Vector2Add(node->position, Vector2Scale(rotated_90_deg, node->radius));
        // DrawCircleV(new_dir, 5, GREEN);
        vertices[n_vertices - i - 1] = new_dir;
    }

    // tail
    DrawCircleV(node->position, node->radius + 5, border_color);
    DrawCircleV(node->position, node->radius, body_color);

    // draw head
    DrawCircleV(chain_head->position, chain_head->radius + 5, border_color);
    DrawCircleV(chain_head->position, chain_head->radius, body_color);

    draw_polygon(n_vertices, vertices, body_color, border_color);
}