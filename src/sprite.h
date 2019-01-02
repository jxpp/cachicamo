#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <SDL_gpu.h>

#include "entity.h"
#include "graphics.h"
#include "hashtable.h"
#include "logging.h"
#include "position_component.h"

typedef struct {
  GPU_Image* image;
  GPU_Rect* rect;
  size_t n;
} Sprite;

Sprite** sprite_map;

void sprite_init(void);

void sprite_register(Entity, const char*);
void sprite_deregister(Entity);

void sprite_draw(Entity);

void sprite_setImage(Sprite*, const char*);

void sprite_update(Sprite*);

#endif
