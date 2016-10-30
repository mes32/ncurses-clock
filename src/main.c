/**
 *  main.c - ncurses-clock
 *
 *  This this program draws a clock in the terminal window using ncurses.
 *
 */

#include <time.h>
#include "dateTimeModel.h"
#include "clockWindow.h"


static const long WAIT_MSEC = 50;

static struct timespec *initSleep(long milliseconds);
static void sleepInLoop(struct timespec *duration_ts);


int main() {

    char *timeBuffer = initBuffer();
    char *dateBuffer = initBuffer();        
    struct timespec *duration_ts = initSleep(WAIT_MSEC);

    initClockWindow();

    while(1) {

        resetClockWindow();

        updateTimeBuffer(timeBuffer);
        updateDateBuffer(dateBuffer);
        updateClockWindow(timeBuffer, dateBuffer);

        sleepInLoop(duration_ts);
    }

    deleteClockWindow();

    deleteBuffer(&timeBuffer);
    deleteBuffer(&dateBuffer);

    return 0;
}


/**
 * Initializes sleep functionality. Allocates and returns a time specification struct.
 * This specification is configured to represent the input duration of sleep in milliseconds.
 */
static struct timespec *initSleep(long milliseconds) {
    struct timespec *duration_ts = malloc(sizeof(struct timespec));
    duration_ts->tv_sec = milliseconds / 1000;
    duration_ts->tv_nsec = (milliseconds % 1000) * 1000000;
    return duration_ts;
}

/**
 * Sleep for some previously configured duration
 */
static void sleepInLoop(struct timespec *duration_ts) {
    nanosleep(duration_ts, NULL);
}
