#pragma once

#define QT_CAPACITY 8

typedef struct {
    float x, y;
} vec2;

typedef struct {
    vec2 origin;
    vec2 size; 
} rectangle;

typedef enum node_type {
    POINTS,
    RECURSIVE,
} node_type;

union qtnode {
    // array of points OR 4 other quadtrees
    struct {
        vec2 points[QT_CAPACITY];
        int length;
    } points;

    struct {
        struct quadtree *nw, *ne, *sw, *se;
    } quadrants;
};

typedef struct quadtree {
    rectangle boundary;
    node_type type;
    union qtnode data;
} quadtree;