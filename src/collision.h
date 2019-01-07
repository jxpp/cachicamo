#ifndef COLLISION_H
#define COLLISION_H

#define MAX_TAGS 256
#define MAX_CBOXES 1024

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <SDL.h>
#include <SDL_gpu.h>

#include "logging.h"
#include "graphics.h"
#include "entity.h"
#include "position_c.h"

typedef uint32_t CTagId;

typedef struct _collision_tag_t {
  CTagId id;
  char* name;
  void (*action)(void*);
  void* actionArgs;
} CollisionTag;

typedef struct _collision_box_t {
  GPU_Rect box;
  Entity* entity;
  CTagId tagId;
  //int priority;
} CollisionBox;

CollisionTag** collision_tagMap;
CTagId collision_tagMapCounter;

CollisionBox** collision_map;
size_t collision_nBoxes;
CTagId* collision_mapTags;

void collision_init(void);

CTagId collision_addNewTag(const char*, void(*)(void*), void*);

void collision_showBoxes(void);

void collision_register(CTagId, Entity*, GPU_Rect);

void collision_process(void);

#endif
