#include <stdio.h>
#include <conio.h>
#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;

#define KEY_LOWER_W 119
#define KEY_UPPER_W 87
#define KEY_LOWER_S 115
#define KEY_UPPER_S 83
#define KEY_LOWER_A 97
#define KEY_UPPER_A 65
#define KEY_LOWER_D 100
#define KEY_UPPER_D 68


class Main
{
	public:
		int mazeSize;
		int key;
		int x;
		int y;
		int ex;
		int ey;
		int rx;
		int ry;
		int movementCountdown;
		int attackCountdown;
		int angle;
		int attackX;
		int attackY;
		bool killedEnemy;
		void render();
		int nonblockInput();
		void parseInputs();
};


void Main::render() //int playerx, int playery, int enemyx, int enemyy, int attackX, int attackY, int mazeSize
{
	int i;
	int j;
	for(i = 0; i < mazeSize + 2; i = i + 1)
	{
	printf("-");
	}
	printf("\n");
	for(i = 0; i < mazeSize; i = i + 1)
	{
		printf("|");
		for(j = 0; j < mazeSize; j = j + 1)
		{
			if ((i != y || j != x) && (i != ey || j != ex) && (i != attackY || j != attackX))
			{
				printf(" ");
			}
			else if (i == y && j == x)
			{
				printf("+");
			}
			else if (i == ey && j == ex)
			{
				printf("X");
			}
			else
			{
				printf("O");
			}
		}
		printf("|\n");
	}
	for(i = 0; i < mazeSize + 2; i = i + 1)
	{
	printf("-");
	}
	printf("\n");
}
int Main::nonblockInput()
{
	int t = 0;
	if (kbhit())
	{
		t = getch();
	}
	else
	{
		t = -1;
	}
	return t;
}
void Main::parseInputs()
{
	if (key == KEY_LOWER_W || key == KEY_UPPER_W)
	{
		if (y != 0)
		{
			y--;
			angle = 3;
		}
	}
	else if (key == 115 || key == 83)
	{
		if (y != mazeSize - 1)
		{
			y++;
			angle = 1;
		}
	}
	else if (key == 97 || key == 65)
	{
		if (x != 0)
		{
			x--;
			angle = 2;
		}
	}
	else if (key == 100 || key == 68)
	{
		if (x != mazeSize - 1)
		{
			x++;
			angle = 0;
		}
	}
	else if (key == 111 || key == 79)
	{
		if (mainClass.angle == 0)
		{
			mainClass.attackX = mainClass.x + 1;
			mainClass.attackY = mainClass.y;
		}
		else if (mainClass.angle == 1)
		{
			mainClass.attackX = mainClass.x;
			mainClass.attackY = mainClass.y + 1;
		}
		else if (mainClass.angle == 2)
		{
			mainClass.attackX = mainClass.x - 1;
			mainClass.attackY = mainClass.y;
		}
		else
		{	mainClass.attackX = mainClass.x;
			mainClass.attackY = mainClass.y - 1;
		}
	}
}

int main()
{
	Main mainClass;
	mainClass.mazeSize = 20;
	int key;
	mainClass.x = 0;
	mainClass.y = 0;
	mainClass.ex = mainClass.mazeSize - 1;
	mainClass.ey = mainClass.mazeSize - 1;
	mainClass.movementCountdown = 0;
	mainClass.attackCountdown = 0;
	mainClass.angle = 0;
	mainClass.attackX = -1;
	mainClass.attackY = -1;
	mainClass.killedEnemy = false;
	clrscr();
	mainClass.render(); //x, y, ex, ey, attackX, attackY, mazeSize
	bool enemyMoved = false;
	int rx, ry;
	do
	{
		mainClass.key = mainClass.nonblockInput();
		mainClass.movementCountdown = mainClass.movementCountdown + 1;
		if (mainClass.attackX != -1 || mainClass.attackY != -1)
		{
			//mainClass.attackCountdown = mainClass.attackCountdown + 1;
			mainClass.attackCountdown++;
		}
		if (mainClass.attackCountdown >= 500)
		{
			mainClass.attackX = -1;
			mainClass.attackY = -1;
			mainClass.attackCountdown = 0;
		}
		if (mainClass.movementCountdown == 10000)
		{
			enemyMoved = false;
			rx = (rand() % 3) - 1;
			ry = (rand() % 3) - 1;
			if (rx == -1 && mainClass.ex != 0)
			{
				mainClass.ex = mainClass.ex - 1;
				enemyMoved = true;
			}
			if (rx == 1 && mainClass.ex != mainClass.mazeSize - 1)
			{
				mainClass.ex = mainClass.ex + 1;
				enemyMoved = true;
			}
			if (ry == -1 && mainClass.ey != 0)
			{
				mainClass.ey = mainClass.ey - 1;
				enemyMoved = true;
			}
			if (ry == 1 && mainClass.ey != mainClass.mazeSize - 1)
			{
				mainClass.ey = mainClass.ey + 1;
				enemyMoved = true;
			}
			mainClass.movementCountdown = 0;
		}
		if (mainClass.key != -1 || enemyMoved)
		{
			clrscr();
			mainClass.render();
		}
		if (mainClass.attackX == mainClass.ex && mainClass.attackY == mainClass.ey)
		{
			clrscr();
			printf("\n\n\n      You did it!");
			printf(" ");
			clrscr();
			mainClass.killedEnemy = true;
			mainClass.key = 27;
		}
	} while(mainClass.key != 27);
	clrscr();
	if (mainClass.killedEnemy)
	{
		printf("Congrats, you have killed the evil enemy!\n");
	}
	return 0;
}
