#include "input.h"

void input_init(void) {
  input.actionArgs = malloc(sizeof(void*) * N_SDL_KEYS);
  for(int i=0; i<N_SDL_KEYS; i++) {
    input.keys[i] = false;
    input.actions[i] = NULL;
    input.actionArgs[i] = NULL;
  }
}

void input_keyDown(SDL_Scancode scancode) {
  input.keys[scancode] = true;
}

void input_keyUp(SDL_Scancode scancode) {
  input.keys[scancode] = false;
}

void input_register(SDL_Scancode scancode, void (*action)(void*), void* args) {
  input.actions[scancode] = action;
  input.actionArgs[scancode] = args;
}

void input_process(void) {
  for(int i=0; i<N_SDL_KEYS; i++) {
    if(input.keys[i] && input.actions[i] != NULL) {
      input.actions[i](input.actionArgs[i]);
    }
  }
}
