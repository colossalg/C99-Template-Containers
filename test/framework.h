#ifndef COLOSSALG_TESTING_FRAMEWORK_H
#define COLOSSALG_TESTING_FRAMEWORK_H

#define RUN_TEST_IN_OWN_PROCESS(test_name) \
	run_test_in_own_process(#test_name "()", &test_name);

void run_test_in_own_process(const char* name, void (*test)());

#endif // COLOSSALG_TESTING_FRAMEWORK_H
