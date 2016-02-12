#include <stdlib.h>

#include <var.h>

var_t *var_init(string_t *name) {
	var_t *var = (var_t*) malloc(sizeof(var_t));
	if (var == NULL)
		return NULL;

	var->name = name == NULL ? string_from_stdin() : name;
	var->def = set_init();

	return var;
}

void var_free(var_t *var) {
	if (var == NULL)
		return;

	string_free(var->name);
	set_free(var->def);
	free(var);
}

bool_t var_set_interval(var_t *var, u64 begin, u64 end) {
	if (var == NULL)
		return FALSE;

	if (var->def != NULL)
		set_free(var->def);

	var->def = set_init_from_interval(begin, end);
	
	return var->def == NULL ? FALSE : TRUE;
}

bool_t var_add_to_definition(var_t *var, u64 el) {
	return var == NULL ? FALSE : set_add_element(var->def, el);
}
