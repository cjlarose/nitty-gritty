#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "array.h"
#define INITIAL_CAPACITY 4

Array Array_init(int length, size_t data_length) {
    Array arr = malloc(sizeof(struct array));
    arr->data_length = data_length;
    arr->capacity = (length > 0) ? upper_power_of_2(length) : INITIAL_CAPACITY;
    arr->length = length;
    arr->start = calloc(arr->capacity, data_length);
    return arr;
}

void * Array_get(Array arr, int i) {
    assert(arr != NULL);
    assert(i < arr->length);
    return arr->start + arr->data_length * i;
}

void Array_set(Array arr, int i, void * element) {
    assert(arr != NULL);
    void * pos = arr->start + arr->data_length * i;
    memcpy(pos, element, arr->data_length);
}

void _Array_resize(Array arr) {
    int new_capacity = arr->capacity * 2;
    arr->start = realloc(arr->start, new_capacity);
    memset(arr->start + arr->capacity, 0, arr->capacity);
    arr->capacity = new_capacity;
}

void Array_append(Array arr, void * element) {
    assert(arr != NULL);
    if (arr->length == arr->capacity)
        _Array_resize(arr);
    arr->length++;
    Array_set(arr, arr->length - 1, element);
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

int main() {
    Array arr = Array_init(4, 5);
    Array_set(arr, 0, "helo"); 
    //Array_set(arr, 1, "chrs"); 
    //Array_set(arr, 2, "roey"); 
    //Array_set(arr, 3, "ches"); 
    printf("%s\n", (char *) Array_get(arr, 0));
    //printf("%s\n", (char *) Array_get(arr, 1));
    //printf("%s\n", (char *) Array_get(arr, 2));
    //printf("%s\n", (char *) Array_get(arr, 3));

    //Array_append(arr, "five");
    //Array_append(arr, "sixx");
    //Array_append(arr, "sevn");
    //Array_append(arr, "eiht");
    //printf("%s\n", (char *) Array_get(arr, 4));
    //printf("%s\n", (char *) Array_get(arr, 5));
    //printf("%s\n", (char *) Array_get(arr, 6));
    //printf("%s\n", (char *) Array_get(arr, 7));

    //Array arr2 = Array_init(0, 5);
    //Array_append(arr2, "what");
    //Array_append(arr2, "wutt");
    //printf("%s\n", (char *) Array_get(arr, 0));
    //printf("%s\n", (char *) Array_get(arr, 1));

    return 0;
}
