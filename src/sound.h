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

#ifndef __sound_h
#define __sound_h

#include <stdio.h>
#ifdef __APPLE__
#   include <SDL2_mixer/SDL_mixer.h>
#else
#   include <SDL2/SDL_mixer.h>
#endif
#include "defs.h"
#include "audio.h"

//#define playSound sound_play

typedef struct _sound {
    Mix_Chunk* sdlSound;
    uint8_t volume;
} Sound;

void sound_set_volume(Sound* sound, uint8_t vol);

BOOL sound_load_from_mem(Sound* sound, const char* data, uint32_t length, AUDIO* audio);
BOOL sound_load(Sound* sound, const char* filename, AUDIO* audio);
void sound_destroy(Sound* sound);
void sound_play(Sound* sound);

#endif // sound_h