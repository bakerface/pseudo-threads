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

#ifndef MOCHA_H_
#define MOCHA_H_

#include <stdio.h>

#define MOCHA_STATE_BEFORE   0
#define MOCHA_STATE_IT       1
#define MOCHA_STATE_AFTER    2
#define MOCHA_STATE_FINISHED 3

#define MOCHA_GROUP_IGNORED 0
#define MOCHA_GROUP_PASSED  1
#define MOCHA_GROUP_FAILED  2

typedef struct mocha {
  unsigned int state;
  unsigned int group;
  unsigned int current;
  unsigned int last;
  unsigned int passed;
  unsigned int failed;
  unsigned int ignored;
  unsigned int asserts;
  const char *reason;
} mocha_t;

#define mocha_init(mocha) do { \
  (mocha)->state = MOCHA_STATE_BEFORE; \
  (mocha)->group = MOCHA_GROUP_IGNORED; \
  (mocha)->current = 0; \
  (mocha)->last = 0; \
  (mocha)->passed = 0; \
  (mocha)->failed = 0; \
  (mocha)->ignored = 0; \
  (mocha)->asserts = 0; \
  (mocha)->reason = 0; \
} while (0)

#define mocha_describe(mocha, what) \
  for ((mocha)->state = MOCHA_STATE_BEFORE, \
    (mocha)->current = 0, \
    (mocha)->last = 0, \
    puts(what); \
    (MOCHA_STATE_FINISHED == (mocha)->state) ? (puts(""), 0) : 1; )

#define mocha_before_each(mocha) \
  for (; MOCHA_STATE_BEFORE == (mocha)->state; \
    (mocha)->state = MOCHA_STATE_IT)

#define mocha_it(mocha, should) \
  for ((mocha)->group = MOCHA_GROUP_IGNORED, \
    (mocha)->last = ((mocha)->last < __LINE__ \
      ? __LINE__ : (mocha)->last); \
    MOCHA_STATE_IT == (mocha)->state \
      && (mocha)->current < __LINE__ \
      && (__LINE__ == ((mocha)->current = __LINE__)); \
    (mocha)->state = MOCHA_STATE_AFTER, \
      ((mocha)->group == MOCHA_GROUP_IGNORED \
        ? ((mocha)->ignored++, puts(" ! " should), MOCHA_GROUP_IGNORED) \
        : ((mocha)->group == MOCHA_GROUP_PASSED \
          ? ((mocha)->passed++, puts(" ✓ " should), MOCHA_GROUP_PASSED) \
          : ((mocha)->failed++, printf(" ✗ " should ": expected %s\r\n", \
            (mocha)->reason), MOCHA_GROUP_FAILED))))

#define mocha_after_each(mocha) \
  for (; MOCHA_STATE_AFTER == (mocha)->state; \
    (mocha)->state = ((mocha)->current == (mocha)->last) \
      ? MOCHA_STATE_FINISHED : MOCHA_STATE_BEFORE)

#define mocha_assert(mocha, condition) \
  if (!(condition)) { \
    (mocha)->asserts++; \
    (mocha)->group = MOCHA_GROUP_FAILED; \
    (mocha)->reason = #condition; \
    continue; \
  } else { \
    (mocha)->asserts++; \
    (mocha)->group = MOCHA_GROUP_PASSED; \
  }

#endif /* MOCHA_H_ */
