#include "col.h"
#include <stdlib.h>

void recursive_quadrants(quadtree *t, vec2 *point, void (*func)(quadtree*, vec2*)) {
    s_quadrants *q = &t->data.quadrants;
    const double mid_x = ((double) t->boundary.bl.x + (double) t->boundary.tr.x)/2.;
    const double mid_y = ((double) t->boundary.bl.y + (double) t->boundary.tr.y)/2.;
    if (point->x <= mid_x) { // west
        if (point->y <= mid_y) // north
            func(t->data.quadrants.nw, point);
        else // south
            func(t->data.quadrants.sw, point);
    } else { // east
        if (point->y <= mid_y) // north
            func(t->data.quadrants.ne, point);
        else // south
            func(t->data.quadrants.se, point);
    }
}

int point_inside_rect(vec2 *point, rectangle *rect) {
    return (
        point->x >= rect->bl.x &&
        point->y <= rect->bl.y
        &&
        point->x <= rect->tr.x &&
        point->y >= rect->tr.y
    );
}

quadtree* make_quadrant(rectangle boundary) {
    quadtree *q = malloc(sizeof(quadtree));
    *q = (quadtree) {
        .boundary = boundary,
        .type = POINTS,
        .data = (union qtnode) {
            .points = {{0}, 0}
        }
    };

    return q;
}

void subdivide(quadtree *t) {
    vec2* points = (vec2*) t->data.points.points;

    const double mid_x = ((double) t->boundary.bl.x + (double) t->boundary.tr.x)/2.;
    const double mid_y = ((double) t->boundary.bl.y + (double) t->boundary.tr.y)/2.;

    t->data = (union qtnode) {
        .quadrants = (s_quadrants) {
            .nw = make_quadrant((rectangle) {
                .bl = (vec2) { t->boundary.bl.x, mid_y },
                .tr = (vec2) { mid_x, t->boundary.tr.y },
            }),
            .ne = make_quadrant((rectangle) {
                .bl = (vec2) { mid_x, mid_y },
                .tr = (vec2) { t->boundary.tr.x, t->boundary.tr.y },
            }),
            .sw = make_quadrant((rectangle) {
                .bl = (vec2) { t->boundary.bl.x, t->boundary.bl.y },
                .tr = (vec2) { mid_x, mid_y },
            }),
            .se = make_quadrant((rectangle) {
                .bl = (vec2) { mid_x, t->boundary.bl.y },
                .tr = (vec2) { t->boundary.tr.x, mid_y },
            }),
        },
    };
    for (int i=0; i<QT_CAPACITY; i++)
        insert(t, &points[i]);
}

void insert(quadtree *t, vec2 *point) {
    if (t->type == POINTS) {
        t->data.points.points[t->data.points.length] = point;
        t->data.points.length++;
        if (t->data.points.length == QT_CAPACITY)
            subdivide(t);
    } else recursive_quadrants(t, point, insert);
}

void remove(quadtree *t, vec2 *point) {
    if (t->type == POINTS) {
        int i;

        // Remove item
        for (i=0; i<t->data.points.length; i++)
            if (t->data.points.points[i] == point) {
                t->data.points.points[i] = NULL;
                break;
            }
        // Removed item's index is `i`

        // For each index ahead of `i`, set `i` to that index and increase both
        // This shifts the right part of the list left
        // { 1 2 3 4 5 6 }
        // { 1 2 3 5 6 NULL }
        for (int k=i+1; k<t->data.points.length; k++, i++) {
            t->data.points.points[i] = t->data.points.points[k];
            t->data.points.points[k] = NULL;
        }
        t->data.points.length--;

    } else recursive_quadrants(t, point, remove);
}

vec2* closest_to(quadtree *t, vec2 *point) {
    return NULL;
}
