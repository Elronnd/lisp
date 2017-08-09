#include "build-lisp.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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


Lval builtin_strcat(Lval *vals, lint numvals) {
	if (numvals == 0)
		error("Required at least one parameter for concatenation");

	Lval tmp = {.type = LTYPE_STR, .str = NULL};

	for (lint i = 0; i < numvals; i++) {
		if (i == 0) {
			tmp.str = malloc(strlen(vals[0].str) + 1);
			tmp.str[0] = '\0';
		} else {
			tmp.str = realloc(tmp.str, strlen(tmp.str) + strlen(vals[i].str) + 1);
		}


		strcat(tmp.str, vals[i].str);
	}

	return tmp;
}

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

Lval builtin_if(Lval *vals, lint numvals) {
	if ((vals[0].type != LTYPE_BOOL) && (vals[0].type != LTYPE_INT))
		error("Type %d cannot be coerced to a boolean", vals[0].type);

	bool foo = (vals[0].type == LTYPE_BOOL) ? vals[0].boolean : vals[0].integer;

	if (foo) {
		return vals[1];
	} else {
		if (numvals == 1) {
			Lval out = {.type = LTYPE_VOID};
			return out;
		} else {
			return vals[2];
		}
	}
}
