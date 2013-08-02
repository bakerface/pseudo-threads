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

thread_state_t assert_routine(thread_t *thread, unsigned char flag) {
    thread_start(thread) {
	    thread_assert(thread, flag == 0);
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
	    
	    jasmine_it(jasmine, "should continue if an assertion passes") {
		    jasmine_expect(jasmine,
			    THREAD_STATE_FINISHED == assert_routine(&thread, 0));
	    }
	    
	    jasmine_it(jasmine, "should assert if an assertion fails") {
		    jasmine_expect(jasmine,
			    THREAD_STATE_ASSERTED == assert_routine(&thread, 1));
	    }
	    
	    jasmine_it(jasmine, "should restart after an assertion fails") {
	        jasmine_expect(jasmine,
			    THREAD_STATE_ASSERTED == assert_routine(&thread, 1));
	    
		    jasmine_expect(jasmine,
			    THREAD_STATE_FINISHED == assert_routine(&thread, 0));
	    }
    }
}

