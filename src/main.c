#include "coral.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>  // malloc&friends
#include <editline/readline.h>


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
		char buf[2048];
		valtostr(ast.val, buf);
		printf("%s", buf);
	} else {
		printf("(%s ", ast.op);
		for (lint i = 0; i < ast.numchilds; i++) {
			printast(ast.childs[i]);

			// print a space in between most expressions, but not after
			// the last one -- it should butt up against the closing )
			if (i < ast.numchilds-1)
				putchar(' ');
		}

		putchar(')');
	}
}

static bool isin(int needle, int *haystack, int numstack) {
	for (int i = 0; i < numstack; i++) {
		if (needle == haystack[i])
			return true;
	}

	return false;
}


Lval callfunc(char *name, Lval *in, lint numasts, bool runtime) {
	lint i, j;

	for (i = 0; i < SIZE(builtins); i++) {
		if (!strcmp(name, builtins[i].name)) {
			for (j = 0; j < numasts; j++) {
				if (!isin(in[j].type, (int*)builtins[i].validtypes, SIZE(builtins[i].validtypes)) &&
				    !isin(LTYPE_ANY, (int*)builtins[i].validtypes, SIZE(builtins[i].validtypes)))
					goto continueout;
			}

			if (((numasts < builtins[i].minargs) && (builtins[i].minargs != -1)) ||
			    ((numasts > builtins[i].maxargs) && (builtins[i].maxargs != -1))) {
				goto wrongargs;
			}


			if (runtime || builtins[i].ispure) {
				return builtins[i].func(in, numasts);
			} else {
				Lval ret = {.type = LTYPE_AST};

				Ast ast = {.isval = false, .op = name, .numchilds = numasts, .childs = malloc(sizeof(Ast) * numasts)};

				for (lint i = 0; i < numasts; i++) {
					ast.childs[i].isval = true;
					ast.childs[i].val = in[i];
				}

				ret.ast = &ast;

				return ret;
			}

continueout:
			continue;
		}
	}

	error("Unknown function %s", name);

wrongargs:
	error("Got %d args when the expected range was %d to %d", numasts, builtins[i].minargs, builtins[i].maxargs);
}


Lval runast(Ast ast, bool runtime) {
	if (ast.isval) {
		return ast.val;
	} else {
		Lval *vals = malloc(sizeof(Lval) * ast.numchilds);

		for (lint i = 0; i < ast.numchilds; i++) {
			vals[i] = runast(ast.childs[i], runtime);
		}

		return callfunc(ast.op, vals, ast.numchilds, runtime);
	}
}




int main(void) {
	char *buf;
	lint foo = 0;

	while (true) {
		buf = readline("repl> ");

		if (buf == NULL) {
			putchar('\n');
			break;
		}

		add_history(buf);

		if (!strcmp(buf, "quit"))
			break;

		foo = 0;
		Ast a = tokenize(buf, &foo);

		parseast(&a);

		printf("Ast: "); printast(a); putchar('\n');

		Lval t = runast(a, false);

		char foo[2048];
		valtostr(t, foo);
		printf("%s\n", foo);


		free(buf);
	}

	return 0;
}
