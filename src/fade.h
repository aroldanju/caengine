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

#ifndef __fade_h__
#define __fade_h__

#include "video.h"

typedef struct _fade {
    BOOL    enabled;
    int16_t  alpha;
    uint32_t  ticks;
    uint32_t  delay;
    uint32_t w, h;
    void    (*onFadeEnd)(void*);
    void *param;

    BOOL    in;
    uint8_t r, g, b;
} Fade;

void fade_create(Fade* fade, int width, int height);

void fade_enable(Fade* fade, void (*onFadeEnd)(void*), void* param);

void fade_out(Fade* fade, void (*onFadeEnd)(void*), void* param);

void fade_render(Fade* fade, Video* video);

void fade_set_color(Fade* fade, uint8_t r, uint8_t g, uint8_t b);

#endif // __fade_h__