#ifndef QUADTREE_H
#define QUADTREE_H

#include <stdlib.h>
#include <stdint.h>

typedef struct _quadtree_bucket_t {
  void** contents;
  size_t maxContents;
} QuadTreeBucket;



typedef struct _quadtree_t {
  QuadTreeBucket* buckets;
  struct _quadtree_t* children;
} QuadTree;

void QuadTree_init(QuadTree*);

#endif
