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

#ifndef __resources_h
#define __resources_h

#include "image.h"
#include "sound.h"
#include "ttf.h"
#include "music.h"
#include "animation.h"

#define RESOURCES_MAX_IMAGES    	512
#define RESOURCES_MAX_SOUNDS    	16
#define RESOURCES_MAX_FONTS     	1
#define RESOURCE_MAX_MUSICS     	8
#define RESOURCES_MAX_PALETTES     	1
#define RESOURCE_MAX_ANIMATIONS     2

typedef struct _resources {
    uint32_t    numImages;
    Image       *images[RESOURCES_MAX_IMAGES];

    uint32_t    numSounds;
    Sound       *sounds[RESOURCES_MAX_SOUNDS];

    uint32_t    numFonts;
    Ttf         *fonts[RESOURCES_MAX_FONTS];

    uint32_t    numPalettes;
    PAL         *palettes[RESOURCES_MAX_PALETTES];

    uint32_t    numMusics;
    Music       *musics[RESOURCE_MAX_MUSICS];

    uint32_t    numAnimations;
    Animation   *animations[RESOURCE_MAX_ANIMATIONS];
} Resources;

extern Resources G_RESOURCES;

void resources_create(Resources* resources);
void resources_add_image(Resources* resources, Image* image);
void resources_add_sound(Resources* resources, Sound* sfx);
void resources_add_music(Resources* resources, Music* music);
void resources_add_font(Resources* resources, Ttf* ttf);
void resources_add_palette(Resources* resources, PAL* palette);
void resources_add_animation(Resources* resources, Animation* animation);
void resources_release(Resources* resources);

#endif  // __resources_h