#include "col.h"
#include <stdlib.h>
#include <stdio.h>

void qt_recursive_quadrants(quadtree *t, vec2 *point, void (*func)(quadtree*, vec2*)) {
    // the 4 quadrants inside the current quadrant
    s_quadrants *q = &t->data.quadrants;
    const double mid_x = ((double) t->boundary.bl.x + (double) t->boundary.tr.x)/2.;
    const double mid_y = ((double) t->boundary.bl.y + (double) t->boundary.tr.y)/2.;
    if (point->x <= mid_x) { // west
        if (point->y <= mid_y) { // north
            printf("Runnign FUNC for NW\n");
            func(t->data.quadrants.nw, point);
        } else { // south
            printf("Runnign FUNC for SW\n");
            func(t->data.quadrants.sw, point);
        }
    } else { // east
        if (point->y <= mid_y) { // north
            printf("Runnign FUNC for NE\n");
            func(t->data.quadrants.ne, point);
        } else { // south
            printf("Runnign FUNC for SE\n");
            func(t->data.quadrants.se, point);
        }
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

quadtree* qt_make(rectangle boundary) {
    // create and return a new empty quadtree
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

void qt_subdivide(quadtree *t) {
    s_point* node = t->data.points.head;

    const double mid_x = ((double) t->boundary.bl.x + (double) t->boundary.tr.x)/2.;
    const double mid_y = ((double) t->boundary.bl.y + (double) t->boundary.tr.y)/2.;

    // make the quadtree recursive and set its data to 4 equally sized quadrants
    t->type = RECURSIVE;
    t->data = (union qtnode) {
        .quadrants = (s_quadrants) {
            .nw = qt_make((rectangle) {
                .bl = (vec2) { t->boundary.bl.x, mid_y },
                .tr = (vec2) { mid_x, t->boundary.tr.y },
            }),
            .ne = qt_make((rectangle) {
                .bl = (vec2) { mid_x, mid_y },
                .tr = (vec2) { t->boundary.tr.x, t->boundary.tr.y },
            }),
            .sw = qt_make((rectangle) {
                .bl = (vec2) { t->boundary.bl.x, t->boundary.bl.y },
                .tr = (vec2) { mid_x, mid_y },
            }),
            .se = qt_make((rectangle) {
                .bl = (vec2) { mid_x, t->boundary.bl.y },
                .tr = (vec2) { t->boundary.tr.x, mid_y },
            }),
        },
    };

    // reinsert points previously inside the quadtree
    for (; node != NULL; node = node->next)
        qt_insert(t, node->point);
}

void qt_insert(quadtree *t, vec2 *point) {
    if (t->type == POINTS) {
        // if the data is of type POINTS, set new point
        // to be the new head of the linked list
        s_point *oldhead = t->data.points.head;
        t->data.points.head = malloc(sizeof(s_point));
        t->data.points.head->point = point;
        t->data.points.head->next = oldhead;
        t->data.points.length++;

        // max length reached -> subdivide
        if (t->data.points.length == QT_CAPACITY)
            qt_subdivide(t);
    // else run qt_insert() for every quadrant inside itself
    } else qt_recursive_quadrants(t, point, qt_insert);
}

void qt_remove(quadtree *t, vec2 *point) {
    if (t->type == POINTS) {
        // if the head is the point to be removed:
        s_point *node = t->data.points.head;
        if (node->point == point) {
            s_point *next = node->next;
            free(t->data.points.head);
            t->data.points.head = next;
        }
        // else
        for (; node->next != NULL; node = node->next)
            // if next node is node to be removed
            if (node->next->point == point) {
                //  free it and set its `next` to current node `next`
                s_point *to_remove = node->next;
                node->next = node->next->next;
                free(to_remove);
                t->data.points.length--;
                break;
            }

    // else run qt_remove() for every quadrant inside itself
    } else qt_recursive_quadrants(t, point, qt_remove);
}

void qt_free(quadtree *t) {
    if (t->type == POINTS) {
        for (s_point *node = t->data.points.head; node != NULL;) {
            s_point *next = node->next;
            free(node);
            node = next; // free every point
        }
    } else {
        // free every quadrant
        qt_free(t->data.quadrants.nw);
        qt_free(t->data.quadrants.ne);
        qt_free(t->data.quadrants.sw);
        qt_free(t->data.quadrants.se);
    }
    free(t);
}

void qt_foreach(quadtree *t, void (*quad)(quadtree*), void (*pt)(vec2*)) {
    // for each RECURSIVE quadrant inside `t` and `t` itself, run func();
    quad(t);
    if (t->type == RECURSIVE) {
        qt_foreach(t->data.quadrants.nw, quad, pt);
        qt_foreach(t->data.quadrants.ne, quad, pt);
        qt_foreach(t->data.quadrants.sw, quad, pt);
        qt_foreach(t->data.quadrants.se, quad, pt);
    } else for (s_point *node = t->data.points.head; node != NULL; node = node->next)
        pt(node->point);
}

vec2* qt_closest_to(quadtree *t, vec2 *point) {
    // return closest point to `point`
    return NULL;
}
