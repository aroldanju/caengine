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

#ifndef __image_h
#define __image_h

#ifdef __APPLE__
#include <SDL2/SDL.h>
#else
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_system.h>
#endif

#include "defs.h"
#include "video.h"

typedef struct _pal {
    uint8_t 	color[256][3];
} PAL;

typedef struct _img {
    uint32_t 	width;
    uint32_t 	height;
    uint8_t 	*data;
} IMG;

uint32_t surface_get_pixel(SDL_Surface* surface, int x, int y);

void surface_set_pixel(SDL_Surface* surface, int x, int y, uint32_t pixel);

typedef struct _image {
    SDL_Surface *surface;
    SDL_Texture *texture;
} Image;

BOOL image_load_img(Image *image, const char *data, uint32_t length, Video* video, const PAL* palette);

BOOL image_load_from_mem(Image *image, const char *data, uint32_t length, Video* video);

BOOL image_load(Image *image, const char *filename, Video* video);

void image_destroy(Image *image);

void image_render(Image *image, int32_t x, int32_t y, Video* video);

BOOL image_extract(Image* dst, Image *src,  uint32_t x, uint32_t y, uint32_t w, uint32_t h, Video* video);

void image_set_alpha(Image* image, uint8_t alpha);

BOOL image_copy(Image* dst, const Image* src, Video* video);

BOOL image_pal_load(PAL* pal, const char* data, uint32_t length);

void image_create(Image* image);

BOOL image_create_texture(Image* dst, const Image* src, uint32_t width, uint32_t height, Video* video);

#endif /* __image_h */
