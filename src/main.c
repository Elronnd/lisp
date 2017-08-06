#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <editline/readline.h>


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
