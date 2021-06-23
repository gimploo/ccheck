CC = gcc
CCFLAGS = -Wall -Wextra -pedantic

all: ccheck

debug: CCFLAGS += -DDEBUG -g
debug: ccheck

ccheck: main.c
	$(CC) $(CCFLAGS) main.c -o ../build/ccheck

clean: 
	rm -rf ../build/*
