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

#include "engine.h"

BOOL engine_init(Engine* engine) {

    printf("Initializing video system...\n");
    if (!video_init(&engine->video)) {
#ifdef __CAENGINE_DEBUG__
        printf("engine_init(): error initializing video.\n");
#endif
        return FALSE;
    }

    printf("Initializing audio system...\n");
    if (!audio_init(&engine->audio)) {
#ifdef __CAENGINE_DEBUG__
        printf("engine_init(): error initializing audio.\n");
#endif
        return FALSE;
    }

    resources_create(&G_RESOURCES);

    return TRUE;
}

void engine_release(Engine* engine) {
    resources_release(&G_RESOURCES);
    audio_release(&engine->audio);
    video_release(&engine->video);
}