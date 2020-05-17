#include "timer.h"

void timer_start(Timer* timer) {
	timer->running = TRUE;
	timer->tickStart = SDL_GetTicks();
}

BOOL timer_elapsed(const Timer* timer) {
	if (timer->running) {
		if (SDL_GetTicks() - timer->tickStart >= timer->interval) {
			return TRUE;
		}
	}

	return FALSE;
}

void timer_create(Timer* timer, uint32_t interval)	{
	timer->tickStart = 0;
	timer->interval = interval;
	timer->running = FALSE;
}