#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdlib.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_gpu.h>
#include <SDL_gpu_OpenGL_4.h>

#include <glew.h>

#include "globals.h"


struct _graphics_t {
  GPU_Target* screen;
};

extern struct _graphics_t graphics;

void graphics_init(void);

void graphics_frameStart(void);
void graphics_frameEnd(void);

void graphics3D_start(void);
void graphics3D_end(void);

GPU_Image* graphics_loadImage(const char*);

void graphics_drawToScreen(GPU_Image*, GPU_Rect*, float, float);


#endif
