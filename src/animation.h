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

#ifndef animation_h
#define animation_h

#include "defs.h"
#include "video.h"
#include "image.h"

#define ANIMATION_MAXFRAMES     35

typedef struct _animation {
    uint32_t      delay;
    BOOL        infinite;
    uint32_t      currentFrame;
    uint32_t      numFrames;
    Image       *frames[ANIMATION_MAXFRAMES];
    uint32_t      lastTick;
    BOOL        finished;
} Animation;

void animation_copy(Animation* dst, const Animation *src);
void animation_reset(Animation * animation);
void animation_create(Animation* animation, uint32_t delay);
int32_t animation_addFrame(Animation* animation, Image* frame);
void animation_update(Animation* animation);
void animation_render(Animation* animation, Video *video, int32_t x, int32_t y);
BOOL animation_ended(Animation* animation);
Image* animation_getCurrentFrame(Animation* animation);
BOOL animation_hasFinished(const Animation* animation);

#endif // animation_h
