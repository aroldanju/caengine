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

#include "resources.h"

void resources_create(Resources* resources) {
    int i;

    resources->numImages = 0;
    for (i = 0; i < RESOURCES_MAX_IMAGES; i++) {
        resources->images[i] = NULL;
    }

    resources->numSounds = 0;
    for (i = 0; i < RESOURCES_MAX_SOUNDS; i++) {
        resources->sounds[i] = NULL;
    }

    resources->numFonts = 0;
    for (i = 0; i < RESOURCES_MAX_FONTS; i++) {
        resources->fonts[i] = NULL;
    }

    resources->numMusics = 0;
    for (i = 0; i < RESOURCE_MAX_MUSICS; i++) {
        resources->musics[i] = NULL;
    }

    resources->numPalettes = 0;
}

void resources_add_image(Resources* resources, Image* image)   {

	if (resources->numImages >= RESOURCES_MAX_IMAGES) {
#ifdef __CAENGINE_DEBUG__
		printf("resources_add_image(): max number of images reached %d\n", RESOURCES_MAX_IMAGES);
#endif
		return;
	}

    resources->images[resources->numImages] = image;
    resources->numImages++;
}


void resources_add_music(Resources* resources, Music* music) {
    resources->musics[resources->numMusics] = music;
    resources->numMusics++;
}

void resources_add_sound(Resources* resources, Sound *sfx)   {
    resources->sounds[resources->numSounds] = sfx;
    resources->numSounds++;
}

void resources_add_font(Resources* resources, Ttf *ttf)   {
    resources->fonts[resources->numFonts] = ttf;
    resources->numFonts++;
}

void resources_add_palette(Resources* resources, PAL *palette)   {
    resources->palettes[resources->numPalettes] = palette;
    resources->numPalettes++;
}

void resources_release(Resources* resources)    {
    int i ;

    for (i = 0; i < resources->numImages; i++) {
        image_destroy(resources->images[i]);
        resources->images[i] = NULL;
    }
    resources->numImages = 0;

    for (i = 0; i < resources->numSounds; i++) {
        sound_destroy(resources->sounds[i]);
        resources->sounds[i] = NULL;
    }
    resources->numSounds = 0;

    for (i = 0; i < resources->numFonts; i++) {
        ttf_destroy(resources->fonts[i]);
        resources->fonts[i] = NULL;
    }
    resources->numFonts = 0;

    for (i = 0; i < resources->numMusics; i++) {
        music_release(resources->musics[i]);
        resources->musics[i] = NULL;
    }
    resources->numMusics = 0;
}