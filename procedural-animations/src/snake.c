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
        .chain = chain,

        .border_color = WHITE,
        .body_color = BLUE,
        .border_size = 3,
    };

}


void draw_lines(int array_size, Vector2* vertex_array, Color col, int border_size) {
    for (int i = 0; i < (array_size - 2) / 2; i++) {

        // TODO: make it ease
        DrawLineEx(vertex_array[i], vertex_array[i + 1], border_size, col);
        DrawLineEx(vertex_array[array_size - 1 - i], vertex_array[array_size - 2 - i], border_size, col);
    }
}


// from snake, points are in a anticlockwise fashion
void draw_polygon(int array_size, Vector2* vertex_array, Color col) {
    for (int i = 0; i < (array_size - 2) / 2; i++) {
        DrawTriangle(vertex_array[array_size - 1 - i], vertex_array[1 + i], vertex_array[i], col);
        DrawTriangle(vertex_array[array_size - 1 - i], vertex_array[array_size - 2 - i], vertex_array[1 + i], col);
    }
}
void DrawArc(Vector2 center, float radius, int startAngle, int endAngle, Color color, float thickness) {
    #define SEGMENTS 32
    
    // Ensure start angle is less than end angle
    if (startAngle > endAngle) {
        startAngle -= endAngle;
        endAngle += startAngle;
        startAngle = -startAngle;
    }
    
    // Calculate step size
    float stepSize = (endAngle - startAngle) / (float)(SEGMENTS);
    
    // Create array to store points
    Vector2 points[SEGMENTS + 1];
    
    // Calculate points
    for (int i = 0; i <= SEGMENTS; i++) {
        float angle = startAngle + i * stepSize;
        float x = center.x + cosf(angle * DEG2RAD) * radius;
        float y = center.y + sinf(angle * DEG2RAD) * radius;
        points[i] = (Vector2){x, y};
    }
    
    for (int i = 0; i < SEGMENTS - 1; i++) {
        DrawLineEx(points[i], points[i + 1], thickness, color);
        // DrawLineEx(points[i].x, points[i].y, points[(i+1)%SEGMENTS].x, points[(i+1)%SEGMENTS].y, color);
    }
}
void snake_render_body_border(Snake* snake) {

    Chain* chain = snake->chain;
    Node* chain_head= snake->chain->chain_head;

    Color border_color = snake->border_color;
    float border_size = snake->border_size;

    draw_lines(chain->n_border_vertices, chain->border_vertices, border_color, border_size);

    // draw head
    // angle from x axis
    float head_angle = Vector2Angle(chain->direction, (Vector2){1, 0}) * RAD2DEG;
    // DrawCircleSector(chain_head->position, chain_head->radius + border_size / 2, -head_angle-90, -head_angle+90, 100, border_color);
    DrawArc(chain_head->position, chain_head->radius, -head_angle-90, -head_angle+90 + 7, border_color, border_size); // + 7 to give some offset if too stretched

    // draw tail
    Node* chain_tail = chain_head + chain->chain_length - 1;
    Vector2 direction = chain_get_direction(chain, chain->chain_length - 1);
    float tail_angle = Vector2Angle(direction, (Vector2){1, 0}) * RAD2DEG;
    // DrawCircleSector(chain_tail->position, chain_tail->radius + border_size / 2, -tail_angle+90, -tail_angle+270, 100, border_color);
    DrawArc(chain_tail->position, chain_tail->radius, -tail_angle+90, -tail_angle+270 + 7, border_color, border_size);



}

void snake_render_body(Snake* snake) {
    // draw vertices

    Chain* chain = snake->chain;
    Node* chain_head= snake->chain->chain_head;
    Node* chain_tail = chain_head + chain->chain_length - 1;

    Color body_color = snake->body_color;
    float border_size = snake->border_size;

    draw_polygon(snake->chain->n_border_vertices, snake->chain->border_vertices, body_color);

    // draw head
    // angle from x axis
    float head_angle = Vector2Angle(chain->direction, (Vector2){1, 0}) * RAD2DEG;
    DrawCircleSector(chain_head->position, chain_head->radius - border_size / 2, -head_angle-90, -head_angle+90, 100, body_color); // in degrees

    // draw tail
    Vector2 direction = chain_get_direction(chain, chain->chain_length - 1);
    float tail_angle = Vector2Angle(direction, (Vector2){1, 0}) * RAD2DEG;
    DrawCircleSector(chain_tail->position, chain_tail->radius - border_size / 2, -tail_angle+90, -tail_angle+270, 100, body_color);

}
