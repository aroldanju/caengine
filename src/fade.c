/*
 *  ca-engine - Simple game engine
 *  Copyright (C) 2016 A. Roldán
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * 	arldn.dev -at- gmail.com
 */

#include "fade.h"

void fade_create(Fade* fade, int width, int height) {
    fade->w = width;
    fade->h = height;
    fade->delay = 250;
    fade->enabled = FALSE;
    fade->r = fade->g = fade->b = 0;
}

void fade_enable(Fade* fade, void (*onFadeEnd)(void*), void *param) {
    fade->alpha = 0;
    fade->enabled = TRUE;
    fade->ticks = SDL_GetTicks();
    fade->onFadeEnd = onFadeEnd;
    fade->param = param;
    fade->in = TRUE;
}


void fade_out(Fade* fade, void (*onFadeEnd)(void*), void* param) {
    fade->alpha = 255;
    fade->enabled = TRUE;
    fade->ticks = SDL_GetTicks();
    fade->onFadeEnd = onFadeEnd;
    fade->param = param;
    fade->in = FALSE;
}

void fade_set_color(Fade* fade, uint8_t r, uint8_t g, uint8_t b)	{
	fade->r = r;
	fade->g = g;
	fade->b = b;
}

void fade_render(Fade* fade, Video* video) {
    if (fade->enabled) {
        SDL_Rect rect = (SDL_Rect){ 0, 0, fade->w, fade->h };
        SDL_SetRenderDrawBlendMode(video->renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(video->renderer, fade->r, fade->g, fade->b, fade->alpha);
        SDL_RenderFillRect(video->renderer, &rect);
        if (SDL_GetTicks() - fade->ticks >= fade->delay) {
            if (fade->in) {
                fade->alpha += 32;
                fade->ticks = SDL_GetTicks();
                if (fade->alpha >= 255) {
                    fade->alpha = 255;
                    fade->in = FALSE;
                    if (fade->onFadeEnd != NULL) {
                        fade->onFadeEnd(fade->param);
                    }
                }
            }
            else {
                fade->alpha -= 32;
                fade->ticks = SDL_GetTicks();
                if (fade->alpha <= 0) {
                    fade->enabled = FALSE;
                }
            }
        }

		SDL_SetRenderDrawColor(video->renderer, 0, 0, 0, 255);
    }
}