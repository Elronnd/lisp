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
		printf("%s", ast.val.undecided);
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


Lval callfunc(const char *name, Lval *in, size_t numasts) {
	for (size_t i = 0; i < sizeof(builtins); i++) {
		if (!strcmp(name, builtins[i].name)) {
			return builtins[i].func(in, numasts);
		}
	}
}

Lval parseast(Ast ast) {
	if (ast.isval) {
		return ast.val;
	} else {
		Lval *vals = malloc(sizeof(Lval) * ast.numchilds);

		for (size_t i = 0; i < ast.numchilds; i++) {
			vals[i] = parseast(ast.childs[i]);
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

		Lval t = parseast(a);

		printf("%lld\n", t.integer);

		printf("Ast: "); printast(a);

		free(buf);
	}

	return 0;
}
