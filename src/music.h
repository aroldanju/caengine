#ifndef music_h
#define music_h

#ifdef __APPLE__
#include <SDL2_mixer/SDL_mixer.h>
#else
#include <SDL2/SDL_mixer.h>
#endif

#include "defs.h"
#include "audio.h"

typedef struct _music {
    Mix_Music* sdlMusic;
    uint8_t volume;
    BOOL enabled;
} Music;

void music_setVolume(Music* music, uint8_t vol);
void music_disable(Music* music);
void music_enable(Music* music);

BOOL music_load(Music* music, const char *filename);
BOOL music_load_from_mem(Music* music, const char *data, uint32_t length, AUDIO* audio);
void music_play(Music* music);
void music_play_loops(Music* music, int loops);
void music_stop(Music* music);
void music_release(Music* music);
void music_resume(Music* music);
void music_pause(Music* music);

#endif // music_h