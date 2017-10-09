#include "coral.h"

#include <inttypes.h>
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


static Lval parse_lval(char *str) {
	Lval tmp;

	if (str[0] == '"') {
		tmp.type = LTYPE_STR;
		tmp.str = malloc(strlen(str));

		str[strlen(str)-1] = '\0';
		// +1 to get rid of the "
		strcpy(tmp.str, str + 1);
		free(str);
	} else if ((str[0] == '#') && (strlen(str) == 2) && (str[1] == 'f' || str[1] == 't')) {
		tmp.type = LTYPE_BOOL;
		switch (str[1]) {
			case 'f': tmp.boolean = false; break;
			case 't': tmp.boolean = true; break;
		}
	} else if (couldbeint(str, &tmp.integer)) {
		tmp.type = LTYPE_INT;
	} else if (couldbefloat(str, &tmp.lfloat)) {
		tmp.type = LTYPE_FLOAT;
	} else {
		tmp.type = LTYPE_VARIABLE;
		tmp.varname = malloc(strlen(str));
		strcpy(tmp.varname, str);
		free(str);
	}

	return tmp;
}

void valtostr(Lval val, char bufout[2048]) {
	switch (val.type) {
		case LTYPE_INT: sprintf(bufout, "%" PRId64, val.integer); break;
		case LTYPE_STR: sprintf(bufout, "\"%s\"", val.str); break;
		case LTYPE_FLOAT: sprintf(bufout, "%.20Lf", val.lfloat); break;
		case LTYPE_BOOL: strcpy(bufout, val.boolean ? "true" : "false"); break;
		default: strcpy(bufout, "<unknown>");
	}
}


Ast parseast(Token_tree *t) {
	Ast ret = {.isval = false};

	if (t->first.istree) {
		error("Functions cannot be trees yet, they must be literals.");
	}
	ret.op = t->first.str; // reuse this memory


	ret.numchilds = t->numargs;
	ret.childs = calloc(sizeof(struct Ast), ret.numchilds);


	for (lint i = 0; i < t->numargs; i++) {
		if (t->args[i].istree) {
			ret.childs[i] = parseast(t->args[i].tree);
			free(t->args[i].tree);
			ret.childs[i].isval = false;
		} else {
			ret.childs[i].isval = true;
			ret.childs[i].val = parse_lval(t->args[i].str);
		}
	}

	free(t->args);

	return ret;
}
