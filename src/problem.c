#include <stdlib.h>
#include <stdio.h>

#include <problem.h>

problem_t *problem_init(const char *filename) {
    problem_t *p = NULL;
    FILE *f = NULL;
    char *str = NULL;

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

    // TODO : lire le fichier et implanter le langage

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
