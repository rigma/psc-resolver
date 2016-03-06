#ifndef TREE_H
#define TREE_H

#include "E7defines.h"
#include <stddef.h>

typedef struct leaf_t {
	u64 name;
    u64 value;
    struct leaf_t **children;
    size_t n_children;
    struct leaf_t *ancestor;
} leaf_t;
typedef leaf_t* tree_t;

tree_t tree_init();
void tree_free(tree_t t);

leaf_t *leaf_init(u64 value, leaf_t *ancestor, u64 name);
void leaf_free(leaf_t *l);

void leaf_append(leaf_t *l, leaf_t *successor);
void leaf_remove(leaf_t *l, leaf_t *successor);

#endif
