#include <cstdlib>
#include <ctime>
#include <list>
#include <ncurses.h>

enum Move {
    UP, DOWN, LEFT, RIGHT
};

struct Point {
    int x, y;
    Move m;

    Point() : x(0), y(0), m(RIGHT) {}

    Point(int x_, int y_, Move m_) : x(x_), y(y_), m(m_) {}
};

int Field_x0 = 0, Field_y0 = 2, Field_x1 = 40, Field_y1 = 20;
int Food_x, Food_y, score = 0;
std::list<Point> snake;

bool checkFoodCoord() {
    int x = Food_x;
    int y = Food_y;
    for (std::list<Point>::iterator it = snake.begin(); it != snake.end(); ++it) {
        if (x == it->x || y == it->y) {
            return false;
        }
    }
    return true;
}

void newFood() {
    bool good;
    do {
        Food_x = Field_x0 + 1 + rand() % (Field_x1 - (Field_x0 + 1));
        Food_y = Field_y0 + 1 + rand() % (Field_y1 - (Field_y0 + 1));
        good = checkFoodCoord();
    } while (!good);
}

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

void initGame() {
    Move m = RIGHT;
    int xC = (Field_x0 + 1 + (Field_x1 - (Field_x0 + 1))) / 2;
    int yC = (Field_y0 + 1 + (Field_y1 - (Field_y0 + 1))) / 2;
    snake.push_back(Point(xC + 1, yC, m));
    snake.push_back(Point(xC, yC, m));
    snake.push_back(Point(xC - 1, yC, m));
    newFood();
}

int main() {
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    nodelay(stdscr, TRUE);
    srand(time(0));
    initGame();
    Move m = snake.front().m;
    bool running = true;
    do {
        render();
        int key = getch();
        switch (key) {
            case 'q':
            case 'Q':
                running = false;
                break;
            case KEY_UP:
                m = UP;
                break;
            case KEY_DOWN:
                m = DOWN;
                break;
            case KEY_LEFT:
                m = LEFT;
                break;
            case KEY_RIGHT:
                m = RIGHT;
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