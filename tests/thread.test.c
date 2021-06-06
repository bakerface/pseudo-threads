/**
 * Copyright (c) 2013, 2021 Chris Baker <mail.chris.baker@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */

#include <thread.h>
#include "thread.test.h"

int run_routine(thread_t *thread, unsigned char *count) {
  thread_start(thread) {
    (*count)++;
  }

  return THREAD_SUCCESS;
}

int restart_routine(thread_t *thread) {
  thread_start(thread) {
    thread_restart(thread);
  }

  return THREAD_SUCCESS;
}

int yield_routine(thread_t *thread, unsigned char *count) {
  thread_start(thread) {
    thread_yield(thread);
    (*count)++;
  }

  return THREAD_SUCCESS;
}

int wait_routine(thread_t *thread, unsigned char flag) {
  thread_start(thread) {
    thread_wait(thread, flag == 0);
  }

  return THREAD_SUCCESS;
}

int assert_routine(thread_t *thread, unsigned char flag) {
  thread_start(thread) {
    thread_assert(thread, flag == 0);
  }

  return THREAD_SUCCESS;
}

void thread_test(mocha_t *mocha) {
  thread_t thread;

  mocha_describe(mocha, "a thread") {
    mocha_before_each(mocha) {
      thread_init(&thread);
    }

    mocha_after_each(mocha) {
      /* no cleanup required */
    }

    mocha_it(mocha, "can run to completion") {
      unsigned char count = 0;

      mocha_assert(mocha,
          THREAD_SUCCESS == run_routine(&thread, &count));

      mocha_assert(mocha, 1 == count);
    }

    mocha_it(mocha, "should retain success state") {
      unsigned char count = 0;

      mocha_assert(mocha,
          THREAD_SUCCESS == run_routine(&thread, &count));

      mocha_assert(mocha,
          THREAD_SUCCESS == run_routine(&thread, &count));

      mocha_assert(mocha, 1 == count);
    }

    mocha_it(mocha, "can restart") {
      mocha_assert(mocha,
          THREAD_PENDING == restart_routine(&thread));

      mocha_assert(mocha,
          THREAD_PENDING == restart_routine(&thread));
    }

    mocha_it(mocha, "can yield execution") {
      unsigned char count = 0;

      mocha_assert(mocha,
          THREAD_PENDING == yield_routine(&thread, &count));

      mocha_assert(mocha, 0 == count);

      mocha_assert(mocha,
          THREAD_SUCCESS == yield_routine(&thread, &count));

      mocha_assert(mocha, 1 == count);

      mocha_assert(mocha,
          THREAD_SUCCESS == yield_routine(&thread, &count));

      mocha_assert(mocha, 1 == count);
    }

    mocha_it(mocha, "can wait for a condition") {
      mocha_assert(mocha,
          THREAD_PENDING == wait_routine(&thread, 3));

      mocha_assert(mocha,
          THREAD_PENDING == wait_routine(&thread, 2));

      mocha_assert(mocha,
          THREAD_PENDING == wait_routine(&thread, 1));

      mocha_assert(mocha,
          THREAD_SUCCESS == wait_routine(&thread, 0));

      mocha_assert(mocha,
          THREAD_SUCCESS == wait_routine(&thread, 1));
    }

    mocha_it(mocha, "should proceed if an asserted condition is met") {
      mocha_assert(mocha,
          THREAD_SUCCESS == assert_routine(&thread, 0));
    }

    mocha_it(mocha, "should halt if an asserted condition is not met") {
      mocha_assert(mocha,
          THREAD_FAILURE == assert_routine(&thread, 1));
    }

    mocha_it(mocha, "should retain failure state") {
      mocha_assert(mocha,
          THREAD_FAILURE == assert_routine(&thread, 1));

      mocha_assert(mocha,
          THREAD_FAILURE == assert_routine(&thread, 0));
    }
  }
}
