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

#include "sound.h"

void sound_set_volume(Sound* sound, uint8_t vol)   {
    sound->volume = vol;
}

BOOL sound_load_from_mem(Sound* sound, const char* data, uint32_t length, AUDIO* audio)   {
    SDL_RWops* rWops = SDL_RWFromMem((void*)data, length);

    sound->sdlSound = Mix_LoadWAV_RW(rWops, 1);
    if( !sound->sdlSound ) {
#ifdef __CAENGINE_DEBUG__
        printf("sound_load(): Error loading sound: %s\n", Mix_GetError());
#endif
        return FALSE;
    }

    sound->volume = audio->settings.soundVol;

    Mix_VolumeChunk(sound->sdlSound, sound->volume);

    return TRUE;
}


BOOL sound_load(Sound* sound, const char* filename, AUDIO* audio)   {
    sound->sdlSound = Mix_LoadWAV(filename);
    if( !sound->sdlSound ) {
#ifdef __CAENGINE_DEBUG__
        printf("sound_load(): Error loading sound: %s\n", Mix_GetError());
#endif
        return FALSE;
    }

    sound->volume = 127;

    Mix_VolumeChunk(sound->sdlSound, sound->volume);

    return TRUE;
}

void sound_destroy(Sound* sound)    {
    if ( sound ) {
        if ( sound->sdlSound ) {
            Mix_FreeChunk(sound->sdlSound);
            sound->sdlSound = NULL;
        }
    }
}

void sound_play(Sound* sound)   {
    if ( Mix_PlayChannel(-1, sound->sdlSound, 0) == -1 ) {

#ifdef __CAENGINE_DEBUG__
        printf("sound_play(): Error playing sound: %s\n", Mix_GetError());
#endif

    }
}