#include <stdlib.h>

#include <E7set.h>

set_t *set_init() {
	set_t *s = (set_t*) malloc(sizeof(set_t));
	if (s == NULL)
		return NULL;

	s->set = NULL;
	s->size = 0;

	return s;
}

set_t *set_init_from_table(u64 *table, size_t size) {
	set_t *s = NULL;
	size_t i = 0;

	if (table == NULL)
		return NULL;

	s = (set_t*) malloc(sizeof(set_t));
	if (s == NULL)
		return NULL;

	s->set = (u64*) malloc(size * sizeof(u64));
	s->size = size;

	if (s->set == NULL) {
		free(s);

		return NULL;
	}

	for (; i < size; i++)
		s->set[i] = table[i];

	return s;
}

set_t *set_init_from_interval(u64 begin, u64 end) {
	set_t *s = NULL;
	u64 i = 0;

	if (begin > end)
		return NULL;

	s = (set_t*) malloc(sizeof(set_t));
	if (s == NULL)
		return NULL;

	s->size = (size_t) (end - begin + 1);
	s->set = (u64*) malloc(s->size * sizeof(u64));
	
	if (s->set == NULL) {
		free(s);

		return NULL;
	}

	for (; i < s->size; i++)
		s->set[i] = begin + i;

	return s;
}

void set_free(set_t *s) {
	if (s == NULL)
		return;

	free(s->set);
	free(s);
}

bool_t in_set(set_t *s, u64 el) {
	size_t i = 0;

	if (s == NULL)
		return FALSE;

	for (; i < s->size; i++) {
		if (s->set[i] == el)
			return TRUE;
	}

	return FALSE;
}

bool_t set_add_element(set_t *s, u64 el) {
	void *tmp = NULL;

	if (s == NULL || in_set(s, el))
		return FALSE;

	tmp = s->set == NULL ? malloc(sizeof(u64)) : realloc(s->set, (s->size + 1) * sizeof(u64));
	if (tmp == NULL)
		return FALSE;

	s->set = (u64*) tmp;
	s->set[s->size] = el;
	s->size++;

	return TRUE;
}
