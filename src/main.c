#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/song.h"
#include "../common/input.h"
#include "data-structures/linear-queue/linear_queue.h"
#include "data-structures/circular-queue/circular_queue.h"

/* Preloaded sample tracks to facilitate fast academic evaluation / viva demonstration */
static void load_sample_songs(LinearQueue *lq) {
    Song samples[] = {
        create_song(101, "Bohemian Rhapsody", "Queen", "Rock", 354),
        create_song(102, "Billie Jean", "Michael Jackson", "Pop", 294),
        create_song(103, "Hotel California", "Eagles", "Rock", 391),
        create_song(104, "Take Five", "Dave Brubeck", "Jazz", 324),
        create_song(105, "Shape of You", "Ed Sheeran", "Pop", 233)
    };
    int n = sizeof(samples) / sizeof(samples[0]);
    int added = 0;
    for (int i = 0; i < n; i++) {
        if (lq_enqueue(lq, samples[i])) {
            added++;
        }
    }
    printf("Successfully loaded %d sample tracks into Play Queue.\n", added);
}

int main(void) {
    LinearQueue play_queue;
    CircularQueue recent_queue;

    lq_init(&play_queue);
    cq_init(&recent_queue);

    int choice;
    do {
        printf("\n======================================================\n");
        printf("       MUSIC MANAGEMENT SYSTEM - ACADEMIC REVIEW 1    \n");
        printf("======================================================\n");
        printf(" [LINEAR QUEUE - Play Queue]\n");
        printf("  1. Enqueue Song to Play Queue\n");
        printf("  2. Dequeue Song from Play Queue\n");
        printf("  3. Play Next Song (Dequeue + Add to Recently Played)\n");
        printf("  4. Display Play Queue\n");
        printf("\n [CIRCULAR QUEUE - Recently Played]\n");
        printf("  5. Add Song Directly to Recently Played\n");
        printf("  6. Display Recently Played History (Chronological)\n");
        printf("\n [UTILITY]\n");
        printf("  7. Load Sample Songs into Play Queue\n");
        printf("  0. Exit\n");
        printf("======================================================\n");

        choice = read_int("Enter your choice (0-7): ");

        switch (choice) {
            case 1: {
                if (lq_is_full(&play_queue)) {
                    printf("[OVERFLOW ERROR] Play Queue is full (Max %d songs). Cannot enqueue.\n",
                           MAX_LINEAR_QUEUE);
                    break;
                }
                int id = read_int("Enter Song ID: ");
                char title[MAX_TITLE_LEN];
                char artist[MAX_ARTIST_LEN];
                char genre[MAX_GENRE_LEN];
                read_string("Enter Song Title: ", title, sizeof(title));
                read_string("Enter Artist Name: ", artist, sizeof(artist));
                read_string("Enter Genre: ", genre, sizeof(genre));
                int duration = read_int("Enter Duration (in seconds): ");

                Song s = create_song(id, title, artist, genre, duration);
                lq_enqueue(&play_queue, s);
                break;
            }

            case 2: {
                Song removed;
                if (lq_dequeue(&play_queue, &removed)) {
                    printf("Dequeued Song Details: ");
                    print_song(&removed);
                }
                break;
            }

            case 3: {
                Song playing;
                if (lq_dequeue(&play_queue, &playing)) {
                    printf(">>> Now Playing: ");
                    print_song(&playing);
                    cq_insert(&recent_queue, playing);
                }
                break;
            }

            case 4:
                lq_display(&play_queue);
                break;

            case 5: {
                int id = read_int("Enter Song ID: ");
                char title[MAX_TITLE_LEN];
                char artist[MAX_ARTIST_LEN];
                char genre[MAX_GENRE_LEN];
                read_string("Enter Song Title: ", title, sizeof(title));
                read_string("Enter Artist Name: ", artist, sizeof(artist));
                read_string("Enter Genre: ", genre, sizeof(genre));
                int duration = read_int("Enter Duration (in seconds): ");

                Song s = create_song(id, title, artist, genre, duration);
                cq_insert(&recent_queue, s);
                break;
            }

            case 6:
                cq_display(&recent_queue);
                break;

            case 7:
                load_sample_songs(&play_queue);
                break;

            case 0:
                printf("Exiting Music Management System (Review 1). Goodbye!\n");
                break;

            default:
                printf("Invalid choice (%d). Please select an option between 0 and 7.\n", choice);
                break;
        }
    } while (choice != 0);

    return 0;
}
