#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

void error(const char *file, size_t line, const char *fmt, ...) {
	fprintf(stderr, "ERROR! %s:%zu: ", file, line);

	va_list args;
	va_start(args, fmt);

	vfprintf(stderr, fmt, args);

	fputc('\n', stderr);

	va_end(args);

	exit(1);
}
