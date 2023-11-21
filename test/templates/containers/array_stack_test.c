#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../../dummy/person.h"

#include "./generated/array_stack_of_person.h"

void test_array_stack_of_xxx_push_and_pop()
{
    array_stack_of_person* stack = array_stack_of_person_create(people_len);
    if (NULL == stack) {
        fprintf(stderr, "array_stack_of_person_create() failed.");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < people_len; ++i) {
        bool res = stack->push(stack, people[i]);
        if (!res) {
            fprintf(stderr, "push() failed.");
            exit(EXIT_FAILURE);
        }
    }

    assert(people_len == stack->size);
    assert(people_len == stack->head + 1);

    for (size_t i = 0; i < people_len; ++i) {
        array_stack_optional_person res = stack->pop(stack);
        if (!res.has_value) {
            fprintf(stderr, "pop() failed.");
            exit(EXIT_FAILURE);
        }

        assert(person_equals(&people[people_len - i - 1], &res.value));
    }

    assert( 0 == stack->size);
    assert(-1 == stack->head);

    for (size_t i = 0; i < people_len; ++i) {
        bool res = stack->push(stack, people[i]);
        if (!res) {
            fprintf(stderr, "push() failed.");
            exit(EXIT_FAILURE);
        }
    }

    assert(people_len == stack->size);
    assert(people_len == stack->head + 1);

    for (size_t i = 0; i < people_len; ++i) {
        array_stack_optional_person res = stack->pop(stack);
        if (!res.has_value) {
            fprintf(stderr, "pop() failed.");
            exit(EXIT_FAILURE);
        }

        assert(person_equals(&people[people_len - i - 1], &res.value));
    }

    assert( 0 == stack->size);
    assert(-1 == stack->head);

    stack->destroy(stack);
}

void test_array_stack_of_xxx_overflow()
{
    array_stack_of_person* stack = array_stack_of_person_create(people_len);
    if (NULL == stack) {
        fprintf(stderr, "array_stack_of_person_create() failed.");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < people_len; ++i) {
        bool res = stack->push(stack, people[i]);
        if (!res) {
            fprintf(stderr, "push() failed.");
            exit(EXIT_FAILURE);
        }
    }

    bool res = stack->push(stack, john_doe);
    assert(!res);

    stack->destroy(stack);
}

void test_array_stack_of_xxx_underflow()
{
    array_stack_of_person* stack = array_stack_of_person_create(people_len);
    if (NULL == stack) {
        fprintf(stderr, "array_stack_of_person_create() failed.");
        exit(EXIT_FAILURE);
    }

    array_stack_optional_person res = stack->pop(stack);
    assert(!res.has_value);

    stack->destroy(stack);
}

static void dummy_destroy_person(person p)
{
    static size_t index = 0;

    assert(person_equals(&people[index], &p));

    index++;
}

void test_array_stack_of_xxx_destroy()
{
    array_stack_of_person* stack = array_stack_of_person_create(people_len);
    if (NULL == stack) {
        fprintf(stderr, "array_stack_of_person_create() failed.");
        exit(EXIT_FAILURE);
    }
    stack->destroy_data = &dummy_destroy_person;

    for (size_t i = 0; i < people_len; ++i) {
        bool res = stack->push(stack, people[i]);
        if (!res) {
            fprintf(stderr, "push() failed.");
            exit(EXIT_FAILURE);
        }
    }

    stack->destroy(stack);
}