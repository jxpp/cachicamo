#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>

typedef uint32_t K;
typedef void* V;

typedef struct _hash_table_entry_t {
  K key;
  V value;
} HashTableEntry;

typedef struct _hash_table_t {
  size_t size;
  size_t load;
  HashTableEntry** entries;
  pthread_mutex_t lock;
} HashTable;

void initHashTable(HashTable*);
HashTable* hashtable_new(void);

V getHashTable(HashTable*, K);

void setHashTable(HashTable*, K, V);

/*
void deleteHashTable(HashTable*, K);
void clearHashTable(HashTable*);

void resizeHashTable(HashTable*);

void rehashHashTable(HashTable*, HashTable*);
*/

#endif
