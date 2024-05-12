#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


//check if client is Windows based or not
#ifdef _WIN32
#include <basetsd.h>
#define BUFFER_SIZE 1024;
typedef SSIZE_T ssize_t;
#else
#include <unistd.h>
#endif

typedef struct
{
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
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

ssize_t fgets(char **lineptr, size_t *n, FILE *stream);

int main(int argc, char* argv[]) {
    InputBuffer* input_buffer = new_input_buffer();
    while (true) {
        print_prompt();
        read_input(input_buffer);

        if (strcmp(input_buffer->buffer, ".exit")==0) {
            close_input_buffer(input_buffer);
            exit(EXIT_SUCCESS);
        } else {
            printf("Unrecognized command - '%s' .\n", input_buffer-> buffer);
        }
    }
}