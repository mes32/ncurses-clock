# Makefile for ncurses-clock program

# --- Define compiler and compiler options ---
CC = gcc
CFLAGS = -std=c99 -g -Wall -O2
INCLUDES = -lncurses -lpthread


# --- List program modules and associated object files ---
MODULES_LIST = \
	main \
	blockString \
	clockWindow \
	dateTimeModel \
	scanAndConfig \

OBJECT_FILES = $(MODULES_LIST:%=obj/%.o)


# --- Define the build rules ---
all: bin/main

bin/main : $(OBJECT_FILES)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJECT_FILES) -o bin/main

obj/%.o: src/%.c
	$(CC) $(CFLAGS) $< -o $@ -c 

clean:
	rm -f bin/main $(OBJECT_FILES)