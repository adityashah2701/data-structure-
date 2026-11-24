#ifndef SONG_H
#define SONG_H

#include <stdio.h>
#include <string.h>

#define MAX_TITLE_LEN 64
#define MAX_ARTIST_LEN 64
#define MAX_GENRE_LEN 32

/* Structure representing a Song in the system */
typedef struct {
    int id;
    char title[MAX_TITLE_LEN];
    char artist[MAX_ARTIST_LEN];
    char genre[MAX_GENRE_LEN];
    int duration; /* Duration in seconds */
} Song;

/* Helper function to construct a Song object */
static inline Song create_song(int id, const char *title, const char *artist, const char *genre, int duration) {
    Song s;
    s.id = id;
    strncpy(s.title, title, MAX_TITLE_LEN - 1);
    s.title[MAX_TITLE_LEN - 1] = '\0';
    strncpy(s.artist, (artist != NULL) ? artist : "-", MAX_ARTIST_LEN - 1);
    s.artist[MAX_ARTIST_LEN - 1] = '\0';
    strncpy(s.genre, (genre != NULL) ? genre : "-", MAX_GENRE_LEN - 1);
    s.genre[MAX_GENRE_LEN - 1] = '\0';
    s.duration = duration;
    return s;
}

/* Helper function to display song details cleanly */
static inline void print_song(const Song *s) {
    if (s == NULL) {
        return;
    }
    /* If full metadata is present (like in preloaded sample tracks), show formatted details */
    if (s->duration > 0 && strcmp(s->artist, "-") != 0 && s->artist[0] != '\0') {
        int minutes = s->duration / 60;
        int seconds = s->duration % 60;
        printf("[ID: %3d] %-22s | Artist: %-16s | Genre: %-10s | %d:%02d\n",
               s->id, s->title, s->artist, s->genre, minutes, seconds);
    } else if (s->genre[0] != '\0' && strcmp(s->genre, "-") != 0) {
        printf("[ID: %3d] %-22s | Genre: %-10s\n", s->id, s->title, s->genre);
    } else {
        printf("[ID: %3d] %-22s\n", s->id, s->title);
    }
}

#endif /* SONG_H */
