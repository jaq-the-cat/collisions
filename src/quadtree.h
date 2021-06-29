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

typedef enum qt_data_type {
    QTD_POINTS,
    QTD_RECURSIVE,
} qt_data_type;

typedef struct qt_point {
    vec2 *point;
    struct qt_point *next;
} qt_point;

typedef struct qt_points {
    qt_point *head;
    int length;
} qt_points;

typedef enum qt_quadrants {
    NW, NE,
    SW, SE,
} qt_quadrants;

typedef union qt_data {
    // array of points OR 4 other quadtrees
    qt_points points;
    struct quadtree* quadrants[4];
} qt_data;

typedef struct quadtree {
    rectangle boundary;
    qt_data_type type;
    qt_data data;
} quadtree;

quadtree* qt_make(rectangle boundary);

void qt_insert(quadtree *qt, vec2 *point);
void qt_remove(quadtree *qt, vec2 *point);

vec2* qt_closest_to(quadtree *qt, vec2 *point);

void qt_foreach(quadtree *qt, void (*quad)(quadtree*), void (*pt)(vec2*));
void qt_free(quadtree *qt);
