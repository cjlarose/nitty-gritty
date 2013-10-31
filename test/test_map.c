#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "map.h"
#include "minunit.h"

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

void print_kv(void *ptr1, void **ptr2) {
    printf("%s => %s\n", (char *) ptr1, (char *) *ptr2);
}

struct map *my_map = NULL;
char **args = NULL;

char * test_init() {
    my_map = map_new(&str_hash, &str_eq, 4);
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
    char *keys[] = {"one", "three", "five", "seven", "nine"};

    int i;
    for (i = 0; i < 5; i++) {
        char *value = (char *) *(map_find(my_map, keys[i]));
        printf("%s\n", value);
    }
    return NULL;
}

char * test_apply() {
    map_apply(my_map, &print_kv);
    return NULL;
}

char *all_tests() {
    mu_suite_start();
    mu_run_test(test_init);
    mu_run_test(test_insert);
    mu_run_test(test_insert_alpha);
    mu_run_test(test_find);
    mu_run_test(test_apply);

    map_free(my_map, NULL);

    int j;
    for (j = 0; j < 26; j++)
        free(args[j]);
    free(args);
    return NULL;
}

RUN_TESTS(all_tests);
