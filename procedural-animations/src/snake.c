#include "snake.h"
#include "chain.h"
#include <stdlib.h>
#include <raylib.h>
#include <raymath.h>


// float snake_body_function(int x) {
//     return -pow((float)x/2-1, 2) + 1;
// } 
// 
// float* snake_create_sizes(int len, int starting_size) {
//     float* snake_body_array_radiuses = malloc(sizeof(float) * len);
// 
//     for (int i = 0; i < len; i++) {
//         float body_modifier = snake_body_function(i);
//         snake_body_array_radiuses[i] = fmin(starting_size + body_modifier, 0);
//         printf("%d-%f\n", i, snake_body_array_radiuses[i]);
//     }
//     
//     return snake_body_array_radiuses;
// }

Snake snake_create(int snake_body_size, float* snake_body_array, Chain* chain) {


    return (Snake) {
        .SNAKE_BODY_LENGTH = snake_body_size,
        .SNAKE_BODY_ARRAY_RADIUSES = snake_body_array,
        .chain = chain
    };

}


// from snake, points are in a anticlockwise fashion
void draw_polygon(int array_size, Vector2* vertex_array, Color body, Color border, int border_size) {
    for (int i = 0; i < (array_size - 2) / 2; i++) {
        DrawTriangle(vertex_array[array_size - 1 - i], vertex_array[1 + i], vertex_array[i], body);
        DrawTriangle(vertex_array[array_size - 1 - i], vertex_array[array_size - 2 - i], vertex_array[1 + i], body);

        // borders
        // TODO: make it ease
        DrawLineEx(vertex_array[i], vertex_array[i + 1], border_size, border);
        DrawLineEx(vertex_array[array_size - 1 - i], vertex_array[array_size - 2 - i], border_size, border);
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
    float border_size = 3;

    // two points of whole body_color
    Node* node;
    for (int i = 0; i < chain->chain_length; i++) {
        node = snake->chain->chain_head + i;

        if (i == 0) direction = chain->direction; // head already has direction
        else direction = Vector2Normalize(Vector2Subtract((node - 1)->position, node->position)); // direction looking at previous node in chain

        // two points on borders of screen
        Vector2 rotated_90_deg = Vector2Rotate(direction, PI / 2);
        Vector2 new_dir = Vector2Add(node->position, Vector2Scale(rotated_90_deg, node->radius));
        // DrawCircleV(new_dir, 5 + i, RED);
        vertices[i] = new_dir;

        rotated_90_deg = Vector2Rotate(direction, -PI / 2);
        new_dir = Vector2Add(node->position, Vector2Scale(rotated_90_deg, node->radius));
        // DrawCircleV(new_dir, 5 + i, GREEN);
        vertices[n_vertices - i - 1] = new_dir;
    }


    draw_polygon(n_vertices, vertices, body_color, border_color, border_size);
    free(vertices);

    // draw head
    // angle from x axis
    float head_angle = Vector2Angle(chain->direction, (Vector2){1, 0}) * RAD2DEG;
    DrawCircleSector(chain_head->position, chain_head->radius + border_size / 2, -head_angle-90, -head_angle+90, 100, border_color);
    DrawCircleSector(chain_head->position, chain_head->radius - border_size / 2, -head_angle-90, -head_angle+90, 100, body_color); // in degrees

    // draw tail
    float tail_angle = Vector2Angle(direction, (Vector2){1, 0}) * RAD2DEG;
    DrawCircleSector(node->position, node->radius + border_size / 2, -tail_angle+90, -tail_angle+270, 100, border_color);
    DrawCircleSector(node->position, node->radius - border_size / 2, -tail_angle+90, -tail_angle+270, 100, body_color);

}
