#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include "E7defines.h"

typedef struct node_t {
	void *value;
	struct node_t *pred;
	struct node_t *succ;
} node_t;

typedef struct {
	node_t *first;
	node_t *last;
	size_t size;
} list_t;

list_t *list_init(list_t *l);
void list_free(list_t *l);

void *list_at(list_t *l, size_t offset);

bool_t list_prepend(list_t *l, void *el);
bool_t list_append(list_t *l, void *el);
bool_t list_insert(list_t *l, node_t *after, node_t *before, void *el);
u64 *list_to_u64table(list_t *l);

bool_t list_remove(list_t *l, void *el, bool_t all);

#endif
