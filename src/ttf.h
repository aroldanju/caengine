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

#ifndef TTF_H
#define TTF_H

#ifdef __APPLE__
#   include <SDL2_ttf/SDL_ttf.h>
#else
#   include <SDL2/SDL_ttf.h>
#endif

#include "defs.h"

typedef struct _ttf {
    TTF_Font *font;
    uint32_t  size;
} Ttf;


BOOL ttf_loadFromMem(Ttf* font, char *data, unsigned int len, uint32_t size);

BOOL ttf_loadFromFile(Ttf* font, const char* filename, uint32_t size);

void ttf_destroy(Ttf *font);

SDL_Surface* ttf_render(Ttf * font, const char* text, uint8_t r, uint8_t g, uint8_t b);
SDL_Surface* ttf_render_wrap(Ttf * font, const char* text, uint8_t r, uint8_t g, uint8_t b, uint32_t w);

uint32_t ttf_getWidth(Ttf* font, const char* text);

#endif // TTF_H

