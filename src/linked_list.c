#include <stdlib.h>
#include <stdbool.h>
#include "linked_list.h"
#include "utils.h"

void list_prepend(struct linked_list **list, void *datum) {
    struct linked_list *new_list = smalloc(sizeof(struct linked_list));
    new_list->datum = datum;
    new_list->next = *list;
    *list = new_list;
};

void list_free(struct linked_list *list) {
    struct linked_list *node = list;
    while (node != NULL) {
        struct linked_list *tmp = node->next;
        free(node);
        node = tmp;
    }
}

struct linked_list *list_min(struct linked_list *list, int (*cmp)(void *, void *)) {
    if (list == NULL)
        return NULL;
    struct linked_list *min = list;
    struct linked_list *node = list->next;
    while (node != NULL) {
        if (cmp(node->datum, min->datum) < 0)
            min = node;
        node = node->next;
    }
    return min;
}

void list_remove(struct linked_list **list, struct linked_list *node) {
    struct linked_list **tmp = list;
    while (*tmp != NULL) {
        if (*tmp == node) {
            struct linked_list *next = (*tmp)->next;
            free(*tmp);
            *tmp = next;
            return;
        }
        tmp = &(*tmp)->next;
    }
}

void *list_sort(struct linked_list *list, int(*cmp)(void *, void *)) {
    struct linked_list *ptr1, *ptr2;
    void *tmp;
    for (ptr1 = list; ptr1 != NULL; ptr1 = ptr1->next) {
        for (ptr2 = ptr1->next; ptr2 != NULL; ptr2 = ptr2->next) {
            if (cmp(ptr1->datum, ptr2->datum) > 0) {
                tmp = ptr1->datum;
                ptr1->datum = ptr2->datum;
                ptr2->datum = tmp;
            }
        }
    }
    return NULL;
}

void *list_find(struct linked_list *list, void *needle, bool(*eq)(void *, void *)) {
    struct linked_list *ptr = list;
    for (; ptr != NULL; ptr = ptr->next)
        if (eq(needle, ptr->datum))
            return ptr;
    return NULL;
}

int list_length(struct linked_list *list) {
    int c = 0;
    struct linked_list *ptr = list;
    for (; ptr != NULL; ptr = ptr->next, c++);
    return c;
}

void list_apply(struct linked_list *list, void(*fn)(void *)) {
    struct linked_list *ptr = list;
    for (; ptr != NULL; ptr = ptr->next)
        fn(ptr->datum);
}

void **list_to_array(struct linked_list *list) {
    int len = list_length(list);
    void **arr = smalloc(len * sizeof(void *));
    struct linked_list *ptr = list;
    int i;
    for (i = 0; ptr != NULL; ptr = ptr->next, i++)
        arr[i] = ptr->datum;
    return arr;
}

int list_index_of(struct linked_list *list, void *needle) {
    struct linked_list *ptr = list;
    int i;
    for (i = 0; ptr != NULL; ptr = ptr->next, i++)
        if (ptr->datum == needle)
            return i;
    return -1;
}
