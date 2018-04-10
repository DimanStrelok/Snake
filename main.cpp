#include <cstdlib>
#include <ncurses.h>

int Field_x0 = 0, Field_y0 = 2, Field_x1 = 40, Field_y1 = 20;
int Food_x = 5, Food_y = 5, score = 0;

void printRect(int x0, int y0, int x1, int y1) {
    int x = x0;
    int y = y0;
    for (; x <= x1; x++) {
        mvaddch(y, x, '#');
    }
    x--;
    y++;
    for (; y < y1; y++) {
        mvaddch(y, x, '|');
    }
    for (; x >= x0; x--) {
        mvaddch(y, x, '#');
    }
    x++;
    y--;
    for (; y > y0; y--) {
        mvaddch(y, x, '|');
    }
}

void render() {
    clear();
    printRect(Field_x0, Field_y0, Field_x1, Field_y1);
    printRect(0, 0, Field_x1, Field_y0);
    mvprintw(1, 1, "Score %d", score);
    mvaddch(Food_y, Food_x, 'F');
    mvaddch(0, 0, '#');
    refresh();
}

int main() {
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    nodelay(stdscr, TRUE);
    bool running = true;
    do {
        int key = getch();
        switch (key) {
            case 'q':
            case 'Q':
                running = false;
                break;
            default:
                break;
        }
    } while (running);
    nodelay(stdscr, FALSE);
    getch();
    clear();
    endwin();
    return 0;
}