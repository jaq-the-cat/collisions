#pragma once

#define QT_CAPACITY 8

typedef struct {
    float x, y;
} vec2;

typedef struct {
    vec2 origin;
    vec2 size; 
} rectangle;

typedef struct {
    rectangle boundary;
    vec2 points[QT_CAPACITY];
    int length;
} quadtree;
