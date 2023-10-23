#ifndef COLOSSALG_LINKED_LIST_H
#define COLOSSALG_LINKED_LIST_H

#include <stdbool.h>
#include <stdlib.h>

#define DECLARE_LINKED_LIST_T(typename)                                                         \
                                                                                                \
    struct list_of_##typename;                                                                  \
    struct list_of_##typename##_item;                                                           \
                                                                                                \
    typedef struct list_of_##typename list_of_##typename;                                       \
    typedef struct list_of_##typename##_item list_of_##typename##_item;                         \
                                                                                                \
    struct list_of_##typename {                                                                 \
        size_t size;                                                                            \
        list_of_##typename##_item* head;                                                        \
        list_of_##typename##_item* tail;                                                        \
                                                                                                \
        bool (*insert_at_head)(list_of_##typename* list, typename data);                        \
        void (*remove_head)(list_of_##typename* list);                                          \
        bool (*insert_at_tail)(list_of_##typename* list, typename data);                        \
        void (*remove_tail)(list_of_##typename* list);                                          \
        bool (*insert_before)(list_of_##typename##_item* item, typename data);                  \
        bool (*insert_after)(list_of_##typename##_item* item, typename data);                   \
        void (*remove)(list_of_##typename##_item* item);                                        \
        void (*clear)(list_of_##typename* list);                                                \
        void (*destroy)(list_of_##typename* list);                                              \
                                                                                                \
        void (*destroy_data)(typename data);                                                    \
    };                                                                                          \
                                                                                                \
    struct list_of_##typename##_item {                                                          \
        list_of_##typename* list;                                                               \
        typename data;                                                                          \
        list_of_##typename##_item* prev;                                                        \
        list_of_##typename##_item* next;                                                        \
    };                                                                                          \
                                                                                                \
    list_of_##typename* list_of_##typename##_create();                                          \

#define DEFINE_LINKED_LIST_T(typename)                                                          \
                                                                                                \
    list_of_##typename##_item* list_of_##typename##_item_create(                                \
        typename data,                                                                          \
        list_of_##typename* list,                                                               \
        list_of_##typename##_item* prev,                                                        \
        list_of_##typename##_item* next                                                         \
    ) {                                                                                         \
        list_of_##typename##_item* item = malloc(sizeof(list_of_##typename##_item));            \
        if (NULL == item) {                                                                     \
            return NULL;                                                                        \
        }                                                                                       \
                                                                                                \
        item->list = list;                                                                      \
        item->data = data;                                                                      \
        item->prev = prev;                                                                      \
        item->next = next;                                                                      \
                                                                                                \
        return item;                                                                            \
    }                                                                                           \
                                                                                                \
    bool list_of_##typename##_insert_at_head(list_of_##typename* list, typename data)           \
    {                                                                                           \
        list_of_##typename##_item* new_head =                                                   \
            list_of_##typename##_item_create(data, list, NULL, list->head);                     \
        if (NULL == new_head) {                                                                 \
            return false;                                                                       \
        }                                                                                       \
                                                                                                \
        if (0 == list->size) {                                                                  \
            list->head = new_head;                                                              \
            list->tail = new_head;                                                              \
        } else {                                                                                \
            list->head->prev = new_head;                                                        \
            list->head = new_head;                                                              \
        }                                                                                       \
        list->size++;                                                                           \
                                                                                                \
        return true;                                                                            \
    }                                                                                           \
                                                                                                \
    void list_of_##typename##_remove_head(list_of_##typename* list)                             \
    {                                                                                           \
        if (0 == list->size) {                                                                  \
            return;                                                                             \
        }                                                                                       \
                                                                                                \
        list_of_##typename##_item* old_head = list->head;                                       \
                                                                                                \
        if (1 == list->size) {                                                                  \
            list->head = NULL;                                                                  \
            list->tail = NULL;                                                                  \
        } else {                                                                                \
            list->head = old_head->next;                                                        \
            list->head->prev = NULL;                                                            \
        }                                                                                       \
        list->size--;                                                                           \
                                                                                                \
        list->destroy_data(old_head->data);                                                     \
        free(old_head);                                                                         \
    }                                                                                           \
                                                                                                \
    bool list_of_##typename##_insert_at_tail(list_of_##typename* list, typename data)           \
    {                                                                                           \
        list_of_##typename##_item* new_tail =                                                   \
            list_of_##typename##_item_create(data, list, list->tail, NULL);                     \
        if (NULL == new_tail) {                                                                 \
            return false;                                                                       \
        }                                                                                       \
                                                                                                \
        if (0 == list->size) {                                                                  \
            list->head = new_tail;                                                              \
            list->tail = new_tail;                                                              \
        } else {                                                                                \
            list->tail->next = new_tail;                                                        \
            list->tail = new_tail;                                                              \
        }                                                                                       \
        list->size++;                                                                           \
                                                                                                \
        return true;                                                                            \
    }                                                                                           \
                                                                                                \
    void list_of_##typename##_remove_tail(list_of_##typename* list)                             \
    {                                                                                           \
        if (0 == list->size) {                                                                  \
            return;                                                                             \
        }                                                                                       \
                                                                                                \
        list_of_##typename##_item* old_tail = list->tail;                                       \
                                                                                                \
        if (1 == list->size) {                                                                  \
            list->head = NULL;                                                                  \
            list->tail = NULL;                                                                  \
        } else {                                                                                \
            list->tail = old_tail->prev;                                                        \
            list->tail->next = NULL;                                                            \
        }                                                                                       \
        list->size--;                                                                           \
                                                                                                \
        list->destroy_data(old_tail->data);                                                     \
        free(old_tail);                                                                         \
    }                                                                                           \
                                                                                                \
    bool list_of_##typename##_insert_before(list_of_##typename##_item* item, typename data)     \
    {                                                                                           \
        if (NULL == item) {                                                                     \
            return false;                                                                       \
        }                                                                                       \
                                                                                                \
        list_of_##typename* list = item->list;                                                  \
                                                                                                \
        if (list->head == item) {                                                               \
            return list->insert_at_head(list, data);                                            \
        }                                                                                       \
                                                                                                \
        list_of_##typename##_item* new_item =                                                   \
            list_of_##typename##_item_create(data, list, item->prev, item);                     \
        if (NULL == new_item) {                                                                 \
            return false;                                                                       \
        }                                                                                       \
                                                                                                \
        item->prev->next = new_item;                                                            \
        item->prev = new_item;                                                                  \
                                                                                                \
        list->size++;                                                                           \
                                                                                                \
        return new_item;                                                                        \
    }                                                                                           \
                                                                                                \
    bool list_of_##typename##_insert_after(list_of_##typename##_item* item, typename data)      \
    {                                                                                           \
        if (NULL == item) {                                                                     \
            return false;                                                                       \
        }                                                                                       \
                                                                                                \
        list_of_##typename* list = item->list;                                                  \
                                                                                                \
        if (list->tail == item) {                                                               \
            return list->insert_at_tail(list, data);                                            \
        }                                                                                       \
                                                                                                \
        list_of_##typename##_item* new_item =                                                   \
            list_of_##typename##_item_create(data, list, item, item->next);                     \
        if (NULL == new_item) {                                                                 \
            return false;                                                                       \
        }                                                                                       \
                                                                                                \
        item->next->prev = new_item;                                                            \
        item->next = new_item;                                                                  \
                                                                                                \
        list->size++;                                                                           \
                                                                                                \
        return new_item;                                                                        \
    }                                                                                           \
                                                                                                \
    void list_of_##typename##_remove(list_of_##typename##_item* item)                           \
    {                                                                                           \
        if (NULL == item) {                                                                     \
            return;                                                                             \
        }                                                                                       \
                                                                                                \
        list_of_##typename* list = item->list;                                                  \
                                                                                                \
        if (list->head == item) {                                                               \
            list->remove_head(list);                                                            \
            return;                                                                             \
        }                                                                                       \
        if (list->tail == item) {                                                               \
            list->remove_tail(list);                                                            \
            return;                                                                             \
        }                                                                                       \
                                                                                                \
        item->prev->next = item->next;                                                          \
        item->next->prev = item->prev;                                                          \
                                                                                                \
        list->size--;                                                                           \
                                                                                                \
        list->destroy_data(item->data);                                                         \
        free(item);                                                                             \
    }                                                                                           \
                                                                                                \
    void list_of_##typename##_clear(list_of_##typename* list)                                   \
    {                                                                                           \
        list_of_##typename##_item* item = list->head;                                           \
        while (NULL != item) {                                                                  \
            list_of_##typename##_item* next = item->next;                                       \
            list->destroy_data(item->data);                                                     \
            free(item);                                                                         \
            item = next;                                                                        \
        }                                                                                       \
                                                                                                \
        list->size = 0;                                                                         \
        list->head = NULL;                                                                      \
        list->tail = NULL;                                                                      \
    }                                                                                           \
                                                                                                \
    void list_of_##typename##_destroy(list_of_##typename* list)                                 \
    {                                                                                           \
        list->clear(list);                                                                      \
        free(list);                                                                             \
    }                                                                                           \
                                                                                                \
    void list_of_##typename##_destroy_data_default(typename data) {}                            \
                                                                                                \
    list_of_##typename* list_of_##typename##_create()                                           \
    {                                                                                           \
        list_of_##typename* list = malloc(sizeof(list_of_##typename));                          \
        if (NULL == list) {                                                                     \
            return NULL;                                                                        \
        }                                                                                       \
                                                                                                \
        list->size = 0;                                                                         \
        list->head = NULL;                                                                      \
        list->tail = NULL;                                                                      \
                                                                                                \
        list->insert_at_head = &list_of_##typename##_insert_at_head;                            \
        list->remove_head = &list_of_##typename##_remove_head;                                  \
        list->insert_at_tail = &list_of_##typename##_insert_at_tail;                            \
        list->remove_tail = &list_of_##typename##_remove_tail;                                  \
        list->insert_before = &list_of_##typename##_insert_before;                              \
        list->insert_after = &list_of_##typename##_insert_after;                                \
        list->remove = &list_of_##typename##_remove;                                            \
        list->clear = &list_of_##typename##_clear;                                              \
        list->destroy = &list_of_##typename##_destroy;                                          \
                                                                                                \
        list->destroy_data = &list_of_##typename##_destroy_data_default;                        \
                                                                                                \
        return list;                                                                            \
    }                                                                                           \

#endif // COLOSSALG_SINGLE_LINKED_LIST_H
