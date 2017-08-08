#include "build-lisp.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

Lval builtin_intadd(Lval *vals, size_t numvals) {
	Lval tmp = {.type = LTYPE_INT, .integer = 0};

	for (size_t i = 0; i < numvals; i++) {
		tmp.integer += vals[i].integer;
	}

	return tmp;
}

Lval builtin_floatadd(Lval *vals, size_t numvals) {
	Lval tmp = {.type = LTYPE_FLOAT, .lfloat = 0.0};

	for (size_t i = 0; i < numvals; i++) {
		tmp.lfloat += (vals[i].type == LTYPE_FLOAT) ? vals[i].lfloat : vals[i].integer;
	}

	return tmp;
}


Lval builtin_add(Lval *vals, size_t numvals) {
	if (numvals == 0)
		error("Required at least one parameter for addition");

	for (size_t i = 0; i < numvals; i++) {
		if (vals[i].type == LTYPE_FLOAT)
			return builtin_floatadd(vals, numvals);
	}

	return builtin_intadd(vals, numvals);
}

Lval builtin_intsub(Lval *vals, size_t numvals) {
	Lval tmp = {.type = LTYPE_INT, .integer = 0};

	for (size_t i = 0; i < numvals; i++) {
		tmp.integer -= vals[i].integer;
	}

	return tmp;
}

Lval builtin_floatsub(Lval *vals, size_t numvals) {
	Lval tmp = {.type = LTYPE_FLOAT, .lfloat = 0.0};

	for (size_t i = 0; i < numvals; i++) {
		tmp.lfloat -= (vals[i].type == LTYPE_FLOAT) ? vals[i].lfloat : vals[i].integer;
	}

	return tmp;
}



Lval builtin_sub(Lval *vals, size_t numvals) {
	if (numvals == 0)
		error("Required at least one parameter for subtraction");

	for (size_t i = 0; i < numvals; i++) {
		if (vals[i].type == LTYPE_FLOAT)
			return builtin_floatsub(vals, numvals);
	}


	return builtin_intsub(vals, numvals);
}



Lval builtin_intmul(Lval *vals, size_t numvals) {
	Lval tmp = {.type = LTYPE_INT, .integer = 1};

	for (size_t i = 0; i < numvals; i++) {
		tmp.integer *= vals[i].integer;
	}

	return tmp;
}

Lval builtin_floatmul(Lval *vals, size_t numvals) {
	Lval tmp = {.type = LTYPE_FLOAT, .lfloat = 1.0};

	for (size_t i = 0; i < numvals; i++) {
		tmp.lfloat *= (vals[i].type == LTYPE_FLOAT) ? vals[i].lfloat : vals[i].integer;
	}

	return tmp;
}


Lval builtin_mul(Lval *vals, size_t numvals) {
	if (numvals == 0)
		error("Required at least one parameter for multiplication");

	for (size_t i = 0; i < numvals; i++) {
		if (vals[i].type == LTYPE_FLOAT)
			return builtin_floatmul(vals, numvals);
	}


	return builtin_intmul(vals, numvals);
}


Lval builtin_intdiv(Lval *vals, size_t numvals) {
	Lval tmp = {.type = LTYPE_INT, .integer = 1};

	for (size_t i = 0; i < numvals; i++) {
		tmp.integer /= vals[i].integer;
	}

	return tmp;
}

Lval builtin_floatdiv(Lval *vals, size_t numvals) {
	Lval tmp = {.type = LTYPE_FLOAT, .lfloat = 1.0};

	for (size_t i = 0; i < numvals; i++) {
		tmp.lfloat /= (vals[i].type == LTYPE_FLOAT) ? vals[i].lfloat : vals[i].integer;
	}

	return tmp;
}



Lval builtin_div(Lval *vals, size_t numvals) {
	if (numvals == 0)
		error("Required at least one parameter for division");

	for (size_t i = 0; i < numvals; i++) {
		if (vals[i].type == LTYPE_FLOAT)
			return builtin_floatdiv(vals, numvals);
	}

	return builtin_intdiv(vals, numvals);
}


Lval builtin_concat(Lval *vals, size_t numvals) {
	if (numvals == 0)
		error("Required at least one parameter for concatenation");

	Lval tmp = {.type = LTYPE_STR, .str = NULL};

	for (size_t i = 0; i < numvals; i++) {
		tmp.str = realloc(tmp.str, strlen(tmp.str) + strlen(vals[i].str) + 1);
		
		if (i == 0)
			tmp.str[0] = '\0';

		strcat(tmp.str, vals[i].str);
	}

	return tmp;
}
