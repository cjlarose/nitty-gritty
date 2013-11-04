#ifndef _HASH_MAP_H_
#define _HASH_MAP_H_
#include <stdbool.h>

typedef unsigned long long int(*hash_fn)(void *hashable);

struct map_node {
    void *key;
    void *value;
};

struct map {
    hash_fn hash_fn;
    bool(*key_eq)(void *, void*);
    struct linked_list **entries; // list of map_nodes
    int size; // size of values[]
    int m; // modulo number
    int split_index;
};

void map_init(struct map *map, hash_fn hash_fn, bool(*key_eq)(void *, void *), int initial_size);
struct map *map_new(hash_fn hash_fn, bool(*key_eq)(void *, void *), int initial_size);

void map_insert(struct map *map, void *key, void *val);

void **map_find(struct map *map, void *key);
bool map_delete(struct map *map, void *key, void(*free_fn)(void *, void*));

void map_free(struct map *map, void(*free_fn)(void *, void *));

void map_apply(struct map *map, void(*fn)(void *, void **));
#endif
