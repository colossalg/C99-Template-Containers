#ifndef COLOSSALG_TESTING_PERSON_H
#define COLOSSALG_TESTING_PERSON_H

#include <stdbool.h>

typedef struct person {
    char fname[32];
    char lname[32];
} person;
typedef person* person_ptr;

bool person_equals(const person* a, const person* b);
void person_print(const person* p);

#endif // COLOSSALG_TESTING_PERSON_H
