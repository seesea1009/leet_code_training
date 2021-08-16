#ifndef __LIST_H__
#define __LIST_H__

#include <stdlib.h>
#include <stdbool.h>

#ifndef OFFSET_OF
#define OFFSET_OF(type, member)             ((size_t)&(((type *)0)->member))
#endif
#ifndef CONTAINER_OF
#define CONTAINER_OF(ptr, type, member)     ((type *)((void *)ptr - OFFSET_OF(type, member)))
#endif

#define LIST_ENTRY(ptr, type, member)       CONTAINER_OF(ptr, type, member)
#define LIST_HEAD_INIT(name)                { &(name), &(name) }
#define LIST_HEAD(name)     \
    struct list_head name = LIST_HEAD_INIT(name)

#define LIST_FOR_EACH(pos, head)    \
    for (pos = (head)->next; pos != head; pos = pos->next)

#define LIST_FOR_EACH_SAFE(pos, n, head)    \
    for (pos = (head)->next, n = pos->next; pos != head; pos = n, n = pos->next)

struct list_head {
    struct list_head *prev;
    struct list_head *next;
};

static inline void __list_add(struct list_head *node, struct list_head *prev, struct list_head *next) {
    prev->next = node;
    next->prev = node;
    node->prev = prev;
    node->next = next;
}

static inline void __list_del(struct list_head *prev, struct list_head *next) {
    prev->next = next;
    next->prev = prev;
}

static inline void list_add(struct list_head *node, struct list_head *head) {
    __list_add(node, head, head->next);
}

static inline void list_add_tail(struct list_head *node, struct list_head *head) {
    __list_add(node, head->prev, head);
}

static inline void list_del(struct list_head *node) {
    __list_del(node->prev, node->next);
}

static inline bool list_empty(struct list_head *head) {
    return head->next == head;
}

#endif  /* __LIST_H__ */
