#include "link.h"
#include <raylib.h>
#include <raymath.h>


void apply_link(Link* link) {
    Vector2 axis = Vector2Subtract(link->obj1->position_current, link->obj2->position_current);
    float dist = Vector2Length(axis);

    // normalize axis vector
    Vector2 n = axis;
    n.x /= dist;
    n.y /= dist;

    float delta = link->target_dist - dist;
    link->obj1->position_current = Vector2Add(
        link->obj1->position_current,
        Vector2Scale(n, 0.5 * delta)
    );
    link->obj2->position_current = Vector2Add(
        link->obj2->position_current,
        Vector2Scale(n, 0.5 * delta)
    );
}
