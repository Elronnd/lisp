#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
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


typedef struct Ast {
	bool isval;

	union {
		// c11 ftw!
		struct {
			struct Ast *childs;
			size_t numchilds;
		};

		long val;
	};


	char op;
} Ast;

void printast(Ast ast) {

	if (ast.isval) {
		printf("%ld", ast.val);
	} else {
		printf("(%c ", ast.op);
		for (size_t i = 0; i < ast.numchilds; i++) {
			printast(ast.childs[i]);
			if (i < ast.numchilds-1)
				putchar(' ');
		}

		putchar(')');
	}
}



long parseast(Ast ast) {
	if (ast.isval) {
		return ast.val;
	} else {
		long *vals = malloc(sizeof(long) * ast.numchilds);
		long tmp;

		for (size_t i = 0; i < ast.numchilds; i++) {
			vals[i] = parseast(ast.childs[i]);
		}

		switch (ast.op) {
			case '+': tmp = vals[0] + vals[1]; break;
			case '-': tmp = vals[0] - vals[1]; break;
			case '*': tmp = vals[0] * vals[1]; break;
			case '/': tmp = vals[0] / vals[1]; break;
			default: printf("Unknown operation %c!!", ast.op); tmp = -1;
		}

		return tmp;
	}
}

int main(void) {
	Ast ast;

	ast.isval = false;
	ast.op = '+';
	ast.childs = malloc(sizeof(ast) * 2);
	ast.numchilds = 2;

	ast.childs[0].isval = true;
	ast.childs[0].val = 3;

	ast.childs[1].isval = false;
	ast.childs[1].op = '*';
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
