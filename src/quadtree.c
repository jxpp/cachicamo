#include "quadtree.h"

void QuadTree_init(QuadTree* quadTree) {
  quadTree->buckets = malloc(sizeof(QuadTreeBucket));
  quadTree->children = malloc(sizeof(QuadTree*) * 4);
}
