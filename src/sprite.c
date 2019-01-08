#include "sprite.h"

static void _sprite_free(Sprite* sprite) {
  for (unsigned int i = 0; i < sprite->nFrames; i++) {
    free(sprite->frames[i]);
  }
  free(sprite->frames);
  free(sprite);
}

static void _sprite_cleanup(void) {
  for (Entity i = 0; i < MAX_ENTITIES; i++) {
    if (sprite_map[i] != NULL) {
      _sprite_free(sprite_map[i]);
      sprite_map[i] = NULL;
    }
  }
  free(sprite_map);
  free(sprite_loadedImagesPaths);
  free(sprite_loadedImages);
}

void sprite_init(void) {
  sprite_map = malloc(sizeof(Sprite*) * MAX_ENTITIES);
  for (Entity i = 0; i < MAX_ENTITIES; i++) {
    sprite_map[i] = NULL;
  }

  sprite_loadedImagesPaths = malloc(sizeof(char*) * IMAGE_PATH_LIST_SIZE);
  sprite_loadedImages = malloc(sizeof(GPU_Image*) * IMAGE_PATH_LIST_SIZE);
  sprite_loadedImagesRefCount = malloc(sizeof(size_t*) * IMAGE_PATH_LIST_SIZE);
  for (int i = 0; i < IMAGE_PATH_LIST_SIZE; i++) {
    sprite_loadedImagesPaths[i] = NULL;
    sprite_loadedImages[i] = NULL;
    sprite_loadedImagesRefCount[i] = 0;
  }

  atexit(_sprite_cleanup);
}

int sprite_loadImage(const char* path) {
  char* imagePtr;
  int i = 0;
  for (; i < IMAGE_PATH_LIST_SIZE; i++) {
    imagePtr = sprite_loadedImagesPaths[i];
    if (imagePtr == NULL) {
      sprite_loadedImagesPaths[i] = malloc(sizeof(char*) * strlen(path));
      strcpy(sprite_loadedImagesPaths[i], path);
      sprite_loadedImages[i] = graphics_loadImage(path);
      sprite_loadedImagesRefCount[i]++;
      break;
    }
    if (strcmp(imagePtr, path) == 0) {
      sprite_loadedImagesRefCount[i]++;
      break;
    }
  }
  return i;
}

void sprite_register(Entity entity, const char* path, float x, float y, float w, float h) {
  Sprite* sprite = malloc(sizeof(Sprite));

  GPU_Rect* rect = malloc(sizeof(GPU_Rect));
  rect->x = x;
  rect->y = y;
  rect->w = w;
  rect->h = h;
  sprite->rect = rect;

  sprite->nFrames = 1;
  sprite->frames = malloc(sizeof(GPU_Rect*) * sprite->nFrames);
  sprite->frames[0] = sprite->rect;

  sprite->image = sprite_loadedImages[sprite_loadImage(path)];
  sprite_map[entity] = sprite;
}

void sprite_deregister(Entity entity) {
  Sprite* sprite = sprite_map[entity];
  if (sprite == NULL) {
    logging_log(WARNING, "sprite", "Attempting to deregister a non registered entity");
    return;
  }
  _sprite_free(sprite);
}

void sprite_process(void) {
  Sprite* sprite;
  Position* pos;

  for (Entity entity = 0; entity < MAX_ENTITIES; entity++) {
    if (sprite_map[entity] != NULL) {
      sprite = sprite_map[entity];
      pos = position_get(entity);

      graphics_drawQueueAppendImage(
        0,
        sprite->image,
        sprite->rect,
        pos->x,
        pos->y
      );
    }
  }
}

void sprite_draw(Entity entity) {
  Sprite* sprite = sprite_map[entity];
  Position* pos = position_get(entity);
  graphics_drawToScreen(sprite->image, sprite->rect, pos->x, pos->y);
}

void sprite_update(Sprite* sprite) {
  sprite->currentFrame++;
  sprite->currentFrame %= sprite->nFrames;
  sprite->rect = sprite->frames[sprite->currentFrame];
}
