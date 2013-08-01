/*
 * The MIT License (MIT)
 * 
 * Copyright (c) 2013 Christopher M. Baker
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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

