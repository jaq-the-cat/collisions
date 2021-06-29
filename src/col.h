#pragma once

#define QT_CAPACITY 3

#define VEC2(x, y) (vec2) {x, y}
#define RECT(x, y, w, h) (rectangle) \
    {VEC2(x, y), VEC2(w, h)}

typedef struct {
    float x, y;
} vec2;

typedef struct {
    vec2 origin, size;
} rectangle;

typedef enum node_type {
    POINTS,
    RECURSIVE,
} qt_node_type;

typedef struct s_quadrants {
    struct quadtree *nw, *ne, *sw, *se;
} qt_quadrants;

typedef struct qt_point {
    vec2 *point;
    struct qt_point *next;
} qt_point;

typedef struct {
    qt_point *head;
    int length;
} qt_points;

union qt_data {
    // array of points OR 4 other quadtrees
    qt_points points;
    qt_quadrants quadrants;
};

typedef struct quadtree {
    rectangle boundary;
    qt_node_type type;
    union qt_data data;
} quadtree;

quadtree* qt_make(rectangle boundary);

void qt_insert(quadtree *qt, vec2 *point);
void qt_remove(quadtree *qt, vec2 *point);

vec2* qt_closest_to(quadtree *qt, vec2 *point);

void qt_foreach(quadtree *qt, void (*quad)(quadtree*), void (*pt)(vec2*));
void qt_free(quadtree *qt);
