CC = gcc
WARNINGS = -Wextra -Wall

ifeq ($(CFG), release)
DEBUG =
OPTIMIZE = -O2
else
DEBUG = -g
OPTIMIZE =
endif

FLAGS = $(WARNINGS) $(DEBUG) $(OPTIMIZE)

CFLAGS = $(FLAGS)

sudoku: main.o sudoku.o
	$(CC) $^ -o $@ $(FLAGS)

main.o sudoku.o: sudoku.h

.PHONY: clean
clean:
	$(RM) *.o sudoku
