/**
 *  asciiArtString.c - ncurses-clock
 *
 *  This module creates and manages strings of ASCII art block letters
 *
 */

#include "blockString.h"


static GlyphMatrix BLOCK_LETTER_A =
{
    "  0o  ",
    " o  o ",
    ".0  o.",
    "o0oo00",
    "0    o",
    "o    0",
    "0.   0"
};

static GlyphMatrix BLOCK_LETTER_M =
{
    "0    0",
    "0o  o0",
    "o 0o o",
    "0    o",
    "o    0",
    "o    o",
    "0    0"
};

static GlyphMatrix BLOCK_LETTER_P =
{
    "0o00o.",
    "0    0",
    "o    o",
    "0oo00'",
    "o     ",
    "0     ",
    "o     "
};

static GlyphMatrix BLOCK_LETTER_0 =
{
    ".o00o.",
    "0    o",
    "o    0",
    "o    o",
    "0    0",
    "o    0",
    "`0oo0'"
};

static GlyphMatrix BLOCK_LETTER_1 =
{
    "  o0  ",
    "   0  ",
    "   o  ",
    "   0  ",
    "   o  ",
    "   0  ",
    " 0oo00"
};

static GlyphMatrix BLOCK_LETTER_2 =
{
    ".o00o.",
    "     0",
    "     o",
    "    0'",
    "   0  ",
    " .0   ",
    "o0o0o0"
};

static GlyphMatrix BLOCK_LETTER_3 =
{
    ".o00o.",
    "     0",
    "     o",
    "  .o0 ",
    "     o",
    "     0",
    "`0oo0'"
};

static GlyphMatrix BLOCK_LETTER_4 =
{
    "o   0 ",
    "0   o ",
    "o   o ",
    "0oo00o",
    "    0 ",
    "    o ",
    "    0 "
};

static GlyphMatrix BLOCK_LETTER_5 =
{
    "0oo00o",
    "o     ",
    "0     ",
    "oo00o.",
    "     0",
    "     o",
    "`0oo0'"
};

static GlyphMatrix BLOCK_LETTER_6 =
{
    ".o00o.",
    "0     ",
    "o     ",
    "0o00o.",
    "0    0",
    "0    o",
    "`0oo0'"
};

static GlyphMatrix BLOCK_LETTER_7 =
{
    "0oo0o0",
    "     o",
    "     0",
    "    0 ",
    "   0  ",
    "  o   ",
    " 0    "
};

static GlyphMatrix BLOCK_LETTER_8 =
{
    ".o00o.",
    "0    o",
    "o    0",
    "`o00o'",
    "0    o",
    "o    0",
    "`0oo0'"
};

static GlyphMatrix BLOCK_LETTER_9 =
{
    ".o00o.",
    "0    o",
    "o    0",
    "`0oo0o",
    "     0",
    "     o",
    "`0oo0'"
};

static GlyphMatrix BLOCK_LETTER_PERIOD =
{
    "      ",
    "      ",
    "      ",
    "      ",
    "      ",
    "  o0  ",
    "  0o  "
};

static GlyphMatrix BLOCK_LETTER_COLON =
{
    "  o0  ",
    "  00  ",
    "      ",
    "      ",
    "      ",
    "  0o  ",
    "  oo  "
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
    "000000",
    "0    0",
    "000000",
    "0    0",
    "000000",
    "0    0",
    "000000"
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

