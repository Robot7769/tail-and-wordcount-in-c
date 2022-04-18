EXECUTABLE = tail wordcount #wordcount-dynamic libhtab.a libhtab.so
CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra #-O2y #-m32
#CPPFLAGS = -std=c++17 -pedantic -Wall	#CC = g++ 
MODULES = htab_bucket_count.o htab_clear.o htab_erase.o htab_find.o htab_for_each.o htab_free.o htab_hash_function.o htab_init.o htab_lookup_add.o htab_resize.o htab_size.o
LIBS = htab_struct.h 
#LDLIBS = -lm #-m32

.PHONY: all zip clean

all: $(EXECUTABLE)
# souboty .o (závislosti)
error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c -o error.o

tail.o: tail.c error.h
	$(CC) $(CFLAGS) -c tail.c -o tail.o

#$(MODULES).o: $(MODULES).c
#	$(CC) $(CFLAGS) -c $(MODULES).c -o $(MODULES).o

htab_%.o: htab_%.c 
	$(CC) $(CFLAGS) -c $^

io.o: io.c
	$(CC) $(CFLAGS) -c io.c -o io.o

libhtab.a: $(MODULES)
	ar -crs libhtab.a $^ error.o

#libhtab.so: $(MODULES:.o=.pic.o)
#	$(CC) -shared -fPIC $(L)
#
#libhtab.so: wordcount.c htab.h io.c
#	$(CC) $(CFLAGS) -c wordcount.c -so libhtab.so
#
wordcount.o: htab.h wordcount.c io.c
	$(CC) $(CFLAGS) -c wordcount.c io.c
#
#wordcount-dynamic.o: wordcount.c htab.h io.c
#	$(CC) $(CFLAGS) -c wordcount.c -o wordcount-dynamic.o
#


#spustitelné binárky
tail: tail.o error.o 
	$(CC) tail.o error.o $(LDLIBS) -o tail

#wordcount: wordcount.o libhtab.a
#	$(CC) wordcount.o libhtab.a error.o -o wordcount
wordcount: wordcount.o  io.o libhtab.a  htab_struct.h htab.h
	$(CC) $(CFLAGS) -static -o $@ wordcount.o libhtab.a
#	$(CC) wordcount.o libhtab.a -o wordcount



#pomocné příkazy
zip:
	zip xskrab12.zip *.c *.h *.cc Makefile


clean: 
	rm -f $(EXECUTABLE) *.o *.a *.so

