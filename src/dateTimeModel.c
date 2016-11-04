/**
 *  dateTimeModel.c - ncurses-clock
 *
 *  This module defines functionality for updating strings with current date and time information.
 *  This is the Model portion of the MVC pattern. See clockWindow for View and main for Controller.
 *
 */

#include "dateTimeModel.h"


static const char *TIME_FORMAT_STRING_12H = "%l:%M:%S %p";  // Format time as a string ( 2:03:56 PM)
static const char *TIME_FORMAT_STRING_24H = "%H:%M:%S";     // Format time as a string (14:03:56)
static const char *TIME_FORMAT_STRING_12H_NOSEC = "%l:%M %p";  // Format time as a string ( 2:03 PM)
static const char *TIME_FORMAT_STRING_24H_NOSEC = "%H:%M";     // Format time as a string (14:03)

static const char *DATE_FORMAT_STRING = "%A - %B %d, %Y";   // Format date as a string Sunday - October 30, 2016
static const size_t BUFFER_SIZE = 50;                       // Number of characters in string buffers

static char TIME_FORMAT_STRING[16];


static void setFormat_12H();
static void setFormat_24H();
static void setFormat_12H_NOSEC();
static void setFormat_24H_NOSEC();


/**
 * Configures the time mode (12-hour or 24-hour) used for the date-time-model
 */
void configureTimeMode(ProgramConfig config) {
    // TODO: TIME_FORMAT_STRING len = 16 is a magic number
    if (config.use24h) {
        if (config.secsOff) {
            setFormat_24H_NOSEC();
        } else {
            setFormat_24H();
        }
    } else {
        if (config.secsOff) {
            setFormat_12H_NOSEC();
        } else {
            setFormat_12H();
        }
    }
}

/**
 * Initialize a string to hold date/time information
 */
char *initBuffer() {
	char *buffer = malloc(BUFFER_SIZE);
	assert(buffer != NULL);
	return buffer;
}

/**
 * Update a string to contain a formatted sequence of characters representing the current time
 */
void updateTimeBuffer(char *timeBuffer) {
    time_t now = time(0);
    struct tm* tm_info;
    tm_info = localtime(&now);

    strftime(timeBuffer, BUFFER_SIZE, TIME_FORMAT_STRING, tm_info);
}

/**
 * Update a string to contain a formatted sequence of characters representing the current date
 */
void updateDateBuffer(char *dateBuffer) {
    time_t now = time(0);
    struct tm* tm_info;
    tm_info = localtime(&now);

    strftime(dateBuffer, BUFFER_SIZE, DATE_FORMAT_STRING, tm_info);
}

/**
 * Free memory allocated for a string holding date or time information
 */
void deleteBuffer(char **bufferRef) {
	free(*bufferRef);
	*bufferRef = NULL;
}

static void setFormat_12H() {
    size_t len = strlen(TIME_FORMAT_STRING_12H);
    strncpy(TIME_FORMAT_STRING, TIME_FORMAT_STRING_12H, len);
}

static void setFormat_24H(char **format) {
    size_t len = strlen(TIME_FORMAT_STRING_12H);
    strncpy(TIME_FORMAT_STRING, TIME_FORMAT_STRING_24H, len);
}

static void setFormat_12H_NOSEC(char **format) {
    size_t len = strlen(TIME_FORMAT_STRING_12H);
    strncpy(TIME_FORMAT_STRING, TIME_FORMAT_STRING_12H_NOSEC, len);
}

static void setFormat_24H_NOSEC(char **format) {
    size_t len = strlen(TIME_FORMAT_STRING_12H);
    strncpy(TIME_FORMAT_STRING, TIME_FORMAT_STRING_24H_NOSEC, len);
}