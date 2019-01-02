#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "engine.h"
#include "entity.h"
#include "logging.h"

#include "component.h"

void moveUp(void* entity) {
  Entity e = *((Entity*) entity);
  Position* position = position_get(e);
  position->y -= 1.0f;
}
void moveLeft(void* entity) {
  Entity e = *((Entity*) entity);
  Position* position = position_get(e);
  position->x -= 1.0f;
}
void moveDown(void* entity) {
  Entity e = *((Entity*) entity);
  Position* position = position_get(e);
  position->y += 1.0f;
}
void moveRight(void* entity) {
  Entity e = *((Entity*) entity);
  Position* position = position_get(e);
  position->x += 1.0f;
}

int main(void) {
  init();

  Entity paquirri = 23;
  component_register(SPRITE, paquirri, "ball.png");
  component_register(POSITION, paquirri, 10.0, 10.0);
  component_register(INPUT, SDL_SCANCODE_W, &moveUp, &paquirri);
  component_register(INPUT, SDL_SCANCODE_A, &moveLeft, &paquirri);
  component_register(INPUT, SDL_SCANCODE_S, &moveDown, &paquirri);
  component_register(INPUT, SDL_SCANCODE_D, &moveRight, &paquirri);

  bool open = true;

  while (open) {
    frameStart();
    open = handleEvents();
    sprite_draw(paquirri);
    graphics3D_start();
    graphics3D_end();
    frameEnd();
  }

  return EXIT_SUCCESS;
}
