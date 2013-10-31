#ifndef _UTILS_H
#define _UTILS_H
#include <stdbool.h>
#include <stdio.h>
FILE *get_file(char *filename, char *mode);
void *smalloc(size_t size);
void *scalloc(size_t count, size_t size);
void *srealloc(void *ptr, size_t size);
bool is_alphanumeric(char *str);
bool is_alpha(char *str);
int upper_power_of_2(int v);
#endif
