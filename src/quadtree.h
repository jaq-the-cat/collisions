#pragma once
#include "util.h"
#include "llpoints.h"

#define QT_CAPACITY 12

typedef enum qt_quadrants {
    NW=0, NE=1,
    SW=2, SE=3,
} qt_quadrants;

typedef enum qt_data_type {
    QTD_POINTS,
    QTD_RECURSIVE,
} qt_data_type;

typedef union qt_data {
    // array of points OR 4 other quadtrees
    ll_points points;
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
