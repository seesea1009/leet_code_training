#ifndef __STACK_H__
#define __STACK_H__

#include <stdlib.h>
#include <stdbool.h>

typedef int stack_data_t;
struct stack {
    stack_data_t *base;
    stack_data_t *top;
    stack_data_t *end;
};

static inline struct stack *stack_init(size_t size) {
    struct stack *sp = (struct stack *)malloc(sizeof(struct stack));
    sp->base = (stack_data_t *)malloc(sizeof(stack_data_t) * size);
    sp->top  = sp->base;
    sp->end  = sp->base + size;
    return sp;
}

static inline void stack_push(struct stack *sp, stack_data_t data) {
    *sp->top++ = data;
}

static inline void stack_pop(struct stack *sp) {
    --sp->top;
}

static inline stack_data_t stack_top(struct stack *sp) {
    return *(sp->top - 1);
}

static inline bool stack_empty(struct stack *sp) {
    return sp->top == sp->base;
}

static inline bool stack_full(struct stack *sp) {
    return sp->top == sp->end;
}

static inline void stack_free(struct stack *sp) {
    if (sp) {
        if (sp->base) {
            free(sp->base);
            sp->base = NULL;
        }
        sp->top = NULL;
        sp->end = NULL;
        free(sp);
    }
}

#endif  /* __STACK_H__ */
