#include "framework.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void run_test_in_own_process(const char* name, void (*test)())
{
    fprintf(stderr, "Running test %s...\n", name);

    pid_t pid = fork();
    if (-1 == pid) {
        fprintf(stderr, "Failure: Was unable to fork process for test.\n");
    } else if (0 == pid) {
        test();
        exit(EXIT_SUCCESS);
    } else {
        int status = 0;
        wait(&status);
        if (0 == status) {
            fprintf(stderr, "Success.\n");
        } else {
            fprintf(stderr, "Failure: Process exited with code %i.\n", status);
        }
    }
}
