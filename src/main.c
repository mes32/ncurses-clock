#include <ncurses.h>
#include <string.h>
#include <time.h>

void loopWait();

int main() {

    initscr();

    while(1) {
        time_t now = time(0);
        char *mesg = ctime(&now);

        int row, col;
        getmaxyx(stdscr, row, col);

        mvprintw(row / 2, (col-strlen(mesg)) / 2, "%s", mesg);
        mvprintw(row - 1, 0, ":");
        move(row - 1, 1);

        refresh();
        loopWait();
    }

    endwin();

    return 0;
}

void loopWait() {

    long milliseconds = 50;

    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
}