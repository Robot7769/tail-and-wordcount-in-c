CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra -O2 #-m32
LDLIBS = -lm #-m32

.PHONY: all zip clean

all: tail #wordcount wordcount-dynamic libhtab.a libhtab.so
# souboty .o (závislosti)
error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c -o error.o

tail.o: tail.c error.h
	$(CC) $(CFLAGS) -c tail.c -o tail.o

#libhtab.a: htab.c htab.h io.c
#	$(CC) $(CFLAGS) -c htab.c -a libhtab.a
#
#libhtab.so: wordcount.c htab.h io.c
#	$(CC) $(CFLAGS) -c wordcount.c -so libhtab.so
#
#wordcount.o: wordcount.c htab.h io.c
#	$(CC) $(CFLAGS) -c wordcount.c -o wordcount.o
#
#wordcount-dynamic.o: wordcount.c htab.h io.c
#	$(CC) $(CFLAGS) -c wordcount.c -o wordcount-dynamic.o
#


#spustitelné binárky
tail: tail.o error.o 
	$(CC) tail.o error.o $(LDLIBS) -o tail

#primes-i: primes-i.o error.o bitset-i.o eratosthenes-i.o 
#	$(CC) primes-i.o error.o bitset-i.o eratosthenes-i.o $(CFLAGS) -o primes-i
#
#steg-decode: steg-decode.o error.o bitset.o eratosthenes.o ppm.o
#	$(CC) steg-decode.o error.o bitset.o eratosthenes.o ppm.o $(CFLAGS) -o steg-decode
#
#steg-encode: steg-encode.o error.o bitset.o eratosthenes.o ppm.o
#	$(CC) steg-encode.o error.o bitset.o eratosthenes.o ppm.o $(CFLAGS) -o steg-encode 


#pomocné příkazy
zip:
	zip xskrab12.zip *.c *.h *.cc Makefile


clean: 
	rm -f *.o 

