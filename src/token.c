#include "build-lisp.h"

#include <stdlib.h>
#include <ctype.h>


Ast tokenize(const char *str, lint *index) {
#define munch_whitespace \
	while (isspace(str[*index])) { \
		(*index)++; \
		if (str[*index] == '\0') \
			error("Unexpected end of code."); \
	} \

#define slurpstr(dest) do { \
		lint len = 1; \
		dest = calloc(1, len); \
		bool inquotes = false; \
		if (str[*index] == '"') \
			inquotes = true; \
\
		while (inquotes || (!isspace(str[*index]) && (str[*index] != ')') && (str[*index] != '('))) { \
			if (!str[*index]) \
				error("Unexpected end of code"); \
\
			dest = realloc(dest, ++len); \
			dest[len-2] = str[(*index)++]; \
\
			if (inquotes && (str[*index] == '"')) { \
				dest = realloc(dest, ++len); \
				dest[len-2] = str[(*index)++]; \
				break; \
			} \
		} \
		dest[len-1] = '\0'; \
	} while (0)



	Ast tmp = {.isval = false, .numchilds = 0};

	munch_whitespace;

	if (str[*index] != '(')
		error("Expected (, but instead got %c, at index %zu!", str[*index], *index);

	(*index)++; // get past the (

	munch_whitespace;

	tmp.op = NULL;

	slurpstr(tmp.op);

	munch_whitespace;


precheck:
	if (str[*index] == ')') {
		(*index)++;
		return tmp;
	} else if (str[*index] == '(') {
		tmp.childs = realloc(tmp.childs, (++tmp.numchilds) * sizeof(Ast));
		tmp.childs[tmp.numchilds-1] = tokenize(str, index);
		goto precheck;
	} else {
		tmp.childs = realloc(tmp.childs, (++tmp.numchilds) * sizeof(Ast));
		tmp.childs[tmp.numchilds-1].isval = true;
		tmp.childs[tmp.numchilds-1].val.type = LTYPE_UNDECIDED;
		slurpstr(tmp.childs[tmp.numchilds-1].val.undecided);
		munch_whitespace;
		goto precheck;
	}

	return tmp;
}
