/**
 *  asciiArtString.c - ncurses-clock
 *
 *  This module creates and manages strings of ASCII art block letters
 *
 */

#include "blockString.h"


static GlyphMatrix BLOCK_LETTER_A =
{
    "  Xx  ",
    " x  x ",
    ".X  x.",
    "xXxxXX",
    "X    x",
    "x    X",
    "X.   X"
};

static GlyphMatrix BLOCK_LETTER_M =
{
    "X    X",
    "Xx  xX",
    "x Xx x",
    "X    x",
    "x    X",
    "x    x",
    "X    X"
};

static GlyphMatrix BLOCK_LETTER_P =
{
    "XxXXx.",
    "X    X",
    "x    x",
    "XxxXX'",
    "x     ",
    "X     ",
    "x     "
};

static GlyphMatrix BLOCK_LETTER_0 =
{
    ".xXXx.",
    "X    x",
    "x    X",
    "x    x",
    "X    X",
    "x    X",
    "`XxxX'"
};

static GlyphMatrix BLOCK_LETTER_1 =
{
    "  xX  ",
    "   X  ",
    "   x  ",
    "   X  ",
    "   x  ",
    "   X  ",
    " XxxXX"
};

static GlyphMatrix BLOCK_LETTER_2 =
{
    ".xXXx.",
    "     X",
    "     x",
    "    X'",
    "   X  ",
    " .X   ",
    "xXxXxX"
};

static GlyphMatrix BLOCK_LETTER_3 =
{
    ".xXXx.",
    "     X",
    "     x",
    "  .xX ",
    "     x",
    "     X",
    "`XxxX'"
};

static GlyphMatrix BLOCK_LETTER_4 =
{
    "x   X ",
    "X   x ",
    "x   x ",
    "XxxXXx",
    "    X ",
    "    x ",
    "    X "
};

static GlyphMatrix BLOCK_LETTER_5 =
{
    "XxxXXx",
    "x     ",
    "X     ",
    "xxXXx.",
    "     X",
    "     x",
    "`XxxX'"
};

static GlyphMatrix BLOCK_LETTER_6 =
{
    ".xXXx.",
    "X     ",
    "x     ",
    "XxXXx.",
    "X    X",
    "X    x",
    "`XxxX'"
};

static GlyphMatrix BLOCK_LETTER_7 =
{
    "XxxXxX",
    "     x",
    "     X",
    "    X ",
    "   X  ",
    "  x   ",
    " X    "
};

static GlyphMatrix BLOCK_LETTER_8 =
{
    ".xXXx.",
    "X    x",
    "x    X",
    "`xXXx'",
    "X    x",
    "x    X",
    "`XxxX'"
};

static GlyphMatrix BLOCK_LETTER_9 =
{
    ".xXXx.",
    "X    x",
    "x    X",
    "`XxxXx",
    "     X",
    "     x",
    "`XxxX'"
};

static GlyphMatrix BLOCK_LETTER_PERIOD =
{
    "      ",
    "      ",
    "      ",
    "      ",
    "      ",
    "  xX  ",
    "  Xx  "
};

static GlyphMatrix BLOCK_LETTER_COLON =
{
    "  xX  ",
    "  XX  ",
    "      ",
    "      ",
    "      ",
    "  Xx  ",
    "  xx  "
};

static GlyphMatrix BLOCK_LETTER_SPACE =
{
    "      ",
    "      ",
    "      ",
    "      ",
    "      ",
    "      ",
    "      "
};

static GlyphMatrix BLOCK_LETTER_ERROR =
{
    "XXXXXX",
    "X    X",
    "XXXXXX",
    "X    X",
    "XXXXXX",
    "X    X",
    "XXXXXX"
};

/**
 * Initializes a BlockLetter struct that includes an ASCII art glyph representation of the input char.
 * A string of BlockLetters can be formed by linking as linked list.
 */
BlockLetter *initBlockLetter(char inputLetter, BlockLetter *next){
    BlockLetter *blockLetter = malloc(sizeof(BlockLetter));

    blockLetter->height = LETTER_HEIGHT;
    blockLetter->width = LETTER_WIDTH - 1;
    blockLetter->next = next;

    switch (inputLetter) {
        case 'A':
            blockLetter->glyph = &BLOCK_LETTER_A;
            break;
        case 'M':
            blockLetter->glyph = &BLOCK_LETTER_M;
            break;
        case 'P':
            blockLetter->glyph = &BLOCK_LETTER_P;
            break;       
        case '0':
            blockLetter->glyph = &BLOCK_LETTER_0;
            break;
        case '1':
            blockLetter->glyph = &BLOCK_LETTER_1;
            break;
        case '2':
            blockLetter->glyph = &BLOCK_LETTER_2;
            break;
        case '3':
            blockLetter->glyph = &BLOCK_LETTER_3;
            break;
        case '4':
            blockLetter->glyph = &BLOCK_LETTER_4;
            break;
        case '5':
            blockLetter->glyph = &BLOCK_LETTER_5;
            break;
        case '6':
            blockLetter->glyph = &BLOCK_LETTER_6;
            break;
        case '7':
            blockLetter->glyph = &BLOCK_LETTER_7;
            break;
        case '8':
            blockLetter->glyph = &BLOCK_LETTER_8;
            break;
        case '9':
            blockLetter->glyph = &BLOCK_LETTER_9;
            break;
        case '.':
            blockLetter->glyph = &BLOCK_LETTER_PERIOD;
            break;
        case ':':
            blockLetter->glyph = &BLOCK_LETTER_COLON;
            break;
        case ' ':
            blockLetter->glyph = &BLOCK_LETTER_SPACE;
            break;
        default:
            blockLetter->glyph = &BLOCK_LETTER_ERROR;
    }

    return blockLetter;
}

/**
 * Delete a BlockLetter and free the associated memory
 */
void deleteBlockLetter(BlockLetter **letterRef) {
    free(*letterRef);
    *letterRef = NULL;
}

/**
 * Initialize a BlockString struct. Produces a linked list of BlockLetters based on the input string.
 */
BlockString *initBlockString(char *inputString) {
    BlockString *newString = malloc(sizeof(BlockString));

    newString->height = 0;
    newString->width = 0;
    BlockLetter *current = NULL;
    char c;

    int len = strlen(inputString) - 1;
    for (int i = len; i >= 0; i--) {
        c = inputString[i];
        current = initBlockLetter(c, current);
        newString->width += current->width + INTER_LETTER_SPACE;
    }

    newString->head = current;
    return newString;    
}

/**
 * Delete a BlockString and free the associated memory
 */
void deleteBlockString(BlockString **stringRef) {
    BlockString *string = *stringRef;

    BlockLetter *toDelete = string->head;
    BlockLetter *current = string->head->next;
    if (toDelete != NULL) {
        deleteBlockLetter(&toDelete);
    }

    while(current != NULL) {
        toDelete = current;
        current = current->next;
        deleteBlockLetter(&toDelete);
    }

    free(string);
    string = NULL;
}

