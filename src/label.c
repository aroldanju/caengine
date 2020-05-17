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

#include "label.h"

void label_create(Label* label, Ttf* font)  {
    label->needUpdate = TRUE;
    label->font = font;
    strcpy(label->caption, "");

    label->image.surface = NULL;
    label->image.texture = NULL;

    label->image.alpha = 255;
    label->image.colorMod = FALSE;
}

void label_setCaption(Label* label, const char* caption) {
    strcpy(label->caption, caption);
    label->needUpdate = TRUE;
}

void label_render(Label* label, Video* video, int x, int y) {
    if (strlen(label->caption) == 0) {
        return;
    }

    if (label->needUpdate) {
        label->image.surface = ttf_render( label->font, label->caption, label->r, label->g, label->b );
        label->image.texture = SDL_CreateTextureFromSurface(video->renderer, label->image.surface);
        label->needUpdate = FALSE;
    }

    image_render(&label->image, x, y, video);
}

void label_render_wrap(Label* label, Video* video, int x, int y, int w) {
    if (strlen(label->caption) == 0) {
        return;
    }

    if (label->needUpdate) {
        label->image.surface = ttf_render_wrap( label->font, label->caption, label->r, label->g, label->b, w );
        label->image.texture = SDL_CreateTextureFromSurface(video->renderer, label->image.surface);
        label->needUpdate = FALSE;
    }

    image_render(&label->image, x, y, video);
}

void label_destroy(Label* label) {
    if (strlen(label->caption) == 0) {
        return;
    }

    image_destroy(&label->image);
}

void label_setFont(Label* label, Ttf* ttf) {
    label->font = ttf;
    label->needUpdate = TRUE;
}

void label_setColor(Label* label, uint8_t r, uint8_t g, uint8_t b) {
    label->r = r;
    label->g = g;
    label->b = b;
    label->needUpdate = TRUE;
}

uint32_t label_get_width(Label* label)  {
    if (!label->needUpdate && label->image.surface) {
        return label->image.surface->w;
    }

    return 0;
}