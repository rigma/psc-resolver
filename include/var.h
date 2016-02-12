#ifndef VAR_H
#define VAR_H

#include "defines.h"
#include "set.h"
#include "str.h"

typedef struct {
	string_t *name;
	set_t *def;
} var_t;

var_t *var_init(string_t *name);
void var_free(var_t *var);

bool_t var_set_interval(var_t *var, u64 begin, u64 end);
bool_t var_add_to_definition(var_t *var, u64 el);

#endif
