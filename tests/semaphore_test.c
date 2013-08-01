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

#include "semaphore_test.h"
#include "thread.h"
#include "semaphore.h"

thread_state_t semaphore_thread(thread_t *thread, semaphore_t *semaphore) {
    thread_start(thread) {
	    semaphore_wait(thread, semaphore);
    }

    return THREAD_STATE_FINISHED;
}

void semaphore_test(jasmine_t *jasmine) {
    thread_t thread;
    semaphore_t semaphore;

    jasmine_describe(jasmine, "a semaphore") {
	    jasmine_before(jasmine) {
		    thread_init(&thread);
		    semaphore_init(&semaphore, 0);
	    }

	    jasmine_after(jasmine) {

	    }

	    jasmine_it(jasmine, "should initialize with the specified count") {
		    semaphore_init(&semaphore, 10);
		    jasmine_expect(jasmine, 10 == semaphore.count);
	    }

	    jasmine_it(jasmine, "should increment when signaled") {
		    semaphore_signal(&semaphore);
		    jasmine_expect(jasmine, 1 == semaphore.count);
	    }

	    jasmine_it(jasmine, "should be able to wait for a signal") {
		    jasmine_expect(jasmine,
			    THREAD_STATE_WAITING == semaphore_thread(&thread, &semaphore));
	    }

	    jasmine_it(jasmine, "should stop waiting when signaled") {
		    semaphore_signal(&semaphore);

		    jasmine_expect(jasmine,
			    THREAD_STATE_FINISHED == semaphore_thread(&thread, &semaphore));
	    }

	    jasmine_it(jasmine, "should decrement after wait") {
		    semaphore_signal(&semaphore);
		    semaphore_thread(&thread, &semaphore);
		    jasmine_expect(jasmine, 0 == semaphore.count);
	    }
    }
}

