#ifndef ARRAY
#define ARRAY
#include <stdlib.h>
typedef struct Array {
    size_t data_length; // size in bytes of single element
    int length;         // current length of the virtual array
    int capacity;       // current length of real array
    void * start;       // ptr to start of real array
} Array;

/* Initialize a dynamic array that stores elements of size data_length */
Array *Array_init(int length, size_t data_length);

/* Return the contents at index i */
void *Array_get(Array *arr, int i);

/* Set the contents at index i to element */
void Array_set(Array *arr, int i, void * element);

/* Add an element to the end of the array */
void Array_append(Array *arr, void * element);

/* Free a dynamic array */
void Array_free(Array *arr);
#endif
