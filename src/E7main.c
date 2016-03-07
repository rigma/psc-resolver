#include <stdlib.h>
#include <stdio.h>

#include "E7problem.h"

int main(int argc, char **argv) {
	problem_t *p = problem_init("E72.txt");
	printf("bonjour\n");
	u64 *solution;

	solution = problem_solve(p);

	problem_free(p);
	system("pause");

	return EXIT_SUCCESS;
}
