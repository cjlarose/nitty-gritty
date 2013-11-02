#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "map.h"
#include "linked_list.h"
#include "utils.h"
/*
 * Hashmap implementation based on an implementation I wrote in Java for CSC 
 * 345, which was based on slides written by Prof. Bonki Moon, University of 
 * Arizona, which were likely based on a textbook description of an algorithm 
 * originally described by Withold Litwin in 1980 and later popularized by 
 * Paul Larson. 
 */

/* 
 * map_new(hash_fn, key_eq, size) initializes a new map.  hash_fn must take
 * a pointer to a key and return the hash of that key.  key_eq must take two
 * keys and return true iff the two keys should be considered equal. The map
 * will initialize have size size, but will dynamically increase as 
 * necessary.
 */
struct map *map_new(hash_fn hash_fn, bool(*key_eq)(void *, void *), 
    int initial_size) {
    struct map *new_map = smalloc(sizeof(struct map));
    new_map->hash_fn = hash_fn;
    new_map->key_eq = key_eq;
    new_map->entries = scalloc(initial_size, sizeof(struct linked_list *));
    new_map->size = initial_size;
    new_map->m = initial_size;
    new_map->split_index = 0;
    return new_map;
}

void **_map_find_in_nodes(struct map *map, struct linked_list *list_node, void *key) {
    for (; list_node != NULL; list_node = list_node->next) {
        struct map_node *node = (struct map_node *) list_node->datum;
        if (map->key_eq(node->key, key))
            return &node->value;
    }
    return NULL;
}

/*
 * _map_insert(map, index, value) will attempt to insert the value into the 
 * map at the index.  Returns true iff the insertion was successful (the key 
 * wasn't already defined).  Sets the value of collision to true iff a collsion
 * occured during insertion.
 */
bool _map_set(struct map *map, int index, struct map_node *node, bool *collision) {
    bool collision_occured = true;
    struct linked_list *keys = map->entries[index];
    if (keys == NULL)
        collision_occured = false;
    else if (_map_find_in_nodes(map, keys, node->key) != NULL)
        return false;

    if (collision != NULL)
        *collision = collision_occured;

    list_prepend(&map->entries[index], node);
    return true;
}

/*
 * map_ensure_capacity(map, capacity) will increase the value table of map if 
 * it is less than capacity. Shamelessly uses realloc against Dr. Debray's
 * coding standards.
 */
void _map_ensure_capacity(struct map *map, int capacity) {
    int i, new_size;
    if (map->size < capacity) {
        new_size = map->size * 2;
        map->entries = srealloc(
            map->entries, 
            new_size * sizeof(struct linked_list *)
        );
        for (i = map->size; i < new_size; i++)
            map->entries[i] = NULL;
        map->size = new_size;
    }
}

/*
 * map_rehash_keys(map, i, m) will rehash all the keys at index i using
 * modulus m
 */
void _map_rehash_keys(struct map *map, int index, int m) {
    struct linked_list *keys = map->entries[index];
    map->entries[index] = NULL;
    struct linked_list *next;
    for(; keys != NULL; keys = next) {
        next = keys->next;
        struct map_node *node = (struct map_node *) keys->datum;
        _map_set(map, map->hash_fn(node->key) % m, node, NULL);
        free(keys);
    }
}

struct map_node *map_node_new(void *key, void *value) {
    struct map_node *node = smalloc(sizeof(struct map_node));
    node->key = key;
    node->value = value;
    return node;
}

/*
 * map_insert(map, k, v) associates a given key in a map with a value v. If 
 * there is already a value defined for that key, the value is overwritten. 
 */
void map_insert(struct map *map, void *key, void *val) {
    unsigned long long int hash = map->hash_fn(key);
    int index = hash % map->m;
    if (index < map->split_index)
        index = hash % (map->m << 1);

    bool collision;
    struct map_node *node = map_node_new(key, val);
    if (_map_set(map, index, node, &collision)) {
        if (collision) {
            _map_ensure_capacity(map, map->m + map->split_index + 1);
            _map_rehash_keys(map, map->split_index, map-> m << 1);
            map->split_index++;
            if (map->split_index == map->m) {
                map->split_index = 0;
                map->m <<= 1;
            }
        }
    } else 
        free(node);
}

void **map_find(struct map *map, void *key) {
    unsigned long long int hash = map->hash_fn(key);
    int index = hash % map->m;
    if (index < map->split_index)
        index = hash % (map->m << 1);

    struct linked_list *keys = map->entries[index];
    if (keys != NULL)
        return _map_find_in_nodes(map, keys, key);
    return NULL;
}

void map_free(struct map *map, void(*free_fn)(void *, void *)) {
    int i;
    struct linked_list *next;
    for (i = 0; i < map->size; i++) {
        struct linked_list *list_nodes = map->entries[i];
        for (; list_nodes != NULL; list_nodes = next) {
            struct map_node *map_node = (struct map_node *) list_nodes->datum;
            if (free_fn != NULL)
                free_fn(map_node->key, map_node->value);
            free(map_node);
            next = list_nodes->next;
            free(list_nodes);
        }
    }
    free(map->entries);
    free(map);    
}

void map_apply(struct map *map, void(*fn)(void *, void **)) {
    int i;
    for (i = 0; i < map->size; i++) {
        struct linked_list *list_nodes = map->entries[i];
        for (; list_nodes != NULL; list_nodes = list_nodes->next) {
            struct map_node *map_node = (struct map_node *) list_nodes->datum;
            fn(map_node->key, &map_node->value);
        }
    }
}
