#include "engine.h"

void init(void) {
  graphics_init();
  input_init();
  entity_init();
  sprite_init();
  position_init();
  collision_init();
  mainGame.time = 0;
  logging_log(DEBUG, "cachicamo", "inited succesfully");
}

void frameStart(void) {
  mainGame.time = SDL_GetTicks();
  graphics_frameStart();
}

void frameEnd(void) {
  
  if((SDL_GetTicks() - mainGame.time) < TICKS_PER_FRAME) {
    unsigned blap = TICKS_PER_FRAME - SDL_GetTicks() + mainGame.time;
    SDL_Delay(blap);
  }
  graphics_frameEnd();
}

int handleEvents(void) {
  static SDL_Event event;

  while(SDL_PollEvent(&event)) {
    switch(event.type) {
      case SDL_QUIT: return 0;
      case SDL_KEYDOWN: input_keyDown(event.key.keysym.scancode); break;
      case SDL_KEYUP: input_keyUp(event.key.keysym.scancode); break;
    }
  }

  input_process();

  return 1;
}
