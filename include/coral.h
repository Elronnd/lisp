// vim: ft=c
#include <stdbool.h>
#include <stdint.h>


#ifndef CORAL_H
#define CORAL_H

#define SIZE(x)	(lint)(sizeof(x) / sizeof(x[0]))


typedef enum {
	LTYPE_UNDECIDED = 1, // char*.  Currently unused but maybe later
	LTYPE_INT,      // long long
	LTYPE_FLOAT,    // long double
	LTYPE_STR,      // char*
	LTYPE_BOOL,     // bool
	LTYPE_RAW,      // void*
	LTYPE_VARIABLE, // char*
	LTYPE_AST,      // Ast
	LTYPE_VOID,     // none
	LTYPE_ANY,      // none
} Ltype;

typedef struct Ast Ast;

typedef int64_t lint;
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

typedef struct Token_tree Token_tree;
typedef struct {
	Token_tree *tree;
	char *str;
	bool istree;
} Token;

struct Token_tree {
	Token first;

	lint numargs;

	Token *args; // can be NULL if numargs == 0
};


struct Ast {
	bool isval;

	char *op;
	lint numchilds;
	struct Ast *childs;

	Lval val;
};

typedef struct {
	const char *name;
	Lval (*func)(Lval *vals, lint numvals);
	lint minargs, maxargs;
	Ltype validtypes[4];
	bool ispure;
} function;




extern Lval runast(Ast ast, bool runtime);
extern void printast(Ast ast);


// builtins.c
extern Lval builtin_intadd(Lval *vals, lint numvals);
extern Lval builtin_floatadd(Lval *vals, lint numvals);

extern Lval builtin_intsub(Lval *vals, lint numvals);
extern Lval builtin_floatsub(Lval *vals, lint numvals);

extern Lval builtin_intmul(Lval *vals, lint numvals);
extern Lval builtin_floatmul(Lval *vals, lint numvals);


extern Lval builtin_intdiv(Lval *vals, lint numvals);
extern Lval builtin_floatdiv(Lval *vals, lint numvals);

extern Lval builtin_strcat(Lval *vals, lint numvals);

extern Lval builtin_intcmp(Lval *vals, lint numvals);
extern Lval builtin_floatcmp(Lval *vals, lint numvals);
extern Lval builtin_boolcmp(Lval *vals, lint numvals);
extern Lval builtin_strcmp(Lval *vals, lint numvals);

extern Lval builtin_if(Lval *vals, lint numvals);

extern Lval builtin_intsqrt(Lval *vals, lint numvals);
extern Lval builtin_floatsqrt(Lval *vals, lint numvals);

extern Lval builtin_intlt(Lval *vals, lint numvals);
extern Lval builtin_floatlt(Lval *vals, lint numvals);
extern Lval builtin_intgt(Lval *vals, lint numvals);
extern Lval builtin_floatgt(Lval *vals, lint numvals);

extern Lval builtin_readchar(Lval *vals, lint numvals);

static function builtins[] = {
        {"+", builtin_intadd, .minargs = 1, .maxargs = -1, {LTYPE_INT}, true},
        {"+", builtin_floatadd, .minargs = 1, .maxargs = -1, {LTYPE_FLOAT, LTYPE_INT}, true},

        {"-", builtin_intsub, .minargs = 1, .maxargs = -1, {LTYPE_INT}, true},
        {"-", builtin_floatsub, .minargs = 1, .maxargs = -1, {LTYPE_FLOAT, LTYPE_INT}, true},

        {"*", builtin_intmul, .minargs = 2, .maxargs = -1, {LTYPE_INT}, true},
        {"*", builtin_floatmul, .minargs = 2, .maxargs = -1, {LTYPE_FLOAT, LTYPE_INT}, true},

        {"/", builtin_intdiv, .minargs = 2, .maxargs = -1, {LTYPE_INT}, true},
        {"/", builtin_floatdiv, .minargs = 2, .maxargs = -1, {LTYPE_FLOAT, LTYPE_INT}, true},

	{"~", builtin_strcat, .minargs = 1, .maxargs = -1, {LTYPE_STR}, true},

	{"=", builtin_intcmp, .minargs = 2, .maxargs = -1, {LTYPE_INT}, true},
	{"=", builtin_floatcmp, .minargs = 2, .maxargs = -1, {LTYPE_FLOAT, LTYPE_INT}, true},
	{"=", builtin_boolcmp, .minargs = 2, .maxargs = -1, {LTYPE_BOOL}, true},
	{"=", builtin_strcmp, .minargs = 2, .maxargs = -1, {LTYPE_STR}, true},

	{"if", builtin_if, .minargs = 2, .maxargs = 3, {LTYPE_ANY}, true},

	{"sqrt", builtin_intsqrt, .minargs = 1, .maxargs = 1, {LTYPE_INT}, true},
	{"sqrt", builtin_floatsqrt, .minargs = 1, .maxargs = 1, {LTYPE_FLOAT}, true},

	{"<", builtin_intlt, .minargs = 2, .maxargs = -1, {LTYPE_INT}, true},
	{"<", builtin_floatlt, .minargs = 2, .maxargs = -1, {LTYPE_INT, LTYPE_FLOAT}, true},
	{">", builtin_intgt, .minargs = 2, .maxargs = -1, {LTYPE_INT}, true},
	{">", builtin_floatgt, .minargs = 2, .maxargs = -1, {LTYPE_INT, LTYPE_FLOAT}, true},

	{"readchar", builtin_readchar, .minargs = 0, .maxargs = 0, {0}, false},
};


// token.c
Token_tree tokenize(const char *str, lint *index);

// parse.c
void valtostr(Lval val, char bufout[2048]);
Ast parseast(Token_tree *t);


_Noreturn extern void _error(const char *file, lint line, const char *fmt, ...);
#define error(...) _error(__FILE__, __LINE__, __VA_ARGS__)

#endif // CORAL_H
