/**
 *  dateTimeModel.h - ncurses-clock
 *
 *  This module defines functionality for updating strings with current date and time information
 *  This is the Model portion of the MVC pattern. See clockWindow for View and main for Controller.
 *
 */

#ifndef DATE_TIME_MODEL_H
#define DATE_TIME_MODEL_H

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "scanAndConfig.h"


/**
 * Configures the time mode (12-hour or 24-hour) used for the date-time-model
 */
void configureTimeMode(ProgramConfig config);

/**
 * Initialize a string to hold date/time information
 */
char *initBuffer();

/**
 * Update a string to contain a formatted sequence of characters representing the current time
 */
void updateTimeBuffer(char *timeBuffer);

/**
 * Update a string to contain a formatted sequence of characters representing the current date
 */
void updateDateBuffer(char *dateBuffer);

/**
 * Free memory allocated for a string holding date or time information
 */
void deleteBuffer(char **bufferRef);


#endif 
