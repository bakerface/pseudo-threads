/*
 * Copyright (c) 2013 Christopher M. Baker - Confidential - All Rights Reserved
 *
 */

#include "thread_test.h"
#include "semaphore_test.h"
#include "timer_test.h"

int main(void) {
    jasmine_t jasmine;
    jasmine_init(&jasmine);

    thread_test(&jasmine);
    semaphore_test(&jasmine);
    timer_test(&jasmine);

    printf("jasmine: %u passed, %u failed, %u expects\r\n",
        jasmine.passed, jasmine.failed, jasmine.expects);

    return jasmine.failed;
}

