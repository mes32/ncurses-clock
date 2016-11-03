/**
 *  asciiArtString.c - ncurses-clock
 *
 *  This module creates and manages strings of ASCII art block letters
 *
 */

#include "blockString.h"

static const int LETTER_HEIGHT = 7;
static const int LETTER_WIDTH  = 7;

static const Glyph BLOCK_LETTER_0 =
{
    ".xXXx.",
    "X    x",
    "x    X",
    "x    x",
    "X    X",
    "x    X",
    "`XxxX'"
};

static const Glyph BLOCK_LETTER_1 =
{
    "  xX  ",
    "   X  ",
    "   x  ",
    "   X  ",
    "   x  ",
    "   X  ",
    " XxxXX"
};

static const Glyph BLOCK_LETTER_2 =
{
    ".xXXx.",
    "     X",
    "     x",
    "    X'",
    "   X  ",
    " .X   ",
    "xXxXxX"
};

static const Glyph BLOCK_LETTER_3 =
{
    ".xXXx.",
    "     X",
    "     x",
    "  .xX ",
    "     x",
    "     X",
    "`XxxX'"
};

static const Glyph BLOCK_LETTER_4 =
{
    "x   X ",
    "X   x ",
    "x   x ",
    "XxxXXx",
    "    X ",
    "    x ",
    "    X "
};

static const Glyph BLOCK_LETTER_5 =
{
    "XxxXXx",
    "x     ",
    "X     ",
    "xxXXx.",
    "     X",
    "     x",
    "`XxxX'"
};

static const Glyph BLOCK_LETTER_6 =
{
    ".xXXx.",
    "X     ",
    "x     ",
    "XxXXx.",
    "X    X",
    "X    x",
    "`XxxX'"
};

static const Glyph BLOCK_LETTER_7 =
{
    "XxxXxX",
    "     x",
    "     X",
    "    X ",
    "   X  ",
    "  x   ",
    " X    "
};

static const Glyph BLOCK_LETTER_8 =
{
    ".xXXx.",
    "X    x",
    "x    X",
    "`xXXx'",
    "X    x",
    "x    X",
    "`XxxX'"
};

static const Glyph BLOCK_LETTER_9 =
{
    ".xXXx.",
    "X    x",
    "x    X",
    "`XxxXx",
    "     X",
    "     x",
    "`XxxX'"
};

static const Glyph BLOCK_LETTER_PERIOD =
{
    "      ",
    "      ",
    "      ",
    "      ",
    "      ",
    "  xX  ",
    "  Xx  "
};

static const Glyph BLOCK_LETTER_COLON =
{
    "  xX  ",
    "  XX  ",
    "      ",
    "      ",
    "      ",
    "  Xx  ",
    "  xx  "
};

static const Glyph BLOCK_LETTER_SPACE =
{
    "      ",
    "      ",
    "      ",
    "      ",
    "      ",
    "      ",
    "      "
};

BlockLetter *initBlockLetter(char inputLetter){
    BlockLetter *blockLetter = malloc(sizeof(BlockLetter));

    blockLetter->height = LETTER_HEIGHT;
    blockLetter->width = LETTER_WIDTH;
    blockLetter->next = NULL;

    char b[7][7];
    char a[7][7] = b;
    Glyph *ptr = &BLOCK_LETTER_1;

    switch (inputLetter) {
        case '0':
            blockLetter->glyph = &BLOCK_LETTER_1;
            break;
        /*case '1':
            blockLetter->glyph = BLOCK_LETTER_1;
            break;
        case '2':
            blockLetter->glyph = BLOCK_LETTER_1;
            break;
        case '3':
            blockLetter->glyph = BLOCK_LETTER_1;
            break;
        case '4':
            blockLetter->glyph = BLOCK_LETTER_1;
            break;
        case '5':
            blockLetter->glyph = BLOCK_LETTER_1;
            break;
        case '6':
            blockLetter->glyph = BLOCK_LETTER_1;
            break;
        case '7':
            blockLetter->glyph = BLOCK_LETTER_1;
            break;
        case '8':
            blockLetter->glyph = BLOCK_LETTER_1;
            break;
        case '9':
            blockLetter->glyph = BLOCK_LETTER_1;
            break;
        case '1':
            blockLetter->glyph = BLOCK_LETTER_1;
            break;
        case '1':
            blockLetter->glyph = BLOCK_LETTER_1;
            break;*/
        default:
            assert(0);
    }

    return blockLetter;
}

BlockString *initBlockString(char *inputString) {
    return NULL;
}

