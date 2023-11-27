#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../../dummy/person.h"

#include "./generated/data_structures.h"

list_of_person* create_populated_list_of_person()
{
    list_of_person* list = list_of_person_create();
    if (NULL == list) {
        fprintf(stderr, "list_of_person_create() failed.");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < people_len; ++i) {
        bool res = list->insert_at_tail(list, people[i]);
        if (!res) {
            fprintf(stderr, "insert_at_tail() failed.");
            exit(EXIT_FAILURE);
        }
    }

    return list;
}

void test_list_of_xxx_insert_at_head()
{
    list_of_person* list = list_of_person_create();
    if (NULL == list) {
        fprintf(stderr, "list_of_person_create() failed.");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < people_len; ++i) {
        bool res = list->insert_at_head(list, people[i]);
        if (!res) {
            fprintf(stderr, "insert_at_head() failed.");
            exit(EXIT_FAILURE);
        }
    }

    assert(people_len == list->size);
    assert(NULL != list->head);
    assert(NULL != list->tail);

    list_of_person_item* item = list->tail;
    for (size_t i = 0; i < people_len; ++i) {
        //person_print(&item->data);
        assert(person_equals(&people[i], &item->data));
        item = item->prev;
    }

    list->destroy(list);
}

void test_list_of_xxx_insert_at_tail()
{
    list_of_person* list = list_of_person_create();
    if (NULL == list) {
        fprintf(stderr, "list_of_person_create() failed.");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < people_len; ++i) {
        bool res = list->insert_at_tail(list, people[i]);
        if (!res) {
            fprintf(stderr, "insert_at_tail() failed.");
            exit(EXIT_FAILURE);
        }
    }

    assert(people_len == list->size);
    assert(NULL != list->head);
    assert(NULL != list->tail);

    list_of_person_item* item = list->head;
    for (size_t i = 0; i < people_len; ++i) {
        //person_print(&item->data);
        assert(person_equals(&people[i], &item->data));
        item = item->next;
    }

    list->destroy(list);
}

void test_list_of_xxx_insert_before_head()
{
    list_of_person* list = create_populated_list_of_person();

    list_of_person_item* old_head = list->head;

    bool res = list->insert_before(list->head, john_doe);
    if (!res) {
        fprintf(stderr, "insert_before() failed.");
        exit(EXIT_FAILURE);
    }

    assert(people_len + 1 == list->size);

    list_of_person_item* new_item = list->head;

    assert(new_item->prev == NULL);
    assert(new_item->next == old_head && new_item->next->prev == new_item);

    assert(person_equals(&john_doe, &new_item->data));

    list->destroy(list);
}

void test_list_of_xxx_insert_before_tail()
{
    list_of_person* list = create_populated_list_of_person();

    list_of_person_item* tail_old_prev = list->tail->prev;

    bool res = list->insert_before(list->tail, john_doe);
    if (!res) {
        fprintf(stderr, "insert_before() failed.");
        exit(EXIT_FAILURE);
    }

    assert(people_len + 1 == list->size);

    list_of_person_item* new_item = list->tail->prev;

    assert(new_item->prev == tail_old_prev  && new_item->prev->next == new_item);
    assert(new_item->next == list->tail     && new_item->next->prev == new_item);

    assert(person_equals(&john_doe, &new_item->data));

    list->destroy(list);
}

void test_list_of_xxx_insert_after_head()
{
    list_of_person* list = create_populated_list_of_person();

    list_of_person_item* head_old_next = list->head->next;

    bool res = list->insert_after(list->head, john_doe);
    if (!res) {
        fprintf(stderr, "insert_after() failed.");
        exit(EXIT_FAILURE);
    }

    assert(people_len + 1 == list->size);

    list_of_person_item* new_item = list->head->next;

    assert(new_item->prev == list->head     && new_item->prev->next == new_item);
    assert(new_item->next == head_old_next  && new_item->next->prev == new_item);

    assert(person_equals(&john_doe, &new_item->data));

    list->destroy(list);
}

void test_list_of_xxx_insert_after_tail()
{
    list_of_person* list = create_populated_list_of_person();

    list_of_person_item* old_tail = list->tail;

    bool res = list->insert_after(list->tail, john_doe);
    if (!res) {
        fprintf(stderr, "insert_after() failed.");
        exit(EXIT_FAILURE);
    }

    assert(people_len + 1 == list->size);

    list_of_person_item* new_item = list->tail;

    assert(new_item->prev == old_tail && new_item->prev->next == new_item);
    assert(new_item->next == NULL);

    assert(person_equals(&john_doe, &new_item->data));

    list->destroy(list);
}

void test_list_of_xxx_remove_head()
{
    list_of_person* list = create_populated_list_of_person();

    list_of_person_item* old_head_next = list->head->next;

    list->remove_head(list, true);

    assert(people_len - 1 == list->size);

    assert(list->head == old_head_next);
    assert(NULL == old_head_next->prev);

    assert(person_equals(&people[1], &old_head_next->data));

    list->destroy(list);
}

void test_list_of_xxx_remove_tail()
{
    list_of_person* list = create_populated_list_of_person();

    list_of_person_item* old_tail_prev = list->tail->prev;

    list->remove_tail(list, true);

    assert(people_len - 1 == list->size);

    assert(list->tail == old_tail_prev);
    assert(NULL == old_tail_prev->next);

    assert(person_equals(&people[people_len - 2], &old_tail_prev->data));

    list->destroy(list);
}

void test_list_of_xxx_remove()
{
    list_of_person* list = create_populated_list_of_person();

    list_of_person_item* item = list->head;
    for (size_t i = 0; i < people_len / 2; ++i) {
        item = item->next;
    }

    list_of_person_item* old_prev = item->prev;
    list_of_person_item* old_next = item->next;

    list->remove(item, true);

    assert(people_len - 1 == list->size);

    assert(old_next == item->prev->next);
    assert(old_prev == item->next->prev);
}

static void dummy_destroy_person(person p)
{
    static size_t index = 0;

    assert(person_equals(&people[index], &p));

    index++;
}

void test_list_of_xxx_clear()
{
    list_of_person* list = create_populated_list_of_person();
    list->destroy_data = &dummy_destroy_person;

    list->clear(list);

    list->destroy(list);
}
