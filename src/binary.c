#include "binary.h"

#include <stdlib.h>
#include <string.h>

#define has_real ((sizeof(long double)) == sizeof(double))

#define push(val) do { \
	ret = realloc(ret, ++(*len)); \
	ret[(*len)-1] = val; \
} while (0)

#define pusharr(arr, num) do { \
	for (int _i = 0; _i < num; _i++) { \
		push(arr[_i]); \
	} \
} while (0)

#define push_longint(val, type) do { \
	union { \
		uint8_t arr[sizeof(type)]; \
		type value; \
	} _value; \
	_value.value = val; \
	pusharr(_value.arr, sizeof(type)); \
} while (0)


static void serialize_ast(uint8_t *ret, lint *len, Ast ast);


static void serialize_lval(uint8_t *ret, lint *len, Lval val) {
	push(0x03); // value initializer
	push(val.type);
	switch (val.type) {
		case LTYPE_UNDECIDED: error("Tried to serialize an value of undecided type!"); break;
		case LTYPE_INT: push_longint(val.integer, lint); break;
		case LTYPE_FLOAT:
			if (has_real) {
				push_longint(val.lfloat, real);
				// push a 64-bit integer, for compatability
				push_longint((double)val.lfloat, double);
			} else {
				push_longint(val.lfloat, real);
			}
			break;
		case LTYPE_STR:
			push_longint((lint)strlen(val.str), lint);
			pusharr(val.str, strlen(val.str));
			break;
		case LTYPE_BOOL: push(val.boolean); break;
		case LTYPE_RAW: error("Tried to serialize a value of type raw!"); break;
		case LTYPE_VARIABLE: error("Tried to serialize a variable!"); break;
		case LTYPE_AST: serialize_ast(ret, len, *(val.ast)); break;
		case LTYPE_VOID: break; // so the compiler doesn't complain
	}
	push(0x04); // value terminator
}

static void serialize_ast(uint8_t *ret, lint *len, Ast ast) {
	push(0x01);

	if (ast.isval) {
		push(0x01); // This ast is a value
		serialize_lval(ret, len, ast.val);
	} else {
		push(0x0); // This ast is an expression

		// push the operator
		push_longint((lint)strlen(ast.op), lint);
		pusharr(ast.op, strlen(ast.op));

		// number of arguments
		push_longint(ast.numchilds, lint);

		// push the arguments
		for (lint i = 0; i < ast.numchilds; i++) {
			serialize_ast(ret, len, ast.childs[i]);
		}
	}

	push(0x02);
}



uint8_t *binary_serialize(Ast ast, lint *len) {
	*len = 0;
	uint8_t *ret;


	lint magic = 0xdecaffad;
	push_longint(magic, lint);

	push(0x0); push(0x0); // version 0.0

	push(!has_real);

	serialize_ast(ret, len, ast);

	lint endmagic = 0xdefeca7e;
	push_longint(endmagic, lint);

