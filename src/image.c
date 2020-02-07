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

#include "image.h"

BOOL image_load_img(Image *image, const char *data, uint32_t length, Video* video, const PAL* palette) {
    uint32_t width, height;
    uint8_t r, g, b;
    uint8_t index;
    int i, j;

    width = *(uint32_t*)data;
    height = *(uint32_t*)(data + 4);

    image->surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    if (!image->surface) {
#ifdef __CAENGINE_DEBUG__
        printf("image_load_img(): error loading image: %s\n", SDL_GetError());
#endif
        return FALSE;
    }

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            index = data[8 + (i * width + j)];

            r = palette->color[index][0];
            g = palette->color[index][1];
            b = palette->color[index][2];

            surface_set_pixel(image->surface, j, i, SDL_MapRGB(image->surface->format, r, g, b));
        }
    }

    SDL_SetColorKey(image->surface, SDL_TRUE, SDL_MapRGB(image->surface->format, 0, 0, 0));

    image->texture = SDL_CreateTextureFromSurface(video->renderer, image->surface);
    if ( !image->texture ) {
#ifdef __CAENGINE_DEBUG__
        printf("image_load_from_mem(): error creating texture: %s\n", SDL_GetError());
#endif  // DEBUG_IMAGE
        SDL_FreeSurface(image->surface);
        return FALSE;
    }

    return TRUE;
}

BOOL image_load_from_mem(Image *image, const char* data, uint32_t length, Video* video) {
    image->surface = NULL;
    image->texture = NULL;

    SDL_RWops* rw = SDL_RWFromMem((void*)data, length);
    image->surface = SDL_LoadBMP_RW(rw, 1);
    if ( !image->surface ) {
#ifdef __CAENGINE_DEBUG__
        printf("image_load_from_mem(): error loading image: %s\n", SDL_GetError());
#endif  // __CAENGINE_DEBUG__
        return FALSE;
    }

    SDL_SetColorKey(image->surface, SDL_TRUE, SDL_MapRGB(image->surface->format, 0, 0, 0));

    image->texture = SDL_CreateTextureFromSurface(video->renderer, image->surface);
    if ( !image->texture ) {
#ifdef __CAENGINE_DEBUG__
        printf("image_load_from_mem(): error creating texture: %s\n", SDL_GetError());
#endif  // __CAENGINE_DEBUG__
        SDL_FreeSurface(image->surface);
        return FALSE;
    }

    return TRUE;
}

BOOL image_load(Image *image, const  char* filename, Video* video) {
    image->surface = NULL;
    image->texture = NULL;

    image->surface = SDL_LoadBMP(filename);
    if ( !image->surface ) {
#ifdef __CAENGINE_DEBUG__
        printf("image_load(): error loading image: %s\n", SDL_GetError());
#endif  // __CAENGINE_DEBUG__
        return FALSE;
    }

    SDL_SetColorKey(image->surface, SDL_TRUE, SDL_MapRGB(image->surface->format, 0, 0, 0));

    image->texture = SDL_CreateTextureFromSurface(video->renderer, image->surface);
    if ( !image->texture ) {
#ifdef __CAENGINE_DEBUG__
        printf("image_load(): error creating texture: %s\n", SDL_GetError());
#endif  // __CAENGINE_DEBUG__
        SDL_FreeSurface(image->surface);
        return FALSE;
    }

    return TRUE;
}

void image_create(Image* image) {
    image->surface = NULL;
    image->texture = NULL;
}

void image_destroy(Image *image) {
    if ( image->surface ) {
        SDL_FreeSurface(image->surface);
        image->surface = NULL;
    }

    if ( image->texture ) {
        SDL_DestroyTexture(image->texture);
        image->texture = NULL;
    }
}

void image_render(Image *image, int32_t x, int32_t y, Video* video) {
    if (!image) {
#ifndef __CAENGINE_DEBUG__
        printf("image_render(): image is null.\n");
#endif
        return;
    }

    if (!image->surface || !image->texture) {
        return;
    }

    SDL_Rect rect = (SDL_Rect){ x, y, image->surface->w, image->surface->h };
    SDL_RenderCopy(video->renderer, image->texture, NULL, &rect);
}

BOOL image_extract(Image* dst, Image *src, uint32_t x, uint32_t y, uint32_t w, uint32_t h, Video* video) {
    dst->surface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
    if ( !dst->surface ) {
#ifdef __CAENGINE_DEBUG__
        printf("image_extract(): error creating dst image: %s\n", SDL_GetError());
#endif
        return FALSE;
    }

    SDL_Rect rect = (SDL_Rect){ x, y, w, h };
    SDL_BlitSurface(src->surface, &rect, dst->surface, 0);
    SDL_SetColorKey(dst->surface, SDL_TRUE, SDL_MapRGB(dst->surface->format, 0, 0, 0));

    dst->texture = SDL_CreateTextureFromSurface(video->renderer, dst->surface);
    if ( !dst->texture ) {
#ifdef __CAENGINE_DEBUG__
        printf("image_extract(): error creating texture: %s\n", SDL_GetError());
#endif  // __CAENGINE_DEBUG__
        SDL_FreeSurface(dst->surface);
        return FALSE;
    }

    return TRUE;
}

BOOL image_copy(Image* dst, const Image* src, Video* video) {
    dst->surface = SDL_CreateRGBSurface(0, src->surface->w, src->surface->h, 32, 0, 0, 0, 0);
    if ( !dst->surface ) {
#ifdef __CAENGINE_DEBUG__
        printf("image_copy(): error creating dst image: %s\n", SDL_GetError());
#endif
        return FALSE;
    }

    SDL_Rect rect = (SDL_Rect){ 0, 0, src->surface->w, src->surface->h };
    SDL_BlitSurface(src->surface, &rect, dst->surface, 0);
    SDL_SetColorKey(dst->surface, SDL_TRUE, SDL_MapRGB(dst->surface->format, 0, 0, 0));

    dst->texture = SDL_CreateTextureFromSurface(video->renderer, dst->surface);
    if ( !dst->texture ) {
#ifdef __CAENGINE_DEBUG__
        printf("image_copy(): error creating texture: %s\n", SDL_GetError());
#endif  // DEBUG_IMAGE
        SDL_FreeSurface(dst->surface);
        return FALSE;
    }

    return TRUE;
}

void image_set_alpha(Image* image, uint8_t alpha) {
    SDL_SetTextureBlendMode(image->texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(image->texture, alpha);
}


uint32_t surface_get_pixel(SDL_Surface* surface, int x, int y) {
    const uint32_t bpp = surface->format->BytesPerPixel;
    uint8_t *p = (uint8_t*)surface->pixels + y * surface->pitch + x * bpp;
    return *(uint32_t*)p;
}

void surface_set_pixel(SDL_Surface* surface, int x, int y, uint32_t pixel) {
    uint32_t *pixels = (uint32_t*)surface->pixels;
    pixels[(y * surface->w) + x] = pixel;
}

BOOL image_pal_load(PAL* pal, const char* data, uint32_t length){
    if (length != sizeof(PAL)) {
        return FALSE;
    }

    memcpy(pal->color, data, length);
    return TRUE;
}

BOOL image_create_texture(Image* dst, const Image* src, uint32_t width, uint32_t height, Video* video)	{
	const uint32_t w = width / src->surface->w;
	const uint32_t ow = width % src->surface->w;
	const uint32_t h = height / src->surface->h;
	const uint32_t oh = height % src->surface->h;

	SDL_Rect rect = (SDL_Rect){ 0, 0, ow, oh };

	// TODO Create an image width x height with repeated texture

	return FALSE;
}
