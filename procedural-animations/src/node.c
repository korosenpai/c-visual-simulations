#include "node.h"
#include "constants.h"
#include <raylib.h>
#include <raymath.h>

Node node_create(Vector2 position, float radius) {
    return (Node) {
        .position = position,
        .radius = radius,
    };
}

void node_render_skeleton(Node* node) {
    // small circle on point
    DrawCircleV(node->position, node->radius * 0.1, WHITE);

    // arc to show circumference
    DrawCircleLinesV(node->position, node->radius, WHITE);

}

