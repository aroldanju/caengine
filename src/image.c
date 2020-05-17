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

BOOL image_create_blank(Image* image)	{
	image->surface = NULL;
	image->texture = NULL;
	image->needUpdate = FALSE;
	image->alpha = 255;
	image->red = image->green = image->blue = 0;
	image->colorMod = FALSE;

	return TRUE;
}

BOOL image_create_blank_sized(Image* image, uint32_t w, uint32_t h) {
    image_create_blank(image);
    image->surface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
    image->needUpdate = TRUE;

    SDL_SetColorKey(image->surface, SDL_TRUE, SDL_MapRGB(image->surface->format, 0, 0, 0));

    return TRUE;
}

BOOL image_load_img(Image *image, const char *data, uint32_t length/*, Video* video*/, const PAL* palette) {
    uint32_t width, height;
    uint8_t r, g, b;
    uint8_t index;
    int i, j;

    width = *(uint32_t*)data;
    height = *(uint32_t*)(data + 4);

    image->colorMod = FALSE;

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

	image->needUpdate = TRUE;
	image->alpha = 255;

	/*
    image->texture = SDL_CreateTextureFromSurface(video->renderer, image->surface);
    if ( !image->texture ) {
#ifdef __CAENGINE_DEBUG__
        printf("image_load_from_mem(): error creating texture: %s\n", SDL_GetError());
#endif  // DEBUG_IMAGE
        SDL_FreeSurface(image->surface);
        return FALSE;
    }
    */

    return TRUE;
}

BOOL image_load_from_mem(Image *image, const char* data, uint32_t length/*, Video* video*/) {
    image->surface = NULL;
    image->texture = NULL;

	image->colorMod = FALSE;

    SDL_RWops* rw = SDL_RWFromMem((void*)data, length);
    image->surface = SDL_LoadBMP_RW(rw, 1);
    if ( !image->surface ) {
#ifdef __CAENGINE_DEBUG__
        printf("image_load_from_mem(): error loading image: %s\n", SDL_GetError());
#endif  // __CAENGINE_DEBUG__
        return FALSE;
    }

    SDL_SetColorKey(image->surface, SDL_TRUE, SDL_MapRGB(image->surface->format, 0, 0, 0));

    image->needUpdate = TRUE;

    /*
    image->texture = SDL_CreateTextureFromSurface(video->renderer, image->surface);
    if ( !image->texture ) {
#ifdef __CAENGINE_DEBUG__
        printf("image_load_from_mem(): error creating texture: %s\n", SDL_GetError());
#endif  // __CAENGINE_DEBUG__
        SDL_FreeSurface(image->surface);
        return FALSE;
    }
    */

    return TRUE;
}

BOOL image_load(Image *image, const  char* filename/*, Video* video*/) {
    image->surface = NULL;
    image->texture = NULL;

	image->colorMod = FALSE;

    image->surface = SDL_LoadBMP(filename);
    if ( !image->surface ) {
#ifdef __CAENGINE_DEBUG__
        printf("image_load(): error loading image: %s\n", SDL_GetError());
#endif  // __CAENGINE_DEBUG__
        return FALSE;
    }

    SDL_SetColorKey(image->surface, SDL_TRUE, SDL_MapRGB(image->surface->format, 0, 0, 0));

    image->needUpdate = TRUE;

    /*
    image->texture = SDL_CreateTextureFromSurface(video->renderer, image->surface);
    if ( !image->texture ) {
#ifdef __CAENGINE_DEBUG__
        printf("image_load(): error creating texture: %s\n", SDL_GetError());
#endif  // __CAENGINE_DEBUG__
        SDL_FreeSurface(image->surface);
        return FALSE;
    }
    */

    return TRUE;
}

void image_create(Image* image) {
    image->surface = NULL;
    image->texture = NULL;
    image->alpha = 255;
	image->colorMod = FALSE;
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

void image_render_sized(Image* image, int32_t x, int32_t y, uint32_t w, uint32_t h, Video *video) {
	if (!image) {
#ifndef __CAENGINE_DEBUG__
		printf("image_render_sized(): image is null.\n");
#endif
		return;
	}

	if (!image->surface) {
#ifndef __CAENGINE_DEBUG__
		printf("image_render_sized(): image surface is null.\n");
#endif
		return;
	}

	if (image->needUpdate) {
		if (image->texture) {
			SDL_DestroyTexture(image->texture);
		}

		image->texture = SDL_CreateTextureFromSurface(video->renderer, image->surface);
		if (!image->texture) {
#ifdef __CAENGINE_DEBUG__
			printf("image_render(): error creating texture: %s\n", SDL_GetError());
#endif  // __CAENGINE_DEBUG__
			SDL_FreeSurface(image->surface);
			return;
		}

		image_set_alpha(image, image->alpha);
		if (image->colorMod) {
			image_set_color_mod(image, image->red, image->green, image->blue);
		}

		image->needUpdate = FALSE;
	}

	SDL_Rect rect = (SDL_Rect){ x, y, w == -1 ? image->surface->w : w, h == -1 ? image->surface->h : h };
	SDL_RenderCopy(video->renderer, image->texture, NULL, &rect);
}

void image_render(Image *image, int32_t x, int32_t y, Video* video) {
	if (!image->surface) {
#ifndef __CAENGINE_DEBUG__
		printf("image_render(): image surface is null.\n");
#endif
		return;
	}

	image_render_sized(image, x, y, image->surface->w, image->surface->h, video);
}

BOOL image_extract(Image* dst, Image *src, uint32_t x, uint32_t y, uint32_t w, uint32_t h/*, Video* video*/) {

	image_create_blank(dst);

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

    dst->needUpdate = TRUE;

    /*
    dst->texture = SDL_CreateTextureFromSurface(video->renderer, dst->surface);
    if ( !dst->texture ) {
#ifdef __CAENGINE_DEBUG__
        printf("image_extract(): error creating texture: %s\n", SDL_GetError());
#endif  // __CAENGINE_DEBUG__
        SDL_FreeSurface(dst->surface);
        return FALSE;
    }
    */

    return TRUE;
}

BOOL image_extract_destination(Image* dst, Image *src, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t tx, uint32_t ty, uint32_t tw, uint32_t th) {
    if (!dst->surface) {
        return FALSE;
    }

    SDL_Rect rect = (SDL_Rect){ x, y, w, h };
    SDL_Rect rectdst = (SDL_Rect){ tx, ty, tw, th };
    SDL_BlitSurface(src->surface, &rect, dst->surface, &rectdst);
    SDL_SetColorKey(dst->surface, SDL_TRUE, SDL_MapRGB(dst->surface->format, 0, 0, 0));

    dst->needUpdate = TRUE;

    return TRUE;
}

BOOL image_copy(Image* dst, const Image* src/*, Video* video*/) {
	if (dst->surface) {
		SDL_FreeSurface(dst->surface);
		dst->surface = NULL;
	}

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

    dst->needUpdate = TRUE;

    /*
    dst->texture = SDL_CreateTextureFromSurface(video->renderer, dst->surface);
    if ( !dst->texture ) {
#ifdef __CAENGINE_DEBUG__
        printf("image_copy(): error creating texture: %s\n", SDL_GetError());
#endif  // DEBUG_IMAGE
        SDL_FreeSurface(dst->surface);
        return FALSE;
    }
    */

    return TRUE;
}

void image_set_alpha(Image* image, uint8_t alpha) {

	image->alpha = alpha;

	if (image->texture) {
		SDL_SetTextureBlendMode(image->texture, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(image->texture, alpha);
	}
	else {
		image->needUpdate = TRUE;
	}
}

void image_set_color_mod(Image* image, uint8_t r, uint8_t g, uint8_t b)	{
	image->red = r;
	image->green = g;
	image->blue = b;
	image->colorMod = TRUE;

	if (image->texture) {
		SDL_SetTextureColorMod(image->texture, r, g, b);
	}
	else {
		image->needUpdate = TRUE;
	}
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

BOOL image_create_texture(Image* dst, const Image* src, uint32_t width, uint32_t height/*, Video* video*/)	{
	const uint32_t w = width / src->surface->w;
	const uint32_t ow = width % src->surface->w;
	const uint32_t h = height / src->surface->h;
	const uint32_t oh = height % src->surface->h;

	SDL_Rect rect = (SDL_Rect){ 0, 0, ow, oh };

	// TODO Create an image width x height with repeated texture

	return FALSE;
}
