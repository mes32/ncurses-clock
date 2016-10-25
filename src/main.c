#include <ncurses.h>
#include <string.h> 

int main() {

    char mesg[] = "01:19 AM";
    int row, col;

    initscr();
    getmaxyx(stdscr, row, col);

    mvprintw(row / 2, (col-strlen(mesg)) / 2, "%s", mesg);
    mvprintw(row - 1, 0, ":");
    move(row - 1, 1);

    refresh();
    getch();
    endwin();

    return 0;
}