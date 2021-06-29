#include "llpoints.h"

#include <stdlib.h>
#include <stdio.h>

void dl_insert(datalist *ll, type point) {
    dlnode *oldhead = ll->head;
    ll->head = malloc(sizeof(dlnode));
    ll->head->point = point;
    ll->head->next = oldhead;
    ll->length++;
}

void dl_remove(datalist *ll, type point) {
    if (ll->head->point == point) {
        // remove head
        dlnode *newhead = ll->head->next;
        free(ll->head);
        ll->head = newhead;
    } else {
        // remove some other data
        for (dlnode *node = ll->head; node->next != NULL; node = node->next) {
            if (node->next->point == point) {
                dlnode *next = node->next->next;
                free(node->next);
                node->next = next;
            }
        }
    }
}

void dl_foreach(datalist *ll, void (*func)(type)) {
    for (dlnode *node = ll->head; node != NULL; node = node->next)
        func(node->point);
}

void dl_free(datalist *ll) {
    dlnode *next;
    for (dlnode *node = ll->head; node != NULL;) {
        next = node->next;
        free(node);
        node = next;
    }
}
