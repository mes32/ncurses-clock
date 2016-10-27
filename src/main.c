#include <ncurses.h>
#include <string.h>
#include <time.h>

static const long WAIT_MSEC = 50;
static struct timespec WAIT_TIMESPEC;
static int row, col;

static void initializeWait();
static void waitInLoop();
static char *getTimeString();
static char *getDateString();
static void printTime(char *currentTime);
static void printDate(char *currentDate);
static void printFooter();
static void cursorToRestPosition();

int main() {

    initializeWait();
    initscr();

    while(1) {

        getmaxyx(stdscr, row, col);

        char *currentTime = getTimeString();
        char *currentDate = getDateString();

        printTime(currentTime);
        printDate(currentDate);
        printFooter();

        cursorToRestPosition();
        refresh();
        waitInLoop();
    }

    endwin();

    return 0;
}

static void initializeWait() {
    long milliseconds = WAIT_MSEC;
    WAIT_TIMESPEC.tv_sec = milliseconds / 1000;
    WAIT_TIMESPEC.tv_nsec = (milliseconds % 1000) * 1000000;
}

static void waitInLoop() {
    nanosleep(&WAIT_TIMESPEC, NULL);
}

static char *getTimeString() {
    time_t now = time(0);
    char *mesg = ctime(&now);
    return mesg;
}

static char *getDateString() {
    return "Thursday October 27, 2016";
}

static void printTime(char *currentTime) {
    mvprintw(row / 2, (col - strlen(currentTime)) / 2, "%s", currentTime);
}

static void printDate(char *currentDate) {
    mvprintw(row / 2 + 1, (col - strlen(currentDate)) / 2, "%s", currentDate);
}
static void printFooter() {
    mvprintw(row - 1, 0, ":");
}

static void cursorToRestPosition() {
    move(row - 1, 1);
}
