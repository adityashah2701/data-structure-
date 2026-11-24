#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <string.h>

/*
 * Clear leftover characters (like the Enter key '\n') from the keyboard buffer.
 * In C, scanf leaves '\n' in the input stream; this loop cleans it up.
 */
static inline void clear_buffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        /* Discard characters until newline or end of file */
    }
}

/*
 * Read an integer from the user.
 * 1. Prints the prompt (e.g., "Enter Song ID: ").
 * 2. Reads the number using standard scanf.
 * 3. Clears the trailing Enter key so future inputs work cleanly.
 */
static inline int read_int(const char *prompt) {
    int value = 0;
    printf("%s", prompt);
    if (scanf("%d", &value) != 1) {
        clear_buffer();
        return 0;
    }
    clear_buffer();
    return value;
}

/*
 * Read a string (including spaces, e.g. "Bohemian Rhapsody").
 * 1. Prints the prompt (e.g., "Enter Song Title: ").
 * 2. Uses fgets to safely read up to 'size' characters without buffer overflow.
 * 3. Replaces the trailing '\n' with '\0' (null terminator).
 */
static inline void read_string(const char *prompt, char *str, int size) {
    printf("%s", prompt);
    if (fgets(str, size, stdin) != NULL) {
        int len = (int)strlen(str);
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
        }
    } else {
        str[0] = '\0';
    }
}

#endif /* INPUT_H */
