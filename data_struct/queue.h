#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdlib.h>
#include <stdbool.h>

typedef int queue_data_t;
struct queue {
    queue_data_t *buf;
    size_t front;
    size_t rear;
    size_t size;
};

static inline struct queue *queue_init(size_t size) {
    struct queue *q = (struct queue *)malloc(sizeof(struct queue));
    q->buf = (queue_data_t *)malloc(sizeof(queue_data_t) * (size + 1));
    q->front  = 0;
    q->rear   = 0;
    q->size   = size + 1;
    return q;
}

static inline void queue_push_front(struct queue *q, queue_data_t data) {
    q->front = (q->front + q->size - 1) % q->size;
    q->buf[q->front] = data;
}

static inline void queue_push_back(struct queue *q, queue_data_t data) {
    q->buf[q->rear] = data;
    q->rear = (q->rear + 1) % q->size;
}

static inline void queue_push(struct queue *q, queue_data_t data) {
    queue_push_back(q, data);
}

static inline void queue_pop_front(struct queue *q) {
    q->front = (q->front + 1) % q->size;
}

static inline void queue_pop_back(struct queue *q) {
    q->rear = (q->rear + q->size - 1) % q->size;
}

static inline void queue_pop(struct queue *q) {
    queue_pop_front(q);
}

static inline queue_data_t queue_top(struct queue *q) {
    return q->buf[q->front];
}

static inline queue_data_t queue_front(struct queue *q) {
    return q->buf[q->front];
}

static inline queue_data_t queue_back(struct queue *q) {
    return q->buf[(q->rear + q->size - 1) % q->size];
}

static inline bool queue_empty(struct queue *q) {
    return q->rear == q->front;
}

static inline bool queue_full(struct queue *q) {
    return (q->rear + 1) % q->size == q->front;
}

static inline void queue_free(struct queue *q) {
    if (q) {
        if (q->buf) {
            free(q->buf);
            q->buf = NULL;
        }
        free(q);
    }
}

#endif  /* __QUEUE_H__ */
