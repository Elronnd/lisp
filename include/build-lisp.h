// vim: ft=c
#include <stdbool.h>
#include <stddef.h>  // size_t


#ifndef BUILDLISP_H
#define BUILDLISP_H

#define SIZE(x)	(sizeof(x) / sizeof(x[0]))


typedef enum {
	LTYPE_UNDECIDED = 1, // char*.  We have lazy parsing, which can be good, or bad, just like python.
			// Good for performance, but bad if something like this happens: (if true (+ 5 7) (- 5 "asdf")).  That's not an error
	LTYPE_INT,   // long long
	LTYPE_FLOAT, // long double
	LTYPE_STR,   // char*
	LTYPE_BOOL,  // bool
	LTYPE_RAW,   // void*
	LTYPE_VARIABLE, // char*
	LTYPE_AST    // Ast
} Ltype;

typedef struct Ast Ast;

typedef signed long long lint;
typedef long double real;

typedef struct {
	Ltype type;

	lint integer;
	real lfloat;
	char *str;
	bool boolean;
	void *raw;
	char *undecided;
	char *varname;
	Ast *ast;
} Lval;


struct Ast {
	bool isval;

	struct Ast *childs;
	size_t numchilds;

	Lval val;

	char *op;
};

typedef struct {
	const char *name;
	Lval (*func)(Lval *vals, size_t numvals);
	Ltype validtypes[2];
} function;




extern Lval runast(Ast ast);
extern void printast(Ast ast);


// builtins.c
extern Lval builtin_add(Lval *vals, size_t numvals);
extern Lval builtin_sub(Lval *vals, size_t numvals);
extern Lval builtin_mul(Lval *vals, size_t numvals);
extern Lval builtin_div(Lval *vals, size_t numvals);
extern Lval builtin_concat(Lval *vals, size_t numvals);
extern Lval builtin_cmp(Lval *vals, size_t numvals);

static function builtins[] = {
        {"+", builtin_add, {LTYPE_INT, LTYPE_FLOAT}},
        {"-", builtin_sub, {LTYPE_INT, LTYPE_FLOAT}},
        {"*", builtin_mul, {LTYPE_INT, LTYPE_FLOAT}},
        {"/", builtin_div, {LTYPE_INT, LTYPE_FLOAT}},
	{"~", builtin_concat, {LTYPE_STR}},
};


// token.c
Ast tokenize(const char *str, size_t *index);

// parse.c
void valtostr(Lval val, char bufout[2048]);
void parseast(Ast *ast);


_Noreturn extern void _error(const char *file, size_t line, const char *fmt, ...);
#define error(...) _error(__FILE__, __LINE__, __VA_ARGS__)

#endif
