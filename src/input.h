#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

#include <SDL.h>

#include "globals.h"
#include "entity.h"

struct {
  bool keys[N_SDL_KEYS];
  void (*actions[N_SDL_KEYS])(void*);
  void** actionArgs;
} input;

void input_init(void);

void input_keyDown(SDL_Scancode);
void input_keyUp(SDL_Scancode);

void input_register(SDL_Scancode, void (*)(void*), void*);

void input_process(void);

#endif
