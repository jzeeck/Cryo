# the compiler to use.
CC=gcc

#Linker flags.
LFLAGS=

#Compile flags.
CFLAGS=-c -Wall

#exec file name
EXECUTABLE=cryo

#Different filecategories
MAIN=cryo.c
#Symetric cryptos
SYCRYPTO=rc.c
#Asymetric cryptos
ASCRYPTO=
#Key generator
GENERATOR=
#Util file
UTIL=util.c



compile: cryo.o rc.o keygen.o
	$(CC) cryo.o rc.o util.o keygen.o lib/simplerandom.o -o cryo



all: $(MAIN) $(SYCRYPTO) $(EXECUTABLE)

$(EXECUTABLE): 
	$(CC) $(LFLAGS) $(MAIN) -o $@

keygen.o: keygen.c
	$(CC) $(CFLAGS) keygen.c

util.o: util.c
	$(CC) $(CFLAGS) util.c

cryo.o: cryo.c
	$(CC) $(CFLAGS) cryo.c

rc.o: rc.c util.o
	$(CC) $(CFLAGS) rc.c

run: compile
	./cryo plaintext

clean:
	rm cryo *.o

keygen:
	$(CC) $(CFLAGS) keygen.c


generate:
	./cryo -G
