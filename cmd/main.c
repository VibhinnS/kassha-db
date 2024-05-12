#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


//check if client is Windows based or not
#ifdef _WIN32
#include <basetsd.h>
#define BUFFER_SIZE 1024;
typedef SSIZE_T CUSTOM_SSIZE_T;
#else
#include <unistd.h>
#endif

typedef struct
{
    char* buffer;
    size_t buffer_length;
    CUSTOM_SSIZE_T input_length;
} InputBuffer;

InputBuffer* new_input_buffer() {
    InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;

    return input_buffer;
}

void print_prompt() {
    printf("db > ");
}

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

void read_input(InputBuffer* input_buffer) {
    CUSTOM_SSIZE_T bytes_read = 
        custom_getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

    if (bytes_read <= 0) {
        printf("Error reading input \n");
        exit(EXIT_FAILURE);
    }

    if (input_buffer->buffer[bytes_read-1]=='\n') {
        input_buffer->buffer[bytes_read-1] = '\0';
    }
}

void close_input_buffer(InputBuffer* input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}

int main(int argc, char* argv[]) {
    InputBuffer* input_buffer = new_input_buffer();
    while (true) {
        print_prompt();
        read_input(input_buffer);

        if (strcmp(input_buffer->buffer, ".exit")==0) {
            close_input_buffer(input_buffer);
            exit(EXIT_SUCCESS);
        } else {
            printf("Unrecognized command - %s", input_buffer-> buffer);
        }
    }
}