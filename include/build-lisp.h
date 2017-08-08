// vim: ft=c
#include <stdbool.h>


#ifndef BUILDLISP_H
#define BUILDLISP_H

#define SIZE(x)	(lint)(sizeof(x) / sizeof(x[0]))


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
	lint numchilds;

	Lval val;

	char *op;
};

typedef struct {
	const char *name;
	Lval (*func)(Lval *vals, lint numvals);
	lint minargs, maxargs;
	Ltype validtypes[4];
} function;




extern Lval runast(Ast ast);
extern void printast(Ast ast);


// builtins.c
extern Lval builtin_add(Lval *vals, lint numvals);
extern Lval builtin_sub(Lval *vals, lint numvals);
extern Lval builtin_mul(Lval *vals, lint numvals);
extern Lval builtin_div(Lval *vals, lint numvals);
extern Lval builtin_concat(Lval *vals, lint numvals);
extern Lval builtin_cmp(Lval *vals, lint numvals);

static function builtins[] = {
        {"+", builtin_add, .minargs = 1, .maxargs = -1, {LTYPE_INT, LTYPE_FLOAT}},
        {"-", builtin_sub, .minargs = 1, .maxargs = -1, {LTYPE_INT, LTYPE_FLOAT}},
        {"*", builtin_mul, .minargs = 2, .maxargs = -1, {LTYPE_INT, LTYPE_FLOAT}},
        {"/", builtin_div, .minargs = 2, .maxargs = -1, {LTYPE_INT, LTYPE_FLOAT}},
	{"~", builtin_concat, .minargs = 1, .maxargs = -1, {LTYPE_STR}},
//	{"=", builtin_cmp, .minargs = 2, .maxargs = -1, {LTYPE_INT, LTYPE_FLOAT, LTYPE_BOOL, LTYPE_STR}}
};


// token.c
Ast tokenize(const char *str, lint *index);

// parse.c
void valtostr(Lval val, char bufout[2048]);
void parseast(Ast *ast);


_Noreturn extern void _error(const char *file, lint line, const char *fmt, ...);
#define error(...) _error(__FILE__, __LINE__, __VA_ARGS__)

#endif
