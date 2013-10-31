#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

FILE *get_file(char *filename, char *mode) {
    FILE *ptr = NULL;
    if ((ptr = fopen(filename, mode)) == NULL) {
        perror(filename);
        exit(1);
    }
    return ptr;
}

void *smalloc(size_t size) {
    void *ptr = NULL;
    if ((ptr = malloc(size)) == NULL) {
        fprintf(stderr, "Unable to allocate sufficient memory");
        exit(1);
    }
    return ptr;
}

void *scalloc(size_t count, size_t size) {
    void *ptr = NULL;
    if ((ptr = calloc(count, size)) == NULL) {
        fprintf(stderr, "Unable to allocate sufficient memory");
        exit(1);
    }
    return ptr;
}

void *srealloc(void *ptr, size_t size) {
    void *ptr2; 
    if ((ptr2 = realloc(ptr, size)) == NULL) {
        fprintf(stderr, "Unable to allocate sufficient memory");
        exit(1);
    }
    return ptr2;
}

bool is_alphanumeric(char *str) {
    for (; *str != '\0'; str++)
        if (!isalnum(*str))
            return false;
    return true;
}

bool is_alpha(char *str) {
    for (; *str != '\0'; str++)
        if (!isalpha(*str))
            return false;
    return true;
}

int upper_power_of_2(int v) {
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}
