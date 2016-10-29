#include <ncurses.h>
#include <string.h>
#include <time.h>


static const long WAIT_MSEC = 50;
static struct timespec WAIT_TIMESPEC;

static char *TIME_FORMAT = "%l:%M:%S %p";
static char *DATE_FORMAT = "%A - %B %d, %Y";

static const size_t BUFFER_SIZE = 50;
static int row, col;


static void initializeNCScreen();
static void initializeWait();
static void waitInLoop();
static void setTimeString(char *timeBuffer);
static void setDateString(char *dateBuffer);
static void printTime(char *currentTime);
static void printDate(char *currentDate);
static void printFooter();
static void cursorToRestPosition();

static const enum ColorPairType {
    COLOR_PAIR_WHITE = 0,
    COLOR_PAIR_GREEN = 1
} ColorPairs;

int main() {

    char timeBuffer[BUFFER_SIZE];
    char dateBuffer[BUFFER_SIZE];        

    initializeNCScreen();
    initializeWait();

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
