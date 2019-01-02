#include "collision.h"

static bool collision_floatIntersection(GPU_Rect* A, GPU_Rect* B) {
  float Amin, Amax, Bmin, Bmax;
  // This is literally just the code for SDL_HasIntersection, only with
  // GPU_Rects, i.e., floats

  //if (!A) {
  //  SDL_InvalidParamError("A");
  //  return SDL_FALSE;
  //}

  //if (!B) {
  //  SDL_InvalidParamError("B");
  //  return SDL_FALSE;
  //}

  ///* Special cases for empty rects */
  //if (SDL_RectEmpty(A) || SDL_RectEmpty(B)) {
  //  return SDL_FALSE;
  //}

  /* Horizontal intersection */
  Amin = A->x;
  Amax = Amin + A->w;
  Bmin = B->x;
  Bmax = Bmin + B->w;
  if (Bmin > Amin)
    Amin = Bmin;
  if (Bmax < Amax)
    Amax = Bmax;
  if (Amax <= Amin)
    return false;

  /* Vertical intersection */
  Amin = A->y;
  Amax = Amin + A->h;
  Bmin = B->y;
  Bmax = Bmin + B->h;
  if (Bmin > Amin) {
    Amin = Bmin;
  }
  if (Bmax < Amax) {
    Amax = Bmax;
  }
  if (Amax <= Amin) {
    return false;
  }

  return true;
}

void collision_init(void) {
  puts("initing collision");
  collision_tagMap = malloc(sizeof(CollisionTag*) * MAX_TAGS);
  for (int i = 0; i < MAX_TAGS; i++) {
    collision_tagMap[i] = NULL;
  }
  collision_tagMapCounter = 0;

  collision_map = malloc(sizeof(CollisionBox*) * MAX_CBOXES);
  collision_nBoxes = 0;
  collision_mapTags = malloc(sizeof(CTagId) * MAX_CBOXES);
  puts("inited collision");
}

CTagId collision_addNewTag(const char* name, void(*action)(void*), void* actionArgs) {
  printf("adding tag %s\n", name);
  printf("creating tag \n");
  CollisionTag* newCollisionTag = malloc(sizeof(CollisionTag));
  newCollisionTag->id = collision_tagMapCounter;
  newCollisionTag->name = malloc(sizeof(char*) * strlen(name));
  strcpy(newCollisionTag->name, name);
  newCollisionTag->action = action;
  newCollisionTag->actionArgs = actionArgs;

  collision_tagMap[collision_tagMapCounter] = newCollisionTag;

  printf("added tag %s\n", name);
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

void collision_process(void) {
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
        if (collision_floatIntersection(&a, &b)) {
          collision_tagMap[collision_mapTags[i]]->action((void*) collision_map[i]);
        }
      }
    }
  }
}
