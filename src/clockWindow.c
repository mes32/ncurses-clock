/**
 *  clockWindow.c - ncurses-clock
 *
 *  This module defines functionality for the ncurses window that draws the clock.
 *  This is the View portion of the MVC pattern. See dateTimeModel for Model and main for
 *  Controller.
 *
 */

#include "clockWindow.h"

static const enum ColorPairType {   // Pairs of colors available for drawing
    COLOR_PAIR_WHITE = 0,
    COLOR_PAIR_GREEN = 1
} ColorPairs;          
static int row, col;                // Dimensions of the window

static void printTime(char *currentTime);
static void printDate(char *currentDate);
static void printFooter();
static void cursorToRestPosition();


/**
 * Initialize the ncurses window for displaying the clock
 */
void initClockWindow() {
    WINDOW *window = initscr();
    start_color();

    //bool hasColors = has_colors();
    //bool canChangeColors = can_change_color();

    init_pair(COLOR_PAIR_WHITE, COLOR_WHITE, COLOR_BLACK);
    init_pair(COLOR_PAIR_GREEN, COLOR_GREEN, COLOR_BLACK);
    wbkgd(window, COLOR_PAIR(COLOR_PAIR_WHITE));
}

/**
 * Clear the window contents and reset the dimensions to handle resizing 
 */
void resetClockWindow() {
	endwin();
    refresh();
    clear();
    getmaxyx(stdscr, row, col);
}

/**
 * Draw the current state of the window 
 */
void updateClockWindow(char *timeBuffer, char *dateBuffer) {
	printTime(timeBuffer);
    printDate(dateBuffer);
    printFooter();

    cursorToRestPosition();
    refresh();
}

/**
 * Delete the window and clean up
 */
void deleteClockWindow() {
	// TODO: add free()
	endwin();
}

/**
 * Prints the current time from the buffer
 */ 
static void printTime(char *currentTime) {
    attron(COLOR_PAIR(COLOR_PAIR_GREEN));
    mvprintw(row / 2, (col - strlen(currentTime)) / 2, "%s", currentTime);
    attroff(COLOR_PAIR(COLOR_PAIR_GREEN));
}

/**
 * Prints the current date from the buffer
 */
static void printDate(char *currentDate) {
    attron(COLOR_PAIR(COLOR_PAIR_WHITE));
    mvprintw(row / 2 + 1, (col - strlen(currentDate)) / 2, "%s", currentDate);
    attroff(COLOR_PAIR(COLOR_PAIR_WHITE));
}

/**
 * Prints a short section of text at the bottom of the screen
 */
static void printFooter() {
    attron(COLOR_PAIR(COLOR_PAIR_GREEN));
    //mvprintw(row - 2, 0, "(Q) quit, (C) countdown, (T) timer");
    mvprintw(row - 2, 0, "(Q) quit");
    mvprintw(row - 1, 0, ":");
    attroff(COLOR_PAIR(COLOR_PAIR_GREEN));
}

/**
 * Moves the cursor to the bottom of the screen 
 */
static void cursorToRestPosition() {
    move(row - 1, 1);
}


