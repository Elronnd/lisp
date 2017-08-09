CC = clang

CFLAGS-base = -Iinclude -I../include -Wall -Wextra -pedantic -std=c11

CFLAGS-debug = -ggdb -O0 -g3
CFLAGS-normal = -g -O2
CFLAGS-release = -g0 -O3

CFLAGS = $(CFLAGS-base) $(CFLAGS-debug)
LDFLAGS = -ledit -lm


OBJ = src/main.o src/util.o src/token.o src/parse.o src/builtins/builtinarith.o src/builtins/builtincmp.o src/builtins/builtin.o

default: $(OBJ)
	$(CC) $(LDFLAGS) -o lisp $(OBJ)

clean:
	rm src/*.o src/builtins/*.o lisp
