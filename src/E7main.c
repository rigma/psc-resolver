#include <stdlib.h>
#include <stdio.h>

#include "E7problem.h"

int main(int argc, char **argv) {
	problem_t *p = problem_init("E71.txt");

	u64 solution;

	solution = problem_solve(p);

	problem_free(p);

	return EXIT_SUCCESS;
}
