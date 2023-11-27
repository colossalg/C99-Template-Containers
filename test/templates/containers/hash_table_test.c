#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "../../dummy/person.h"

#include "./generated/data_structures.h"

#define BUFF_LEN (8 * 1024)
#define TEMP_LEN 512

char* read_file_contents(char* file_path)
{
    char* buff = calloc(BUFF_LEN, sizeof(char));
    if (NULL == buff) {
        fprintf(stderr, "malloc() failed.");
        exit(EXIT_FAILURE);
    }

    FILE* file = fopen(file_path, "r");
    if (NULL == file) {
        fprintf(stderr, "fopen() failed.");
        exit(EXIT_FAILURE);
    }

    int bytes = fread(buff, sizeof(char), BUFF_LEN, file);
    if (0 == bytes) {
        fprintf(stderr, "fread() failed.");
        exit(EXIT_FAILURE);
    }

    fclose(file);

    return buff;
}

char* read_dict_contents(const dict_of_int_and_person* dict)
{
    char* buff = calloc(BUFF_LEN, sizeof(char));
    if (NULL == buff) {
        fprintf(stderr, "malloc() failed.");
        exit(EXIT_FAILURE);
    }

    char temp[TEMP_LEN];
    for (size_t i = 0; i < dict->num_slots; ++i) {
        bzero(temp, TEMP_LEN);
        sprintf(temp, "Slot #%ld:\n", i);
        strncat(buff, temp, TEMP_LEN);

        list_of_pair_of_int_and_person_item* item = dict->slots[i]->head;
        while (NULL != item) {
            person p = item->data.value_2;
            bzero(temp, TEMP_LEN);
            sprintf(
                temp,
                "Person{ id: %i, fname: %s, lname: %s }\n",
                p.id,
                p.fname,
                p.lname
            );
            strncat(buff, temp, TEMP_LEN);

            item = item->next;
        }
    }

    return buff;
}

size_t person_dict_hash_func(int key)
{
    return key;
}

bool person_dict_comparator(int key_1, int key_2)
{
    return key_1 == key_2;
}

void person_dict_destroy_data(pair_of_int_and_person pair) {}

void test_dict_of_xxx_and_xxx_insert_and_remove()
{
    dict_of_int_and_person* dict = dict_of_int_and_person_create(
        3,
        &person_dict_hash_func,
        &person_dict_comparator,
        &person_dict_destroy_data
    );
    if (NULL == dict) {
        fprintf(stderr, "dict_of_int_and_person_create() failed.");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < people_len; ++i) {
        bool res = dict->insert(dict, people[i].id, people[i]);
        if (!res) {
            fprintf(stderr, "insert() failed.");
            exit(EXIT_FAILURE);
        }
    }

    char* post_insert_file_contents = read_file_contents("./test-data/hash-table-post-insert.txt");
    char* post_insert_dict_contents = read_dict_contents(dict);

    if (0 != strcmp(post_insert_file_contents, post_insert_dict_contents)) {
        fprintf(stderr, "Post insert file contents:\n%s\n", post_insert_file_contents);
        fprintf(stderr, "Post insert dict contents:\n%s\n", post_insert_dict_contents);
        exit(EXIT_FAILURE);
    }

    free(post_insert_file_contents);
    free(post_insert_dict_contents);

    dict->remove(dict, 0, false);
    dict->remove(dict, 1, false);

    char* post_remove_file_contents = read_file_contents("./test-data/hash-table-post-remove.txt");
    char* post_remove_dict_contents = read_dict_contents(dict);

    if (0 != strcmp(post_remove_file_contents, post_remove_dict_contents)) {
        fprintf(stderr, "Post remove file contents:\n%s\n", post_remove_file_contents);
        fprintf(stderr, "Post remove dict contents:\n%s\n", post_remove_dict_contents);
        exit(EXIT_FAILURE);
    }

    free(post_remove_file_contents);
    free(post_remove_dict_contents);

    dict->destroy(dict);
}

void test_dict_of_xxx_and_xxx_find()
{
    dict_of_int_and_person* dict = dict_of_int_and_person_create(
        3,
        &person_dict_hash_func,
        &person_dict_comparator,
        &person_dict_destroy_data
    );
    if (NULL == dict) {
        fprintf(stderr, "dict_of_int_and_person_create() failed.");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < people_len; ++i) {
        bool res = dict->insert(dict, people[i].id, people[i]);
        if (!res) {
            fprintf(stderr, "insert() failed.");
            exit(EXIT_FAILURE);
        }
    }

    for (size_t i = 0; i < people_len; ++i) {
        optional_pair_of_int_and_person opp = dict->find(dict, people[i].id);
        assert(opp.has_value);
        assert(person_equals(&people[i], &opp.value.value_2));
    }

    optional_pair_of_int_and_person opp = dict->find(dict, 99);
    assert(!opp.has_value);

    dict->destroy(dict);
}