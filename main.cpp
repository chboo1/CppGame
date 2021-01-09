#include <stdio.h>
#include <conio.h>
#include <cstdlib>


void render(int playerx, int playery, int enemyx, int enemyy, int attackX, int attackY, int mazeSize)
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
			if ((i != playery || j != playerx) && (i != enemyy || j != enemyx) && (i != attackY || j != attackX))
			{
				printf(" ");
			}
			else if (i == playery && j == playerx)
			{
				printf("+");
			}
			else if (i == enemyy && j == enemyx)
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
int nonblockInput()
{
	int x = 0;
	if (kbhit())
	{
		x = getch();
	}
	else
	{
		x = -1;
	}
	return x;
}

int main()
{
	int mazeSize = 20;
	int key;
	int x = 0;
	int y = 0;
	int ex = mazeSize - 1;
	int ey = mazeSize - 1;
	int rx;
	int ry;
	int movementCountdown = 0;
	int attackCountdown = 0;
	int angle = 0;
	int attackX = -1;
	int attackY = -1;
	bool killedEnemy = false;
	clrscr();
	render(x, y, ex, ey, attackX, attackY, mazeSize);
	do
	{
		key = nonblockInput();
		//key = getch();
		if (key == 119 || key == 87)
		{
			if (y != 0)
			{
				y = y - 1;
				angle = 3;
			}
		}
		else if (key == 115 || key == 83)
		{
			if (y != mazeSize - 1)
			{
				y = y + 1;
				angle=1;
			}
		}
		else if (key == 97 || key == 65)
		{
			if (x != 0)
			{
				x = x - 1;
				angle = 2;
			}
		}
		else if (key == 100 || key == 68)
		{
			if (x != mazeSize - 1)
			{
				x = x + 1;
				angle = 0;
			}
		}
		else if (key == 111 || key == 79)
		{
			if (angle == 0)
			{
				attackX = x + 1;
				attackY = y;
			}
			else if (angle == 1)
			{
				attackX = x;
				attackY = y + 1;
			}
			else if (angle == 2)
			{
				attackX = x - 1;
				attackY = y;
			}
			else
			{	attackX = x;
				attackY = y - 1;
			}
		}
		movementCountdown = movementCountdown + 1;
		if (attackX != -1 || attackY != -1)
		{
		attackCountdown = attackCountdown + 1;
		}
		if (attackCountdown >= 500)
		{
			attackX = -1;
			attackY = -1;
			attackCountdown = 0;
		}
		if (movementCountdown == 10000)
		{
			rx = (rand() % 3) - 1;
			ry = (rand() % 3) - 1;
			if (rx == -1 && ex != 0)
			{
				ex = ex - 1;
			}
			if (rx == 1 && ex != mazeSize - 1)
			{
				ex = ex + 1;
			}
			if (ry == -1 && ey != 0)
			{
				ey = ey - 1;
			}
			if (ry == 1 && ey != mazeSize - 1)
			{
				ey = ey + 1;
			}
			movementCountdown = 0;
		}
		if (key != -1 || rx == -1 || rx == 1 || ry == -1 || ry == 1)
		{
		clrscr();
		render(x, y, ex, ey, attackX, attackY, mazeSize);
		if (key == -1)
		{
			rx = 0;
			ry = 0;
		}
		}
		//sleep(1);
		if (attackX == ex && attackY == ey)
		{
			clrscr();
			printf("\n\n\n      You did it!");
			printf(" ");
			sleep(3);
			clrscr();
			killedEnemy = true;
			key = 27;
		}
	} while(key != 27);
	clrscr();
	if (killedEnemy)
	{
		printf("Bonne Fete Papa!\n");
		printf("J'espere que ce petit jeu t'a plu.\n");
		printf("Mais surtout, Bonne fete!\n");
	}
	return 0;
}
