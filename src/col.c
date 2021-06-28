#include "col.h"
#include <stdlib.h>

void recursive_quadrants(quadtree *t, vec2 point, void (*func)(quadtree*, vec2)) {
    s_quadrants *q = &t->data.quadrants;
    const double mid_x = ((double) t->boundary.bl.x + (double) t->boundary.tr.x)/2.;
    const double mid_y = ((double) t->boundary.bl.y + (double) t->boundary.tr.y)/2.;
    if (point.x <= mid_x) { // west
        if (point.y <= mid_y) // north
            func(t->data.quadrants.nw, point);
        else // south
            func(t->data.quadrants.sw, point);
    } else { // east
        if (point.y <= mid_y) // north
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
            .points = {NULL, 0}
        }
    };

    return q;
}

void subdivide(quadtree *t) {
    s_point* node;

    const double mid_x = ((double) t->boundary.bl.x + (double) t->boundary.tr.x)/2.;
    const double mid_y = ((double) t->boundary.bl.y + (double) t->boundary.tr.y)/2.;

    t->type = RECURSIVE;
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
    for (node = t->data.points.head; node != NULL; node = node->next)
        insert(t, node->point);
}

void insert(quadtree *t, vec2 point) {
    if (t->type == POINTS) {
        s_point *oldhead = t->data.points.head;
        t->data.points.head = malloc(sizeof(s_point));
        t->data.points.head->point = point;
        t->data.points.head->next = oldhead;
        t->data.points.length++;
        if (t->data.points.length == QT_CAPACITY)
            subdivide(t);
    } else recursive_quadrants(t, point, insert);
}

void remove(quadtree *t, vec2 point) {
    if (t->type == POINTS) {
        for (s_point *node = t->data.points.head; node->next != NULL; node = node->next)
            if (node->next->point.x == point.x && node->next->point.y == point.y) {
                // next node to be removed
                s_point *to_remove = node->next;
                node->next = node->next->next;
                free(to_remove);
                t->data.points.length--;
                break;
            }

    } else recursive_quadrants(t, point, remove);
}

vec2* closest_to(quadtree *t, vec2 point) {
    return NULL;
}
