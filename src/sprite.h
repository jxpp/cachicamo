#ifndef SPRITE_H
#define SPRITE_H

#include <stdarg.h>
#include <string.h>

#include <SDL.h>
#include <SDL_gpu.h>

#include "entity.h"
#include "graphics.h"
#include "hashtable.h"
#include "logging.h"
#include "position_c.h"

#define IMAGE_PATH_LIST_SIZE 128

typedef struct {
  GPU_Image* image;
  GPU_Rect* rect;
  GPU_Rect** frames;
  size_t nFrames;
  size_t currentFrame;
} Sprite;

Sprite** sprite_map;

char** sprite_loadedImagesPaths;
GPU_Image** sprite_loadedImages;
size_t* sprite_loadedImagesRefCount;

int sprite_loadImage(const char*);

void sprite_init(void);

void sprite_register(Entity, const char*, float x, float y, float w, float h);
void sprite_deregister(Entity);

void sprite_markForDrawing(Entity);

void spriteAnimated_register(Entity, const char*, GPU_Rect*);

void sprite_draw(Entity);

void sprite_update(Sprite*);

#endif
