#pragma once
#include "util.h"

typedef struct dlnode {
    qt_type point;
    struct dlnode *next;
} dlnode;

typedef struct datalist {
    dlnode *head;
    int length;
} datalist;

#define DATALIST (datalist) {NULL, 0}

void dl_insert(datalist *ll, qt_type point);
void dl_remove(datalist *ll, qt_type point);
void dl_foreach(datalist *ll, void (*func)(qt_type));
void dl_free(datalist *ll);
