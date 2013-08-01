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

