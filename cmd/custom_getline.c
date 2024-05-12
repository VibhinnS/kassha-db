#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "custom_getline.h" 


CUSTOM_SSIZE_T custom_getline(char **lineptr, size_t *n, FILE *stream) {
    size_t bufsize = 0;
    CUSTOM_SSIZE_T characters_read = 0;
    if (!lineptr || !n || !stream) {
        return -1;
    }

    if (*lineptr == NULL || *n == 0) {
        bufsize = BUFFER_SIZE;
        *lineptr = (char *)malloc(bufsize * sizeof(char));
        if(*lineptr == NULL) {
            return -1;
        }
        *n = bufsize;
    }

    char *ptr = *lineptr;
    int c;
    while ((c = fgetc(stream)) != EOF) {
        if (characters_read >= *n-1) {
            bufsize += BUFFER_SIZE;
            *lineptr = (char *)realloc(*lineptr, bufsize * sizeof(char));
            if (*lineptr == NULL) {
                return -1;
            }
            *n = bufsize;
            ptr = *lineptr + characters_read;
        }
        *ptr++ = c;
        characters_read++;
        if (c=='\n') {
            break;
        }
    }
    *ptr = '\0';

    return characters_read == 0 ? -1 : characters_read;
}
