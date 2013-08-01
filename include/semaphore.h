/*
 * Copyright (c) 2013 Christopher M. Baker - Confidential - All Rights Reserved
 *
 */

#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

typedef struct semaphore {
    unsigned short count;
} semaphore_t;

#define semaphore_init(semaphore, n) (semaphore)->count = n
#define semaphore_signal(semaphore) (semaphore)->count++

#define semaphore_wait(thread, semaphore) do { \
    thread_wait(thread, (semaphore)->count > 0); \
    (semaphore)->count--; \
} while (0)

#endif /* SEMAPHORE_H_ */

