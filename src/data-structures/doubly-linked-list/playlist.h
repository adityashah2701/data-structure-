#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "../../../common/song.h"

/*
 * Doubly Linked List Node
 * Stores a song and bidirectional links (prev and next).
 */
typedef struct PlaylistNode {
    Song song;
    struct PlaylistNode *prev;
    struct PlaylistNode *next;
} PlaylistNode;

/*
 * Playlist Structure using Doubly Linked List
 * Allows dynamic expansion, forward/backward traversal,
 * and current playback navigation.
 */
typedef struct {
    PlaylistNode *head;
    PlaylistNode *tail;
    PlaylistNode *current; /* Pointer to active song for navigation */
    int count;
} Playlist;

/* Function Declarations */
void playlist_init(Playlist *pl);
int playlist_is_empty(const Playlist *pl);
int playlist_add(Playlist *pl, Song song);
int playlist_remove_by_id(Playlist *pl, int song_id);
void playlist_display_forward(const Playlist *pl);
void playlist_display_backward(const Playlist *pl);
Song* playlist_get_current(const Playlist *pl);
Song* playlist_next(Playlist *pl);
Song* playlist_prev(Playlist *pl);
int playlist_set_current(Playlist *pl, int song_id);
void playlist_free(Playlist *pl);

#endif /* PLAYLIST_H */
