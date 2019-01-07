#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL.h>
#include <SDL_image.h>

#include "collision.h"
#include "globals.h"
#include "input.h"
#include "graphics.h"
#include "logging.h"
#include "sprite.h"
#include "position_c.h"


void init(void);
void frameStart(void);
void frameEnd(void);

int handleEvents(void);


#endif
