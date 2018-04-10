#include <cstdlib>
#include <ncurses.h>

int main() {
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    mvprintw(0, 0, "Hello, World!");
    refresh();
    getch();
    clear();
    endwin();
    return 0;
}