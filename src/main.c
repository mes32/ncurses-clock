#include <ncurses.h>
#include <string.h>
#include <time.h>
#include "dateTimeModel.h"
#include "clockWindow.h"


static const long WAIT_MSEC = 50;

static struct timespec *initSleep(long milliseconds);
static void sleepInLoop(struct timespec *durationRef);


int main() {

    char *timeBuffer = initBuffer();
    char *dateBuffer = initBuffer();        

    initClockWindow();
    struct timespec *sleep_ts = initSleep(WAIT_MSEC);

    while(1) {

        resetClockWindow();

        updateTimeBuffer(timeBuffer);
        updateDateBuffer(dateBuffer);
        updateClockWindow(timeBuffer, dateBuffer);

        sleepInLoop(sleep_ts);
    }

    deleteClockWindow();

    deleteBuffer(&timeBuffer);
    deleteBuffer(&dateBuffer);

    return 0;
}


static struct timespec *initSleep(long milliseconds) {
    struct timespec *durationRef = malloc(sizeof(struct timespec));
    struct timespec duration = *durationRef;
    duration.tv_sec = milliseconds / 1000;
    duration.tv_nsec = (milliseconds % 1000) * 1000000;
    return durationRef;
}

static void sleepInLoop(struct timespec *durationRef) {
    nanosleep(durationRef, NULL);
}
