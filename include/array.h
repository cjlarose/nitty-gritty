#ifndef _ARRAY_H_
#define _ARRAY_H_
#include <stdlib.h>
typedef struct Array {
    size_t data_length; // size in bytes of single element
    int length;         // current length of the virtual array
    int capacity;       // current length of real array
    void * start;       // ptr to start of real array
} Array;

/* Initialize a dynamic array that stores elements of size data_length */
void array_init(Array * arr, int length, size_t data_length);
Array *array_new(int length, size_t data_length);

/* Return the contents at index i */
void *array_get(Array *arr, int i);

/* Set the contents at index i to element */
void array_set(Array *arr, int i, void * element);

/* Add an element to the end of the array */
void array_append(Array *arr, void * element);

/* Double the size of the array */
void array_resize(Array *arr);

/* Free a dynamic array */
void array_free(Array *arr);
#endif
