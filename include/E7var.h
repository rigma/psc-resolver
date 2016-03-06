#ifndef VAR_H
#define VAR_H

#include "E7defines.h"
#include "E7set.h"
#include "E7str.h"

typedef struct {
	//string_t *name;
	u64 name;
	set_t *def;
} var_t;

var_t *var_init(u64 /*string_t * */ name);
void var_free(var_t *var);

bool_t var_set_interval(var_t *var, u64 begin, u64 end);
bool_t var_add_to_definition(var_t *var, u64 el);

#endif
