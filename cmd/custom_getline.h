#ifndef CUSTOM_GETLINE_H
#define CUSTOM_GETLINE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <basetsd.h>
#define BUFFER_SIZE 1024
typedef SSIZE_T CUSTOM_SSIZE_T;
#else
#include <unistd.h>
#endif

CUSTOM_SSIZE_T custom_getline(char **lineptr, size_t *n, FILE *stream);

#endif
