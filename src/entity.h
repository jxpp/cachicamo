#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>

#include "hashtable.h"

#define MAX_ENTITIES (1 << 16) - 1


typedef uint16_t Entity;

extern Entity entityIdCounter;

HashTable entity_namedMap;

void entity_init(void);

Entity _entity_register(uint64_t);

Entity entity_registerAnon();
Entity entity_registerNamed(const char*);

uint64_t _djb2_hash(const char*);


#endif
