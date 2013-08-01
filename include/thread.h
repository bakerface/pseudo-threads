/*
 * Copyright (c) 2013 Christopher M. Baker - Confidential - All Rights Reserved
 *
 */

#ifndef THREAD_H_
#define THREAD_H_

typedef unsigned char thread_state_t;

#define THREAD_STATE_FINISHED   0
#define THREAD_STATE_WAITING    1
#define THREAD_STATE_YIELDING   2
#define THREAD_STATE_RESTARTING 3

#define THREAD_LINE_START 0
#define THREAD_LINE_END   ((unsigned short)-1)

typedef struct thread {
    unsigned short line;
} thread_t;

#define thread_init(thread) (thread)->line = THREAD_LINE_START

#define thread_start(thread) \
    switch ((thread)->line) \
	    case THREAD_LINE_START: \
		    if (THREAD_LINE_END == ((thread)->line = THREAD_LINE_END))

#define thread_restart(thread) do { \
    thread_init(thread); \
    return THREAD_STATE_RESTARTING; \
} while (0)

#define thread_yield(thread) do { \
    (thread)->line = __LINE__; \
    return THREAD_STATE_YIELDING; \
    case __LINE__: \
	    (thread)->line = THREAD_LINE_END; \
} while (0)

#define thread_wait(thread, condition) do { \
    (thread)->line = __LINE__; \
    case __LINE__: \
	    if (!(condition)) { \
		    return THREAD_STATE_WAITING; \
	    } \
	    (thread)->line = THREAD_LINE_END; \
} while (0)

#endif /* THREAD_H_ */

