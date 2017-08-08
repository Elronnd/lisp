#include "build-lisp.h"

#include <stddef.h>
#include <stdlib.h>

const char *valtostr(Lval val) {
	return "Undone";
}

Lval getundecided(Lval val) {
	Lval tmp = {.type = LTYPE_INT};
	tmp.integer = atoll(val.undecided);

	return tmp;
}

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
		tmp.lfloat += vals[i].lfloat;
	}

	return tmp;
}


Lval builtin_add(Lval *vals, size_t numvals) {
	if (numvals == 0)
		error("Required at least one parameter for addition");

	for (size_t i = 0; i < numvals; i++) {
		if (vals[i].type == LTYPE_UNDECIDED)
			vals[i] = getundecided(vals[i]);
	}

	Ltype tmp = vals[0].type;
	if ((tmp != LTYPE_INT) && (tmp != LTYPE_FLOAT))
		error("Unexpected type %d (can only be INT or FLOAT) for adding, in variable %s", tmp, valtostr(vals[0]));

	for (size_t i = 1; i < numvals; i++) {
		if (vals[i].type != tmp) {
			error("Unexpected type %d (can only be INT or FLOAT), for adding, in variable %s", vals[i].type, valtostr(vals[i]));
		}
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
		tmp.lfloat -= vals[i].lfloat;
	}

	return tmp;
}



Lval builtin_sub(Lval *vals, size_t numvals) {
	if (numvals == 0)
		error("Required at least one parameter for subtraction");

	Ltype tmp = vals[0].type;
	if ((tmp != LTYPE_INT) && (tmp != LTYPE_FLOAT))
		error("Unexpected type %d (can only be INT or FLOAT) for subtracting, in variable %s", tmp, valtostr(vals[0]));

	for (size_t i = 1; i < numvals; i++) {
		if (vals[i].type != tmp) {
			error("Unexpected type %d (can only be INT or FLOAT), for subtracting, in variable %s", vals[i].type, valtostr(vals[i]));
		}
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
		tmp.lfloat *= vals[i].lfloat;
	}

	return tmp;
}



Lval builtin_mul(Lval *vals, size_t numvals) {
	if (numvals == 0)
		error("Required at least one parameter for multiplication");

	Ltype tmp = vals[0].type;
	if ((tmp != LTYPE_INT) && (tmp != LTYPE_FLOAT))
		error("Unexpected type %d (can only be INT or FLOAT) for multiplying, in variable %s", tmp, valtostr(vals[0]));

	for (size_t i = 1; i < numvals; i++) {
		if (vals[i].type != tmp) {
			error("Unexpected type %d (can only be INT or FLOAT), for multiplying, in variable %s", vals[i].type, valtostr(vals[i]));
		}
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
		tmp.lfloat /= vals[i].lfloat;
	}

	return tmp;
}



Lval builtin_div(Lval *vals, size_t numvals) {
	if (numvals == 0)
		error("Required at least one parameter for division");

	Ltype tmp = vals[0].type;
	if ((tmp != LTYPE_INT) && (tmp != LTYPE_FLOAT))
		error("Unexpected type %d (can only be INT or FLOAT) for dividing, in variable %s", tmp, valtostr(vals[0]));

	for (size_t i = 1; i < numvals; i++) {
		if (vals[i].type != tmp) {
			error("Unexpected type %d (can only be INT or FLOAT), for dividing, in variable %s", vals[i].type, valtostr(vals[i]));
		}
	}

	switch (tmp) {
		case LTYPE_INT: return builtin_intdiv(vals, numvals);
		case LTYPE_FLOAT: return builtin_floatdiv(vals, numvals);
	}
}


