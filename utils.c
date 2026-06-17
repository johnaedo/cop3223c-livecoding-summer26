#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

char * input(char *prompt, int buffer_size) {

    char *data = malloc(sizeof(char) * (buffer_size));
    // Eat the newline if it's there from a prior scanf call

    printf("%s: ", prompt);

    // 1. Read the line safely
    if (fgets(data, buffer_size+1, stdin) != NULL) {

        // 2. Check if the newline character is in the string
        char *newline = strchr(data, '\n');

        if (newline) {
            // Newline found, replace it with a null terminator to clean up the string
            *newline = '\0';
        } else {
            // No newline found! This means the user typed more than BUFFER_SIZE - 1.
            // We need to FLUSH the remaining characters from the stdin buffer.
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {
                /* Intentional empty loop body to discard extra characters */
            }
        }

        // 3. Use the clean input
        printf("returning: [%s]\n", data);
        return data;
    }

    return NULL;
}
