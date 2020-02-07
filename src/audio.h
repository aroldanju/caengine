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

#ifndef audio_h
#define audio_h

#if defined(__APPLE__)
#	include <SDL2_mixer/SDL_mixer.h>
#elif defined(__WIN32__) || defined(__WIN64__)
#	include <SDL2/SDL_mixer.h>
#else
# 	include <SDL2/SDL_mixer.h>
#endif

#include "defs.h"

typedef struct _audio_settings {
    BOOL 	enabled;
	uint8_t		musicVol;
    uint8_t		soundVol;
    BOOL		musicEnabled;
    BOOL		soundEnabled;
} AUDIO_SETTINGS;

typedef struct _audio {
	AUDIO_SETTINGS	settings;
} AUDIO;

void audio_set_music_volume(AUDIO* audio, uint8_t vol);
void audio_set_sound_volume(AUDIO* audio, uint8_t vol);

void audio_toggle_music(AUDIO* audio);
void audio_toggle_sound(AUDIO* audio);

BOOL audio_init(AUDIO* audio);

void audio_disable(AUDIO* audio);
void audio_enable(AUDIO* audio);

BOOL audio_is_playing_music();
void audio_stop_music();

void audio_release(AUDIO* audio);

#endif // audio_h
