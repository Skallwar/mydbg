#include <stdlib.h>

#include <assert.h>

#include "intrlist.h"

intrlist_t *intrlist_new()
{
    intrlist_t *list = malloc(sizeof(*list));

    if (!list) {
        return NULL;
    }

    list->prev = list;
    list->next = list;

    return list;
}

void intrlist_init(intrlist_t *list)
{
    list->prev = list;
    list->next = list;
}

void intrlist_push(intrlist_t *list, intrlist_t *node)
{
    assert(list);
    assert(node);

    node->prev = list;
    node->next = list->next;
    list->next = node;
    node->next->prev = node;
}

void intrlist_append(intrlist_t *list, intrlist_t *node)
{
    assert(list);
    assert(node);

    node->next = list;
    node->prev = list->prev;
    list->prev = node;
    node->prev->next = node;
}

intrlist_t *intrlist_remove(intrlist_t *elm)
{
    assert(elm);

    if (elm->next == elm && elm->prev == elm) {
        return NULL;
    }

    elm->prev->next = elm->next;
    elm->next->prev = elm->prev;

    elm->prev = elm;
    elm->next = elm;

    return elm;
}

bool intrlist_isempty(intrlist_t *list)
{
    return list->next == list && list->prev == list;
}
