#ifndef LINEAR_QUEUE_H
#define LINEAR_QUEUE_H

#include "../../../common/song.h"

#define MAX_LINEAR_QUEUE 10

/*
 * Linear Queue Data Structure
 * Used for song queuing (FIFO - First In, First Out).
 * Manages upcoming songs waiting to be played.
 */
typedef struct {
    Song items[MAX_LINEAR_QUEUE];
    int front;
    int rear;
} LinearQueue;

/* Function Declarations */
void lq_init(LinearQueue *q);
int lq_is_empty(const LinearQueue *q);
int lq_is_full(const LinearQueue *q);
int lq_enqueue(LinearQueue *q, Song song);
int lq_dequeue(LinearQueue *q, Song *out_song);
int lq_peek(const LinearQueue *q, Song *out_song);
void lq_display(const LinearQueue *q);
int lq_count(const LinearQueue *q);

#endif /* LINEAR_QUEUE_H */
