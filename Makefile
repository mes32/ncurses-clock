# Makefile for ncurses-clock program

# Define compiler and compiler flags
CC = gcc
CFLAGS = -std=c99 -g -Wall
INCLUDES =

TARGETS = bin/main.o

all: $(TARGETS)

bin/%.o: src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $<

clean:
	rm -f $(TARGETS)