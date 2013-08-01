/*
 * Copyright (c) 2013 Christopher M. Baker - Confidential - All Rights Reserved
 *
 * jasmine.h - A port of the Jasmine test framework to ANSI C
 *
 */

#ifndef JASMINE_H_
#define JASMINE_H_

#include <stdio.h>

#define JASMINE_STATE_BEFORE   0
#define JASMINE_STATE_IT       1
#define JASMINE_STATE_AFTER    2
#define JASMINE_STATE_FINISHED 3

typedef struct jasmine {
    unsigned char state;
    unsigned char group;
    unsigned short current;
    unsigned short last;
    unsigned short passed;
    unsigned short failed;
    unsigned short expects;
    const char *reason;
} jasmine_t;

#define jasmine_init(jasmine) do { \
    (jasmine)->state = JASMINE_STATE_BEFORE; \
    (jasmine)->group = 0; \
    (jasmine)->current = 0; \
    (jasmine)->last = 0; \
    (jasmine)->passed = 0; \
    (jasmine)->failed = 0; \
    (jasmine)->expects = 0; \
    (jasmine)->reason = 0; \
} while (0)

#define jasmine_describe(jasmine, what) \
    for ((jasmine)->state = JASMINE_STATE_BEFORE, \
            (jasmine)->current = 0, \
            (jasmine)->last = 0, \
            puts(what); \
        (JASMINE_STATE_FINISHED == (jasmine)->state) ? (puts(""), 0) : 1; )

#define jasmine_before(jasmine) \
    for (; JASMINE_STATE_BEFORE == (jasmine)->state; \
        (jasmine)->state = JASMINE_STATE_IT)

#define jasmine_it(jasmine, should) \
    for ((jasmine)->group = 1, \
            (jasmine)->last = (unsigned short) ((jasmine)->last < __LINE__ \
            ? __LINE__ : (jasmine)->last); \
        JASMINE_STATE_IT == (jasmine)->state \
            && (jasmine)->current < __LINE__ \
            && (__LINE__ == ((jasmine)->current = __LINE__)); \
        (jasmine)->state = JASMINE_STATE_AFTER, \
            ((jasmine)->group \
            ? ((jasmine)->passed++, puts(" ✓ " should), 1) \
            : ((jasmine)->failed++, printf(" ✗ " should ": expected %s\r\n", \
                (jasmine)->reason), 1)))

#define jasmine_after(jasmine) \
    for (; JASMINE_STATE_AFTER == (jasmine)->state; \
        (jasmine)->state = ((jasmine)->current == (jasmine)->last) \
            ? JASMINE_STATE_FINISHED : JASMINE_STATE_BEFORE)

#define jasmine_expect(jasmine, condition) \
    if (!(condition)) { \
        (jasmine)->expects++; \
        (jasmine)->group = 0; \
        (jasmine)->reason = #condition; \
        continue; \
    } \
    else { \
        (jasmine)->expects++; \
    }

#endif /* JASMINE_H_ */

