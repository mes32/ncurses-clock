#include <ncurses.h>
#include <string.h>
#include <time.h>
#include "dateTimeModel.h"


static const long WAIT_MSEC = 50;
static struct timespec WAIT_TIMESPEC;
static int row, col;

static void initializeNCScreen();
static void initializeWait();
static void waitInLoop();
static void printTime(char *currentTime);
static void printDate(char *currentDate);
static void printFooter();
static void cursorToRestPosition();

static const enum ColorPairType {
    COLOR_PAIR_WHITE = 0,
    COLOR_PAIR_GREEN = 1
} ColorPairs;


int main() {

    char *timeBuffer = initBuffer();
    char *dateBuffer = initBuffer();        

    initializeNCScreen();
    initializeWait();

    while(1) {

        // Clear window in between loops to handle window resize
        endwin();
        refresh();
        clear();

        getmaxyx(stdscr, row, col);

        updateTimeBuffer(timeBuffer);
        updateDateBuffer(dateBuffer);

        printTime(timeBuffer);
        printDate(dateBuffer);
        printFooter();

        cursorToRestPosition();
        refresh();
        waitInLoop();
    }

    endwin();

    deleteBuffer(&timeBuffer);
    deleteBuffer(&dateBuffer);

    return 0;
}


static void initializeNCScreen() {
    WINDOW *window = initscr();
    start_color();

    //bool hasColors = has_colors();
    //bool canChangeColors = can_change_color();

    init_pair(COLOR_PAIR_WHITE, COLOR_WHITE, COLOR_BLACK);
    init_pair(COLOR_PAIR_GREEN, COLOR_GREEN, COLOR_BLACK);
    wbkgd(window, COLOR_PAIR(COLOR_PAIR_WHITE));
}

static void initializeWait() {
    long milliseconds = WAIT_MSEC;
    WAIT_TIMESPEC.tv_sec = milliseconds / 1000;
    WAIT_TIMESPEC.tv_nsec = (milliseconds % 1000) * 1000000;
}

static void waitInLoop() {
    nanosleep(&WAIT_TIMESPEC, NULL);
}

static void printTime(char *currentTime) {
    attron(COLOR_PAIR(COLOR_PAIR_GREEN));
    mvprintw(row / 2, (col - strlen(currentTime)) / 2, "%s", currentTime);
    attroff(COLOR_PAIR(COLOR_PAIR_GREEN));
}

static void printDate(char *currentDate) {
    attron(COLOR_PAIR(COLOR_PAIR_WHITE));
    mvprintw(row / 2 + 1, (col - strlen(currentDate)) / 2, "%s", currentDate);
    attroff(COLOR_PAIR(COLOR_PAIR_WHITE));
}
static void printFooter() {
    attron(COLOR_PAIR(COLOR_PAIR_GREEN));
    mvprintw(row - 1, 0, ":");
    attroff(COLOR_PAIR(COLOR_PAIR_GREEN));
}

static void cursorToRestPosition() {
    move(row - 1, 1);
}
