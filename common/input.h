#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Clear any lingering characters in the input stream */
static inline void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* discard */
    }
}

/* Read a single line string safely using fgets, stripping trailing newline */
static inline void read_string(const char *prompt, char *buffer, int max_len) {
    if (prompt != NULL && prompt[0] != '\0') {
        printf("%s", prompt);
    }
    if (fgets(buffer, max_len, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    } else {
        buffer[0] = '\0';
    }
}

/* Read an integer safely from standard input, re-prompting on invalid format */
static inline int read_int(const char *prompt) {
    int val;
    char buffer[64];
    while (1) {
        if (prompt != NULL && prompt[0] != '\0') {
            printf("%s", prompt);
        }
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            return 0;
        }
        char *endptr;
        val = (int)strtol(buffer, &endptr, 10);
        if (endptr != buffer) {
            /* Skip trailing whitespace */
            while (*endptr == ' ' || *endptr == '\t' || *endptr == '\r' || *endptr == '\n') {
                endptr++;
            }
            if (*endptr == '\0') {
                return val;
            }
        }
        printf("Invalid input. Please enter a valid integer: ");
    }
}

#endif /* INPUT_H */
