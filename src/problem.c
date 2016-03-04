#include <stdlib.h>
#include <stdio.h>

#include <problem.h>

problem_t *problem_init(const char *filename) {
    problem_t *p = NULL;
    FILE *f = NULL;
    char *str = NULL;
	constraint_t *tmpConstraint = NULL;
	u64 temp = 0;
	u64 tmp1 = 0, tmp2 = 0, tmp3 = 0;

    if (filename == NULL)
        return NULL;

    f = fopen(filename, "r");
    if (f != NULL)
        return NULL;

    p = (problem_t*) malloc(sizeof(problem_t));
    if (p == NULL) {
        fclose(f);

        return NULL;
    }

    p->name = string_init(NULL);
    if (p->name == NULL) {
        fclose(f);
        free(p);

        return NULL;
    }

    p->name->str = (char*) malloc((strlen(filename) - 3) * sizeof(char));
    if (p->name->str == NULL) {
        string_free(p->name);
        fclose(f);
        free(p);

        return NULL;
    }

    
	fscanf(f, "%llu", temp);
	// Lecture des variables/domaines de d�finitions
	do
	{
		if (temp > 0)
		{
			problem_add_var(p, &temp);

			fscanf(f, "%lu", temp);
			while (temp != -1)
			{
				// TODO : ajouter tmp au domaine de d�finition
				
				
				fscanf(f, "%lu", temp);
			}
		}
	} while (temp != -2);
	/// Lecture des contraintes
	fscanf(f, "%lu", temp);
	do
	{
		fscanf(f, "%lu", tmp1); // operator
		fscanf(f, "%lu", tmp2); // master
		fscanf(f, "%lu", tmp3); // master_type
		tmpConstraint = constraint_init(var_init(temp), tmp1, tmp2, tmp3);
		problem_add_constraint(p, tmpConstraint);
		fscanf(f, "%lu", temp);
	} while (temp != -3);


    fclose(f);

    return p;
}

void problem_free(problem_t *p)
{
	size_t i = 0;

	if (p == NULL)
        return NULL;
	
	for (; i < p->n_vars; i++)
		var_free(p->vars[i]);
	free(p->vars);

	for (i = 0; i < p->n_constraints; i++)
		constraint_free(p->constraints[i]);
	free(p->constraints);
	
	string_free(p->name);
	free(p);
}

bool_t problem_add_var(problem_t *p, var_t *var) {
	void *tmp = NULL;

	if (p == NULL || var == NULL)
		return FALSE;

	if (p->n_vars > 1)
		tmp = realloc(p->vars, (p->n_vars + 1) * sizeof(var_t*));
	else
		tmp = malloc(sizeof(var_t));

	if (tmp == NULL)
		return FALSE;

	p->vars = (var_t**) tmp;
	p->vars[p->n_vars] = var;
	p->n_vars++;

	return TRUE;
}

bool_t problem_add_constraint(problem_t *p, constraint_t *constraints) {
	void *tmp = NULL;

	if (p == NULL || constraints == NULL)
		return FALSE;

	if (p->n_constraints > 1)
		tmp = realloc(p->constraints, (p->n_constraints + 1) * sizeof(constraint_t*));
	else
		tmp = malloc(sizeof(constraint_t));

	if (tmp == NULL)
		return FALSE;

	p->constraints = (constraint_t**)tmp;
	p->constraints[p->n_constraints] = constraints;
	p->n_constraints++;

	return TRUE;
}
