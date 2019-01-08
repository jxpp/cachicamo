#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdlib.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_gpu.h>
#include <SDL_gpu_OpenGL_4.h>

#include <glew.h>

#include "globals.h"
#include "hashtable.h"
#include "logging.h"

#define DRAW_QUEUE_SIZE 256
#define N_LAYERS 9


extern const SDL_Color DEBUG_COLOR;

struct _graphics_t {
  GPU_Target* screen;
};

enum _draw_request_type_e { IMAGE, GEOMETRY };
typedef enum _draw_request_type_e DrawRequestType;

typedef struct _drawable_image_info_t {
  GPU_Image* image;
  GPU_Rect* rect;
  float x;
  float y;
} DrawableImageInfo;

typedef struct _drawRequest_t {
  DrawRequestType type;
  void *data;
} DrawRequest;

DrawRequest** graphics_drawQueue;
int graphics_drawQueueIndices[N_LAYERS];

void graphics_init(void);

void graphics_frameStart(void);
void graphics_frameDraw(void);
void graphics_frameEnd(void);

void graphics3D_start(void);
void graphics3D_end(void);

GPU_Image* graphics_loadImage(const char*);

void graphics_drawQueueAppendImage(int, GPU_Image*, GPU_Rect*, float, float);

void graphics_drawToScreen(GPU_Image*, GPU_Rect*, float, float);

void graphics_drawDebugRect(GPU_Rect);


#endif
