#pragma once
#include "util.h"

typedef struct ll_node {
    vec2 *point;
    struct ll_node *next;
} ll_node;

typedef struct ll_points {
    ll_node *head;
    int length;
} ll_points;

#define LLPOINTS (ll_points) {NULL, 0}
