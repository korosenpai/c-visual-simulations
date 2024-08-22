#pragma once

#include <raylib.h>
#include <raymath.h>

typedef struct {
    Vector2 position;
    float radius; // only used for drawing
} Node;

Node node_create(Vector2 position);

void node_render(Node* node);