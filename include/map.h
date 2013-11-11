#ifndef _HASH_MAP_H_
#define _HASH_MAP_H_
#include <stdbool.h>

typedef unsigned long long int(*hash_fn)(void *hashable);

typedef struct MapNode {
    void *key;
    void *value;
} MapNode;

typedef struct Map {
    hash_fn hash_fn;
    bool(*key_eq)(void *, void*);
    struct linked_list **entries; // list of map_nodes
    int size; // size of values[]
    int m; // modulo number
    int split_index;
} Map;

void map_init(Map *map, hash_fn hash_fn, bool(*key_eq)(void *, void *), int initial_size);
Map *map_new(hash_fn hash_fn, bool(*key_eq)(void *, void *), int initial_size);

void map_insert(Map *map, void *key, void *val);

void **map_find(Map *map, void *key);
bool map_delete(Map *map, void *key, void(*free_fn)(void *, void*));

void map_free(Map *map, void(*free_fn)(void *, void *));

void map_apply(Map *map, void(*fn)(void *k, void **v, void *info), void *info);
#endif
