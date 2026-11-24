#include "circular_queue.h"
#include <stdio.h>
#include <string.h>

/* Initialize the circular queue */
void cq_init(CircularQueue *q) {
    if (q == NULL) {
        return;
    }
    q->front = -1;
    q->rear = -1;
    q->count = 0;
}

/* Check if the circular queue is empty */
int cq_is_empty(const CircularQueue *q) {
    if (q == NULL) {
        return 1;
    }
    return (q->count == 0);
}

/* Check if the circular queue has reached full capacity (5 songs) */
int cq_is_full(const CircularQueue *q) {
    if (q == NULL) {
        return 0;
    }
    return (q->count == MAX_RECENT);
}

/*
 * Insert a recently played song into the circular queue.
 * If the queue is full, wraps around and overwrites the oldest song at front,
 * then advances the front pointer.
 */
void cq_insert(CircularQueue *q, Song song) {
    if (q == NULL) {
        return;
    }

    if (q->count == 0) {
        /* First element */
        q->front = 0;
        q->rear = 0;
        q->items[q->rear] = song;
        q->count = 1;
        printf("[RECENTLY PLAYED] Added '%s' (Slot 0, 1/%d stored).\n",
               song.title, MAX_RECENT);
    } else if (q->count < MAX_RECENT) {
        /* Space available: normal advance with wraparound */
        q->rear = (q->rear + 1) % MAX_RECENT;
        q->items[q->rear] = song;
        q->count++;
        printf("[RECENTLY PLAYED] Added '%s' (Slot %d, %d/%d stored).\n",
               song.title, q->rear, q->count, MAX_RECENT);
    } else {
        /* Full capacity: overwrite oldest song */
        Song overwritten = q->items[q->front];
        printf("[WRAPAROUND OVERWRITE] Buffer full (max %d songs). Overwriting oldest song '%s' at Slot %d.\n",
               MAX_RECENT, overwritten.title, q->front);

        q->rear = (q->rear + 1) % MAX_RECENT;
        q->items[q->rear] = song;
        q->front = (q->front + 1) % MAX_RECENT; /* Move front to the next oldest */
        printf("[RECENTLY PLAYED] Stored new track '%s' at Slot %d.\n",
               song.title, q->rear);
    }
}

/* Display recently played songs in chronological order (oldest to newest) */
void cq_display(const CircularQueue *q) {
    if (q == NULL || cq_is_empty(q)) {
        printf("--- Recently Played list is empty (0 / %d slots) ---\n", MAX_RECENT);
        return;
    }

    printf("\n=== Recently Played History (Chronological: %d / %d songs) ===\n",
           q->count, MAX_RECENT);
    for (int i = 0; i < q->count; i++) {
        int idx = (q->front + i) % MAX_RECENT;
        const char *tag = "";
        if (i == 0 && q->count > 1) {
            tag = " [Oldest]";
        } else if (i == q->count - 1) {
            tag = " [Most Recent]";
        }
        printf("  %d.%-15s (Slot %d) ", i + 1, tag, idx);
        print_song(&q->items[idx]);
    }
    printf("=================================================================\n");
}

/* Return the count of songs stored */
int cq_get_count(const CircularQueue *q) {
    if (q == NULL) {
        return 0;
    }
    return q->count;
}
