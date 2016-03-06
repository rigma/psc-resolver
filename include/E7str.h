#ifndef STR_H
#define STR_H

#include <stddef.h>

#include "E7defines.h"

typedef struct {
	char *str;
	size_t length;
} string_t;

string_t *string_init(char *str);
void string_free(string_t *str);

string_t *string_from_stdin();

string_t *string_cpy(string_t *str);

bool_t string_add_char(string_t *str, char c);
bool_t string_cat(string_t *a, string_t *b);
bool_t string_cmp(string_t *a, string_t *b);

#endif
