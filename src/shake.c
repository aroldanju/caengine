#include "shake.h"

void shake_create(Shake* shake, uint8_t strength, uint32_t duration)	{
	shake->strength = strength;
	shake->x = shake->y = 0.0f;
	shake->duration = duration;
	shake->enabled = FALSE;

	if (shake->strength == 0) {
		shake->strength = 1;
	}
}

void shake_start(Shake *shake)	{
	shake->tick = SDL_GetTicks();
	shake->enabled = TRUE;
}

void shake_update(Shake *shake, float dt)	{
	if (shake->enabled) {

		const int strength = shake->strength / 2;

		shake->x = -(shake->strength / 2) + (rand() % strength);

		if (SDL_GetTicks() - shake->tick >= shake->duration) {
			shake->enabled = FALSE;
			shake->x = shake->y = 0.0f;
		}
	}
}

