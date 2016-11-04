/**
 *  main.c - ncurses-clock
 *
 *  This this program draws a clock in the terminal window using ncurses.
 *
 */

#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "clockWindow.h"
#include "dateTimeModel.h"
#include "scanAndConfig.h"


static const long WAIT_MSEC = 500;

static bool isRunning;
static pthread_mutex_t lockIsRunning;


static void *updateClockThreadFunc(void *arg);
static void *listenThreadFunc(void *arg);
static struct timespec *initSleep(long milliseconds);
static void sleepInLoop(struct timespec *duration_ts);


int main(int argc, char *argv[]) {

    ProgramConfig *config = scanArguments(argc, argv);
    if (config->shouldExit) {
        return config->exitCode;
    }

    configureTimeMode(*config);

    isRunning = true;
    if (pthread_mutex_init(&lockIsRunning, NULL) != 0) {
        printf("Failed to initialize mutex.\n");
        return 1;
    }

    initClockWindow();

    pthread_t listenThread;
    pthread_create(&listenThread, NULL, listenThreadFunc, NULL);

    pthread_t updateClockThread;
    pthread_create(&updateClockThread, NULL, updateClockThreadFunc, NULL);
    pthread_join(updateClockThread, NULL);

    deleteClockWindow();

    return 0;
}


/**
 * Upates the clock window using a pthread
 */
static void *updateClockThreadFunc(void *arg) {

    char *timeBuffer = initBuffer();
    char *dateBuffer = initBuffer();        
    struct timespec *duration_ts = initSleep(WAIT_MSEC);

    while(1) {
        resetClockWindow();

        updateTimeBuffer(timeBuffer);
        updateDateBuffer(dateBuffer);
        updateClockWindow(timeBuffer, dateBuffer);

        sleepInLoop(duration_ts);

        pthread_mutex_unlock(&lockIsRunning);
        if (!isRunning) {
            break;
        }
        pthread_mutex_lock(&lockIsRunning);
    }

    deleteBuffer(&timeBuffer);
    deleteBuffer(&dateBuffer);

    return NULL;
}

/**
 * Listens for key presses in a pthread
 */
static void *listenThreadFunc(void *arg) {

    while (1) {
        char c = (char)getch();
        if (c == 'q' || c == 'Q') {
            pthread_mutex_unlock(&lockIsRunning);
            isRunning = false;
            pthread_mutex_lock(&lockIsRunning);
            return NULL;
        }
    }

    return NULL;
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
