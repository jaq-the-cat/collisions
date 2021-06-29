#include "llpoints.h"

#include <stdlib.h>

void ll_insert(ll_points *ll, vec2 *point) {
    ll_node *oldhead = ll->head;
    ll->head = malloc(sizeof(ll_node));
    ll->head->point = point;
    ll->head->next = oldhead;
}

void ll_remove(ll_points *ll, vec2 *point) {
    if (ll->head->point == point) {
        // remove head
        ll_node *newhead = ll->head->next;
        free(ll->head);
        ll->head = newhead;
    } else {
        // remove some other point
        for (ll_node *node = ll->head; node->next != NULL; node = node->next) {
            if (node->next->point == point) {
                ll_node *next = node->next->next;
                free(node->next);
                node->next = next;
            }
        }
    }
}

void ll_free(ll_points *ll, vec2 *point) {
    ll_node *next;
    for (ll_node *node = ll->head; node != NULL;) {
        next = node->next;
        free(node);
        node = next;
    }
}
