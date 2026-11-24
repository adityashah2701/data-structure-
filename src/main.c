#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/song.h"
#include "../common/input.h"
#include "data-structures/linear-queue/linear_queue.h"
#include "data-structures/circular-queue/circular_queue.h"
#include "data-structures/doubly-linked-list/playlist.h"
#include "data-structures/binary-search-tree/genre_bst.h"

/* Preload sample data across all Review 2 data structures for testing and viva demonstration */
static void load_sample_data(LinearQueue *lq, Playlist *pl, BSTNode **bst_root) {
    Song samples[] = {
        create_song(101, "Bohemian Rhapsody", "Queen", "Rock", 354),
        create_song(102, "Billie Jean", "Michael Jackson", "Pop", 294),
        create_song(103, "Hotel California", "Eagles", "Rock", 391),
        create_song(104, "Take Five", "Dave Brubeck", "Jazz", 324),
        create_song(105, "Shape of You", "Ed Sheeran", "Pop", 233),
        create_song(106, "Clair de Lune", "Claude Debussy", "Classical", 302),
        create_song(107, "Lose Yourself", "Eminem", "Hip-Hop", 326)
    };
    int n = sizeof(samples) / sizeof(samples[0]);

    for (int i = 0; i < n; i++) {
        /* Add first 4 songs to Queue */
        if (i < 4) {
            lq_enqueue(lq, samples[i]);
        }
        /* Add all to Playlist */
        playlist_add(pl, samples[i]);
        /* Insert genres into BST */
        *bst_root = bst_insert(*bst_root, samples[i].genre);
    }
    printf("\n[SUCCESS] Sample data loaded across Queue (4 songs), Playlist (7 songs), and Genre BST.\n");
}

int main(void) {
    LinearQueue play_queue;
    CircularQueue recent_queue;
    Playlist my_playlist;
    BSTNode *genre_root = NULL;

    lq_init(&play_queue);
    cq_init(&recent_queue);
    playlist_init(&my_playlist);

    int choice;
    do {
        printf("\n======================================================\n");
        printf("       MUSIC MANAGEMENT SYSTEM - ACADEMIC REVIEW 2    \n");
        printf("======================================================\n");
        printf(" [LINEAR QUEUE - Play Queue]\n");
        printf("   1. Enqueue Song to Play Queue\n");
        printf("   2. Dequeue Song from Play Queue\n");
        printf("   3. Play Next Song from Queue (Dequeue -> Recently Played)\n");
        printf("   4. Display Play Queue\n");
        printf("\n [CIRCULAR QUEUE - Recently Played]\n");
        printf("   5. Display Recently Played History (Chronological, Max 5)\n");
        printf("\n [DOUBLY LINKED LIST - Playlist Management]\n");
        printf("   6. Add Song to Playlist\n");
        printf("   7. Remove Song from Playlist by ID\n");
        printf("   8. Display Playlist (Forward: Head -> Tail)\n");
        printf("   9. Display Playlist (Backward: Tail -> Head)\n");
        printf("  10. Show Current Playing Song in Playlist\n");
        printf("  11. Next Song in Playlist\n");
        printf("  12. Previous Song in Playlist\n");
        printf("\n [BINARY SEARCH TREE - Genre Categories]\n");
        printf("  13. Insert Genre into BST\n");
        printf("  14. Search Genre in BST\n");
        printf("  15. Display Genres: Inorder Traversal (Sorted Alphabetical)\n");
        printf("  16. Display Genres: Preorder Traversal\n");
        printf("  17. Display Genres: Postorder Traversal\n");
        printf("\n [UTILITY]\n");
        printf("  18. Load Sample Data (Queue, Playlist, and Genres)\n");
        printf("   0. Exit & Clean Memory\n");
        printf("======================================================\n");

        choice = read_int("Enter your choice (0-18): ");

        switch (choice) {
            /* Linear Queue */
            case 1: {
                if (lq_is_full(&play_queue)) {
                    printf("[OVERFLOW ERROR] Play Queue is full (Max %d songs).\n", MAX_LINEAR_QUEUE);
                    break;
                }
                int id = read_int("Enter Song ID: ");
                char title[MAX_TITLE_LEN];
                read_string("Enter Song Title: ", title, sizeof(title));

                Song s = create_song(id, title, "-", "-", 0);
                lq_enqueue(&play_queue, s);
                break;
            }

            case 2: {
                Song removed;
                if (lq_dequeue(&play_queue, &removed)) {
                    printf("Dequeued Song: ");
                    print_song(&removed);
                }
                break;
            }

            case 3: {
                Song playing;
                if (lq_dequeue(&play_queue, &playing)) {
                    printf(">>> Now Playing from Queue: ");
                    print_song(&playing);
                    cq_insert(&recent_queue, playing);
                }
                break;
            }

            case 4:
                lq_display(&play_queue);
                break;

            /* Circular Queue */
            case 5:
                cq_display(&recent_queue);
                break;

            /* Doubly Linked List */
            case 6: {
                int id = read_int("Enter Song ID: ");
                char title[MAX_TITLE_LEN], genre[MAX_GENRE_LEN];
                read_string("Enter Song Title: ", title, sizeof(title));
                read_string("Enter Genre Category: ", genre, sizeof(genre));

                Song s = create_song(id, title, "-", genre, 0);
                playlist_add(&my_playlist, s);
                /* Automatically register genre in BST */
                genre_root = bst_insert(genre_root, genre);
                break;
            }

            case 7: {
                int id = read_int("Enter Song ID to remove from playlist: ");
                playlist_remove_by_id(&my_playlist, id);
                break;
            }

            case 8:
                playlist_display_forward(&my_playlist);
                break;

            case 9:
                playlist_display_backward(&my_playlist);
                break;

            case 10: {
                Song *curr = playlist_get_current(&my_playlist);
                if (curr != NULL) {
                    printf(">>> Current Playing Track in Playlist: ");
                    print_song(curr);
                } else {
                    printf("Playlist is empty or no track currently selected.\n");
                }
                break;
            }

            case 11: {
                Song *next_song = playlist_next(&my_playlist);
                if (next_song != NULL) {
                    printf(">>> Moved to Next Track: ");
                    print_song(next_song);
                    cq_insert(&recent_queue, *next_song);
                }
                break;
            }

            case 12: {
                Song *prev_song = playlist_prev(&my_playlist);
                if (prev_song != NULL) {
                    printf(">>> Moved to Previous Track: ");
                    print_song(prev_song);
                    cq_insert(&recent_queue, *prev_song);
                }
                break;
            }

            /* Binary Search Tree */
            case 13: {
                char genre[MAX_GENRE_NAME];
                read_string("Enter Genre Name to insert: ", genre, sizeof(genre));
                if (genre[0] != '\0') {
                    genre_root = bst_insert(genre_root, genre);
                }
                break;
            }

            case 14: {
                char genre[MAX_GENRE_NAME];
                read_string("Enter Genre Name to search: ", genre, sizeof(genre));
                BSTNode *found = bst_search(genre_root, genre);
                if (found != NULL) {
                    printf("[BST FOUND] Genre '%s' exists in catalog with %d song(s).\n",
                           found->genre, found->song_count);
                } else {
                    printf("[BST NOT FOUND] Genre '%s' is not in the catalog.\n", genre);
                }
                break;
            }

            case 15:
                printf("\n=== Genre Directory (Inorder: Alphabetical) ===\n");
                if (genre_root == NULL) {
                    printf("  (No genres added yet)\n");
                } else {
                    bst_inorder(genre_root);
                }
                printf("===============================================\n");
                break;

            case 16:
                printf("\n=== Genre Directory (Preorder Traversal) ===\n");
                if (genre_root == NULL) {
                    printf("  (No genres added yet)\n");
                } else {
                    bst_preorder(genre_root);
                }
                printf("============================================\n");
                break;

            case 17:
                printf("\n=== Genre Directory (Postorder Traversal) ===\n");
                if (genre_root == NULL) {
                    printf("  (No genres added yet)\n");
                } else {
                    bst_postorder(genre_root);
                }
                printf("=============================================\n");
                break;

            case 18:
                load_sample_data(&play_queue, &my_playlist, &genre_root);
                break;

            case 0:
                printf("Cleaning up dynamically allocated memory...\n");
                playlist_free(&my_playlist);
                bst_free(genre_root);
                printf("Exiting Music Management System (Review 2). Goodbye!\n");
                break;

            default:
                printf("Invalid choice (%d). Please enter a number between 0 and 18.\n", choice);
                break;
        }
    } while (choice != 0);

    return 0;
}
