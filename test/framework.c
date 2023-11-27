#include "framework.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define FAILURE "\x1B[31m"
#define SUCCESS "\x1B[32m"
#define RESET   "\x1B[0m"

void run_test_in_own_process(const char* name, void (*test)())
{
    fprintf(stderr, "Running test %s... ", name);

    pid_t pid = fork();
    if (-1 == pid) {
        fprintf(stderr, "%sFailure: Was unable to fork process for test.%s\n", FAILURE, RESET);
    } else if (0 == pid) {
        test();
        exit(EXIT_SUCCESS);
    } else {
        int status = 0;
        wait(&status);
        if (0 == status) {
            fprintf(stderr, "%sSuccess.%s\n", SUCCESS, RESET);
        } else {
            fprintf(stderr, "%sFailure: Process exited with code %i.%s\n", FAILURE, status, RESET);
        }
    }
}
