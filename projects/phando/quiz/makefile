CFLAGS = -fpic -coverage -lm -Wall

all:
	gcc -o quiz testme.c $(CFLAGS)

test:
	gcov testme.c
	
clean:
	-rm -f *.gcno *gcda quiz *.gcov
	-rm -rf *.dSYM