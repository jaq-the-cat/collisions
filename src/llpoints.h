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

void ll_insert(ll_points *ll, vec2 *point);
void ll_remove(ll_points *ll, vec2 *point);
void ll_foreach(ll_points *ll, void (*func)(vec2*));
void ll_free(ll_points *ll, vec2 *point);
