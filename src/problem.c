#include <stdlib.h>
#include <stdio.h>

#include <problem.h>
#include <tree.h>

problem_t *problem_init(const char *filename) {
    problem_t *p = NULL;
    FILE *f = NULL;
    char *str = NULL;
	constraint_t *tmpConstraint = NULL;
	u64 temp = 0;
	u64 tmp1 = 0, tmp2 = 0, tmp3 = 0;
	list_t *tmpList = NULL;
	var_t *tmpVar = NULL;

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
	// Lecture des variables/domaines de définitions
	do
	{
		if (temp > 0)
		{
			tmpVar = var_init(temp);						// On Récupère le nom
			fscanf(f, "%lu", temp);							// On lit le suivant
			do {											//
				var_add_to_definition(tmpVar, temp);		//
				fscanf(f, "%lu", temp);						// On lit le suivant
			} while (temp != -1);							// On continue jusqu'à -1 (fin de la ligne)
			problem_add_var(p, tmpVar);						// On ajoute au problème
		}
	} while (temp != -2);									// On termine la lecture des variables par un -2
	fscanf(f, "%lu", temp);									// Puis on commence la lecture des contraintes
	do
	{
		fscanf(f, "%lu", tmp1);								// On lit l'operateur
		fscanf(f, "%lu", tmp2);								// On lit la 2ème opérande
		fscanf(f, "%lu", tmp3);								// Et on récupère son type (var ou scalaire)
		tmpConstraint = constraint_init(var_init(temp), tmp1, tmp2, tmp3);
		problem_add_constraint(p, tmpConstraint);			// Puis on l'ajoute au problème
		fscanf(f, "%lu", temp);
	} while (temp <= -2);									// Et ça se termine par un -3


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

u64 *problem_solve(problem_t *p) {
    tree_t root = NULL;
    size_t i = 0;
    u64 *solution = NULL;

    if (p == NULL)
        return NULL;

    root = tree_init();
    for (; i < p->n_vars ; i++) {
        problem_alloc(p, root, p->vars[i]);
   }

    return solution;
}

bool_t problem_alloc(problem_t *p, leaf_t *root, var_t *var) {
    leaf_t *leaf = NULL;
    bool_t result = TRUE;
    size_t i = 0;

    if (root->n_children > 0) {
        for (; i < root->n_children ; i++)
            result = result && problem_alloc(p, root->children[i], var);
    } else {
        for (; i < var->def->size ; i++) {
            leaf = leaf_init(var->def->set[i], root, var->name);
            if (leaf == NULL)
                exit(EXIT_FAILURE);

            if (constraint_check(p, root, var->def->set[i])) {
                leaf_append(root, leaf);
            } else {
                leaf_free(leaf);
            }
        }

        if (root->n_children == 0)
            result = FALSE;
    }

    return result;
}
