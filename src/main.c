#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

char *getl(void) {
	size_t tmplen = 0, jumpsize = 2048;
	char *tmp = calloc(sizeof(char), jumpsize);
	char c;

	while ((c = getchar()) != '\n') {
		if (++tmplen > jumpsize) {
			tmp = realloc(tmp, jumpsize*2);
			jumpsize *= 2;
		}

		tmp[tmplen-1] = c;
	}

	tmp = realloc(tmp, tmplen+1);

	tmp[tmplen] = 0;

	return tmp;
}



int main(void) {
	bool done = false;
	char *buf;

	while (!done) {
		printf("repl> ");

		buf = getl();

		if (!strcmp(buf, "quit"))
			done = true;

		printf("You said %s!\n", buf);

		free(buf);
	}

	return 0;
}
