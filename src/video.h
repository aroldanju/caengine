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

#ifndef __video_h
#define __video_h

#ifdef __APPLE__
#include <SDL2/SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include "defs.h"

typedef struct _video {
    char title[32];
    uint32_t windowWidth, windowHeight;
    uint32_t width, height;
    uint8_t fps;
    uint8_t renderQuality;
    char icon[256];

    // FPS
    uint32_t fpsCount, fpsTick, fpsCurrent;
    uint32_t lastFpsTick;
    float   delta;

    // SDL stuff
    SDL_Window* window;
    SDL_Renderer* renderer;

} Video;

BOOL video_init(Video* video);
void video_release(Video* video);

void video_clear(Video* video);
void video_render(Video* video);

uint32_t video_get_fps(Video* video);

void video_render_line(Video* video, uint32_t fx, uint32_t fy, uint32_t tx, uint32_t ty, uint8_t r, uint8_t g, uint8_t b);
void video_render_line_alpha(Video* video, uint32_t fx, uint32_t fy, uint32_t tx, uint32_t ty, uint8_t r, uint8_t g, uint8_t b, uint8_t a) ;
void video_render_rect(Video* video, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t r, uint8_t g, uint8_t b);
void video_render_rect_alpha(Video* video, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

#endif  // __video_h