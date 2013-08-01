/*
 * Copyright (c) 2013 Christopher M. Baker - Confidential - All Rights Reserved
 *
 */

#include "thread_test.h"
#include <thread.h>

thread_state_t run_routine(thread_t *thread, unsigned char *count) {
    thread_start(thread) {
	    (*count)++;
    }

    return THREAD_STATE_FINISHED;
}

thread_state_t restart_routine(thread_t *thread) {
    thread_start(thread) {
	    thread_restart(thread);
    }

    return THREAD_STATE_FINISHED;
}

thread_state_t yield_routine(thread_t *thread, unsigned char *count) {
    thread_start(thread) {
	    thread_yield(thread);
	    thread_yield(thread);
	    (*count)++;
    }

    return THREAD_STATE_FINISHED;
}

thread_state_t wait_routine(thread_t *thread, unsigned char flag) {
    thread_start(thread) {
	    thread_wait(thread, flag == 0);
    }

    return THREAD_STATE_FINISHED;
}

void thread_test(jasmine_t *jasmine) {
    thread_t thread;

    jasmine_describe(jasmine, "a thread") {
	    jasmine_before(jasmine) {
		    thread_init(&thread);
	    }

	    jasmine_after(jasmine) {

	    }

	    jasmine_it(jasmine, "should be able to run to completion") {
		    unsigned char count = 0;

		    jasmine_expect(jasmine,
			    THREAD_STATE_FINISHED == run_routine(&thread, &count));

		    jasmine_expect(jasmine, 1 == count);
	    }

	    jasmine_it(jasmine, "should not be able to run after completion") {
		    unsigned char count = 0;

		    jasmine_expect(jasmine,
			    THREAD_STATE_FINISHED == run_routine(&thread, &count));

		    jasmine_expect(jasmine,
			    THREAD_STATE_FINISHED == run_routine(&thread, &count));

		    jasmine_expect(jasmine, 1 == count);
	    }

	    jasmine_it(jasmine, "should be able to restart from the beginning") {
		    jasmine_expect(jasmine,
			    THREAD_STATE_RESTARTING == restart_routine(&thread));
			    
			jasmine_expect(jasmine,
			    THREAD_STATE_RESTARTING == restart_routine(&thread));
	    }

	    jasmine_it(jasmine, "should be able to yield to other threads") {
	        unsigned char count = 0;
	        
		    jasmine_expect(jasmine,
			    THREAD_STATE_YIELDING == yield_routine(&thread, &count));
			    
			jasmine_expect(jasmine, 0 == count);
			    
			jasmine_expect(jasmine,
			    THREAD_STATE_YIELDING == yield_routine(&thread, &count));
			    
            jasmine_expect(jasmine, 0 == count);

		    jasmine_expect(jasmine,
			    THREAD_STATE_FINISHED == yield_routine(&thread, &count));
			
			jasmine_expect(jasmine, 1 == count);
			    
			jasmine_expect(jasmine,
			    THREAD_STATE_FINISHED == yield_routine(&thread, &count));
			    
			jasmine_expect(jasmine, 1 == count);
	    }

	    jasmine_it(jasmine, "should be able to wait for a condition") {
		    jasmine_expect(jasmine,
			    THREAD_STATE_WAITING == wait_routine(&thread, 3));

		    jasmine_expect(jasmine,
			    THREAD_STATE_WAITING == wait_routine(&thread, 2));

		    jasmine_expect(jasmine,
			    THREAD_STATE_WAITING == wait_routine(&thread, 1));

		    jasmine_expect(jasmine,
			    THREAD_STATE_FINISHED == wait_routine(&thread, 0));
			    
			jasmine_expect(jasmine,
			    THREAD_STATE_FINISHED == wait_routine(&thread, 1));
	    }
    }
}

