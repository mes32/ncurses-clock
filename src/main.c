/**
 *  main.c - ncurses-clock
 *
 *  This this program draws a clock in the terminal window using ncurses.
 *
 */

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "clockWindow.h"
#include "dateTimeModel.h"


typedef struct {
    bool shouldExit;
    int exitCode;
    bool use24h;
} ProgramConfig;

static const long WAIT_MSEC = 50;

static bool isRunning;
static pthread_mutex_t lockIsRunning;


static ProgramConfig *scanArguments(int argc, char *argv[]);
static void printUsage();
static void *updateClockThreadFunc(void *arg);
static void *listenThreadFunc(void *arg);
static struct timespec *initSleep(long milliseconds);
static void sleepInLoop(struct timespec *duration_ts);


int main(int argc, char *argv[]) {

    ProgramConfig *config = scanArguments(argc, argv);
    if (config->shouldExit) {
        return config->exitCode;
    }

    configureTimeMode(config->use24h);

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
 * Scans program arguments and set the configuration struct
 */
static ProgramConfig *scanArguments(int argc, char *argv[]) {
    ProgramConfig *config = malloc(sizeof(ProgramConfig));

    config->shouldExit = false;
    config->exitCode = 0;
    config->use24h = false;

    bool hoursSet = false;
    bool hoursConflict = false;
    bool unknownArg = false;
    int i;
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-12h") == 0) {
            if (hoursSet && config->use24h) {
                hoursConflict = true;
                break;
            } else {
                hoursSet = true;
                config->use24h = false;
            }
        } else if (strcmp(argv[i], "-24h") == 0) {
            if (hoursSet && !config->use24h) {
                hoursConflict = true;
                break;
            } else {
                hoursSet = true;
                config->use24h = true;
            }
        } else if (strcmp(argv[i], "-help") == 0) {
            config->shouldExit = true;
            printUsage();
        } else {
            unknownArg = true;
            break;
        }
    }

    if (unknownArg) {
        config->shouldExit = true;
        config->exitCode = 1;
        printUsage();
        fprintf(stderr, "!!! Error, encountered an unknown argument: %s\n", argv[i]);
    } else if (hoursConflict) {
        config->shouldExit = true;
        config->exitCode = 1;
        printUsage();
        fprintf(stderr, "!!! Error, conflicting arguments for time mode (12-hour versus 24-hour)\n");
    }

    return config;
}

/**
 * Prints a short description of the program and lists the usage options
 */
static void printUsage() {
    printf(
    "\n"
    "ncurses-clock -- draws a clock in the terminal window using the ncurses library\n"
    "\n"
    "Usage: ncurses-clock [options]\n"
    "  options:\n"
    "    -12h     Display time using 12 hour mode. This is the default.\n"
    "    -24h     Display time using 24 hour mode\n"
    "    -help    Display this help message\n"
    "\n"
    );
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
