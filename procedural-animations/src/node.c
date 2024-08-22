#include "node.h"
#include "constants.h"
#include <raylib.h>

Node node_create(Vector2 position) {
    return (Node) {
        .position = position,
        .radius = DISTANCE_CONSTRAINT, // TODO: use array to decide body size
    };
}

void node_render(Node* node) {
    // small circle on point
    DrawCircleV(node->position, node->radius * 0.1, WHITE);

    // arc to show circumference
    DrawCircleLinesV(node->position, node->radius, WHITE);
}
