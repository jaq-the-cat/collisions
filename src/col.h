#pragma once

#define QT_CAPACITY 8

typedef struct {
    float x, y;
} vec2;

typedef struct {
    vec2 bl;
    vec2 tr; 
} rectangle;

typedef enum node_type {
    POINTS,
    RECURSIVE,
} node_type;

typedef struct s_quadrants {
    struct quadtree *nw, *ne, *sw, *se;
} s_quadrants;

union qtnode {
    // array of points OR 4 other quadtrees
    struct {
        vec2* points[QT_CAPACITY];
        int length;
    } points;

    s_quadrants quadrants;
};

typedef struct quadtree {
    rectangle boundary;
    node_type type;
    union qtnode data;
} quadtree;

void insert(quadtree *t, vec2 *point);
vec2* closest_to(quadtree *t, vec2 *point);
