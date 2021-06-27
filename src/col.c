#include "col.h"
#include <stdlib.h>

int point_inside_rect(vec2 *point, rectangle *rect) {
    return (
        point->x >= rect->bl.x &&
        point->y <= rect->bl.y
        &&
        point->x <= rect->tr.x &&
        point->y >= rect->tr.y
    );
}

void subdivide(quadtree *t) {
    vec2* points = (vec2*) t->data.points.points;
    for (int i=0; i<QT_CAPACITY; i++)
        insert(t, &points[i]);
}

void insert(quadtree *t, vec2 *point) {
    if (t->type == POINTS) {
        t->data.points.points[t->data.points.length] = point;
        t->data.points.length++;
        if (t->data.points.length == QT_CAPACITY)
            subdivide(t);
    }
    else {
        s_quadrants *q = &t->data.quadrants;
        const double mid_x = ((double) t->boundary.bl.x + (double) t->boundary.tr.x)/2.;
        const double mid_y = ((double) t->boundary.bl.y + (double) t->boundary.tr.y)/2.;
        if (point->x <= mid_x) { // west
            if (point->y <= mid_y) // north
                insert(t->data.quadrants.nw, point);
            else // south
                insert(t->data.quadrants.sw, point);
        } else { // east
            if (point->y <= mid_y) // north
                insert(t->data.quadrants.ne, point);
            else // south
                insert(t->data.quadrants.se, point);
        }
    }
}

vec2* closest_to(quadtree *t, vec2 *point) {
    return NULL;
}
