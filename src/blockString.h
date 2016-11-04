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


static const size_t LETTER_HEIGHT = 7;
static const size_t LETTER_WIDTH  = 7;
static const size_t INTER_LETTER_SPACE = 1;

typedef char GlyphMatrix[7][7];

typedef struct BlockLetter_def {
	size_t height;
	size_t width;
	GlyphMatrix *glyph;
	struct BlockLetter_def *next;
} BlockLetter;

typedef struct {
	size_t height;
	size_t width;
	BlockLetter *head;
} BlockString;

/**
 * Initializes a BlockLetter struct that includes an ASCII art glyph representation of the input char.
 * A string of BlockLetters can be formed by linking as linked list.
 */
BlockLetter *initBlockLetter(char inputLetter, BlockLetter *next);

/**
 * Delete a BlockLetter and free the associated memory
 */

void deleteBlockLetter(BlockLetter **letterRef);

/**
 * Initialize a BlockString struct. Produces a linked list of BlockLetters based on the input string.
 */
BlockString *initBlockString(char *inputString);

/**
 * Delete a BlockString and free the associated memory
 */
void deleteBlockString(BlockString **stringRef);


#endif