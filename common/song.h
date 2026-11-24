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
    strncpy(s.artist, artist, MAX_ARTIST_LEN - 1);
    s.artist[MAX_ARTIST_LEN - 1] = '\0';
    strncpy(s.genre, genre, MAX_GENRE_LEN - 1);
    s.genre[MAX_GENRE_LEN - 1] = '\0';
    s.duration = duration;
    return s;
}

/* Helper function to display song details */
static inline void print_song(const Song *s) {
    if (s == NULL) {
        return;
    }
    int minutes = s->duration / 60;
    int seconds = s->duration % 60;
    printf("[ID: %3d] %-22s | Artist: %-16s | Genre: %-12s | %d:%02d\n",
           s->id, s->title, s->artist, s->genre, minutes, seconds);
}

#endif /* SONG_H */
