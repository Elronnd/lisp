#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>  // malloc
#include <ctype.h>   // isspace
#include <editline/readline.h>

#include "build-lisp.h"

/*
 * (+ (* 5 7) 3)
 *
 * isval = false
 * op = '+'
 * childs = :
 *     { isval = true
 *       val = 3
 *     }
 *     { isval = false
 *       op = '*'
 *       childs = :
 *       { isval = true
 *         val = 5
 *       }
 *       { isval = true
 *         val = 7
 *       }
 *     }
 *
 *     To evaluate:
 *	 if isexpr:
 *	   map/reduce eval() of op on each child
 *	 else:
 *	   return val
 */


void printast(Ast ast) {
	if (ast.isval) {
		printf("%s", ast.val);
	} else {
		printf("(%s ", ast.op);
		for (size_t i = 0; i < ast.numchilds; i++) {
			printast(ast.childs[i]);

			// print a space in between most expressions, but not after
			// the last one -- it should butt up against the closing )
			if (i < ast.numchilds-1)
				putchar(' ');
		}

		putchar(')');
	}
}


long callfunc(const char *name, long *in, size_t numasts) {
	for (size_t i = 0; i < sizeof(builtins); i++) {
		if (!strcmp(name, builtins[i].name)) {
			return builtins[i].func(in, numasts);
		}
	}
}

/*
long parseast(Ast ast) {
	if (ast.isval) {
		return ast.val;
	} else {
		long *vals = malloc(sizeof(long) * ast.numchilds);
		long tmp;

		for (size_t i = 0; i < ast.numchilds; i++) {
			vals[i] = parseast(ast.childs[i]);
		}

		tmp = callfunc(ast.op, vals, ast.numchilds);

		return tmp;
	}
}
*/

Ast strtoast(char *str, size_t *index) {
#define munch_whitespace do { \
		while (isspace(str[*index]) && str[*index]) { \
			if (!str[*index]) \
				error("Unexpected end of code"); \
			(*index)++; \
		} \
	} while (0);

#define slurpstr(dest) do { \
		size_t len = 1; \
		dest = calloc(1, len); \
\
		while (!isspace(str[*index]) && (str[*index] != ')') && (str[*index] != '(') && str[*index]) { \
			if (!str[*index]) \
				error("Unexpected end of code"); \
\
			dest = realloc(dest, ++len); \
			dest[len-2] = str[(*index)++]; \
			dest[len-1] = 0; \
		} \
	} while (0);



	Ast tmp = {.isval = false, .numchilds = 0};
	size_t size = 0;

	munch_whitespace;

	if (str[*index] != '(')
		error("Expected (, but instead got %c, at index %zu!", str[*index], *index);

	(*index)++; // get past the (

	munch_whitespace;

	tmp.op = NULL;

	// slurp characters one at a time into op
	while (str[*index] != ')' && !isspace(str[*index])) {
		if (!str[*index])
			error("Unexpected end of code");

		tmp.op = realloc(tmp.op, ++size);
		strcat(tmp.op, (char[]){str[(*index)++], 0});
	}

	munch_whitespace;


precheck:
	if (str[*index] == ')') {
		return tmp;
	} else if (str[*index] == '(') {
		tmp.childs = realloc(tmp.childs, ++tmp.numchilds);
		tmp.childs[tmp.numchilds-1] = strtoast(str, index);
		goto precheck;
	} else {
		tmp.childs = realloc(tmp.childs, ++tmp.numchilds);
		tmp.childs[tmp.numchilds-1].isval = true;
		slurpstr(tmp.childs[tmp.numchilds-1].val);
		munch_whitespace;
		goto precheck;
	}

	return tmp;
}


int main(void) {
	size_t foo = 0;
	Ast a = strtoast("(foo bar baz)", &foo);
	printf("%s", a.childs[0].val);
}

/*
int main(void) {
	Ast ast;

	ast.isval = false;
	ast.op = "+";
	ast.childs = malloc(sizeof(ast) * 2);
	ast.numchilds = 2;

	ast.childs[0].isval = true;
	ast.childs[0].val = 3;

	ast.childs[1].isval = false;
	ast.childs[1].op = "*";
	ast.childs[1].childs = malloc(sizeof(ast) * 2);
	ast.childs[1].numchilds = 2;

	ast.childs[1].childs[0].isval = true;
	ast.childs[1].childs[0].val = 5;
	ast.childs[1].childs[1].isval = true;
	ast.childs[1].childs[1].val = 7;

	printf("Values is %ld\n", parseast(ast));

	printf("Formatted: ");
	printast(ast);
	putchar('\n');
}
*/

#if 0
int main(void) {
	bool done = false;
	char *buf;

	while (!done) {
		buf = readline("repl> ");

		if (buf == NULL) {
			putchar('\n');
			break;
		}

		add_history(buf);

		if (!strcmp(buf, "quit"))
			done = true;

		printf("You said %s!\n", buf);

		free(buf);
	}

	return 0;
}
#endif
