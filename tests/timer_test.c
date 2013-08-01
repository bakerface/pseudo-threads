/*
 * Copyright (c) 2013 Christopher M. Baker - Confidential - All Rights Reserved
 *
 */

#include "timer_test.h"

typedef unsigned long clock_t;

clock_t now = 1000;

clock_t clock(void) {
    return now;
}

#include "timer.h"

void timer_test(jasmine_t *jasmine) {
    timer_t timer;

    jasmine_describe(jasmine, "a timer") {
	    jasmine_before(jasmine) {
	    
	    }

	    jasmine_after(jasmine) {

	    }

	    jasmine_it(jasmine, "should initialize with the end time") {
	        timer_init(&timer, 1000);
		    jasmine_expect(jasmine, 2000 == timer.end);
	    }
	    
	    jasmine_it(jasmine, "should report whether the time has expired") {
	        timer_init(&timer, 1000);
		    jasmine_expect(jasmine, !timer_expired(&timer));
		    
		    now += 1000;
		    jasmine_expect(jasmine, timer_expired(&timer));
	    }
    }
}

