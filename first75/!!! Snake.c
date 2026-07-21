
/*******************  *****************************************************
 * Written by Jeff *  * Adding Score + level & fix disappear bug 09/04/03 *
 *    2009/03/31   *  *                                                   *
 *******************  *****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

#define LEFT_BOUNDARY 1
#define UP_BOUNDARY 1

#define EXIT_SNAKE -1
#define PAUSE_GAME 2
#define HELP 3
#define FASTER 4
#define SLOWER 5

char direction = 77;
int size = 24, tail = 6;
int score = 0, level = 3;

char getinput()
{
	char c;
	if (kbhit()) {
        	if ((c = getch()) == -32) return getch();
		else if (c == 27) return EXIT_SNAKE; // exit
		else if (c == ' ') return PAUSE_GAME; // pause
		else if (c == 'h') return HELP; // help
		else if (c == 1) return FASTER;
		else if (c == 26) return SLOWER;
	}

	return direction;
}

void gotoXY(int x, int y)
{
     COORD coord = {x, y};
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
     return;
}

void hiddenCursor()
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.bVisible = FALSE;
    cci.dwSize = 25;
    SetConsoleCursorInfo(hcon, &cci);
}

void printBoundary(int length, int width)
{
	int x, y;
	
	gotoXY(LEFT_BOUNDARY,UP_BOUNDARY);
	printf("%c", 218); // left up corner
	gotoXY(LEFT_BOUNDARY,width);
	printf("%c", 192);
	gotoXY(length,UP_BOUNDARY);
	printf("%c", 191);
	gotoXY(length,width);
	printf("%c", 217);
	
	for (x=2;x<width;x++) {
	        gotoXY(x,UP_BOUNDARY); printf("%c", 196);
	        gotoXY(x,width); printf("%c", 196);
	        gotoXY(LEFT_BOUNDARY,x); printf("%c", 179);
	        gotoXY(length,x); printf("%c", 179);
	}
	
	gotoXY(size+LEFT_BOUNDARY*2+2,size/2+UP_BOUNDARY-2);
	printf("Level: %d", level);
	gotoXY(size+LEFT_BOUNDARY*2+2,size/2+UP_BOUNDARY);
	printf("Score: %d", score);
	gotoXY(size+LEFT_BOUNDARY*2+2,size/2+UP_BOUNDARY+2);
	printf("h - Help");
}

void printSnake(int snake[size][size])
{
	int x, y;
	
	for (x=0;x<size;x++)
	        for (y=0;y<size;y++) {
			gotoXY(y+LEFT_BOUNDARY+1,x+UP_BOUNDARY+1);
			if (snake[x][y] == 1) printf("@");
			else if (snake[x][y] == -1) printf("$");
			else if (snake[x][y] > 0) printf("*");
			else printf(" ");
		}
}

void moveSnake(int snake[size][size])
{
	int x, y, nonSpace;

	for (x=0;x<size;x++)
	        for (y=0;y<size;y++)
	                if (snake[x][y] == tail) {
	                        snake[x][y] = 0;
	                        break;
			}

	for (x=0;x<size;x++)
	        for (y=0;y<size;y++)
	                if (snake[x][y] > 0)
	                        snake[x][y]++;

	for (x=0;x<size;x++)
	        for (y=0;y<size;y++)
	                if (snake[x][y] == 2)
				if (direction == LEFT)
					if (y == 0) snake[x+1][y-1] = 1;
					else snake[x][y-1] = 1;
				else if (direction == RIGHT)
					if (y == size-1) snake[x-1][y+1] = 1;
					else snake[x][y+1] = 1;
				else if (direction == UP)
				        if (x == 0) snake[size-1][y] = 1;
				        else snake[x-1][y] = 1;
				else if (direction == DOWN)
				        if (x == size-1) snake[0][y] = 1;
					else snake[x+1][y] = 1;
}

int checkHead(int snake[size][size])
{
	int i, j, a, b;
	
	for (i=0;i<size;i++)
	        for (j=0;j<size;j++)
	                if (snake[i][j] == 1)
	                        if (j < size-1 && direction == LEFT && snake[i][j-1] == -1) {
					for (a=0;a<size;a++) for (b=0;b<size;b++) if (snake[a][b] > 0) snake[a][b]++;
					snake[i][j-1] = 1; tail++; score+=100;
					return 1;
				} else if (j > 0 && direction == RIGHT && snake[i][j+1] == -1) {
					for (a=0;a<size;a++) for (b=0;b<size;b++) if (snake[a][b] > 0) snake[a][b]++;
					snake[i][j+1] = 1; tail++; score+=100;
					return 1;
				} else if (i < size-1 && direction == UP && snake[i-1][j] == -1) {
					for (a=0;a<size;a++) for (b=0;b<size;b++) if (snake[a][b] > 0) snake[a][b]++;
					snake[i-1][j] = 1; tail++; score+=100;
					return 1;
				} else if (i > 0 && direction == DOWN && snake[i+1][j] == -1) {
					for (a=0;a<size;a++) for (b=0;b<size;b++) if (snake[a][b] > 0) snake[a][b]++;
					snake[i+1][j] = 1; tail++; score+=100;
					return 1;
				} else if (direction == RIGHT && (j == size-1 || snake[i][j+1] > 1)) {
					if (snake[i][j+1] == 2) { direction = LEFT; return 0; }
					return -1;
				} else if (direction == LEFT && (j == 0 || snake[i][j-1] > 1)) {
					if (snake[i][j-1] == 2) { direction = RIGHT; return 0; }
					return -1;
				} else if (direction == UP && (i == 0 || snake[i-1][j] > 1)) {
					if (snake[i-1][j] == 2) { direction = DOWN; return 0; }
					return -1;
				} else if (direction == DOWN && (i == size-1 || snake[i+1][j] > 1)) {
					if (snake[i+1][j] == 2) { direction = UP; return 0; }
     					return -1;
				} else	return 0;
}

void newFood(int snake[size][size])
{
	int x = rand()%size, y = rand()%size;
	
	while (1)
		if (snake[x][y] == 0) {
			snake[x][y] = -1;
			break;
		} else {
			x = rand()%size;
			y = rand()%size;
		}
}

int main()
{
	int initialLen = tail, i, j, check, gameover = 0;
	int snake[size][size], speed = 81, userInput;
	char cmd[100];

	system("title Snake Game");
	system("mode con cp select=437");
	sprintf(cmd,"mode con cols=%d lines=%d", size+LEFT_BOUNDARY*2+13, size+UP_BOUNDARY*2+2);
	system(cmd); hiddenCursor();

	srand(time(NULL));

	for (i=0;i<size;i++)
	        for (j=0;j<size;j++)
			snake[i][j] = 0;

	for (i=0;i<initialLen;i++)
	        snake[0][i] = initialLen - i;

	newFood(snake);

	while (!gameover) {
		printBoundary(size+2,size+2);
		printSnake(snake);

		if (level <= 1) sleep(100);
		else if (level == 2) sleep(50);
		else if (level == 3) sleep(30);
		else if (level == 4) sleep(10);

		gotoXY(2,size+5);
		userInput = getinput();
		if (userInput == EXIT_SNAKE) break;
		else if (userInput == PAUSE_GAME) {
			gotoXY(size/2+LEFT_BOUNDARY+1-3,size/2+UP_BOUNDARY);
			printf("Paused");
			getch();
		} else if (userInput == HELP) {
			gotoXY(size/2+LEFT_BOUNDARY+1-7,size/2+UP_BOUNDARY-2);
			printf("  ESC -- exit");
			gotoXY(size/2+LEFT_BOUNDARY+1-7,size/2+UP_BOUNDARY-1);
			printf("Space -- pause");
			gotoXY(size/2+LEFT_BOUNDARY+1-8,size/2+UP_BOUNDARY+1);
			printf("Ctrl+A -- faster");
			gotoXY(size/2+LEFT_BOUNDARY+1-8,size/2+UP_BOUNDARY+2);
			printf("Ctrl+Z -- slower");
			getch();
		} else if (userInput == FASTER) {
		        if (level < 5) level++;
		} else if (userInput == SLOWER) {
			if (level > 1) level--;
		} else if (userInput == LEFT || userInput == RIGHT ||
			   userInput == DOWN || userInput == UP)
			direction = userInput;
		
		if ((check = checkHead(snake)) == 1) newFood(snake);
		else if (check == -1) gameover = 1;
		moveSnake(snake);
	}
	
	if (gameover) {
                gotoXY(size/2+LEFT_BOUNDARY+1-4,size/2+UP_BOUNDARY);
		printf("You Lose");
	} else {
                gotoXY(size/2+LEFT_BOUNDARY+1-2,size/2+UP_BOUNDARY);
		printf("Exit");
	}
	
	getch();
	return 0;
}
