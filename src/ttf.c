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

#include "ttf.h"

BOOL ttf_loadFromMem(Ttf* font, char *data, unsigned int len, uint32_t size)  {
    font->font = TTF_OpenFontRW( SDL_RWFromMem(data, len), 1, size );
    if ( !font->font ) {
#ifdef __CAENGINE_DEBUG__
        printf("ttf_loadFromMem(): error loading ttf: %s\n", TTF_GetError());
#endif
        return FALSE;
    }

    font->size = size;

    return TRUE;
}

BOOL ttf_loadFromFile(Ttf* font, const char* filename, uint32_t size)  {
    font->font = TTF_OpenFont( filename, size );
    if ( !font->font ) {
#ifdef __CAENGINE_DEBUG__
        printf("ttf_loadFromFile(): error loading ttf: %s\n", TTF_GetError());
#endif
        return FALSE;
    }

    font->size = size;

    return TRUE;
}

void ttf_destroy(Ttf *font)    {
    TTF_CloseFont( font->font );
}

uint32_t ttf_getWidth(Ttf* font, const char* text) {
    SDL_Surface *surface = ttf_render(font, text, 0,0,0);
    if ( surface != NULL ) {
        const uint32_t width = surface->w;
        SDL_FreeSurface(surface);
        return width;
    }

    return 0;
}

SDL_Surface* ttf_render(Ttf * font, const char* text, uint8_t r, uint8_t g, uint8_t b)  {
    SDL_Surface *surface = TTF_RenderText_Blended(font->font, text, (SDL_Color){r, g, b});
    return surface;
}

SDL_Surface* ttf_render_wrap(Ttf * font, const char* text, uint8_t r, uint8_t g, uint8_t b, uint32_t w)  {
    SDL_Surface *surface = TTF_RenderText_Blended_Wrapped(font->font, text, (SDL_Color){r, g, b}, w);
    return surface;
}