#include "framework.h"

#include "templates/containers/linked_list_test.h"

int main(int argc, char** argv)
{
    RUN_TEST_IN_OWN_PROCESS(test_list_of_xxx_insert_at_head_val_type);
    RUN_TEST_IN_OWN_PROCESS(test_list_of_xxx_insert_at_head_ptr_type);
    RUN_TEST_IN_OWN_PROCESS(test_list_of_xxx_insert_at_tail_val_type);
    RUN_TEST_IN_OWN_PROCESS(test_list_of_xxx_insert_at_tail_ptr_type);
    RUN_TEST_IN_OWN_PROCESS(test_list_of_xxx_insert_before_head);
    RUN_TEST_IN_OWN_PROCESS(test_list_of_xxx_insert_before_tail);
    RUN_TEST_IN_OWN_PROCESS(test_list_of_xxx_insert_after_head);
    RUN_TEST_IN_OWN_PROCESS(test_list_of_xxx_insert_after_tail);
    RUN_TEST_IN_OWN_PROCESS(test_list_of_xxx_remove_head);
    RUN_TEST_IN_OWN_PROCESS(test_list_of_xxx_remove_tail);
    RUN_TEST_IN_OWN_PROCESS(test_list_of_xxx_remove);
    RUN_TEST_IN_OWN_PROCESS(test_list_of_xxx_clear);
}
