#include "collision.h"

void collision_init(void) {
  collision_tagMap = malloc(sizeof(CollisionTag*) * MAX_TAGS);
  for (int i = 0; i < MAX_TAGS; i++) {
    collision_tagMap[i] = NULL;
  }
  collision_tagMapCounter = 0;

  collision_map = malloc(sizeof(CollisionBox*) * MAX_CBOXES);
  collision_nBoxes = 0;
  collision_mapTags = malloc(sizeof(CTagId) * MAX_CBOXES);
  logging_log(INFO, "collision", "Inited collision subsystem");
}

CTagId collision_addNewTag(const char* name, void(*action)(void*), void* actionArgs) {
  CollisionTag* newCollisionTag = malloc(sizeof(CollisionTag));
  newCollisionTag->id = collision_tagMapCounter;
  newCollisionTag->name = malloc(sizeof(char*) * strlen(name));
  strcpy(newCollisionTag->name, name);
  newCollisionTag->action = action;
  newCollisionTag->actionArgs = actionArgs;

  collision_tagMap[collision_tagMapCounter] = newCollisionTag;

  return collision_tagMapCounter++;
}

void collision_register(CTagId tag, Entity* e, GPU_Rect rect) {
  CollisionBox* newCollisionBox = malloc(sizeof(CollisionBox));
  newCollisionBox->entity = e;
  newCollisionBox->box = rect;

  collision_map[collision_nBoxes] = newCollisionBox;
  collision_mapTags[collision_nBoxes] = tag;
  collision_nBoxes++;
}

static GPU_Rect collision_calculateOffset(GPU_Rect box, Entity* entity) {
  Position* pos = position_get(*entity);
  GPU_Rect ret = {pos->x + box.x, pos->y + box.y, box.w, box.h};
  return ret;
}

void collision_showBoxes(void) {
  GPU_Rect box;

  for (unsigned int i = 0; i < collision_nBoxes; i++) {
    box = collision_map[i]->box;
    if(collision_map[i]->entity != NULL) {
      box = collision_calculateOffset(box, collision_map[i]->entity);
    }
    graphics_drawDebugRect(box);
  }
}

void collision_process(void) {
  int idx = 0;
  for (unsigned int i = 0; i < collision_nBoxes; i++) {
    for (unsigned int j = i + 1; j < collision_nBoxes; j++) {
      if (collision_mapTags[i] == collision_mapTags[j]) {
        GPU_Rect a, b;
        if(collision_map[i]->entity != NULL) {
          a = collision_calculateOffset(collision_map[i]->box, collision_map[i]->entity);
        } else {
          a = collision_map[i]->box;
        }
        if(collision_map[j]->entity != NULL) {
          b = collision_calculateOffset(collision_map[j]->box, collision_map[j]->entity);
        } else {
          b = collision_map[j]->box;
        }
        if (GPU_IntersectRect(a, b, NULL)) {
          idx = collision_mapTags[i];
          collision_tagMap[idx]->action((void*) collision_tagMap[idx]->actionArgs);
        }
      }
    }
  }
}
