#include "types.h"
#include "stat.h"
#include "user.h"
#include <stdio.h>

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
    printf("스레드 실행 중...\n");
    printf("인자1: %d, 인자2: %d\n", (int)arg1, (int)arg2);
    printf("스레드 종료\n");
    exit();
}

int main(int argc, char *argv[]) {
    int a = 0;
    void *stack = malloc(4096);

    int tid1 = thread_create(test_function, (void *)1, (void *)3, stack);
    if (tid1 != -1) {
        printf("스레드 (tid:%d)가 성공적으로 생성되었습니다.\n", tid1);
    } else {
        printf("스레드 생성 실패. 오류 코드: %d\n", tid1);
    }

    int tid = thread_join(&stack);
    if (tid != -1) {
        printf("스레드가 성공적으로 조인되었습니다.\n");
    } else {
        printf("스레드 조인 실패. 오류 코드: %d\n", tid);
    }

    if (a != 100) {
        printf("스레드가 정상적으로 실행되지 않았습니다.\n");
    }

    printf("메인 스레드 종료\n");
    return 0;
}