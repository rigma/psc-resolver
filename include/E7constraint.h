#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include "E7defines.h"
#include "E7tree.h"
#include "E7str.h"
#include "E7var.h"

typedef enum {
	EQUAL = 0x0, DIFFERENT = 0x1, GT = 0x2, SGT = 0x3, LT = 0x4, SLT = 0x5
} operator_t;

typedef enum {
	VAR = 0x0, SCALAR = 0x1, SET = 0x2
} master_t;

typedef struct {
	var_t *slave;
	u64 master;
	operator_t op;
	master_t master_type;
} constraint_t;

constraint_t *constraint_init(var_t *slave, operator_t op, u64 master, master_t var);
void constraint_free(constraint_t *c);

bool_t constraint_check(size_t size, constraint_t **constraints, leaf_t *leaf, u64 slave, u64 value);

#endif
