#ifndef COLOSSALG_TESTING_PERSON_H
#define COLOSSALG_TESTING_PERSON_H

#include <stdbool.h>
#include <stddef.h>

typedef struct person {
    char fname[32];
    char lname[32];
} person;

extern const size_t people_len;
extern person people[];

extern person john_doe;

bool person_equals(const person* a, const person* b);
void person_print(const person* p);

#endif // COLOSSALG_TESTING_PERSON_H