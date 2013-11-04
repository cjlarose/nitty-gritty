#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_
#include <stdbool.h>
typedef struct linked_list {
    void *datum;
    struct linked_list *next;   
} list;

void list_prepend(struct linked_list **list, void *datum);

void list_free(struct linked_list *list);

struct linked_list *list_min(struct linked_list *list, int (*cmp)(void *, void *));

void list_remove(struct linked_list **list, struct linked_list *node);

void *list_sort(struct linked_list *list, int(*cmp)(void *, void *));

struct linked_list *list_find(struct linked_list *list, bool(*eq)(void *));

int list_length(struct linked_list *list);

void list_apply(struct linked_list *list, void(*fn)(void *));

void **list_to_array(struct linked_list *list);

int list_index_of(struct linked_list *list, void *needle);
#endif
