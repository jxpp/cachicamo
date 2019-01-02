#include "position_component.h"

static void _position_cleanup(void) {
  for (int i = 0; i < MAX_ENTITIES; i++) {
    if(position_map[i] != NULL) {
      free(position_map[i]);
    }
  }
  free(position_map);
}

void position_init(void) {
  position_map = malloc(sizeof(struct _position_t) * MAX_ENTITIES);
  for (int i = 0; i < MAX_ENTITIES; i++) {
    position_map[i] = NULL;
  }
  atexit(_position_cleanup);
}

void position_register(Entity entity, float x, float y) {
  Position* position = malloc(sizeof(struct _position_t));
  position->x = x;
  position->y = y;
  position_map[entity] = position;
}

Position* position_get(Entity entity) {
  return position_map[entity];
}
