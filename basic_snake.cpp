#include <iostream>
#include <curses.h>
#include <stdio.h>
#include <unistd.h>

bool gameOver;

const int width = 20;
const int height = 20;

int x, y, fruitX, fruitY, score;

int tailX[100], tailY[100];
int nTail;

enum eDirections {
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

eDirections dir;

void Setup() {
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(0);

    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width + 1;
    fruitY = rand() % height + 1;
    score = 0;
}

void Draw() {
    clear();
    for (int i = 0; i < width + 2; i++) {
        mvaddch(0, i, '#');
    }
    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width + 1; j++) {
            if (j == 1 || j == width + 1)
                mvaddch(i, j, '#');
            else if (i == y && j == x)
                mvaddch(i, j, '0');
            else if (j == fruitX && i == fruitY)
                mvaddch(i, j, '*');
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        mvaddch(i, j, 'o');
                        print = true;
                    }
                }
                if (!print)
                    mvaddch(i, j, ' ');
            }
        }
    }
    for (int i = 0; i < width + 2; i++) {
        mvaddch(height + 1, i, '#');
    }
    mvprintw(height + 3, 0, "Score: %d", score);
    refresh();
}

void Input() {
    int ch = getch();
    switch (ch) {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
    }
    if ((x > width || x < 0) || (y > height || y < 0)) {
        mvprintw(height + 5, 0, "\t\tGame Over\n\t   You Hit the Wall!");
        gameOver = true;
    }
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            mvprintw(height + 5, 0, "\t\tGame Over\n\t   You Hit the Tail!");
            gameOver = true;
        }
    }
    if (x == fruitX && y == fruitY) {
        score += 10;
        nTail++;
        fruitX = rand() % width + 1;
        fruitY = rand() % height + 1;
    }	
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        usleep(150 * 1000);
    }
    endwin();
    return 0;
}


// #include <iostream>
// #include <curses.h>
// #include <stdio.h>
// #include <unistd.h>

// bool gameOver;

// const int width = 20;
// const int height = 20;

// int x, y, fruitX, fruitY, score;

// int tailX[100], tailY[100];
// int nTail;

// std::string fruit = "*";

// enum eDirections
// {
// 	STOP = 0,
// 	LEFT,
// 	RIGHT,
// 	UP,
// 	DOWN
// };

// eDirections dir;

// void Setup() {
// 	initscr();
// 	cbreak();
// 	noecho();
// 	nodelay(stdscr, TRUE);
// 	keypad(stdscr, TRUE);
// 	curs_set(0);

// 	gameOver = false;
// 	dir = STOP;
// 	x = width / 2;
// 	y = height / 2;
// 	fruitX = rand() % width + 1;
// 	fruitY = rand() % height + 1;
// 	score = 0;
// }

// void Draw() {
// 	clear();
// 	for (int i = 0; i < width + 2; i++) {
// 		// std::cout << "#";
// 		mvaddch(0, i, '#');
// 	}
// 	std::cout << std::endl;
// 	for (int i = 1; i <= height; i++) {
// 		for (int j = 1; j <= width + 1; j++) {
// 			if (j == 1 || j == width + 1)
// 				// std::cout << "#";
// 				mvaddch(i, j, '#');
// 			if (i == y && j == x) {
// 				// std::cout << "0";
// 				mvaddch(i, j, '0');
// 			}
// 			else if (j == fruitX && i == fruitY) {
// 				// std::cout << fruit;
// 				mvaddch(i, j, '*');
// 			}
// 			else {
// 				bool print = false;
// 				for (int k = 0; k < nTail; k++) {
// 					if (tailX[k] == j && tailY[k] == i) {
// 						std::cout << "o";
// 						print = true;
// 					}
// 				}
// 				if (!print)
// 					std::cout << " ";
// 			}
// 		}
// 		std::cout << std::endl;
// 	}
// 	for (int i = 0; i < width + 2; i++) {
// 		std::cout << "#";
// 	}
// 	std::cout << std::endl;
// 	std::cout << "Score: " << score << std::endl;
// }

// void Input() {
// 	int ch = getch();
// 	switch (ch) {
// 		case 'a':
// 				dir = LEFT;
// 				break;
// 			case 'd':
// 				dir = RIGHT;
// 				break;
// 			case 'w':
// 				dir = UP;
// 				break;
// 			case 's':
// 				dir = DOWN;
// 				break;
// 			case 'x':
// 				gameOver = true;
// 				break;
// 	}
// }

// void Logic() {
// 	int prevX = tailX[0];
// 	int prevY = tailY[0];
// 	int prev2X, prev2Y;
// 	tailX[0] = x;
// 	tailY[0] = y;
// 	for (int i = 1; i < nTail; i++) {
// 		prev2X = tailX[i];
// 		prev2Y = tailY[i];
// 		tailX[i] = prevX;
// 		tailY[i] = prevY;
// 		prevX = prev2X;
// 		prevY = prev2Y;
// 	}
// 	switch (dir) {
// 		case LEFT:
// 			x--;
// 			break;
// 		case RIGHT:
// 			x++;
// 			break;
// 		case UP:
// 			y--;
// 			break;
// 		case DOWN:
// 			y++;
// 			break;
// 		case STOP:
// 			break;
// 	}
// 	if ((x > width || x < 0) || (y > height || y < 0)) {
// 		std::cout << "\t\tGame Over" << std::endl;
// 		std::cout << "\t   You Hit the Wall!";
// 		gameOver = true;
// 	}
// 	for (int i = 0; i < nTail; i++) {
// 		if (tailX[i] == x && tailY[i] == y) {
// 			std::cout << "\t\tGame Over" << std::endl;
// 			std::cout << "\t   You Hit the Tail!";
// 			gameOver = true;
// 		}
// 	}
// 	if (x == fruitX && y == fruitY) {
// 		score += 10;
// 		nTail++;
// 		fruitX = rand() % width + 1;
// 		fruitY = rand() % height + 1;
// 	}	
// }

// int main() {
// 	Setup();
// 	while (!gameOver) {
// 		Draw();
// 		Input();
// 		Logic();
// 		usleep(150 * 1000);
// 	}
// 	endwin();
// 	std::cout << fruitX << " " << fruitY;
// 	return 0;
// }
