#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "custom_getline.h"


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
        fflush(stdout);
        read_input(input_buffer);

        if (strcmp(input_buffer->buffer, ".exit")==0) {
            close_input_buffer(input_buffer);
            exit(EXIT_SUCCESS);
        } else {
            printf("Unrecognized command - %s", input_buffer-> buffer);
        }
    }
}