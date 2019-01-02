#include "component.h"

void component_register(enum component_type ctype, ...) {
  va_list argPointer;
  va_start(argPointer, ctype);
  Entity entity;
  float x, y;
  SDL_Scancode scancode;
  void (*action)(void*);
  void* actionArgs;
  char* path;
  switch(ctype) {
    case POSITION:
      entity = (Entity) va_arg(argPointer, int);
      x = (float) va_arg(argPointer, double);
      y = (float) va_arg(argPointer, double);
      position_register(entity, x, y);
      break;
    case INPUT:
      scancode = va_arg(argPointer, SDL_Scancode);
      action = va_arg(argPointer, void (*)(void*));
      actionArgs = va_arg(argPointer, void*);
      input_register(scancode, action, actionArgs);
      break;
    case SPRITE:
      entity = (Entity) va_arg(argPointer, int);
      path = va_arg(argPointer, char*);
      sprite_register(entity, path);
      break;
    default: break;
  }
  va_end(argPointer);
}
