#pragma once

#define VEC2(x, y) (vec2) {x, y}
#define RECT(x, y, w, h) (rectangle) \
    {VEC2(x, y), VEC2(w, h)}

typedef struct {
    float x, y;
} vec2;

typedef struct {
    vec2 origin, size;
} rectangle;
