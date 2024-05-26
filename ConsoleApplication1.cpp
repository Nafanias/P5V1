#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct coeff {
	double a, b, c;
} coeff;

typedef struct result {
	double x1, x2, y1, y2;
} result;

int input(int, char**, coeff*);
void help(char**);
result calc(coeff);
void fixzero(result*);
void print(result);

int main(int argc, char** argv) {
	coeff C;
	if (input(argc, argv, &C)) {
		help(argv);
		exit(EXIT_FAILURE);
	}
	result Ans = calc(C);
	print(Ans);
	return 0;
}

int input(int argc, char** argv, coeff* C) {
	if (argc != 4)
		return 1;
	char* p;
	C->a = strtod(argv[1], &p);

	if (argv[1] == p || *p != '\0' || p == NULL || C->a == 0)
		return 1;
	C->b = strtod(argv[2], &p);
	if (argv[2] == p || *p != '\0' || p == NULL)
		return 1;
	C->c = strtod(argv[3], &p);
	if (argv[3] == p || *p != '\0' || p == NULL)
		return 1;
	return 0;
}

void help(char** argv) {
	printf("Error!\nProgram usage:\n\t%s a b c\n", argv[0]);
	return;
}

result calc(coeff C) {
	result A;
	double D = C.b * C.b - 4 * C.a * C.c;
	if (D < 0) {
		A.x1 = -C.b / 2 / C.a;
		A.x2 = -sqrt(-D) / 2 / C.a;
		A.y1 = -C.b / 2 / C.a;
		A.y2 = sqrt(-D) / 2 / C.a;
	}
	if (D == 0) {
		A.x1 = -C.b / 2 / C.a;
		A.x2 = 0;
		A.y1 = -C.b / 2 / C.a;
		A.y2 = 0;
	}
	if (D > 0) {
		A.x1 = -(C.b + sqrt(D)) / 2 / C.a;
		A.x2 = 0;
		A.y1 = (-C.b + sqrt(D)) / 2 / C.a;
		A.y2 = 0;
	}
	fixzero(&A);
	return A;
}

void fixzero(result* A) {
	if (A->x1 == 0 && signbit(A->x1)) A->x1 = +0.;

	if (A->x2 == 0 && signbit(A->x2)) A->x2 = +0.;
	if (A->y1 == 0 && signbit(A->y1)) A->y1 = +0.;
	if (A->y2 == 0 && signbit(A->y2)) A->y2 = +0.;
	return;
}

void print(result A) {
	printf("x1 = (%g, %g)\nx2 = (%g, %g)\n", A.x1, A.x2, A.y1, A.y2);
}