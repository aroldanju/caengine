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

#ifndef sprite_h
#define sprite_h

#include "defs.h"
#include "animation.h"

#define SPRITE_MAXSTATES    3

typedef struct _sprite {
    uint32_t currentState;
    uint32_t numStates;
    Animation states[SPRITE_MAXSTATES];
} Sprite;

void sprite_create(Sprite* sprite);
Animation* sprite_createState(Sprite* sprite);
void sprite_addState(Sprite* sprite, Image* image);
void sprite_set_current_state(Sprite* sprite, uint32_t state);
void sprite_update(Sprite* sprite);
void sprite_render(Sprite* sprite, Video* video, int32_t x, int32_t y);
void sprite_release(Sprite *sprite);
void sprite_copy(Sprite* dst, const Sprite* src);
Animation* sprite_getCurrentState(Sprite *sprite);

#endif // sprite_h