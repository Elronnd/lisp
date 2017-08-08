CC = clang

CFLAGS-base = -Iinclude -Wall -Wextra -pedantic -std=c11

CFLAGS-debug = -ggdb -O0 -g3
CFLAGS-normal = -g -O2
CFLAGS-release = -g0 -O3

CFLAGS = $(CFLAGS-base) $(CFLAGS-debug)
LDFLAGS = -ledit


OBJ = src/main.o src/builtin.o src/util.o src/token.o src/parse.o

default: $(OBJ)
	$(CC) $(LDFLAGS) -o lisp $(OBJ)

clean:
	rm src/*.o lisp
