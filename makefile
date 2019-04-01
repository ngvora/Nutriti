all: a.out

a.out:
	gcc -Wall string.c dynamic.c UNORDEREDSET.c UNORDEREDMAP.c main.c ROW.c INTEGER.c

clean:
	rm a.out
