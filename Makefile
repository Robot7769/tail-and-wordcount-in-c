EXECUTABLE = tail wordcount wordcount-dynamic libhtab.a libhtab.so
CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra #-O2y #-m32
MODULES = htab_bucket_count.o htab_clear.o htab_erase.o htab_find.o htab_for_each.o htab_free.o htab_hash_function.o htab_init.o htab_lookup_add.o htab_resize.o htab_size.o

.PHONY: all zip clean

all: $(EXECUTABLE)
# souboty .o (závislosti)
error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c -o error.o

tail.o: tail.c error.h
	$(CC) $(CFLAGS) -c tail.c -o tail.o

htab_%.o: htab_%.c 
	$(CC) $(CFLAGS) -fPIC -c $^

io.o: io.c
	$(CC) $(CFLAGS) -c io.c -o io.o

libhtab.a: $(MODULES)
	ar -crs libhtab.a $^ error.o

libhtab.so: $(MODULES)
	$(CC) -fPIC -shared  $^ -o $@ 

wordcount.o: htab.h wordcount.c io.c
	$(CC) $(CFLAGS) -c wordcount.c io.c

#spustitelné binárky
tail: tail.o error.o 
	$(CC) tail.o error.o -o tail

wordcount++: wordcount-.cc
	g++ std=c++17 -pedantic -Wall-O2 -o $@ 

wordcount: wordcount.c  io.c libhtab.a  htab_struct.h htab.h error.h
	$(CC) -o $@  wordcount.c -L. -lhtab

wordcount-dynamic: wordcount.o libhtab.so  htab_struct.h htab.h error.h
	$(CC) -o $@ wordcount.o error.o -L. -lhtab

#pomocné příkazy
zip:
	zip xskrab12.zip *.c *.h *.cc Makefile


clean: 
	rm -f $(EXECUTABLE) *.o *.a *.so

