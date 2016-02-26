#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <str.h>

string_t *string_init(char *str) {
	string_t *s = (string_t*) malloc(sizeof(string_t));
	if (s == NULL)
		return NULL;

	if (str != NULL) {
		s->length = strlen(str) + 1;
		s->str = (char*) malloc(s->length * sizeof(char));
		if (s->str == NULL) {
			free(s);

			return NULL;
		}

		strcpy(s->str, str);
	} else {
		s->str = NULL;
		s->length = 0;
	}

	return s;
}

void string_free(string_t *str) {
	if (str == NULL)
		return;

    if (str->str != NULL)
	    free(str->str);
	
    free(str);
}

string_t *string_from_stdin() {
	string_t *str = string_init(NULL);
	char c = 0;
	
	do {
		c = fgetc(stdin);
		if (c != '\n' || c != EOF) {
			if (!string_add_char(str, c)) {
				string_free(str);

				return NULL;
			}
		}
	} while (c != '\n' || c != EOF);

	return str;
}

string_t *string_cpy(string_t *str) {
	return string_init(str->str);
}

bool_t string_add_char(string_t *str, char c) {
	void *tmp = NULL;

	if (str == NULL)
		return FALSE;

	tmp = str->str == NULL ? malloc(2 * sizeof(char)) : realloc(str->str, (str->length + 1) * sizeof(char));
	if (tmp == NULL)
		return FALSE;

	str->str = (char*) tmp;
	str->str[str->length] = c;
	str->str[str->length + 1] = '\0';
	str->length = str->length == 0 ? 2 : str->length + 1;

	return TRUE;
}

bool_t string_cat(string_t *a, string_t *b) {
	void *tmp = NULL;

	if (a == NULL || b == NULL)
		return FALSE;

	tmp = realloc(a->str, (a->length + b->length - 1) * sizeof(char));
	if (tmp == NULL)
		return FALSE;

	a->str = tmp;
	a->length += b->length - 1;

	strcat(a->str, b->str);

	return TRUE;
}

bool_t string_cmp(string_t *a, string_t *b) {
	return !strcmp(a->str, b->str) ? TRUE : FALSE;
}
