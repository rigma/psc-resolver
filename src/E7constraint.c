#include <stdlib.h>

#include <E7constraint.h>
#include <E7set.h>

constraint_t *constraint_init(var_t *slave, operator_t op, u64 master, master_t master_type) {
	constraint_t *c = (constraint_t*) malloc(sizeof(constraint_t));
	if (c == NULL)
		return NULL;

	// TODO : faudrait vérifier que la variable esclave existe bien en mémoire de façon plus efficace
	if (slave == NULL) {
		free(c);

		return NULL;
	}

	c->slave = slave;
	c->op = op;
	c->master_type = master_type;
	
	// TODO : pareil faudrait vraiment qu'on soit sûr que la variable existe dans ce cas
	/*if (c->master_type == VAR && master == NULL) {
		free(c);

		return NULL;
	}*/

	c->master = master;

	return c;
}

void constraint_free(constraint_t *c) {
	/*if (c->master_type == SCALAR)
		free(c->master);
	else if (c->master_type == SET)
		set_free((set_t*) c->master);*/

	//free(c);
}
 
bool_t constraint_check(size_t size, constraint_t **constraints, leaf_t *leaf, u64 slave, u64 value)
{
	leaf_t *it = leaf;
	bool_t result = TRUE;
	size_t i = 0; // compteur des variables
	
	for (; i < size - 1; i++)
	{
		if (slave == constraints[i]->slave->name)
		{
			if (constraints[i]->master_type == SCALAR) {
				if (constraints[i]->op == EQUAL)
					result = result && constraints[i]->master == value ? TRUE : FALSE;
				else if (constraints[i]->op == DIFFERENT)
					result = result && constraints[i]->master != value ? TRUE : FALSE;
				else if (constraints[i]->op == SGT)
					result = result && constraints[i]->master > value ? TRUE : FALSE;
				else if (constraints[i]->op == SLT)
					result = result && constraints[i]->master < value ? TRUE : FALSE;
				else if (constraints[i]->op == GT)
					result = result && constraints[i]->master >= value ? TRUE : FALSE;
				else if (constraints[i]->op == LT)
					result = result && constraints[i]->master <= value ? TRUE : FALSE;
			} else {		
				while (it != NULL) {
					if (it->name == constraints[i]->master) {
						if (constraints[i]->op == EQUAL)
							result = result && it->value == value ? TRUE : FALSE;
						else if (constraints[i]->op == DIFFERENT)
							result = result && it->value != value ? TRUE : FALSE;
						else if (constraints[i]->op == SGT)
							result = result && it->value > value ? TRUE : FALSE;
						else if (constraints[i]->op == SLT)
							result = result && it->value < value ? TRUE : FALSE;
						else if (constraints[i]->op == GT)
							result = result && it->value >= value ? TRUE : FALSE;
						else if (constraints[i]->op == LT)
							result = result && it->value <= value ? TRUE : FALSE;

						break;
					}

					it = it->ancestor;
				}
			}

			if (!result)
				return FALSE;
		}
	}

	return result;
}