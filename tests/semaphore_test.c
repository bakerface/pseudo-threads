/*
 * Copyright (c) 2013 Christopher M. Baker - Confidential - All Rights Reserved
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

