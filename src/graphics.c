#include "graphics.h"

struct _graphics_t graphics = {
  .screen = NULL
};

void graphics_init(void) {
  GPU_SetDebugLevel(GPU_DEBUG_LEVEL_MAX);
  GPU_Target* screen;
  GPU_SetRequiredFeatures(GPU_FEATURE_BASIC_SHADERS);
  if((screen = GPU_InitRenderer(GPU_RENDERER_OPENGL_4, 800, 600, GPU_DEFAULT_INIT_FLAGS)) == NULL) {
    printf("SDL_gpu could not initialize! SDL_Error: %s\n", SDL_GetError());
    exit(1);
  }
  atexit(GPU_Quit);

  if (glewInit() != GLEW_OK) {
    GPU_LogError("GLEW Failed to initialize\n");
    exit(2);
  }
  graphics.screen = screen;
}

GPU_Image* graphics_loadImage(const char* path) {
  GPU_Image* loadedImage = GPU_LoadImage(path);
  if(loadedImage == NULL) {
    printf("Unable to load image %s! SDL_gpu Error: %s\n", path, SDL_GetError());
    return NULL;
  }
  return loadedImage;
}

void graphics_frameStart(void) {
  GPU_Clear(graphics.screen);
}

void graphics_frameEnd(void) {
  GPU_Flip(graphics.screen);
}

void graphics3D_start(void) {
  GPU_FlushBlitBuffer();

  GPU_MatrixMode(GPU_MODELVIEW);
  GPU_PushMatrix();
  GPU_LoadIdentity();
  GPU_MatrixMode(GPU_PROJECTION);
  GPU_PushMatrix();
  GPU_LoadIdentity();
}

void graphics3D_end(void) {
  GPU_ResetRendererState();

  GPU_MatrixMode(GPU_MODELVIEW);
  GPU_PopMatrix();
  GPU_MatrixMode(GPU_PROJECTION);
  GPU_PopMatrix();
}

void graphics_drawToScreen(GPU_Image* sprite, GPU_Rect* rect, float x, float y) {
  GPU_Blit(sprite, rect, graphics.screen, x, y);
}
