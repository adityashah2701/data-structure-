#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "../../../common/song.h"

#define HASH_TABLE_SIZE 11

/* Status of each hash table slot */
typedef enum {
    SLOT_EMPTY = 0,
    SLOT_OCCUPIED,
    SLOT_DELETED /* Tombstone indicating previously deleted item */
} SlotStatus;

/* Slot entry in the hash table */
typedef struct {
    Song song;
    SlotStatus status;
} HashSlot;

/*
 * Hash Table Structure
 * Uses array-based open addressing with linear probing and tombstones.
 * Key: Song ID (integer).
 */
typedef struct {
    HashSlot slots[HASH_TABLE_SIZE];
    int count;
} HashTable;

/* Function Declarations */
void ht_init(HashTable *ht);
int ht_hash(int song_id);
int ht_is_full(const HashTable *ht);
int ht_is_empty(const HashTable *ht);
int ht_insert(HashTable *ht, Song song);
Song* ht_search(HashTable *ht, int song_id, int *probes_count);
int ht_delete(HashTable *ht, int song_id);
void ht_display(const HashTable *ht);
int ht_count(const HashTable *ht);

#endif /* HASH_TABLE_H */
