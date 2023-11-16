#ifndef TREEMAP_h
#define TREEMAP_h

#include "hashmap.h"

typedef struct TreeNode {
    Pair * pair;
    struct TreeNode * left;
    struct TreeNode * right;
    struct TreeNode * parent;
} TreeNode;

typedef struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
} TreeMap ;

TreeMap * createTreeMap(int (*lower_than_int) (void* key1, void* key2));

void insertTreeMap(TreeMap * tree, void* key, void * value);

void eraseTreeMap(TreeMap * tree, void* key);

Pair * searchTreeMap(TreeMap * tree, void* key);

Pair * upperBound(TreeMap * tree, void* key);

Pair * firstTreeMap(TreeMap * tree);

Pair * nextTreeMap(TreeMap * tree);

#endif /* TREEMAP_h */
