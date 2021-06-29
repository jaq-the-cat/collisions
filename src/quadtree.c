#include "quadtree.h"
#include <stdlib.h>
#include <stdio.h>

#include "util.h"

quadtree* qt_make(rectangle boundary) {
    quadtree *qt = malloc(sizeof(quadtree));
    qt->boundary = boundary;
    qt->type = QTD_POINTS;
    qt->data = (qt_data) {
        .points = LLPOINTS,
    };
    return NULL;
}

void qt_subdivide(quadtree *qt) {
    if (qt->type == QTD_POINTS) {
        qt->type = QTD_RECURSIVE;
        ll_points points = qt->data.points;
        qt->data.quadrants[NW] = qt_make(
            RECT(
                qt->boundary.origin.x,
                qt->boundary.origin.y + qt->boundary.size.y/2,
                qt->boundary.size.x/2,
                qt->boundary.size.y/2
            ));
        qt->data.quadrants[NE] = qt_make(
            RECT(
                qt->boundary.origin.x + qt->boundary.size.x/2,
                qt->boundary.origin.y + qt->boundary.size.y/2,
                qt->boundary.size.x/2,
                qt->boundary.size.y/2
            ));
        qt->data.quadrants[SW] = qt_make(
            RECT(
                qt->boundary.origin.x,
                qt->boundary.origin.y,
                qt->boundary.size.x/2,
                qt->boundary.size.y/2
            ));
        qt->data.quadrants[SE] = qt_make(
            RECT(
                qt->boundary.origin.x + qt->boundary.size.x/2,
                qt->boundary.origin.y,
                qt->boundary.size.x/2,
                qt->boundary.size.y/2
            ));

        // reinsert points
        for (ll_node *node = points.head; node != NULL; node = node->next)
            qt_insert(qt, node->point);
    }
}

int qt_get_quadrant(rectangle *boundary, vec2 *point) {
    // NW=0 NE=1
    // SW=2 SE=3
    int index = 0;

    // if point is lower than the middle
    if (point->y > boundary->origin.y - boundary->size.y/2)
        index += 2; //  south side
    // if point is higher than the middle
    if (point->x > boundary->origin.x + boundary->size.x/2)
        index += 1; // east side

    return index;
}

void qt_insert(quadtree *qt, vec2 *point) {
    if (qt->type == QTD_POINTS) {
        ll_insert(&qt->data.points, point);
        if (qt->data.points.length >= QT_CAPACITY)
            qt_subdivide(qt);
    } else {
        qt_insert(qt->data.quadrants[qt_get_quadrant(&qt->boundary, point)], point);
    }
}

void qt_remove(quadtree *qt, vec2 *point) {
    if (qt->type == QTD_POINTS)
        ll_remove(&qt->data.points, point);
    else
        qt_remove(qt->data.quadrants[qt_get_quadrant(&qt->boundary, point)], point);

}

vec2* qt_closest_to(quadtree *qt, vec2 *point) {
    return NULL;
}

void qt_foreach(quadtree *qt, void (*quad)(quadtree*), void (*pt)(vec2*)) {

}

void qt_free(quadtree *qt) {

}
