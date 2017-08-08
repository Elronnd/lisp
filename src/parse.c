#include "build-lisp.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

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
			tmp.type = LTYPE_STR;
			tmp.str = malloc(strlen(val.undecided));

			val.undecided[strlen(val.undecided)-1] = '\0';
			// +1 to get rid of the "
			strcpy(tmp.str, val.undecided + 1);
			free(val.undecided);

			return tmp;
		} else if ((val.undecided[0] == '#') && (strlen(val.undecided) == 2) && (val.undecided[1] == 'f' || val.undecided[1] == 't')) {
			tmp.type = LTYPE_BOOL;
			switch (val.undecided[1]) {
				case 'f': tmp.boolean = false; break;
				case 't': tmp.boolean = true; break;
			}

			return tmp;
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

void valtostr(Lval val, char bufout[2048]) {
	switch (val.type) {
		case LTYPE_INT: sprintf(bufout, "%lld", val.integer); break;
		case LTYPE_STR: sprintf(bufout, "\"%s\"", val.str); break;
		case LTYPE_FLOAT: sprintf(bufout, "%Lf", val.lfloat); break;
		case LTYPE_BOOL: strcpy(bufout, val.boolean ? "true" : "false"); break;
		default: printf("Unknown.");
	}
}


void parseast(Ast *ast) {
	if (ast->isval) {
		ast->val = parse_lval(ast->val);
	} else {
		for (lint i = 0; i < ast->numchilds; i++) {
			parseast(&(ast->childs[i]));
		}
	}
}
