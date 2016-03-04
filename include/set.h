#ifndef SET_H
#define SET_H

#include <stddef.h>

#include "defines.h"
#inlcude "list.h"

typedef struct {
	u64 *set;
	size_t size;
} set_t;

set_t *set_init();
set_t *set_init_from_table(u64 *table, size_t size);
set_t *set_init_from_interval(u64 begin, u64 end);
void set_free(set_t *s);

bool_t in_set(set_t *s, u64 el);

bool_t set_add_element(set_t *s, u64 el);

#endif
