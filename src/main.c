#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/song.h"
#include "../common/input.h"
#include "data-structures/linear-queue/linear_queue.h"
#include "data-structures/circular-queue/circular_queue.h"
#include "data-structures/doubly-linked-list/playlist.h"
#include "data-structures/binary-search-tree/genre_bst.h"
#include "data-structures/hash-table/hash_table.h"

/* Preload a complete academic demonstration dataset across all five modules */
static void load_demonstration_dataset(HashTable *catalog,
                                       LinearQueue *queue,
                                       Playlist *playlist,
                                       BSTNode **bst_root) {
    Song dataset[] = {
        create_song(101, "Bohemian Rhapsody", "Queen", "Rock", 354),
        create_song(102, "Billie Jean", "Michael Jackson", "Pop", 294),
        create_song(103, "Hotel California", "Eagles", "Rock", 391),
        create_song(104, "Take Five", "Dave Brubeck", "Jazz", 324),
        create_song(105, "Shape of You", "Ed Sheeran", "Pop", 233),
        create_song(106, "Clair de Lune", "Claude Debussy", "Classical", 302),
        create_song(107, "Lose Yourself", "Eminem", "Hip-Hop", 326),
        /* Intentionally choose keys to demonstrate collisions in Hash Table with size 11 */
        /* 112 % 11 == 2 (collides with 101 % 11 == 2) */
        create_song(112, "Smells Like Teen Spirit", "Nirvana", "Grunge", 301)
    };
    int total = sizeof(dataset) / sizeof(dataset[0]);

    for (int i = 0; i < total; i++) {
        /* 1. Register in Hash Table Catalog */
        ht_insert(catalog, dataset[i]);

        /* 2. Categorize in Genre BST */
        *bst_root = bst_insert(*bst_root, dataset[i].genre);

        /* 3. Add to User Playlist (DLL) */
        playlist_add(playlist, dataset[i]);

        /* 4. Enqueue first 4 songs into Play Queue (Linear Queue) */
        if (i < 4) {
            lq_enqueue(queue, dataset[i]);
        }
    }

    printf("\n[SUCCESS] Preloaded %d songs across Hash Table, BST, Playlist, and Play Queue!\n", total);
    printf("Notice: Song ID 101 and Song ID 112 both hash to index 2 (101 %% 11 == 2, 112 %% 11 == 2).\n");
    printf("This showcases linear probing and collision resolution in the Hash Table.\n");
}

int main(void) {
    /* Five Fundamental Data Structures */
    HashTable catalog;
    LinearQueue play_queue;
    CircularQueue recent_queue;
    Playlist my_playlist;
    BSTNode *genre_root = NULL;

    ht_init(&catalog);
    lq_init(&play_queue);
    cq_init(&recent_queue);
    playlist_init(&my_playlist);

    int choice;
    do {
        printf("\n========================================================================\n");
        printf("           MUSIC MANAGEMENT SYSTEM - ACADEMIC REVIEW 3 (FINAL)          \n");
        printf("   Integrated: Linear Queue | Circular Queue | DLL | BST | Hash Table   \n");
        printf("========================================================================\n");
        printf(" [SONG CATALOG & HASH TABLE (Linear Probing & Tombstones)]\n");
        printf("   1. Register New Song (Inserts into Hash Table & Genre BST)\n");
        printf("   2. Search Song by ID in Hash Table (O(1) Lookup)\n");
        printf("   3. Delete Song by ID from Hash Table (Tombstone Deletion)\n");
        printf("   4. Display Hash Table Physical Layout (Slots, Probing, & Tombstones)\n");
        printf("\n [PLAY QUEUE - Linear Queue (FIFO)]\n");
        printf("   5. Enqueue Song into Play Queue\n");
        printf("   6. Dequeue Song from Play Queue\n");
        printf("   7. Play Next Song from Queue (Dequeue -> Add to Recently Played)\n");
        printf("   8. Display Play Queue\n");
        printf("\n [RECENTLY PLAYED - Circular Queue (Chronological, Wraparound)]\n");
        printf("   9. Display Recently Played History (Latest 5 Songs)\n");
        printf("\n [USER PLAYLIST - Doubly Linked List]\n");
        printf("  10. Add Song to Playlist\n");
        printf("  11. Remove Song from Playlist by ID\n");
        printf("  12. Display Playlist (Forward: Head -> Tail)\n");
        printf("  13. Display Playlist (Backward: Tail -> Head)\n");
        printf("  14. Show Active Song in Playlist\n");
        printf("  15. Navigate: Next Song in Playlist\n");
        printf("  16. Navigate: Previous Song in Playlist\n");
        printf("\n [GENRE CATEGORIES - Binary Search Tree]\n");
        printf("  17. Search Genre Category in BST\n");
        printf("  18. Display Genres: Inorder Traversal (Sorted Alphabetical)\n");
        printf("  19. Display Genres: Preorder Traversal\n");
        printf("  20. Display Genres: Postorder Traversal\n");
        printf("\n [ACADEMIC DEMONSTRATION]\n");
        printf("  21. Load Complete Demonstration Dataset\n");
        printf("   0. Exit & Free All Allocated Memory\n");
        printf("========================================================================\n");

        choice = read_int("Enter your choice (0-21): ");

        switch (choice) {
            /* 1. Register Song */
            case 1: {
                if (ht_is_full(&catalog)) {
                    printf("[ERROR] Catalog Hash Table is full (Max %d songs).\n", HASH_TABLE_SIZE);
                    break;
                }
                int id = read_int("Enter Unique Song ID: ");
                /* Check if ID already exists */
                if (ht_search(&catalog, id, NULL) != NULL) {
                    printf("[HASH ERROR] Song with ID %d already exists! Duplicate IDs are not allowed.\n", id);
                    break;
                }
                char title[MAX_TITLE_LEN], genre[MAX_GENRE_LEN];
                read_string("Enter Song Title: ", title, sizeof(title));
                read_string("Enter Genre Category: ", genre, sizeof(genre));

                Song s = create_song(id, title, "-", genre, 0);
                if (ht_insert(&catalog, s)) {
                    genre_root = bst_insert(genre_root, genre);
                    printf("[SUCCESS] Song '%s' (ID: %d) successfully registered in Catalog and Genre BST.\n",
                           s.title, s.id);
                }
                break;
            }

            /* 2. Search Song in Hash Table */
            case 2: {
                int id = read_int("Enter Song ID to search: ");
                int probes = 0;
                Song *found = ht_search(&catalog, id, &probes);
                if (found != NULL) {
                    printf("[HASH FOUND] Song found in %d probe(s)!\n  ", probes);
                    print_song(found);
                } else {
                    printf("[HASH NOT FOUND] Song with ID %d does not exist in catalog (Probed %d slots).\n",
                           id, probes);
                }
                break;
            }

            /* 3. Delete Song from Hash Table */
            case 3: {
                int id = read_int("Enter Song ID to delete: ");
                ht_delete(&catalog, id);
                break;
            }

            /* 4. Display Hash Table Layout */
            case 4:
                ht_display(&catalog);
                break;

            /* 5. Enqueue Song */
            case 5: {
                if (lq_is_full(&play_queue)) {
                    printf("[OVERFLOW ERROR] Play Queue is full (Max %d songs).\n", MAX_LINEAR_QUEUE);
                    break;
                }
                int id = read_int("Enter Song ID to enqueue: ");
                Song *found = ht_search(&catalog, id, NULL);
                if (found != NULL) {
                    lq_enqueue(&play_queue, *found);
                } else {
                    char title[MAX_TITLE_LEN];
                    printf("Note: Song ID %d is not yet registered in Catalog.\n", id);
                    read_string("Enter Song Title to enqueue directly: ", title, sizeof(title));
                    Song s = create_song(id, title, "-", "-", 0);
                    lq_enqueue(&play_queue, s);
                }
                break;
            }

            /* 6. Dequeue Song from Queue */
            case 6: {
                Song removed;
                if (lq_dequeue(&play_queue, &removed)) {
                    printf("Dequeued Song: ");
                    print_song(&removed);
                }
                break;
            }

            /* 7. Play Next Song from Queue */
            case 7: {
                Song playing;
                if (lq_dequeue(&play_queue, &playing)) {
                    printf("\n>>> NOW PLAYING FROM QUEUE: ");
                    print_song(&playing);
                    cq_insert(&recent_queue, playing);
                }
                break;
            }

            /* 8. Display Play Queue */
            case 8:
                lq_display(&play_queue);
                break;

            /* 9. Display Recently Played */
            case 9:
                cq_display(&recent_queue);
                break;

            /* 10. Add Song to Playlist */
            case 10: {
                int id = read_int("Enter Song ID to add to Playlist: ");
                Song *found = ht_search(&catalog, id, NULL);
                if (found != NULL) {
                    playlist_add(&my_playlist, *found);
                } else {
                    char title[MAX_TITLE_LEN], genre[MAX_GENRE_LEN];
                    printf("Note: Song ID %d not found in Catalog.\n", id);
                    read_string("Enter Song Title: ", title, sizeof(title));
                    read_string("Enter Genre Category: ", genre, sizeof(genre));
                    Song s = create_song(id, title, "-", genre, 0);
                    playlist_add(&my_playlist, s);
                    genre_root = bst_insert(genre_root, genre);
                }
                break;
            }

            /* 11. Remove Song from Playlist */
            case 11: {
                int id = read_int("Enter Song ID to remove from Playlist: ");
                playlist_remove_by_id(&my_playlist, id);
                break;
            }

            /* 12. Display Playlist Forward */
            case 12:
                playlist_display_forward(&my_playlist);
                break;

            /* 13. Display Playlist Backward */
            case 13:
                playlist_display_backward(&my_playlist);
                break;

            /* 14. Show Active Song */
            case 14: {
                Song *curr = playlist_get_current(&my_playlist);
                if (curr != NULL) {
                    printf(">>> Currently Selected Playlist Track: ");
                    print_song(curr);
                } else {
                    printf("Playlist is empty or no track currently active.\n");
                }
                break;
            }

            /* 15. Playlist Navigate Next */
            case 15: {
                Song *next_song = playlist_next(&my_playlist);
                if (next_song != NULL) {
                    printf("\n>>> PLAYING NEXT PLAYLIST TRACK: ");
                    print_song(next_song);
                    cq_insert(&recent_queue, *next_song);
                }
                break;
            }

            /* 16. Playlist Navigate Previous */
            case 16: {
                Song *prev_song = playlist_prev(&my_playlist);
                if (prev_song != NULL) {
                    printf("\n>>> PLAYING PREVIOUS PLAYLIST TRACK: ");
                    print_song(prev_song);
                    cq_insert(&recent_queue, *prev_song);
                }
                break;
            }

            /* 17. Search Genre in BST */
            case 17: {
                char genre[MAX_GENRE_NAME];
                read_string("Enter Genre Category to search: ", genre, sizeof(genre));
                BSTNode *found = bst_search(genre_root, genre);
                if (found != NULL) {
                    printf("[BST FOUND] Genre '%s' is present in catalog with %d registered track(s).\n",
                           found->genre, found->song_count);
                } else {
                    printf("[BST NOT FOUND] Genre '%s' is not in the catalog.\n", genre);
                }
                break;
            }

            /* 18. BST Inorder */
            case 18:
                printf("\n=== Genre Catalog (BST Inorder: Alphabetical Order) ===\n");
                if (genre_root == NULL) {
                    printf("  (No genres recorded)\n");
                } else {
                    bst_inorder(genre_root);
                }
                printf("========================================================\n");
                break;

            /* 19. BST Preorder */
            case 19:
                printf("\n=== Genre Catalog (BST Preorder Traversal) ===\n");
                if (genre_root == NULL) {
                    printf("  (No genres recorded)\n");
                } else {
                    bst_preorder(genre_root);
                }
                printf("==============================================\n");
                break;

            /* 20. BST Postorder */
            case 20:
                printf("\n=== Genre Catalog (BST Postorder Traversal) ===\n");
                if (genre_root == NULL) {
                    printf("  (No genres recorded)\n");
                } else {
                    bst_postorder(genre_root);
                }
                printf("===============================================\n");
                break;

            /* 21. Load Demonstration Dataset */
            case 21:
                load_demonstration_dataset(&catalog, &play_queue, &my_playlist, &genre_root);
                break;

            /* 0. Exit */
            case 0:
                printf("\nReleasing dynamically allocated memory (Playlist & BST)...\n");
                playlist_free(&my_playlist);
                bst_free(genre_root);
                printf("Exiting Music Management System. All resources cleanly released. Goodbye!\n");
                break;

            default:
                printf("Invalid choice (%d). Please enter a number between 0 and 21.\n", choice);
                break;
        }
    } while (choice != 0);

    return 0;
}
