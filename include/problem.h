#ifndef PROBLEM_H
#define PROBLEM_H

#include "constraint.h"
#include "str.h"
#include "var.h"

typedef struct {
    string_t *name;
    union {
        constraint_t **constraints;
        size_t n_constraints;
    };
    union {
        var_t **vars;
        size_t n_vars;
    };
} problem_t;

problem_t *problem_init(const char *filename);
void problem_free(problem_t *p);

#endif
