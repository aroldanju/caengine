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

#ifndef __label_h__
#define __label_h__

#include "image.h"
#include "ttf.h"

typedef struct _label {
    Ttf         *font;
    char        caption[256];
    Image       image;
    BOOL        needUpdate;
    uint8_t     r, g, b;
} Label;

void label_create(Label* label, Ttf* font);

void label_setCaption(Label* label, const char* caption);

void label_render(Label* label, Video* video, int x, int y);
void label_render_wrap(Label* label, Video* video, int x, int y, int w);

void label_destroy(Label* label);

void label_setFont(Label* label, Ttf* font);

void label_setColor(Label* label, uint8_t r, uint8_t g, uint8_t b);

uint32_t label_get_width(Label* label);

#endif// __label_h__
