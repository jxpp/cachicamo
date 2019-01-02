#include <stdio.h>

#include "hashtable.h"

#define STARTING_SIZE 1 << 16

size_t _fast_range(uint32_t x, uint32_t n) {
  return ((uint64_t) x * (uint64_t) n) >> 32;
}

static size_t _find_hash_table(HashTable* hashTable, K key) {
  return _fast_range(key, hashTable->size);
}

void initHashTable(HashTable* hashTable) {
  hashTable->size = STARTING_SIZE;
  hashTable->load = 0;
  hashTable->entries = malloc(sizeof(HashTableEntry*) * STARTING_SIZE);
  for (int i = 0; i < STARTING_SIZE; i++) {
    hashTable->entries[i] = NULL;
  }
  pthread_mutex_init(&hashTable->lock, NULL);
}

V getHashTable(HashTable* hashTable, K key) {
  size_t idx = _find_hash_table(hashTable, key);

  HashTableEntry* entry;
  while ((entry = hashTable->entries[idx]) != NULL) {
    // linear probing por ahora
    if (entry->key == key) {
      return entry->value;
    }
    idx++;
    idx %= hashTable->size;
  }
  return 0;
}

void setHashTable(HashTable* hashTable, K key, V value) {
  HashTableEntry* newEntry = malloc(sizeof(HashTableEntry));
  newEntry->key = key;
  newEntry->value = value;
  size_t idx = _find_hash_table(hashTable, key);
  while (hashTable->entries[idx] != NULL) {
    //printf("probing... %lu\n", idx);
    idx++;
    idx %= hashTable->size;
  }
  hashTable->entries[idx] = newEntry;
  hashTable->load++;
}

/*
void deleteHashTable(HashTable* hashTable, K key) {}
void clearHashTable(HashTable* hashTable) {}

void resizeHashTable(HashTable* hashTable) {}

void rehashHashTable(HashTable* hashTableNew, HashTable* hashTableOld) {}
*/
