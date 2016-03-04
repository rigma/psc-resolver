#ifndef PROBLEM_H
#define PROBLEM_H

#include "constraint.h"
#include "str.h"
#include "tree.h"
#include "var.h"

typedef struct {
    string_t *name;
	union {
		var_t **vars;
		size_t n_vars;
	};
	union {
        constraint_t **constraints;
        size_t n_constraints;
    };
} problem_t;

problem_t *problem_init(const char *filename);
void problem_free(problem_t *p);

bool_t problem_add_var(problem_t *p, var_t *var);
bool_t problem_add_constraint(problem_t *p, constraint_t *var);

u64 *problem_solve(problem_t *p);
bool_t problem_alloc(problem_t *p, leaf_t *root, var_t *var);

#endif
