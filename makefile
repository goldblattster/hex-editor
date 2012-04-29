all:
	gcc -c main.h main.c
	gcc -o ghe main.o -lncurses
