#include "build-lisp.h"

#include <stdlib.h>
#include <ctype.h>

static bool couldbeint(const char *str, lint *out) {
	char *endptr;

	*out = strtoll(str, &endptr, 0);

	if (str == endptr)  {
		return false;
	}
	while (isspace(*endptr)) {  // look past the number for junk
		endptr++;
	}   

	if (*endptr) {
		return false;
	}

	return true;
}



static bool couldbefloat(const char *str, real *out) {
	char *endptr;

	*out = strtold(str, &endptr);

	if (str == endptr)  {
		return false;
	}
	while (isspace(*endptr)) {  // look past the number for junk
		endptr++;
	}   

	if (*endptr) {
		return false;
	}

	return true;
}


static Lval parse_lval(Lval val) {
	Lval tmp;

	if (val.type == LTYPE_UNDECIDED) {
		if (val.undecided[0] == '"') {
			val.type = LTYPE_STR;
			val.str = val.undecided;
			return val;
		} else if (couldbeint(val.undecided, &tmp.integer)) {
			tmp.type = LTYPE_INT;
			return tmp;
		} else if (couldbefloat(val.undecided, &tmp.lfloat)) {
			tmp.type = LTYPE_FLOAT;
			return tmp;
		} else {
			val.type = LTYPE_VARIABLE;
			val.varname = val.undecided;
			return val;
		}
	} else {
		return val;
	}
}


void parseast(Ast *ast) {
	if (ast->isval) {
		ast->val = parse_lval(ast->val);
	} else {
		for (size_t i = 0; i < ast->numchilds; i++) {
			parseast(&(ast->childs[i]));
		}
	}
}
