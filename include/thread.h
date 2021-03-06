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

#ifndef THREAD_H_
#define THREAD_H_

#define THREAD_SUCCESS 0
#define THREAD_FAILURE 1
#define THREAD_PENDING 2

#define __LINE_MAX__ ((thread_t) -1)

typedef unsigned short thread_t;

#define thread_init(thread) (*(thread)) = 0

#define thread_start(thread) \
  switch (*(thread)) \
  case 0: \
  if ((*(thread) = __LINE_MAX__))

#define thread_restart(thread) do { \
  thread_init(thread); \
  return THREAD_PENDING; \
} while (0)

#define thread_yield(thread) do { \
  (*(thread)) = __LINE__; \
  return THREAD_PENDING; \
  case __LINE__: \
  (*(thread)) = __LINE_MAX__; \
} while (0)

#define thread_wait(thread, condition) do { \
  (*(thread)) = __LINE__; \
  case __LINE__: \
  if (!(condition)) return THREAD_PENDING; \
  (*(thread)) = __LINE_MAX__; \
} while (0)

#define thread_assert(thread, condition) do { \
  if (!(condition)) { \
    (*(thread)) = __LINE__; \
    case __LINE__: \
    return THREAD_FAILURE; \
  } \
} while (0)

#endif /* THREAD_H_ */
