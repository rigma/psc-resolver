#include <stdlib.h>
#include <string.h>

#include <defines.h>
#include <list.h>

list_t *list_init(list_t *l) {
	node_t *it = NULL, *n = NULL, *previous = NULL;
	list_t *list = NULL;
	
	list = (list_t*) malloc(sizeof(list_t));
	if (list == NULL)
		return NULL;

	list->first = NULL;
	list->last = NULL;
	list->size = 0;

	if (l != NULL) {
		for (it = l->first; it != NULL; it = it->succ) {
			n = (node_t*) malloc(sizeof(node_t));
			if (n == NULL) {
				for (it = list->first; it != NULL; it = it->succ)
					free(n);

				free(list);

				return NULL;
			}
			
			list->last = n;
			if (it == l->first)
				list->first = n;

			if (previous != NULL) {
				n->pred = previous;
				previous->succ = n;
			} else {
				n->pred = NULL;
			}

			n->succ = NULL;
			previous = n;
		}

		list->size = l->size;
	}

	return list;
}

void list_free(list_t *l) {
	node_t *tmp = NULL, *it = NULL;

	if (l == NULL)
		return;

	it = l->first;
	while (it != NULL) {
		tmp = it->succ;
			
		free(it);
			
		it = tmp;
	}

	free(l);
}

void *list_at(list_t *l, size_t offset) {
	node_t *it = NULL;
	size_t i = 0;

	if (l == NULL)
		return NULL;

	it = l->first;
	while (it != NULL && i < offset) {
		it = it->succ;
		i++;
	}

	return it != NULL ? it->value : NULL;
}

bool_t list_prepend(list_t *l, void *el) {
	node_t *n = NULL;

	if (l == NULL)
		return FALSE;

	n = (node_t*) malloc(sizeof(node_t));
	if (n == NULL)
		return FALSE;

	n->value = el;
	n->pred = NULL;
	n->succ = l->first;
	l->first = n;

	if (l->last == NULL)
		l->last = n;

	l->size++;

	return TRUE;
}

bool_t list_append(list_t *l, void *el) {
	node_t *n = NULL;

	if (l == NULL)
		return FALSE;

	n = (node_t*) malloc(sizeof(node_t));
	if (n == NULL)
		return FALSE;

	n->value = el;
	n->pred = l->last;
	n->succ = NULL;
	l->last = n;

	if (l->first == NULL)
		l->first = n;

	l->size++;

	return TRUE;
}

bool_t list_insert(list_t *l, node_t *after, node_t *before, void *el) {
	node_t *n = NULL;

	if (l == NULL) {
		return FALSE;
	} else if (after == NULL && before == NULL) {
		if (l->size != 0 || l->first != NULL || l->last != NULL)
			return FALSE;

		n = (node_t*) malloc(sizeof(node_t*));
		if (n == NULL)
			return FALSE;

		n->value = el;
		n->pred = NULL;
		n->succ = NULL;

		l->first = n;
		l->last = n;
	} else if (after == NULL) {
		return list_prepend(l, el);
	} else if (before == NULL) {
		return list_append(l, el);
	} else {
		if (after->succ != before || before->pred != after)
			return FALSE;

		n = (node_t*) malloc(sizeof(node_t*));
		if (n == NULL)
			return FALSE;

		n->value = el;
		n->pred = after;
		n->succ = before;

		before->succ = n;
		after->pred = n;
	}

	l->size++;

	return TRUE;
}

bool_t list_remove(list_t *l, void *el, bool_t all) {
	node_t *it = NULL;

	if (l == NULL)
		return FALSE;

	it = l->first;
	while (it != NULL) {
		if (it->value == el) {
			if (l->first == it && l->last == it) {
				l->first = NULL;
				l->last = NULL;
			} else if (l->first == it) {
				l->first = it->succ;
				it->succ->pred = NULL;
			} else if (l->last == it) {
				l->last = it->pred;
				it->pred->succ = NULL;
			} else {
				it->pred->succ = it->succ;
				it->succ->pred = it->pred;
			}

			l->size--;
			free(it);

			return all ? TRUE || list_remove(l, el, TRUE) : TRUE;
		}

		it = it->succ;
	}

	return FALSE;
}
