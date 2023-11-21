#include "framework.h"

#include "templates/containers/array_stack_test.h"
#include "templates/containers/linked_list_test.h"

int main(int argc, char** argv)
{
    RUN_TEST_IN_OWN_PROCESS(test_array_stack_of_xxx_push_and_pop);
    RUN_TEST_IN_OWN_PROCESS(test_array_stack_of_xxx_overflow);
    RUN_TEST_IN_OWN_PROCESS(test_array_stack_of_xxx_underflow);
    RUN_TEST_IN_OWN_PROCESS(test_array_stack_of_xxx_destroy);

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
}
