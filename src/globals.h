#ifndef GLOBALS_H
#define GLOBALS_H

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define N_SDL_KEYS 322
#define TICKS_PER_SECOND 1000
#define FRAMES_PER_SECOND 60
#define TICKS_PER_FRAME TICKS_PER_SECOND/FRAMES_PER_SECOND

#define TITLE "dicks"

#include <stdint.h>

#include <SDL.h>
#include <SDL_image.h>

struct _game_t {
    SDL_Window* window;
    SDL_Surface* screenSurface;
    SDL_Renderer* renderer;
    uint32_t time;
};

extern struct _game_t mainGame;

#endif
