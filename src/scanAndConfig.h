/**
 *  scanAndConfig.h - ncurses-clock
 *
 *  This module scans input arguments to produce a configuration struct
 *
 */

#ifndef SCAN_AND_CONFIG_H
#define SCAN_AND_CONFIG_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    bool shouldExit;
    int exitCode;
    bool use24h;
    bool secsOff;
} ProgramConfig;

/**
 * Scans program arguments and sets up the configuration struct
 */
ProgramConfig *scanArguments(int argc, char *argv[]);


#endif