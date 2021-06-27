CC = gcc
CCFLAGS = -Wall -Wextra -pedantic
#include += lib/my_debug.h 
include += lib/my_string.h 

all: ccheck

debug: CCFLAGS += -DDEBUG -g
debug: ccheck_debug

ccheck: lexer.o token.o
	$(CC) $(CCFLAGS) src/main.c -o build/ccheck build/lexer.o build/token.o

lexer.o: src/lexer.c
	$(CC) $(CCFLAGS) -c src/lexer.c -o build/lexer.o

token.o: src/token.c
	$(CC) $(CCFLAGS) -c src/token.c -o build/token.o

ccheck_debug: lexer.o token.o my_debug.o
	$(CC) $(CCFLAGS) src/main.c -o build/ccheck build/lexer.o build/token.o build/my_debug.o

my_debug.o: lib/my_debug.c
	$(CC) $(CCFLAGS) -c lib/my_debug.c -o build/my_debug.o

clean: 
	rm -rf build/*
