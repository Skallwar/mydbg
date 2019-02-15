#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdbool.h>

struct intrlist {
    struct intrlist *prev;
    struct intrlist *next;
};

typedef struct intrlist intrlist_t;

#define typeof __typeof__

#define container_of(ptr, type, member) ({			\
        const typeof(((type *)0)->member) * __mptr = (ptr);	\
        (type *)((char *)__mptr - offsetof(type, member)); })

#define intrlist_entry(head, type, member) container_of(head, type, member)

#define intrlist_foreach(list, cur, member) \
        for (cur = intrlist_entry((list)->next, typeof(*cur), member); \
             &cur->member != list; \
             cur = intrlist_entry(cur->member.next, typeof(*cur), member))

#define intrlist_foreach_reverse(list, cur, member) \
        for (cur = intrlist_entry((list)->prev, typeof(*cur), member); \
             &cur->member != list; \
             cur = intrlist_entry(cur->member.prev, typeof(*cur), member))

/* Init sentinel */
void intrlist_init(intrlist_t *list);

void intrlist_push(intrlist_t *list, intrlist_t *node);
void intrlist_append(intrlist_t *list, intrlist_t *node);

intrlist_t *intrlist_remove(intrlist_t *elm);
#define intrlist_pop(list) intrlist_remove((list)->next)
#define intrlist_strip(list) intrlist_remove((list)->prev)

bool intrlist_isempty(intrlist_t *list);

#endif
