#pragma once

#include <raylib.h>

typedef struct {
    int id;
    int size; // radius
    Color color;

    Vector2 position_current;
    Vector2 position_old;
    Vector2 acceleration;
} VerletObject;

VerletObject vobject_create(int id, Vector2 position_current, Vector2 acceleration);

void vobject_update_position(VerletObject* obj, float dt);
void vobject_accelerate(VerletObject* obj, Vector2 acc);

void vobject_render(VerletObject* obj);
