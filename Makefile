all: test-lab

test-lab: labyrinthe.o test.c
	gcc -Wall -o test-lab labyrinthe.o test.c

labyrinthe.o: labyrinthe.c
	gcc -c -Wall -o labyrinthe.o labyrinthe.c

clean :
	rm labyrinthe.o test-lab
