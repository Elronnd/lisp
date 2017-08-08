#include "build-lisp.h"

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
		printf(buf);
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

static bool isin(int needle, int *haystack, int numstack) {
	for (int i = 0; i < numstack; i++) {
		if (needle == haystack[i])
			return true;
	}

	return false;
}


Lval callfunc(const char *name, Lval *in, size_t numasts) {
	size_t j;

	for (size_t i = 0; i < sizeof(builtins); i++) {
		if (!strcmp(name, builtins[i].name)) {
			for (j = 0; j < numasts; j++) {
				if (!isin(in[j].type, builtins[i].validtypes, SIZE(builtins[i].validtypes))) {
					goto postfor;
				}
			}

			return builtins[i].func(in, numasts);
		}

		continue;
postfor:
		error("Unexpected type %d, for function %s.", in[j].type, name);
	}
}


Lval runast(Ast ast) {
	if (ast.isval) {
		return ast.val;
	} else {
		Lval *vals = malloc(sizeof(Lval) * ast.numchilds);

		for (size_t i = 0; i < ast.numchilds; i++) {
			vals[i] = runast(ast.childs[i]);
		}

		return callfunc(ast.op, vals, ast.numchilds);
	}
}




int main(void) {
	char *buf;
	size_t foo = 0;

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

		Lval t = runast(a);

		char foo[2048];
		valtostr(t, foo);
		printf("%s\n", foo);


		free(buf);
	}

	return 0;
}
