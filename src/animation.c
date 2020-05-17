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

#include "animation.h"

void animation_copy(Animation* dst, const Animation *src)   {
    int i;

    dst->delay= src->delay;
    dst->numFrames = src->numFrames;
    dst->currentFrame = src->currentFrame;
    dst->infinite = src->infinite;
    dst->lastTick = src->lastTick;
    dst->finished = src->finished;

    for ( i = 0; i < src->numFrames; i++ ) {
        dst->frames[i] = src->frames[i];
    }
}

void animation_create(Animation* animation, uint32_t delay)   {
    animation->delay= delay;
    animation->numFrames = 0;
    animation->currentFrame = 0;
    animation->infinite = TRUE;
    animation->lastTick = 0;
    animation->finished = FALSE;
}

int32_t animation_addFrame(Animation* animation, Image* frame)   {
    animation->frames[animation->numFrames] = frame;
    animation->numFrames++;
    return 0;
}

void animation_reset(Animation * animation) {
    animation->currentFrame = 0;
    animation->finished = FALSE;
    animation->lastTick = SDL_GetTicks();
}

BOOL animation_ended(Animation* animation)  {
    return ( animation->currentFrame >= animation->numFrames ) ;
}

void animation_update(Animation* animation/*, uint32 elapsed*/) {

    // Ignore updates if delay is 0 or number of frames is 0
    if ( animation->delay == 0 || animation->numFrames == 0 ) {
        return;
    }

    // Inifite check
    if ( !animation->infinite && animation->finished ) {
        return;
    }

    if (SDL_GetTicks() - animation->lastTick >= animation->delay ) {
        animation->currentFrame++;
        if ( animation->currentFrame >= animation->numFrames ) {
            if ( animation->infinite ) {
                animation->currentFrame = 0;
            }
            else {
                //animation->currentFrame = animation->numFrames - 1;
                animation->finished = TRUE;
            }
        }

        animation->lastTick = SDL_GetTicks();
    }
}

void animation_render_size(Animation* animation, Video* video, int32_t x, int32_t y, int32_t w, int32_t h) {

    if (animation->finished && !animation->infinite) {
        // If animation has finished and it is not infinite, render the last frame
        image_render(animation->frames[animation->numFrames - 1], x, y, video);
    }
    else {

        if (animation->currentFrame >= animation->numFrames) {
#ifdef __CAENGINE_DEBUG__
            printf("animation_render(): invalid current frame (%d of %d)", animation->currentFrame,
                   animation->numFrames);
#endif
            return;
        }

        image_render_sized(animation->frames[animation->currentFrame], x, y, w, h, video);
    }
}

void animation_render(Animation* animation, Video* video, int32_t x, int32_t y) {

    if (animation->finished && !animation->infinite) {
        // If animation has finished and it is not infinite, render the last frame
        image_render(animation->frames[animation->numFrames - 1], x, y, video);
    }
    else {

        if (animation->currentFrame >= animation->numFrames) {
#ifdef __CAENGINE_DEBUG__
            printf("animation_render(): invalid current frame (%d of %d)", animation->currentFrame,
                   animation->numFrames);
#endif
            return;
        }

        image_render(animation->frames[animation->currentFrame], x, y, video);
    }
}

Image* animation_getCurrentFrame(Animation* animation) {
    return animation->frames[animation->currentFrame];
}

BOOL animation_hasFinished(const Animation* animation)  {
    return animation->finished;
}
