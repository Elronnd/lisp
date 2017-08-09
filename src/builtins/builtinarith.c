#include "build-lisp.h"

Lval builtin_intadd(Lval *vals, lint numvals) {
	Lval tmp = {.type = LTYPE_INT, .integer = 0};

	for (lint i = 0; i < numvals; i++) {
		tmp.integer += vals[i].integer;
	}

	return tmp;
}

Lval builtin_floatadd(Lval *vals, lint numvals) {
	Lval tmp = {.type = LTYPE_FLOAT, .lfloat = 0.0};

	for (lint i = 0; i < numvals; i++) {
		tmp.lfloat += (vals[i].type == LTYPE_FLOAT) ? vals[i].lfloat : vals[i].integer;
	}

	return tmp;
}


Lval builtin_intsub(Lval *vals, lint numvals) {
	Lval tmp = {.type = LTYPE_INT, .integer = 0};

	if (numvals == 1) {
		tmp.integer = -vals[0].integer;
		return tmp;
	} else {
		tmp.integer = vals[0].integer;
	}

	for (lint i = 1; i < numvals; i++) {
		tmp.integer -= vals[i].integer;
	}

	return tmp;
}

Lval builtin_floatsub(Lval *vals, lint numvals) {
	Lval tmp = {.type = LTYPE_FLOAT, .lfloat = 0.0};

	if (numvals == 1) {
		tmp.lfloat = (vals[0].type == LTYPE_FLOAT) ? -vals[0].lfloat : -vals[0].integer;
		return tmp;
	} else {
		tmp.lfloat = (vals[0].type == LTYPE_FLOAT) ? vals[0].lfloat : vals[0].integer;
	}

	for (lint i = 1; i < numvals; i++) {
		tmp.lfloat -= (vals[i].type == LTYPE_FLOAT) ? vals[i].lfloat : vals[i].integer;
	}

	return tmp;
}


Lval builtin_intmul(Lval *vals, lint numvals) {
	Lval tmp = {.type = LTYPE_INT, .integer = 1};

	for (lint i = 0; i < numvals; i++) {
		tmp.integer *= vals[i].integer;
	}

	return tmp;
}

Lval builtin_floatmul(Lval *vals, lint numvals) {
	Lval tmp = {.type = LTYPE_FLOAT, .lfloat = 1.0};

	for (lint i = 0; i < numvals; i++) {
		tmp.lfloat *= (vals[i].type == LTYPE_FLOAT) ? vals[i].lfloat : vals[i].integer;
	}

	return tmp;
}


Lval builtin_intdiv(Lval *vals, lint numvals) {
	Lval tmp = {.type = LTYPE_INT, .integer = vals[0].integer};

	for (lint i = 1; i < numvals; i++) {
		tmp.integer /= vals[i].integer;
	}

	return tmp;
}

Lval builtin_floatdiv(Lval *vals, lint numvals) {
	Lval tmp = {.type = LTYPE_FLOAT, .lfloat = (vals[0].type == LTYPE_FLOAT) ? vals[0].lfloat : vals[0].integer};

	for (lint i = 1; i < numvals; i++) {
		tmp.lfloat /= (vals[i].type == LTYPE_FLOAT) ? vals[i].lfloat : vals[i].integer;
	}

	return tmp;
}

