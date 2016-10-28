#include <ncurses.h>
#include <string.h>
#include <time.h>

static const long WAIT_MSEC = 50;
static struct timespec WAIT_TIMESPEC;

static char *TIME_FORMAT = "%l:%M:%S %p";
static char *DATE_FORMAT = "%A - %B %d, %Y";

static const size_t BUFFER_SIZE = 50;
static int row, col;


static void initializeWait();
static void waitInLoop();
static void setTimeString(char *timeBuffer);
static void setDateString(char *dateBuffer);
static void printTime(char *currentTime);
static void printDate(char *currentDate);
static void printFooter();
static void cursorToRestPosition();

int main() {

    char timeBuffer[BUFFER_SIZE];
    char dateBuffer[BUFFER_SIZE];        

    initializeWait();
    initscr();

    while(1) {

        getmaxyx(stdscr, row, col);

        setTimeString(timeBuffer);
        setDateString(dateBuffer);

        printTime(timeBuffer);
        printDate(dateBuffer);
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

static void setTimeString(char *timeBuffer) {
    time_t now = time(0);
    struct tm* tm_info;
    tm_info = localtime(&now);

    strftime(timeBuffer, BUFFER_SIZE, TIME_FORMAT, tm_info);
}

static void setDateString(char *dateBuffer) {
    time_t now = time(0);
    struct tm* tm_info;
    tm_info = localtime(&now);

    strftime(dateBuffer, BUFFER_SIZE, DATE_FORMAT, tm_info);
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
