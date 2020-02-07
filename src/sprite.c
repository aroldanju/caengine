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

#include "sprite.h"

void sprite_create(Sprite* sprite)  {
    int i;

    sprite->currentState = 0;
    sprite->numStates = 0;

    for ( i = 0; i < SPRITE_MAXSTATES; i++ ) {
        animation_create(&sprite->states[i], 0);
    }
}

void sprite_set_current_state(Sprite* sprite, uint32_t state)   {
    if ( state >= sprite->numStates ) {
#ifdef __CAENGINE_DEBUG__
        printf("sprite_setCurrentState(): Error state out of bounds (%d/%d)\n", state, sprite->numStates);
#endif
        return;
    }

    animation_reset(&sprite->states[state]);
    sprite->currentState = state;
}

Animation* sprite_createState(Sprite* sprite)   {
    // Returns last state created
    animation_create(&sprite->states[sprite->numStates], 0);
    sprite->numStates++;
    return &sprite->states[sprite->numStates - 1];
}

void sprite_addState(Sprite* sprite, Image* image)    {
    Animation* animation = sprite_createState(sprite);
    animation_create(animation, 0);
    animation_addFrame(animation, image);
}


void sprite_update(Sprite* sprite)    {
    animation_update(&sprite->states[sprite->currentState]);
}

void sprite_render(Sprite* sprite, Video* video, int32_t x, int32_t y)  {
    if ( sprite->numStates == 0 ) {
#ifdef __CAENGINE_DEBUG__
        printf("sprite_render(): Sprite has not any state");
#endif
        return;
    }

    animation_render(&sprite->states[sprite->currentState], video, x, y);
}

void sprite_release(Sprite *sprite) {
    int i;

    for (i = 0; i < sprite->numStates; i++) {
        sprite->states[i].numFrames = 0;
        sprite->states[i].currentFrame = 0;
    }

    sprite->numStates = 0;
    sprite->currentState = 0;
}

Animation* sprite_getCurrentState(Sprite *sprite)   {
    return &sprite->states[sprite->currentState];
}

void sprite_copy(Sprite* dst, const Sprite* src)    {
    int i;

    dst->currentState = src->currentState;
    dst->numStates = src->numStates;

    for ( i=0;i<src->numStates;i++){
        animation_copy(&dst->states[i], &src->states[i]);
    }
}