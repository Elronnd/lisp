#include "coral.h"

#include <stdlib.h>
#include <ctype.h>


Token_tree tokenize(const char *str, lint *index) {
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
			if ((str[*index] == '\\') && (str[(*index) + 1] == '"')) \
				(*index)++; \
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



	Token_tree ret = {.numargs = 0};

	munch_whitespace;

	if (str[*index] != '(')
		error("Expected (, but instead got %c, at index %zu!", str[*index], *index);

	(*index)++; // get past the (

	munch_whitespace;

	if (str[*index] == '(') {
		ret.first.istree = true;
		*(ret.first.tree) = tokenize(str, index);
	} else {
		ret.first.istree = false;
		slurpstr(ret.first.str);
	}

	munch_whitespace;


precheck:
	if (str[*index] == ')') {
		(*index)++;
		munch_whitespace;
		return ret;
	} else if (str[*index] == '(') {
		ret.args = realloc(ret.args, (++ret.numargs) * sizeof(Token));

		ret.args[ret.numargs-1].istree = true;
		*(ret.args[ret.numargs-1].tree) = tokenize(str, index);
		goto precheck;
	} else {
		ret.args = realloc(ret.args, (++ret.numargs) * sizeof(Token));
		ret.args[ret.numargs-1].istree = false;
		slurpstr(ret.args[ret.numargs-1].str);
		munch_whitespace;
		goto precheck;
	}

	return ret;
}
