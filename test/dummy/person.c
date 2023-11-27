#include "person.h"

#include <stdio.h>
#include <string.h>

const size_t people_len = 5;
person people[] = {
    {
        .id = 0,
        .fname = "Helen",
        .lname = "Wylie"
    },
    {
        .id = 1,
        .fname = "Angus",
        .lname = "Wylie"
    },
    {
        .id = 2,
        .fname = "Reuben",
        .lname = "Wylie"
    },
    {
        .id = 3,
        .fname = "Tracey",
        .lname = "Jones"
    },
    {
        .id = 4,
        .fname = "Samuel",
        .lname = "Wylie"
    }
};

person john_doe = {
    .fname = "John",
    .lname = "Doe"
};

bool person_equals(const person* a, const person* b)
{
    if (
        a->id != b->id ||
        0 != strncmp(a->fname, b->fname, 32) ||
        0 != strncmp(a->lname, b->lname, 32)
    ) {
        return false;
    }

    return true;
}

void person_print(const person* p)
{
    printf("%s %s\n", p->fname, p->lname);
}
