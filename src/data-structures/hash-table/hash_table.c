#include "hash_table.h"
#include <stdio.h>

/* Initialize all slots in the hash table */
void ht_init(HashTable *ht) {
    if (ht == NULL) {
        return;
    }
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        ht->slots[i].status = SLOT_EMPTY;
    }
    ht->count = 0;
}

/* Division hash function for integer Song ID */
int ht_hash(int song_id) {
    return (song_id % HASH_TABLE_SIZE + HASH_TABLE_SIZE) % HASH_TABLE_SIZE;
}

/* Check if the hash table has reached maximum capacity */
int ht_is_full(const HashTable *ht) {
    if (ht == NULL) {
        return 0;
    }
    return (ht->count >= HASH_TABLE_SIZE);
}

/* Check if the hash table is empty */
int ht_is_empty(const HashTable *ht) {
    if (ht == NULL) {
        return 1;
    }
    return (ht->count == 0);
}

/* Return the number of active songs in the table */
int ht_count(const HashTable *ht) {
    if (ht == NULL) {
        return 0;
    }
    return ht->count;
}

/*
 * Insert a song into the hash table.
 * Resolves collisions using linear probing and reuses tombstone slots.
 * Prevents insertion of duplicate Song IDs.
 */
int ht_insert(HashTable *ht, Song song) {
    if (ht == NULL) {
        return 0;
    }

    if (ht_is_full(ht)) {
        printf("[HASH OVERFLOW ERROR] Hash table is full! (Capacity: %d). Cannot insert song '%s' (ID: %d).\n",
               HASH_TABLE_SIZE, song.title, song.id);
        return 0;
    }

    int start_idx = ht_hash(song.id);
    int target_idx = -1;
    int first_tombstone = -1;

    /* Linear probe through the table */
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        int idx = (start_idx + i) % HASH_TABLE_SIZE;

        if (ht->slots[idx].status == SLOT_OCCUPIED) {
            if (ht->slots[idx].song.id == song.id) {
                printf("[HASH ERROR] Duplicate Song ID %d detected ('%s')! Cannot insert duplicate.\n",
                       song.id, ht->slots[idx].song.title);
                return 0;
            }
        } else if (ht->slots[idx].status == SLOT_DELETED) {
            /* Record first tombstone slot encountered for insertion */
            if (first_tombstone == -1) {
                first_tombstone = idx;
            }
        } else if (ht->slots[idx].status == SLOT_EMPTY) {
            /* Found an empty slot, stop probing */
            if (first_tombstone == -1) {
                target_idx = idx;
            }
            break;
        }
    }

    /* Prefer reusing the first tombstone slot if available */
    if (first_tombstone != -1) {
        target_idx = first_tombstone;
    }

    if (target_idx == -1) {
        printf("[HASH ERROR] No suitable slot found for Song ID %d.\n", song.id);
        return 0;
    }

    ht->slots[target_idx].song = song;
    ht->slots[target_idx].status = SLOT_OCCUPIED;
    ht->count++;

    if (target_idx != start_idx) {
        printf("[HASH COLLISION] Key %d hashed to Slot %d (occupied/tombstone). Probed and placed in Slot %d.\n",
               song.id, start_idx, target_idx);
    } else {
        printf("[HASH INSERT] Key %d directly placed in home Slot %d.\n", song.id, target_idx);
    }

    return 1;
}

/*
 * Search for a song by Song ID using linear probing.
 * Continues probing through tombstones and stops at empty slots.
 * Optionally records the number of probes performed.
 */
Song* ht_search(HashTable *ht, int song_id, int *probes_count) {
    if (ht == NULL) {
        return NULL;
    }

    int start_idx = ht_hash(song_id);
    int probes = 0;

    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        probes++;
        int idx = (start_idx + i) % HASH_TABLE_SIZE;

        if (ht->slots[idx].status == SLOT_EMPTY) {
            /* Key does not exist in table */
            break;
        }

        if (ht->slots[idx].status == SLOT_OCCUPIED && ht->slots[idx].song.id == song_id) {
            if (probes_count != NULL) {
                *probes_count = probes;
            }
            return &ht->slots[idx].song;
        }
        /* If SLOT_DELETED (tombstone), continue linear probing */
    }

    if (probes_count != NULL) {
        *probes_count = probes;
    }
    return NULL;
}

/*
 * Delete a song by Song ID from the hash table.
 * Replaces the slot with a TOMBSTONE marker (SLOT_DELETED)
 * to maintain linear probing continuity for previously collided items.
 */
int ht_delete(HashTable *ht, int song_id) {
    if (ht == NULL || ht_is_empty(ht)) {
        printf("[HASH ERROR] Cannot delete: Hash table is empty.\n");
        return 0;
    }

    int start_idx = ht_hash(song_id);

    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        int idx = (start_idx + i) % HASH_TABLE_SIZE;

        if (ht->slots[idx].status == SLOT_EMPTY) {
            /* Key not present */
            break;
        }

        if (ht->slots[idx].status == SLOT_OCCUPIED && ht->slots[idx].song.id == song_id) {
            ht->slots[idx].status = SLOT_DELETED;
            ht->count--;
            printf("[HASH TOMBSTONE] Song '%s' (ID: %d) at Slot %d marked as TOMBSTONE (Deleted).\n",
                   ht->slots[idx].song.title, song_id, idx);
            return 1;
        }
    }

    printf("[HASH ERROR] Song with ID %d not found in hash table.\n", song_id);
    return 0;
}

/* Display the physical hash table layout (slots, tombstones, and stored songs) */
void ht_display(const HashTable *ht) {
    if (ht == NULL) {
        return;
    }

    printf("\n=== Song Catalog Hash Table (Size: %d, Stored: %d) ===\n",
           HASH_TABLE_SIZE, ht->count);
    printf(" Slot | Status    | Song Details\n");
    printf("------+-----------+-------------------------------------------------\n");

    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        if (ht->slots[i].status == SLOT_EMPTY) {
            printf(" [%2d] | [EMPTY]   | ---\n", i);
        } else if (ht->slots[i].status == SLOT_DELETED) {
            printf(" [%2d] | [TOMBSTONE| (Previously: ID %d '%s')\n",
                   i, ht->slots[i].song.id, ht->slots[i].song.title);
        } else {
            int home = ht_hash(ht->slots[i].song.id);
            char flag[16] = "";
            if (home != i) {
                snprintf(flag, sizeof(flag), " (from %d)", home);
            }
            printf(" [%2d] | [OCCUPIED]%s ", i, flag);
            print_song(&ht->slots[i].song);
        }
    }
    printf("=================================================================\n");
}
