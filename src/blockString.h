/**
 *  asciiArtString.h - ncurses-clock
 *
 *  This module creates and manages strings of ASCII art block letters
 *
 */

#ifndef BLOCK_STRING_H
#define BLOCK_STRING_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef char Glyph[7][6];

typedef struct BlockLetter_def {
	int height;
	int width;
	Glyph *glyph;
	struct BlockLetter_def *next;
} BlockLetter;

typedef struct {
	int height;
	int width;
	BlockLetter *strHead;
} BlockString;

BlockLetter *initBlockLetter(char inputLetter);

BlockString *initBlockString(char *inputString);


#endif