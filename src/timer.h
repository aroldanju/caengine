#ifndef __timer_h
#define __timer_h

#include "defs.h"
#include <stdint.h>

typedef struct _timer {
	uint32_t tickStart;
	uint32_t interval;
	BOOL running;
} Timer;

void timer_create(Timer* timer, uint32_t interval);

void timer_start(Timer* timer);

BOOL timer_elapsed(const Timer* timer);



#endif	/* __timer_h */