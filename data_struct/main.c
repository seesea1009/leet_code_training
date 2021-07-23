#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "list.h"
#include "stack.h"
#include "queue.h"


typedef struct listdata_s {
    struct list_head node;
    int data;
} listdata_t;

void print_list(struct list_head *head) {
    struct list_head *pos;
    
    int i = 0;
    printf("=============== list start ===============\n");
    LIST_FOR_EACH(pos, head) {
        listdata_t *elmt = LIST_ENTRY(pos, listdata_t, node);
        printf("  > %04d: %d\n", i++, elmt->data);
    }
    printf("=============== list end ===============\n");
}

void print_stack(struct stack *sp) {
    int i = 0;
    printf("=============== stack start ===============\n");
    printf(" size: %lu\n", (size_t)(sp->top - sp->base));
    stack_data_t *cur = sp->base;
    while (cur != sp->top) {
        printf("  > %04d: %d\n", i++, *cur++);
    }
    printf("=============== stack end  ===============\n");
}

void print_queue(struct queue *q) {
    int i = 0;
    printf("=============== queue start ===============\n");
    printf(" size: %lu, front: %lu, rear: %lu\n", (size_t)((q->rear + q->size - q->front) % q->size), q->front, q->rear);
    size_t idx = q->front;
    while (idx != q->rear) {
        printf("  > %04d: %d\n", i++, q->buf[idx]);
        idx = (idx + 1) % q->size;
    }
    printf("=============== queue end  ===============\n");
}

void destory_list(struct list_head *head) {
    struct list_head *pos, *n;
    LIST_FOR_EACH_SAFE(pos, n, head) {
        listdata_t *elmt = LIST_ENTRY(pos, listdata_t, node);
        list_del(pos);
        free(elmt);
    }
}

void testcase_list_01() {
    LIST_HEAD(listhead);
    struct list_head *head = &listhead;
    listdata_t testdata[8];
    for (int i = 0; i < 8; i++) {
        testdata[i].data = i * 10;
    }

    list_add(&testdata[1].node, head);
    list_add(&testdata[2].node, head);
    list_add(&testdata[3].node, head);
    print_list(head);
    list_add_tail(&testdata[4].node, head);
    list_add_tail(&testdata[5].node, head);
    list_add_tail(&testdata[6].node, head);
    print_list(head);
    list_del(&testdata[2].node);
    list_del(&testdata[5].node);
    print_list(head);
    list_add(&testdata[7].node, head);
    list_add_tail(&testdata[0].node, head);
    print_list(head);
}

void testcase_stack_01() {
    struct stack *s = stack_init(8);

    stack_push(s, 1);
    stack_push(s, 2);
    stack_push(s, 3);
    print_stack(s);
    stack_pop(s);
    stack_pop(s);
    print_stack(s);
    int i = 10;
    while (!stack_full(s)) {
        stack_push(s, i);
        i += 10;
    }
    print_stack(s);
    while (!stack_empty(s)) {
        stack_pop(s);
    }
    print_stack(s);
    stack_free(s);
}

void testcase_queue_01() {
    struct queue *q = queue_init(8);

    print_queue(q);
    queue_push(q, 1);
    queue_push(q, 2);
    print_queue(q);
    queue_pop(q);
    print_queue(q);
    queue_push_front(q, 11);
    queue_push_back(q, 22);
    print_queue(q);
    queue_pop_back(q);
    print_queue(q);
    queue_pop_front(q);
    print_queue(q);

    queue_free(q);
}

int main(int argc, char **argv) {
    printf("hello world\n");
    //testcase_list_01();
    //testcase_stack_01();
    testcase_queue_01();
    return 0;
}