#include "coral.h"

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
