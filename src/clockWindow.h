/**
 *  clockWindow.h - ncurses-clock
 *
 *  This module defines functionality for the ncurses window that draws the clock.
 *  This is the View portion of the MVC pattern. See dateTimeModel for Model and main for
 *  Controller.
 *
 */

#ifndef CLOCK_WINDOW_H
#define CLOCK_WINDOW_H

#include <string.h>
#include <ncurses.h>
#include "blockString.h"


/**
 * Initialize the ncurses window for displaying the clock
 */
void initClockWindow();

/**
 * Clear the window contents and reset the dimensions to handle resizing 
 */
void resetClockWindow();

/**
 * Draw the current state of the window 
 */
void updateClockWindow(char *timeBuffer, char *dateBuffer);

/**
 * Delete the window and clean up
 */
void deleteClockWindow();


#endif 
