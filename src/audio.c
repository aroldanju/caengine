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

#include "audio.h"

void audio_release(AUDIO* audio) {
    Mix_CloseAudio();
}

BOOL audio_init(AUDIO* audio)	{
    /*
    if (Mix_Init(MIX_INIT_MID) != 0) {
#ifdef __CAENGINE_DEBUG__
        printf("audio_init(): error initializing audio: %s\n", Mix_GetError());
#endif
        return FALSE;
    }
    */

	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, AUDIO_U8, 6, 2048)==-1) {
#ifdef __CAENGINE_DEBUG__
	    printf("audio_init(): error initializing audio: %s\n", Mix_GetError());
#endif
		return FALSE;
	}

    Mix_AllocateChannels(16);

	Mix_SetSoundFonts("/usr/share/sounds/sf2/FluidR3_GM.sf2");
	//Mix_SetSoundFonts("/usr/share/sounds/sf3/FluidR3Mono_GM.sf3");
    //Mix_SetSoundFonts("/usr/share/sounds/sf3/MuseScore_General.sf3");

	return TRUE;
}

void audio_set_sound_volume(AUDIO* audio, uint8_t vol)	{
	audio->settings.soundVol = vol;
}

void audio_set_music_volume(AUDIO* audio, uint8_t vol)	{
	audio->settings.musicVol = vol;
	Mix_Volume(0, vol);
}


void audio_toggle_music(AUDIO* audio)	{
	audio->settings.musicEnabled = !audio->settings.musicEnabled;
	if ( audio->settings.musicEnabled == FALSE )	{
		Mix_PauseMusic();
		Mix_VolumeMusic(0);
	}
	else {
		Mix_ResumeMusic();
		Mix_VolumeMusic(audio->settings.musicVol);
	}
}

void audio_toggle_sound(AUDIO* audio)	{
	audio->settings.soundEnabled = !audio->settings.soundEnabled;
	if ( audio->settings.musicEnabled == FALSE )	{
		Mix_HaltChannel(-1);
	}
}


void audio_disable(AUDIO* audio)	{
	audio->settings.enabled = FALSE;

}

void audio_enable(AUDIO* audio)	{
	audio->settings.enabled = TRUE;
}


BOOL audio_is_playing_music()	{
	if ( Mix_PlayingMusic() == SDL_TRUE )	{
		return TRUE;
	}

	return FALSE;
}

void audio_stop_music()	{
	Mix_PausedMusic();
}

