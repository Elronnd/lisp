CC = clang
LD ?= $(CC)

CFLAGS-base = -I../include -ledit -Wall -Wextra -pedantic

CFLAGS-debug = -ggdb -Og -g3
CFLAGS-normal = -g -O2
CFLAGS-release = -g0 -O3

CFLAGS = $(CFLAGS-base) $(CFLAGS-debug)


SRC = main.c builtin.c
OBJ = src/main.o src/builtin.o

default:
	cd src; $(CC) $(CFLAGS) -c $(SRC)
	$(CC) -o lisp $(OBJ)
