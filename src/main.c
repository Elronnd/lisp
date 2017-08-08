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




int main(void) {
	size_t foo = 0;
	char *buf;

	while (true) {
		buf = readline("repl> ");

		if (buf == NULL) {
			putchar('\n');
			break;
		}

		add_history(buf);

		if (!strcmp(buf, "quit"))
			break;

		printast(tokenize(buf, &foo));
		putchar('\n');

		free(buf);
	}

	return 0;
}
