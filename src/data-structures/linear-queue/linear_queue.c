#include "linear_queue.h"
#include <stdio.h>

/* Initialize the linear queue */
void lq_init(LinearQueue *q) {
    if (q == NULL) {
        return;
    }
    q->front = -1;
    q->rear = -1;
}

/* Check if the linear queue is empty */
int lq_is_empty(const LinearQueue *q) {
    if (q == NULL) {
        return 1;
    }
    return (q->front == -1 || q->front > q->rear);
}

/* Check if the linear queue is full (Overflow condition) */
int lq_is_full(const LinearQueue *q) {
    if (q == NULL) {
        return 0;
    }
    return (q->rear == MAX_LINEAR_QUEUE - 1);
}

/* Enqueue a song into the linear queue */
int lq_enqueue(LinearQueue *q, Song song) {
    if (q == NULL) {
        return 0;
    }
    if (lq_is_full(q)) {
        printf("[OVERFLOW ERROR] Play Queue is full! Cannot enqueue '%s' (Max: %d songs).\n",
               song.title, MAX_LINEAR_QUEUE);
        return 0;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->rear++;
    q->items[q->rear] = song;
    printf("[ENQUEUE SUCCESS] Added to Play Queue at position %d: '%s' by %s\n",
           q->rear - q->front + 1, song.title, song.artist);
    return 1;
}

/* Dequeue a song from the linear queue (Underflow condition) */
int lq_dequeue(LinearQueue *q, Song *out_song) {
    if (q == NULL || lq_is_empty(q)) {
        printf("[UNDERFLOW ERROR] Play Queue is empty! No songs to dequeue.\n");
        return 0;
    }
    if (out_song != NULL) {
        *out_song = q->items[q->front];
    }
    printf("[DEQUEUE SUCCESS] Dequeued '%s' by %s from position 1.\n",
           q->items[q->front].title, q->items[q->front].artist);

    q->front++;
    /* Reset pointers when queue becomes empty to reuse space */
    if (q->front > q->rear) {
        q->front = -1;
        q->rear = -1;
    }
    return 1;
}

/* Peek at the song at the front of the queue */
int lq_peek(const LinearQueue *q, Song *out_song) {
    if (q == NULL || lq_is_empty(q)) {
        return 0;
    }
    if (out_song != NULL) {
        *out_song = q->items[q->front];
    }
    return 1;
}

/* Display all songs currently waiting in the linear queue */
void lq_display(const LinearQueue *q) {
    if (q == NULL || lq_is_empty(q)) {
        printf("--- Play Queue is empty (0 / %d slots used) ---\n", MAX_LINEAR_QUEUE);
        return;
    }
    int count = q->rear - q->front + 1;
    printf("\n=== Current Play Queue (%d / %d songs) ===\n", count, MAX_LINEAR_QUEUE);
    for (int i = q->front; i <= q->rear; i++) {
        int pos = (i - q->front) + 1;
        printf("  %2d. ", pos);
        print_song(&q->items[i]);
    }
    printf("===========================================\n");
}

/* Return count of songs in the linear queue */
int lq_count(const LinearQueue *q) {
    if (q == NULL || lq_is_empty(q)) {
        return 0;
    }
    return q->rear - q->front + 1;
}
