#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "map.h"
#include "minunit.h"

#define TABLE_EQ(table, key, value) (strcmp((char *) *(map_find(table, key)), value) == 0)

unsigned long long int str_hash(void *ptr) {
    char *str = (char *) ptr;
    long int h = 0;  
    for (; *str != '\0'; str++) {
        h = (h << 4) + *str;
        long int g = h & 0xF0000000L;
        if (g != 0)
            h ^= g >> 24;
        h &= ~g;
    }
    return h;
}

bool str_eq(void *ptr1, void *ptr2) {
    return strcmp((char *) ptr1, (char *) ptr2) == 0;
}

void print_kv(void *ptr1, void **ptr2, void *info) {
    printf("%s => %s\n", (char *) ptr1, (char *) *ptr2);
}

struct map *my_map = NULL;
char **args = NULL;

char * test_init() {
    my_map = map_new(&str_hash, &str_eq, 4);
    mu_assert(my_map->size == 4, "Incorrect size");
    return NULL;
}

char * test_insert() {
    map_insert(my_map, "one", "two");
    map_insert(my_map, "three", "four");
    map_insert(my_map, "five", "six");
    map_insert(my_map, "seven", "eight");
    map_insert(my_map, "nine", "ten");
    map_insert(my_map, "nine", "potato");
    return NULL;
}

char * test_insert_alpha() {
    args = malloc(26 * sizeof(char *));
    int j;
    for (j = 0; j < 26; j++) {
        char *str = calloc(2, sizeof(char));
        str[0] = j + 65;
        args[j] = str;
        map_insert(my_map, str, str);
    }
    return NULL;
}

char * test_find() {
    mu_assert(TABLE_EQ(my_map, "one", "two"), "Wrong value");
    mu_assert(TABLE_EQ(my_map, "three", "four"), "Wrong value");
    mu_assert(TABLE_EQ(my_map, "five", "six"), "Wrong value");
    mu_assert(TABLE_EQ(my_map, "seven", "eight"), "Wrong value");
    mu_assert(TABLE_EQ(my_map, "nine", "potato"), "Wrong value");
    return NULL;
}

char * test_apply() {
    map_apply(my_map, &print_kv, NULL);
    return NULL;
}

char * test_remove() {
    struct map* map = map_new(&str_hash, &str_eq, 4);
    map_insert(map, "one", "1");
    map_insert(map, "two", "2");
    map_insert(map, "three", "3");

    map_delete(map, "one", NULL);
    map_delete(map, "two", NULL);

    mu_assert(map_find(map, "one") == NULL, "One not deleted");
    mu_assert(map_find(map, "two") == NULL, "Two not deleted");
    mu_assert(map_find(map, "three") != NULL, "Three deleted");

    map_free(map, NULL);
    free(map);
    return NULL;
}

char *all_tests() {
    mu_suite_start();
    mu_run_test(test_init);
    mu_run_test(test_insert);
    mu_run_test(test_insert_alpha);
    mu_run_test(test_find);
    mu_run_test(test_apply);
    mu_run_test(test_remove);

    map_free(my_map, NULL);
    free(my_map);

    int j;
    for (j = 0; j < 26; j++)
        free(args[j]);
    free(args);

    return NULL;
}

RUN_TESTS(all_tests);
