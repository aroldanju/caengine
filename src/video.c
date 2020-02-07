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

#ifdef __APPLE__
#   include <SDL2_ttf/SDL_ttf.h>
#else
#   include <SDL2/SDL_ttf.h>
#endif
#include "video.h"

BOOL video_init(Video* video)    {
    SDL_Surface* iconSurface = NULL;

    video->window = SDL_CreateWindow(video->title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, video->windowWidth, video->windowHeight, SDL_WINDOW_RESIZABLE);
    if (!video->window) {
#ifdef __CAENGINE_DEBUG__
        printf("video_init(): error creating window: %s\n", SDL_GetError());
#endif
        return FALSE;
    }

    video->renderer = SDL_CreateRenderer(video->window, -1, 0);
    if (!video->renderer) {
#ifdef __CAENGINE_DEBUG__
        printf("video_init(): error creating renderer: %s\n", SDL_GetError());
#endif
        return FALSE;
    }

    video->fpsCount = video->fpsCurrent = 0;
    video->fpsTick = SDL_GetTicks();
    video->lastFpsTick = video->fpsTick;

    char hint[8];
    sprintf(hint, "%d", video->renderQuality);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, hint);

    SDL_RenderSetLogicalSize(video->renderer, video->width, video->height);
    SDL_SetWindowSize(video->window, video->windowWidth * 2, video->windowHeight * 2);

    SDL_SetRenderDrawBlendMode(video->renderer, SDL_BLENDMODE_BLEND);

    iconSurface = SDL_LoadBMP(video->icon);
    if (iconSurface)	{
        SDL_SetColorKey(iconSurface, SDL_TRUE, SDL_MapRGB(iconSurface->format, 0, 0, 0));
        SDL_SetWindowIcon(video->window, iconSurface);
        SDL_FreeSurface(iconSurface);
    }
#ifdef __CAENGINE_DEBUG__
    else {
        printf("video_init(): could not set window icon: %s\n", SDL_GetError());
    }
#endif

    if (TTF_Init() != 0) {
#ifdef __CAENGINE_DEBUG__
        printf("video_init(): error initializing font system: %s\n", SDL_GetError());
#endif
        return FALSE;
    }

    return TRUE;
}

void video_release(Video* video)    {
    TTF_Quit();

    if (video->renderer) {
        SDL_DestroyRenderer(video->renderer);
    }

    if (video->window) {
        SDL_DestroyWindow(video->window);
    }

    video->window = NULL;
    video->renderer = NULL;
}

void video_clear(Video* video)  {
    SDL_RenderClear(video->renderer);
}

void video_render(Video* video) {
    SDL_RenderPresent(video->renderer);

    video->fpsCount++;

    if (SDL_GetTicks() - video->fpsTick >= 1000) {
        video->fpsCurrent = video->fpsCount;
        video->fpsCount = 0;
        video->fpsTick = SDL_GetTicks();

        char title[256];
        sprintf(title, "%s - %d FPS", video->title, video->fpsCurrent);
        SDL_SetWindowTitle(video->window, title);
    }

    video->delta = 1.0f;

    // TODO fix this
    // :/
    const uint32_t delay = (1000 / video->fps);

    const uint32_t elapsed = SDL_GetTicks() - video->lastFpsTick;
    if (elapsed < delay) {
        SDL_Delay(delay - (SDL_GetTicks() - video->lastFpsTick));
    } else {
        video->delta += (float) video->fps / 1000.0f * (float) (elapsed - delay);
    }

    video->lastFpsTick = SDL_GetTicks();
}

uint32_t video_get_fps(Video* video)    {
    return video->fpsCurrent;
}

void video_render_line(Video* video, uint32_t fx, uint32_t fy, uint32_t tx, uint32_t ty, uint8_t r, uint8_t g, uint8_t b) {
    SDL_SetRenderDrawColor(video->renderer, r, g, b, 255);
    SDL_RenderDrawLine(video->renderer, fx, fy, tx, ty);

    SDL_SetRenderDrawColor(video->renderer, 0,0, 0, 255);
}

void video_render_rect(Video* video, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t r, uint8_t g, uint8_t b)  {
    SDL_SetRenderDrawColor(video->renderer, r, g, b, 255);
    SDL_Rect rect = (SDL_Rect){x, y, w, h};
    SDL_RenderFillRect(video->renderer, &rect);

    SDL_SetRenderDrawColor(video->renderer, 0,0, 0, 255);
}

void video_render_rect_alpha(Video* video, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t r, uint8_t g, uint8_t b, uint8_t a)  {
    SDL_SetRenderDrawColor(video->renderer, r, g, b, a);
    SDL_Rect rect = (SDL_Rect){x, y, w, h};
    SDL_RenderFillRect(video->renderer, &rect);

    SDL_SetRenderDrawColor(video->renderer, 0,0, 0, 255);
}