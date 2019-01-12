#ifndef CACHICAMO_H
#define CACHICAMO_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL.h>
#include <SDL_image.h>

#include "globals.h"

#include "behaviour.h"
#include "collision.h"
#include "graphics.h"
#include "input.h"
#include "logging.h"
#include "position_c.h"
#include "sprite.h"


void init(void);
void frameStart(void);
void frameEnd(void);

int handleEvents(void);

void cachicamo_processFrame();


#endif
