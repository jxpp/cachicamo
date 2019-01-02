#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

#include <stdio.h>

#include "entity.h"


typedef struct _position_t {
  float x;
  float y;
} Position;

struct _position_t** position_map;

void position_init(void);

void position_register(Entity, float, float);

Position* position_get(Entity);


#endif
