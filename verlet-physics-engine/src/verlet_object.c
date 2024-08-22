#include "verlet_object.h"
#include <raylib.h>
#include <raymath.h>

VerletObject vobject_create(int id, Vector2 position_current, Vector2 acceleration) {
    return (VerletObject) {
        .id = id,
        .size = GetRandomValue(5, 30),
        .color = (Color){GetRandomValue(50, 255),GetRandomValue(50, 255),GetRandomValue(50, 255), 255},

        .position_current = position_current,
        .position_old = position_current,
        .acceleration = acceleration,
    };
}

void vobject_update_position(VerletObject* obj, float dt) {
    Vector2 velocity = Vector2Subtract(obj->position_current, obj->position_old);

    obj->position_old = obj->position_current; // save current position

    // verlet integration -> xn+1 = xn + velocity + acceleration * dt ^ 2
    obj->position_current = Vector2Add(obj->position_current, velocity);
    obj->position_current = Vector2Add(obj->position_current, Vector2Scale(obj->acceleration, dt * dt));

    // reset acceleration
    // obj->acceleration = (Vector2){0};
    obj->acceleration = Vector2Scale(obj->acceleration, 0.7); // air friction

}

void vobject_accelerate(VerletObject* obj, Vector2 acc) {
    obj ->acceleration = Vector2Add(obj->acceleration, acc);
}

void vobject_render(VerletObject* obj) {
    DrawCircleV(obj->position_current, obj->size, obj->color);
}
