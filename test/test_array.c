#include <string.h>
#include "minunit.h"
#include "array.h"

static Array *arr1 = NULL;
static Array *arr2 = NULL;
static Array *arr3 = NULL;

#define ARRAY_ELEMENT_EQ(arr, index, string) strcmp((char *) Array_get(arr, index), string) == 0

char * test_set_get() {
    arr1 = Array_init(4, 5);
    Array_set(arr1, 0, "helo"); 
    Array_set(arr1, 1, "chrs"); 
    Array_set(arr1, 2, "roey"); 
    Array_set(arr1, 3, "ches"); 
    mu_assert(ARRAY_ELEMENT_EQ(arr1, 0, "helo"), "Wrong value");
    mu_assert(ARRAY_ELEMENT_EQ(arr1, 1, "chrs"), "Wrong value");
    mu_assert(ARRAY_ELEMENT_EQ(arr1, 2, "roey"), "Wrong value");
    mu_assert(ARRAY_ELEMENT_EQ(arr1, 3, "ches"), "Wrong value");
    return NULL;
}

char * test_append() {
    Array_append(arr1, "five");
    mu_assert(ARRAY_ELEMENT_EQ(arr1, arr1->length - 1, "five"), "Wrong value");
    Array_append(arr1, "sixx");
    mu_assert(ARRAY_ELEMENT_EQ(arr1, arr1->length - 1, "sixx"), "Wrong value");
    Array_append(arr1, "sevn");
    mu_assert(ARRAY_ELEMENT_EQ(arr1, arr1->length - 1, "sevn"), "Wrong value");
    Array_append(arr1, "eiht");
    mu_assert(ARRAY_ELEMENT_EQ(arr1, arr1->length - 1, "eiht"), "Wrong value");

    mu_assert(ARRAY_ELEMENT_EQ(arr1, 4, "five"), "Wrong value");
    mu_assert(ARRAY_ELEMENT_EQ(arr1, 5, "sixx"), "Wrong value");
    mu_assert(ARRAY_ELEMENT_EQ(arr1, 6, "sevn"), "Wrong value");
    mu_assert(ARRAY_ELEMENT_EQ(arr1, 7, "eiht"), "Wrong value");

    Array_free(arr1);
    return NULL;
}

char * test_init_with_0() {
    arr2 = Array_init(0, 5);
    Array_append(arr2, "what");
    mu_assert(ARRAY_ELEMENT_EQ(arr2, arr2->length - 1, "what"), "Wrong value");
    Array_append(arr2, "wutt");
    mu_assert(ARRAY_ELEMENT_EQ(arr2, arr2->length - 1, "wutt"), "Wrong value");

    mu_assert(ARRAY_ELEMENT_EQ(arr2, 0, "what"), "Wrong value");
    mu_assert(ARRAY_ELEMENT_EQ(arr2, 1, "wutt"), "Wrong value");

    Array_free(arr2);
    return NULL;
}

char * str_test() {
    arr3 = Array_init(0, sizeof(char *));
    char *str1 = "foofoofoofoofoo";
    char *str2 = "bar";
    Array_append(arr3, &str1);
    Array_append(arr3, &str2);

    mu_assert(arr3->length == 2, "Wrong size");
    
    mu_assert(*((char **) Array_get(arr3, 0)) == str1, "Wrong value for arr[0]");
    mu_assert(*((char **) Array_get(arr3, 1)) == str2, "Wrong value for arr[1]");

    Array_free(arr3);
    return NULL;
}

char * resize_test() {
    Array *arr4 = Array_init(0, sizeof(char *)); // actually 4 elements
    char *str1 = "foo";
    int i;
    for (i = 0; i < 25; i++)
        Array_append(arr4, &str1);

    mu_assert(arr4->length == 25, "Wrong size");

    for (i = 0; i < 25; i++)
        mu_assert(*((char **) Array_get(arr4, i)) == str1, "Wrong value");
    return NULL;
}

char * all_tests() {
    mu_suite_start();
    mu_run_test(test_set_get);
    mu_run_test(test_append);
    mu_run_test(test_init_with_0);
    mu_run_test(str_test);
    mu_run_test(resize_test);
    return NULL;
}

RUN_TESTS(all_tests);
