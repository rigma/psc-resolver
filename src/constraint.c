#include <stdlib.h>

#include <constraint.h>
#include <set.h>

constraint_t *constraint_init(var_t *slave, operator_t op, void *master, master_t master_type) {
	constraint_t *c = (constraint_t*) malloc(sizeof(constraint_t));
	if (c == NULL)
		return NULL;

	// TODO : faudrait v�rifier que la variable esclave existe bien en m�moire de fa�on plus efficace
	if (slave == NULL) {
		free(c);

		return NULL;
	}

	c->slave = slave;
	c->op = op;
	c->master_type = master_type;
	
	// TODO : pareil faudrait vraiment qu'on soit s�r que la variable existe dans ce cas
	if (c->master_type == VAR && master == NULL) {
		free(c);

		return NULL;
	}

	c->master = master;

	return c;
}

void constraint_free(constraint_t *c) {
	if (c->master_type == SCALAR)
		free(c->master);
	else if (c->master_type == SET)
		set_free((set_t*) c->master);

	free(c);
}
