#include <stdlib.h>
#include <tree.h>

tree_t tree_init() {
    return leaf_init(NULL, NULL);
}

void tree_free(tree_t t) {
    leaf_free(t);
}

leaf_t *leaf_init(u64 value, leaf_t *ancestor, u64 name) {
    leaf_t *l = (leaf_t*) malloc(sizeof(leaf_t));
    if (l == NULL)
        return NULL;

    l->value = value;

    if (ancestor != NULL) {
        leaf_append(ancestor, l);
        l->ancestor = ancestor;
    }

	l->name = name;

    return l;
}

void leaf_free(leaf_t *l) {
    size_t i = 0;

    if (l == NULL)
        return;

    if (l->n_children > 0) {
        for (; i < l->n_children ; i++)
            leaf_free(l->children[i]);

        free(l->children);
    }

    free(l->value);
    free(l);
}

void leaf_append(leaf_t *l, leaf_t *successor) {
    void *tmp = NULL;

    if (l == NULL || successor == NULL)
        return;

    if (l->n_children > 0)
        tmp = malloc(sizeof(leaf_t*));
    else
        tmp = realloc(l->children, (l->n_children + 1) * sizeof(leaf_t*));

    if (tmp == NULL)
        return;

    l->children = (leaf_t**) tmp;
    l->children[l->n_children++] = successor;
}

void leaf_remove(leaf_t *l, leaf_t *successor) {
    void *tmp = NULL;

    if (l == NULL || successor == NULL)
        return;

    if (l->n_children == 0) {
        return;
    } else if (l->n_children > 1) {
        tmp = realloc(l->children, (l->n_children - 1) * sizeof(leaf_t*));
        if (tmp == NULL)
            return;

        l->children = (leaf_t**) tmp;
    } else {
        free(l->children);
        l->children = NULL;
    }

    l->n_children--;
}
