#include <stddef.h>

#include "build-lisp.h"

long builtin_add(long *asts, size_t numasts) {
	long out = 0;

	for (size_t i = 0; i < numasts; i++) {
		out += asts[i];
	}

	return out;
}


long builtin_sub(long *asts, size_t numasts) {
	long out = 0;

	for (size_t i = 0; i < numasts; i++) {
		out -= asts[i];
	}

	return out;
}


long builtin_mul(long *asts, size_t numasts) {
	long out = 1;

	for (size_t i = 0; i < numasts; i++) {
		out *= asts[i];
	}

	return out;
}


long builtin_div(long *asts, size_t numasts) {
	long out = 1;

	for (size_t i = 0; i < numasts; i++) {
		out /= asts[i];
	}

	return out;
}
