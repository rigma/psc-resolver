#include <stdlib.h>
#include <stdio.h>

#include "problem.h"

int main(int argc, char **argv) {
	problem_t *p = problem_init("1.txt");

	printf("YAHOU");

	problem_free(p);

	return EXIT_SUCCESS;
}
