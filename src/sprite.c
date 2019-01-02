#include "sprite.h"

static void _sprite_cleanup(void) {
  for (Entity i = MAX_ENTITIES; i != 0; i--) {
    if (sprite_map[i] != NULL) {
      free(sprite_map[i]);
      sprite_map[i] = NULL;
    }
  }
  free(sprite_map);
}

void sprite_init(void) {
  sprite_map = malloc(sizeof(Sprite*) * MAX_ENTITIES);
  for (Entity i = MAX_ENTITIES; i != 0; i--) {
    sprite_map[i] = NULL;
  }
  atexit(_sprite_cleanup);
}

void sprite_register(Entity entity, const char* path) {
  Sprite* sprite = malloc(sizeof(Sprite));
  sprite->rect = malloc(sizeof(GPU_Rect));
  sprite->rect->w = 10;
  sprite->rect->h = 10;
  sprite->n = 1;
  sprite_setImage(sprite, path);
  sprite_map[entity] = sprite;
}

void sprite_deregister(Entity entity) {
  Sprite* sprite = sprite_map[entity];
  if (sprite == NULL) {
    logging_log(WARNING, "sprite", "Attempting to deregister a non registered entity");
    return;
  }
  GPU_FreeImage(sprite->image);
  free(sprite->rect);
  free(sprite);
}

void sprite_draw(Entity entity) {
  Sprite* sprite = sprite_map[entity];
  Position* pos = position_get(entity);
  graphics_drawToScreen(sprite->image, sprite->rect, pos->x, pos->y);
}

void sprite_setImage(Sprite* sprite, const char* path) {
  sprite->image = graphics_loadImage(path);
}

void sprite_update(Sprite* sprite) {
  // let's actually write this sometime mmkay
}
