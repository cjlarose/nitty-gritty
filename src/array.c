#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "array.h"
#include "utils.h"
#define INITIAL_CAPACITY 4

void array_init(Array *arr, int length, size_t data_length) {
    arr->data_length = data_length;
    arr->capacity = (length > 0) ? upper_power_of_2(length) : INITIAL_CAPACITY;
    arr->length = length;
    arr->start = calloc(arr->capacity, data_length);
}

Array *array_new(int length, size_t data_length) {
    Array *arr = malloc(sizeof(Array));
    array_init(arr, length, data_length);
    return arr;
}

void *array_get(Array *arr, int i) {
    assert(arr != NULL);
    assert(i < arr->length);
    return arr->start + arr->data_length * i;
}

void array_set(Array *arr, int i, void * element) {
    assert(arr != NULL);
    void * pos = arr->start + arr->data_length * i;
    memcpy(pos, element, arr->data_length);
}

void array_resize(Array *arr) {
    int new_capacity = arr->capacity * 2;
    arr->start = realloc(arr->start, new_capacity * arr->data_length);
    memset(arr->start + arr->capacity * arr->data_length, 0, arr->capacity * arr->data_length);
    arr->capacity = new_capacity;
}

void array_append(Array *arr, void * element) {
    assert(arr != NULL);
    if (arr->length == arr->capacity)
        array_resize(arr);
    arr->length++;
    array_set(arr, arr->length - 1, element);
}

void array_free(Array *arr) {
    free(arr->start);
}
