CFLAGS = -fpic -coverage -lm -Wall

all:
	gcc -o quiz testme.c $(CFLAGS)
	-./quiz
	gcov testme.c
	
clean:
	-rm -f *.gcno *gcda quiz *.gcov
	-rm -rf *.dSYM
