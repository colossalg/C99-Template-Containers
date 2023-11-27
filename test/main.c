#include <stdio.h>

#include "framework.h"

#include "templates/containers/array_queue_test.h"
#include "templates/containers/array_stack_test.h"
#include "templates/containers/hash_table_test.h"
#include "templates/containers/linked_list_test.h"

int main(int argc, char** argv)
{
    printf("Array Queue Tests\n");
    RUN_TEST_IN_OWN_PROCESS(test_array_queue_of_xxx_enqueue_and_dequeue);
    RUN_TEST_IN_OWN_PROCESS(test_array_queue_of_xxx_overflow);
    RUN_TEST_IN_OWN_PROCESS(test_array_queue_of_xxx_underflow);
    RUN_TEST_IN_OWN_PROCESS(test_array_queue_of_xxx_destroy);
    printf("\n");

    printf("Array Stack Tests\n");
    RUN_TEST_IN_OWN_PROCESS(test_array_stack_of_xxx_push_and_pop);
    RUN_TEST_IN_OWN_PROCESS(test_array_stack_of_xxx_overflow);
    RUN_TEST_IN_OWN_PROCESS(test_array_stack_of_xxx_underflow);
    RUN_TEST_IN_OWN_PROCESS(test_array_stack_of_xxx_destroy);
    printf("\n");

    printf("Hash Table Tests\n");
    RUN_TEST_IN_OWN_PROCESS(test_dict_of_xxx_and_xxx_insert_and_remove);
    RUN_TEST_IN_OWN_PROCESS(test_dict_of_xxx_and_xxx_find);
    printf("\n");

    printf("Linked List Tests\n");
    RUN_TEST_IN_OWN_PROCESS(test_list_of_xxx_insert_at_head);
    RUN_TEST_IN_OWN_PROCESS(test_list_of_xxx_insert_at_tail);
    RUN_TEST_IN_OWN_PROCESS(test_list_of_xxx_insert_before_head);
    RUN_TEST_IN_OWN_PROCESS(test_list_of_xxx_insert_before_tail);
    RUN_TEST_IN_OWN_PROCESS(test_list_of_xxx_insert_after_head);
    RUN_TEST_IN_OWN_PROCESS(test_list_of_xxx_insert_after_tail);
    RUN_TEST_IN_OWN_PROCESS(test_list_of_xxx_remove_head);
    RUN_TEST_IN_OWN_PROCESS(test_list_of_xxx_remove_tail);
    RUN_TEST_IN_OWN_PROCESS(test_list_of_xxx_remove);
    RUN_TEST_IN_OWN_PROCESS(test_list_of_xxx_clear);
    printf("\n");
}
