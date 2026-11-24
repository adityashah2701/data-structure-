#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include "../../../common/song.h"

#define MAX_RECENT 5

/*
 * Circular Queue Data Structure
 * Used for maintaining recently played history.
 * Automatically wraps around and overwrites the oldest song when capacity (5) is reached.
 * Displays tracks in chronological order (oldest to newest).
 */
typedef struct {
    Song items[MAX_RECENT];
    int front;
    int rear;
    int count;
} CircularQueue;

/* Function Declarations */
void cq_init(CircularQueue *q);
int cq_is_empty(const CircularQueue *q);
int cq_is_full(const CircularQueue *q);
void cq_insert(CircularQueue *q, Song song);
void cq_display(const CircularQueue *q);
int cq_get_count(const CircularQueue *q);

#endif /* CIRCULAR_QUEUE_H */
