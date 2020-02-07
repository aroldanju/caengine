#ifndef __shake_h
#define __shake_h

#include <stdint.h>

#include <SDL2/SDL.h>

#include "defs.h"

typedef struct _shake {
	float x;
	float y;
	uint8_t strength;
	uint32_t tick;
	BOOL enabled;
	uint32_t duration;
} Shake;

void shake_create(Shake* shake, uint8_t strength, uint32_t duration);

void shake_start(Shake *shake);

void shake_update(Shake *shake, float dt);

#endif	/* __shake_h */