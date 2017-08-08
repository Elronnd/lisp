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

	Ltype tmp = vals[0].type;

	for (size_t i = 0; i < numvals; i++) {
		if ((vals[i].type != LTYPE_INT) && (vals[i].type != LTYPE_FLOAT)) {
			char buf[2048];
			valtostr(vals[i], buf);
			error("Unexpected type %d (can only be INT or FLOAT), for adding, in variable %s", vals[i].type, buf);
		}

		if (vals[0].type == LTYPE_FLOAT)
			tmp = vals[0].type;
	}

	switch (tmp) {
		case LTYPE_INT: return builtin_intadd(vals, numvals);
		case LTYPE_FLOAT: return builtin_floatadd(vals, numvals);
	}
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

	Ltype tmp = vals[0].type;

	for (size_t i = 0; i < numvals; i++) {
		if ((vals[i].type != LTYPE_INT) && (vals[i].type != LTYPE_FLOAT)) {
			char buf[2048];
			valtostr(vals[i], buf);
			error("Unexpected type %d (can only be INT or FLOAT), for subtracting, in variable %s", vals[i].type, buf);
		}

		if (vals[0].type == LTYPE_FLOAT)
			tmp = vals[0].type;
	}


	switch (tmp) {
		case LTYPE_INT: return builtin_intsub(vals, numvals);
		case LTYPE_FLOAT: return builtin_floatsub(vals, numvals);
	}
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

	Ltype tmp = vals[0].type;

	for (size_t i = 0; i < numvals; i++) {
		if ((vals[i].type != LTYPE_INT) && (vals[i].type != LTYPE_FLOAT)) {
			char buf[2048];
			valtostr(vals[i], buf);
			error("Unexpected type %d (can only be INT or FLOAT), for subtracting, in variable %s", vals[i].type, buf);
		}

		if (vals[0].type == LTYPE_FLOAT)
			tmp = vals[0].type;
	}


	switch (tmp) {
		case LTYPE_INT: return builtin_intmul(vals, numvals);
		case LTYPE_FLOAT: return builtin_floatmul(vals, numvals);
	}
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

	Ltype tmp = vals[0].type;

	for (size_t i = 0; i < numvals; i++) {
		if ((vals[i].type != LTYPE_INT) && (vals[i].type != LTYPE_FLOAT)) {
			char buf[2048];
			valtostr(vals[i], buf);
			error("Unexpected type %d (can only be INT or FLOAT), for subtracting, in variable %s", vals[i].type, buf);
		}

		if (vals[0].type == LTYPE_FLOAT)
			tmp = vals[0].type;
	}

	switch (tmp) {
		case LTYPE_INT: return builtin_intdiv(vals, numvals);
		case LTYPE_FLOAT: return builtin_floatdiv(vals, numvals);
	}
}


Lval builtin_concat(Lval *vals, size_t numvals) {
	if (numvals == 0)
		error("Required at least one parameter for concatenation");

	Lval tmp = {.type = LTYPE_STR, .str = NULL};

	for (size_t i = 0; i < numvals; i++) {
		if (vals[i].type != LTYPE_STR) {
			char buf[2048];
			valtostr(vals[i], buf);
			error("Unexpected type %d (can only be STR), for concatenation, in variable %s", vals[i].type, buf);
		}

		tmp.str = realloc(tmp.str, strlen(tmp.str) + strlen(vals[i].str) + 1);
		
		if (i == 0)
			tmp.str[0] = '\0';

		strcat(tmp.str, vals[i].str);
	}

	return tmp;
}
