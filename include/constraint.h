#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include "defines.h"
#include "str.h"
#include "var.h"

typedef enum {
	EQUAL = 0x0, DIFFERENT = 0x1, GT = 0x2, SGT = 0x3, LT = 0x4, SLT = 0x5
} operator_t;

typedef enum {
	VAR = 0x0, SCALAR = 0x1, SET = 0x2
} master_t;

typedef struct {
	var_t *slave;
	void *master;
	operator_t op;
	master_t master_type;
} constraint_t;

constraint_t *constraint_init(var_t *slave, operator_t op, void *master, master_t var);
void constraint_free(constraint_t *c);

#endif
