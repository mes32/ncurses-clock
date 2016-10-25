#include <ncurses.h>
#include <stdio.h>

int main() {
	// Start curses mode
	initscr();	

	// Print Hello World
	printw("Hello World !!!");

	// Print it on to the real screen
	refresh();

	// Wait for user input
	getch();

	// End curses mode
	endwin();

	return 0;
}