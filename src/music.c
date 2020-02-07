#include "music.h"

void music_setVolume(Music* music, uint8_t vol)   {
    music->volume = vol;
}

void music_disable(Music* music)    {
    music->enabled = FALSE;
}

void music_enable(Music* music) {
    music->enabled = TRUE;
}

BOOL music_load_from_mem(Music* music, const char *data, uint32_t length, AUDIO* audio)   {
    SDL_RWops* r = SDL_RWFromMem((void*)data, length);
    music->sdlMusic = Mix_LoadMUS_RW(r, 1);
    if ( !music->sdlMusic ) {
        return FALSE;
    }

    music->enabled = TRUE;
    music->volume = audio->settings.musicVol;
    Mix_VolumeMusic(music->volume);

    return TRUE;
}

BOOL music_load(Music* music, const char *filename) {
    music->sdlMusic = Mix_LoadMUS(filename);
    if ( !music->sdlMusic ) {
        return FALSE;
    }

    music->enabled = TRUE;
    music->volume = 127;
    Mix_VolumeMusic(music->volume);

    return TRUE;
}

void music_play(Music* music) {
    music_play_loops(music, 0);
}

void music_play_loops(Music* music, int loops){
    if (music->enabled)   {
    	Mix_HaltMusic();
		Mix_RewindMusic();
        Mix_PlayMusic(music->sdlMusic, loops);
    }
}

void music_stop(Music* music) {
    Mix_HaltMusic();
}

void music_release(Music* music) {
    Mix_FreeMusic(music->sdlMusic);
}

void music_resume(Music* music) {
    if ( music->enabled )   {

        Mix_ResumeMusic();
    }
}

void music_pause(Music* music)  {
    Mix_PauseMusic();
}