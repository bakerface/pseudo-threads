/*
 * Copyright (c) 2013 Christopher M. Baker - Confidential - All Rights Reserved
 *
 */

#ifndef TIMER_H_
#define TIMER_H_

typedef struct timer {
    clock_t end;
} timer_t;

#define timer_init(timer, ticks) (timer)->end = clock() + (ticks)
#define timer_expired(timer)     ((timer)->end <= clock())

#endif /* TIMER_H_ */

