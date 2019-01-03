#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include <stdbool.h>
#include <stdlib.h>

#include "entity.h"

typedef struct _behaviour_t {
  bool (*conditional)(void*);
  void* conditionalArgs;
  void (*action)(void*);
  void* actionArgs;
} Behaviour;

size_t nBehaviours;
Behaviour** behaviour_map;

void behaviour_init(void);

void behaviour_register(bool (*)(void*), void*, void (*)(void*), void*);

void behaviour_process(void);

#endif
