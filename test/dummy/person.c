#include "person.h"

#include <stdio.h>
#include <string.h>

const size_t people_len = 5;
person people[] = {
    {
        .fname = "Helen",
        .lname = "Wylie"
    },
    {
        .fname = "Angus",
        .lname = "Wylie"
    },
    {
        .fname = "Reuben",
        .lname = "Wylie"
    },
    {
        .fname = "Tracey",
        .lname = "Jones"
    },
    {
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
