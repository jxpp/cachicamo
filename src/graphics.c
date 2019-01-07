#include "graphics.h"

static struct _graphics_t graphics = {
  .screen = NULL
};

static void graphics_cleanup(void) {
  free(graphics_drawQueue);
  GPU_Quit();
}

void graphics_init(void) {
  GPU_SetDebugLevel(GPU_DEBUG_LEVEL_MAX);
  GPU_Target* screen;
  GPU_SetRequiredFeatures(GPU_FEATURE_BASIC_SHADERS);
  if((screen = GPU_InitRenderer(GPU_RENDERER_OPENGL_4, 800, 600, GPU_DEFAULT_INIT_FLAGS)) == NULL) {
    printf("SDL_gpu could not initialize! SDL_Error: %s\n", SDL_GetError());
    exit(1);
  }

  if (glewInit() != GLEW_OK) {
    GPU_LogError("GLEW Failed to initialize\n");
    exit(2);
  }

  graphics.screen = screen;

  graphics_drawQueue = malloc(sizeof(GPU_Image*) * DRAW_QUEUE_SIZE);

  atexit(graphics_cleanup);
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
  for (int i = 0; i < DRAW_QUEUE_SIZE; i++) {
    graphics_drawQueue[i] = NULL;
  }
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

void graphics_frameDraw(void) {
  GPU_Image* queuePtr;
  for (int i = 0; i < DRAW_QUEUE_SIZE; i++) {
    queuePtr = graphics_drawQueue[i];
    if(queuePtr == NULL) {
      break;
    }
  }
}

void graphics_drawToScreen(GPU_Image* sprite, GPU_Rect* rect, float x, float y) {
  GPU_Blit(sprite, rect, graphics.screen, x, y);
}

void graphics_drawDebugRect(GPU_Rect r) {
  static const SDL_Color color = {
    .r = 255,
    .g =   0,
    .b = 255,
    .a = 255
  };
  GPU_Rectangle(graphics.screen, r.x, r.y, r.x+r.w, r.y+r.h, color);
}
