/**
 *  scanAndConfig.c - ncurses-clock
 *
 *  This module scans input arguments to produce a configuration struct
 *
 */

#include "scanAndConfig.h"

static void printUsage();
static ProgramConfig *initProgramConfig();
static void deleteProgramConfig(ProgramConfig *configRef);


/**
 * Scans program arguments and sets up the configuration struct
 */
ProgramConfig *scanArguments(int argc, char *argv[]) {
    ProgramConfig *config = initProgramConfig();

    config->use24h = false;
    config->secsOff = false;

    bool hourModeSet = false;
    bool hourModeConflict = false;
    bool secModeSet = false;
    bool secModeConflict = false;
    bool unknownArg = false;

    int i;
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-12h") == 0) {
            if (hourModeSet && config->use24h) {
                hourModeConflict = true;
                break;
            } else {
                hourModeSet = true;
                config->use24h = false;
            }
        } else if (strcmp(argv[i], "-24h") == 0) {
            if (hourModeSet && !config->use24h) {
                hourModeConflict = true;
                break;
            } else {
                hourModeSet = true;
                config->use24h = true;
            }
        } else if (strcmp(argv[i], "-secs=on") == 0) {
            if (secModeSet && config->secsOff) {
                secModeConflict = true;
                break;
            } else {
                secModeSet = true;
                config->secsOff = false;
            }
        } else if (strcmp(argv[i], "-secs=off") == 0) {
            if (secModeSet && !config->secsOff) {
                secModeConflict = true;
                break;
            } else {
                secModeSet = true;
                config->secsOff = true;
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
    } else if (hourModeConflict) {
        config->shouldExit = true;
        config->exitCode = 1;
        printUsage();
        fprintf(stderr, "!!! Error, conflicting arguments for time mode (12-hour versus 24-hour)\n");
    } else if (secModeConflict) {
        config->shouldExit = true;
        config->exitCode = 1;
        printUsage();
        fprintf(stderr, "!!! Error, conflicting arguments indicate to both include and exclude seconds in time display\n");
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
    "    -12h       Use 12-hour clock mode (default)\n"
    "    -24h       Use 24-hour clock mode\n"
    "    -secs=on   Display time including seconds (default)\n"
    "    -secs=off  Display time without seconds\n"
    "    -help      Show this help message\n"
    "\n"
    );
}

/**
 * Intializes a program configuration struct
 */
static ProgramConfig *initProgramConfig() {
    ProgramConfig *config = malloc(sizeof(ProgramConfig));

    config->shouldExit = false;
    config->exitCode = 0;
    config->use24h = false;

    return config;
}

/**
 * Deletes a program configuration struct and frees memory
 */
static void deleteProgramConfig(ProgramConfig *config) {
	free(config);
	config = NULL;
}