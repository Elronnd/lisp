// vim: ft=c
#include <stdbool.h>

typedef struct Ast {
	bool isval;

	union {
		// c11 ftw!
		struct {
			struct Ast *childs;
			size_t numchilds;
		};

		char *val;
	};


	char *op;
} Ast;

typedef struct {
	const char *name;
	long (*func)(long *asts, size_t numasts);
} function;


extern long parseast(Ast ast);
extern void printast(Ast ast);

extern long builtin_add(long *asts, size_t numasts);
extern long builtin_sub(long *asts, size_t numasts);
extern long builtin_mul(long *asts, size_t numasts);
extern long builtin_div(long *asts, size_t numasts);

static function builtins[] = {
        {"+", builtin_add},
        {"-", builtin_sub},
        {"*", builtin_mul},
        {"/", builtin_div}
};


extern void error(const char *file, size_t line, const char *fmt, ...);
#define error(...) error(__FILE__, __LINE__, __VA_ARGS__)
