#include "types.h"
#include "stat.h"
#include "user.h"

int thread_join(void **stack) {
    return join(stack);
}

int thread_create(void (*fcn)(void *, void *), void *arg1, void *arg2, void *stack) {
    // Allocate memory for the user-space stack
    if (stack == 0) {
        return -1;  // Failed to allocate stack
    }
    return clone(fcn, arg1, arg2, stack);
}

void test_function(void *arg1, void *arg2) {
    printf(0,"thread is runnig...\n");
    printf(2,"arg1: %d, arg2: %d\n", (int)arg1, (int)arg2);
    printf(0,"thread terminated\n");
    exit();
}

int main(int argc, char *argv[]) {
    int a = 0;
    void *stack = malloc(4096);

    int tid1 = thread_create(test_function, (void *)1, (void *)3, stack);
    if (tid1 != -1) {
        printf(1,"thread (tid:%d) is successfully created.\n", tid1);
    } else {
        printf(1,"create thread failed. tid: %d\n", tid1);
    }

    int tid = thread_join(&stack);
    if (tid != -1) {
        printf(0,"thread successfully joined.\n");
    } else {
        printf(1,"thread join failed. tid: %d\n", tid);
    }

    if (a != 100) {
        printf(0,"thread process has malfunction.\n");
    }

    printf(0,"main thread terminated\n");
    return 0;
}