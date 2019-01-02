#include "entity.h"

Entity entityIdCounter = 0;

void entity_init(void) {
  initHashTable(&entity_namedMap);
}

Entity _entity_register(uint64_t id) {
  return id;
}

Entity entity_registerAnon(void) {
  return _entity_register(entityIdCounter++);
}

Entity entity_registerNamed(const char* name) {
  uint64_t hash = _djb2_hash(name);
  setHashTable(&entity_namedMap, hash, entityIdCounter++);
  return _entity_register(_djb2_hash(name));
}

uint64_t _djb2_hash(const char* str) {
  uint64_t hash = 5381;
  size_t c;

  while ((c=*str++) != '\0') {
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  }

  return hash;
}
