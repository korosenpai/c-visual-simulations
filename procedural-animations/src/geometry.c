#include "geometry.h"

void draw_lines(int array_size, Vector2* vertex_array, Color col, int border_size) {
    for (int i = 0; i < (array_size - 2) / 2; i++) {

        // TODO: make it ease
        DrawLineEx(vertex_array[i], vertex_array[i + 1], border_size, col);
        DrawLineEx(vertex_array[array_size - 1 - i], vertex_array[array_size - 2 - i], border_size, col);
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

// from snake, points are in a anticlockwise fashion
void draw_polygon(int array_size, Vector2* vertex_array, Color col) {
    for (int i = 0; i < (array_size - 2) / 2; i++) {
        DrawTriangle(vertex_array[array_size - 1 - i], vertex_array[1 + i], vertex_array[i], col);
        DrawTriangle(vertex_array[array_size - 1 - i], vertex_array[array_size - 2 - i], vertex_array[1 + i], col);
    }
}
