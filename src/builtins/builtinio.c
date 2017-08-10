#include "coral.h"

#include <stdlib.h>
#include <stdio.h>

Lval builtin_readchar(Lval *vals, lint numvals) {
	// to appease the compiler
	(void) vals;
	(void) numvals;

	Lval tmp = {.type = LTYPE_STR, .str = malloc(2)};

	tmp.str[1] = '\0';
	tmp.str[0] = getchar();

	return tmp;
}
