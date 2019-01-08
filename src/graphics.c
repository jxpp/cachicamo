#include "graphics.h"

const SDL_Color DEBUG_COLOR = {
  .r = 255,
  .g =   0,
  .b = 255,
  .a = 255
};

static struct _graphics_t graphics = {
  .screen = NULL
};

static void graphics_cleanup(void) {
  free(graphics_drawQueue);
  GPU_Quit();
}

void graphics_init(void) {
  GPU_Target* screen;

  GPU_SetDebugLevel(GPU_DEBUG_LEVEL_MAX);
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

  graphics_drawQueue = malloc(sizeof(DrawRequest*) * N_LAYERS);
  for (int i = 0; i < N_LAYERS; i++) {
    graphics_drawQueue[i] = malloc(sizeof(DrawRequest) * DRAW_QUEUE_SIZE);
    graphics_drawQueueIndices[i] = 0;
  }


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
  for (int layer = 0; layer < N_LAYERS; layer++) {
    graphics_drawQueueIndices[layer] = 0;
    memset(graphics_drawQueue[layer], 0, sizeof(DrawRequest) * DRAW_QUEUE_SIZE);
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
  DrawRequest draw_request;
  DrawableImageInfo* imageInfo;
  GPU_Rect* rect;

  for (unsigned int layer = 0; layer < N_LAYERS; layer++) {
    for (int req = 0; req < graphics_drawQueueIndices[layer]; req++) {
      draw_request = graphics_drawQueue[layer][req];
      switch (draw_request.type) {
        case IMAGE:
          imageInfo = (DrawableImageInfo*) draw_request.data;
          graphics_drawToScreen(
            imageInfo->image,
            imageInfo->rect,
            imageInfo->x,
            imageInfo->y
          );
          break;
        case GEOMETRY:
          rect = (GPU_Rect*) draw_request.data;
          graphics_drawDebugRect(*rect);
          break;
      }
    }
  }
}

void graphics_drawToScreen(GPU_Image* sprite, GPU_Rect* rect, float x, float y) {
  GPU_Blit(sprite, rect, graphics.screen, x, y);
}

void graphics_drawQueueAppendImage(int layer, GPU_Image* sprite, GPU_Rect* rect, float x, float y) {
  if (layer < 0 || layer >= N_LAYERS) {
    logging_log(WARNING, "graphics",
      "Attempting to add image to non-existing layer"
    );
  }

  DrawableImageInfo* image_info = malloc(sizeof(DrawableImageInfo));
  image_info->image = sprite;
  image_info->rect = rect;
  image_info->x = x;
  image_info->y = y;

  DrawRequest draw_request = {
    .type = IMAGE,
    .data = image_info
  };

  graphics_drawQueue[layer][graphics_drawQueueIndices[layer]] = draw_request;
  graphics_drawQueueIndices[layer]++;
}

void graphics_drawDebugRect(GPU_Rect r) {
  GPU_Rectangle(graphics.screen, r.x, r.y, r.x+r.w, r.y+r.h, DEBUG_COLOR);
}
