CC = clang
LD ?= $(CC)

CFLAGS-base = -I../include -ledit -Wall -Wextra -pedantic -std=c11

CFLAGS-debug = -ggdb -O0 -g3
CFLAGS-normal = -g -O2
CFLAGS-release = -g0 -O3

CFLAGS = $(CFLAGS-base) $(CFLAGS-debug)


SRC = main.c builtin.c util.c
OBJ = src/main.o src/builtin.o src/util.o

default:
	cd src; $(CC) $(CFLAGS) -c $(SRC)
	$(CC) -o lisp $(OBJ)

clean:
	rm src/*.o lisp
