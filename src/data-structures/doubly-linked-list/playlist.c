#include "playlist.h"
#include <stdio.h>
#include <stdlib.h>

/* Initialize the empty playlist */
void playlist_init(Playlist *pl) {
    if (pl == NULL) {
        return;
    }
    pl->head = NULL;
    pl->tail = NULL;
    pl->current = NULL;
    pl->count = 0;
}

/* Check if the playlist is empty */
int playlist_is_empty(const Playlist *pl) {
    if (pl == NULL) {
        return 1;
    }
    return (pl->head == NULL);
}

/* Add a song to the end of the playlist */
int playlist_add(Playlist *pl, Song song) {
    if (pl == NULL) {
        return 0;
    }

    PlaylistNode *new_node = (PlaylistNode *)malloc(sizeof(PlaylistNode));
    if (new_node == NULL) {
        printf("[MEMORY ERROR] Failed to allocate memory for playlist song.\n");
        return 0;
    }

    new_node->song = song;
    new_node->next = NULL;
    new_node->prev = pl->tail;

    if (pl->tail != NULL) {
        pl->tail->next = new_node;
    } else {
        /* List was empty, new node is also head */
        pl->head = new_node;
    }

    pl->tail = new_node;

    /* If no song is currently selected, point current to this song */
    if (pl->current == NULL) {
        pl->current = new_node;
    }

    pl->count++;
    printf("[PLAYLIST SUCCESS] Added '%s' to playlist. (Total: %d songs)\n",
           song.title, pl->count);
    return 1;
}

/* Remove a song from the playlist by its unique Song ID */
int playlist_remove_by_id(Playlist *pl, int song_id) {
    if (pl == NULL || pl->head == NULL) {
        printf("[PLAYLIST ERROR] Cannot remove: Playlist is empty.\n");
        return 0;
    }

    PlaylistNode *curr = pl->head;
    while (curr != NULL && curr->song.id != song_id) {
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("[PLAYLIST ERROR] Song with ID %d not found in playlist.\n", song_id);
        return 0;
    }

    /* Update current pointer if the active song is the one being removed */
    if (pl->current == curr) {
        if (curr->next != NULL) {
            pl->current = curr->next;
        } else {
            pl->current = curr->prev;
        }
    }

    /* Unlink from previous node */
    if (curr->prev != NULL) {
        curr->prev->next = curr->next;
    } else {
        /* curr was head */
        pl->head = curr->next;
    }

    /* Unlink from next node */
    if (curr->next != NULL) {
        curr->next->prev = curr->prev;
    } else {
        /* curr was tail */
        pl->tail = curr->prev;
    }

    printf("[PLAYLIST SUCCESS] Removed song '%s' (ID: %d) from playlist.\n",
           curr->song.title, curr->song.id);

    free(curr);
    pl->count--;
    return 1;
}

/* Display playlist forwards (from Head to Tail) */
void playlist_display_forward(const Playlist *pl) {
    if (pl == NULL || pl->head == NULL) {
        printf("--- Playlist is empty ---\n");
        return;
    }

    printf("\n=== Playlist (Forward Traversal: Head -> Tail, %d songs) ===\n", pl->count);
    PlaylistNode *curr = pl->head;
    int index = 1;
    while (curr != NULL) {
        const char *active_tag = (curr == pl->current) ? " [CURRENT]" : "          ";
        printf("  %2d.%s ", index++, active_tag);
        print_song(&curr->song);
        curr = curr->next;
    }
    printf("============================================================\n");
}

/* Display playlist backwards (from Tail to Head) */
void playlist_display_backward(const Playlist *pl) {
    if (pl == NULL || pl->tail == NULL) {
        printf("--- Playlist is empty ---\n");
        return;
    }

    printf("\n=== Playlist (Backward Traversal: Tail -> Head, %d songs) ===\n", pl->count);
    PlaylistNode *curr = pl->tail;
    int index = pl->count;
    while (curr != NULL) {
        const char *active_tag = (curr == pl->current) ? " [CURRENT]" : "          ";
        printf("  %2d.%s ", index--, active_tag);
        print_song(&curr->song);
        curr = curr->prev;
    }
    printf("=============================================================\n");
}

/* Return pointer to the currently playing song */
Song* playlist_get_current(const Playlist *pl) {
    if (pl == NULL || pl->current == NULL) {
        return NULL;
    }
    return &pl->current->song;
}

/* Navigate to the next song in the playlist */
Song* playlist_next(Playlist *pl) {
    if (pl == NULL || pl->current == NULL) {
        printf("[NAV ERROR] Playlist is empty.\n");
        return NULL;
    }
    if (pl->current->next == NULL) {
        printf("[NAV NOTICE] Already at the end of the playlist.\n");
        return NULL;
    }
    pl->current = pl->current->next;
    return &pl->current->song;
}

/* Navigate to the previous song in the playlist */
Song* playlist_prev(Playlist *pl) {
    if (pl == NULL || pl->current == NULL) {
        printf("[NAV ERROR] Playlist is empty.\n");
        return NULL;
    }
    if (pl->current->prev == NULL) {
        printf("[NAV NOTICE] Already at the beginning of the playlist.\n");
        return NULL;
    }
    pl->current = pl->current->prev;
    return &pl->current->song;
}

/* Set current pointer to a specific song by ID */
int playlist_set_current(Playlist *pl, int song_id) {
    if (pl == NULL || pl->head == NULL) {
        return 0;
    }
    PlaylistNode *curr = pl->head;
    while (curr != NULL) {
        if (curr->song.id == song_id) {
            pl->current = curr;
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}

/* Free all nodes in the playlist to prevent memory leaks */
void playlist_free(Playlist *pl) {
    if (pl == NULL) {
        return;
    }
    PlaylistNode *curr = pl->head;
    while (curr != NULL) {
        PlaylistNode *next = curr->next;
        free(curr);
        curr = next;
    }
    pl->head = NULL;
    pl->tail = NULL;
    pl->current = NULL;
    pl->count = 0;
}
