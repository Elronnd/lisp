#include "build-lisp.h"

#include <math.h>
#include <string.h>


Lval builtin_floatcmp(Lval *vals, lint numvals) {
	const real epsilon = 3.1401849173675503e-16;
	Lval ret = {.type = LTYPE_BOOL, .boolean = false};

	for (lint i = 1; i < numvals; i++) {
		if (fabsl(vals[i].lfloat - vals[i-1].lfloat) >= epsilon) {
			return ret;
		}
	}

	ret.boolean = true;
	return ret;
}

Lval builtin_strcmp(Lval *vals, lint numvals) {
	Lval ret = {.type = LTYPE_BOOL, .boolean = false};

	for (lint i = 1; i < numvals; i++) {
		if (strcmp(vals[i].str, vals[i-1].str)) {
			return ret;
		}
	}

	ret.boolean = true;
	return ret;
}

Lval builtin_intcmp(Lval *vals, lint numvals) {
	Lval ret = {.type = LTYPE_BOOL, .boolean = false};

	for (lint i = 1; i < numvals; i++) {
		if (vals[i].integer != vals[i-1].integer) {
			return ret;
		}
	}

	ret.boolean = true;
	return ret;
}

Lval builtin_boolcmp(Lval *vals, lint numvals) {
	Lval ret = {.type = LTYPE_BOOL, .boolean = false};

	for (lint i = 1; i < numvals; i++) {
		if (vals[i].boolean != vals[i-1].boolean) {
			return ret;
		}
	}

	ret.boolean = true;
	return ret;
}

Lval builtin_intlt(Lval *vals, lint numvals) {
	Lval ret = {.type = LTYPE_BOOL, .boolean = false};

	for (lint i = 1; i < numvals; i++) {
		if (vals[i].integer <= vals[i-1].integer) {
			return ret;
		}
	}

	ret.boolean = true;
	return ret;
}


Lval builtin_floatlt(Lval *vals, lint numvals) {
	Lval ret = {.type = LTYPE_BOOL, .boolean = false};

	for (lint i = 1; i < numvals; i++) {
		if ((vals[i].type == LTYPE_FLOAT ? vals[i].lfloat : vals[i].integer) <= (vals[i-1].type == LTYPE_FLOAT ? vals[i-1].lfloat : vals[i-1].integer)) {
			return ret;
		}
	}

	ret.boolean = true;
	return ret;
}


Lval builtin_intgt(Lval *vals, lint numvals) {
	Lval ret = {.type = LTYPE_BOOL, .boolean = false};

	for (lint i = 1; i < numvals; i++) {
		if (vals[i].integer >= vals[i-1].integer) {
			return ret;
		}
	}

	ret.boolean = true;
	return ret;
}

Lval builtin_floatgt(Lval *vals, lint numvals) {
	Lval ret = {.type = LTYPE_BOOL, .boolean = false};

	for (lint i = 1; i < numvals; i++) {
		if ((vals[i].type == LTYPE_FLOAT ? vals[i].lfloat : vals[i].integer) >= (vals[i-1].type == LTYPE_FLOAT ? vals[i-1].lfloat : vals[i-1].integer)) {
			return ret;
		}
	}

	ret.boolean = true;
	return ret;
}

