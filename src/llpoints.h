#pragma once
#include "util.h"

typedef vec2* type;

typedef struct ll_node {
    type point;
    struct ll_node *next;
} dlnode;

typedef struct ll_points {
    dlnode *head;
    int length;
} datalist;

#define LLPOINTS (ll_points) {NULL, 0}

void dl_insert(datalist *ll, type point);
void dl_remove(datalist *ll, type point);
void dl_foreach(datalist *ll, void (*func)(type));
void dl_free(datalist *ll);
