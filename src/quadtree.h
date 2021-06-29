#pragma once
#include "util.h"
#include "datalist.h"

#define QT_CAPACITY 16

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
    datalist list;
    struct quadtree* quadrants[4];
} qt_data;

typedef struct quadtree {
    rectangle boundary;
    qt_data_type type;
    qt_data data;
} quadtree;

quadtree* qt_make(rectangle boundary);

void qt_insert(quadtree *qt, qt_type point);
void qt_remove(quadtree *qt, qt_type point);

vec2* qt_closest_to(quadtree *qt, qt_type point);

void qt_foreach(quadtree *qt, void (*quad)(quadtree*), void (*data)(qt_type));
void qt_free(quadtree *qt);
