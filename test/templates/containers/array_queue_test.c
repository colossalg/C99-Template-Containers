#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../../dummy/person.h"

#include "./generated/array_queue_of_person.h"

void test_array_queue_of_xxx_enqueue_and_dequeue()
{
    array_queue_of_person* queue = array_queue_of_person_create(people_len);
    if (NULL == queue) {
        fprintf(stderr, "array_queue_of_person_create() failed.");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < people_len; ++i) {
        bool res = queue->enqueue(queue, people[i]);
        if (!res) {
            fprintf(stderr, "enqueue() failed.");
            exit(EXIT_FAILURE);
        }
    }

    assert(queue->size == people_len);
    assert(queue->head == 0);
    assert(queue->tail == people_len);

    for (size_t i = 0; i < people_len; ++i) {
        array_queue_optional_person res = queue->dequeue(queue);
        if (!res.has_value) {
            fprintf(stderr, "dequeue() failed.");
            exit(EXIT_FAILURE);
        }

        assert(person_equals(&people[i], &res.value));
    }

    assert(queue->size == 0);
    assert(queue->head == people_len);
    assert(queue->tail == people_len);

    for (size_t i = 0; i < people_len; ++i) {
        bool res = queue->enqueue(queue, people[i]);
        if (!res) {
            fprintf(stderr, "enqueue() failed.");
            exit(EXIT_FAILURE);
        }
    }

    assert(queue->size == people_len);
    assert(queue->head == people_len);
    assert(queue->tail == people_len - 1);

    for (size_t i = 0; i < people_len; ++i) {
        array_queue_optional_person res = queue->dequeue(queue);
        if (!res.has_value) {
            fprintf(stderr, "dequeue() failed.");
            exit(EXIT_FAILURE);
        }

        assert(person_equals(&people[i], &res.value));
    }

    assert(queue->size == 0);
    assert(queue->head == people_len - 1);
    assert(queue->tail == people_len - 1);

    queue->destroy(queue);
}

void test_array_queue_of_xxx_overflow()
{
    array_queue_of_person* queue = array_queue_of_person_create(people_len);
    if (NULL == queue) {
        fprintf(stderr, "array_queue_of_person_create() failed.");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < people_len; ++i) {
        bool res = queue->enqueue(queue, people[i]);
        if (!res) {
            fprintf(stderr, "enqueue() failed.");
            exit(EXIT_FAILURE);
        }
    }

    bool res = queue->enqueue(queue, john_doe);
    assert(!res);

    queue->destroy(queue);
}

void test_array_queue_of_xxx_underflow()
{
    array_queue_of_person* queue = array_queue_of_person_create(people_len);
    if (NULL == queue) {
        fprintf(stderr, "array_queue_of_person_create() failed.");
        exit(EXIT_FAILURE);
    }

    array_queue_optional_person res = queue->dequeue(queue);
    assert(!res.has_value);

    queue->destroy(queue);
}

static void dummy_destroy_person(person p)
{
    static size_t index = 0;

    assert(person_equals(&people[index], &p));

    index++;
}

void test_array_queue_of_xxx_destroy()
{
    array_queue_of_person* queue = array_queue_of_person_create(people_len);
    if (NULL == queue) {
        fprintf(stderr, "array_queue_of_person_create() failed.");
        exit(EXIT_FAILURE);
    }
    queue->destroy_data = &dummy_destroy_person;

    for (size_t i = 0; i < people_len; ++i) {
        bool res = queue->enqueue(queue, people[i]);
        if (!res) {
            fprintf(stderr, "enqueue() failed.");
            exit(EXIT_FAILURE);
        }
    }

    queue->destroy(queue);
}