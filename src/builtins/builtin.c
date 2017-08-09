#include "build-lisp.h"

#include <stdlib.h>
#include <string.h>


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
