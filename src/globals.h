#ifndef GLOBALS_H
#define GLOBALS_H

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define N_SDL_KEYS 322
#define TICKS_PER_SECOND 1000
#define FRAMES_PER_SECOND 60
#define TICKS_PER_FRAME TICKS_PER_SECOND/FRAMES_PER_SECOND

#define TITLE "Cachicamo"

#include <stdlib.h>


struct _game_t {
    size_t time;
    size_t deltaTime;
};

extern struct _game_t mainGame;

#endif
