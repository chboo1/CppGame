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
#define KEY_LOWER_O 111
#define KEY_UPPER_O 79


class Main
{
	public:
		int mazeSize;
		int key;
		int x;
		int y;
		//ex stands for enemy x and ey stands for enemy y
		int ex;
		int ey;
		//rx stands for random x (random direction enemy will go on the X axis) and ry stands for random y (same thing but on Y axis)
		int rx;
		int ry;
		int movementCountdown;
		int attackCountdown;
		bool attacking = false;
		int angle;
		int attackX;
		int attackY;
		bool killedEnemy;
		bool AIMoved = false;
		bool PlayerMoved = false;
		void render();
		int nonblockInput();
		void parseInputs();
		void moveAI();
		Main()
		{
			printf("Hello there");
			mazeSize = 20;
			x = 0;
			y = 0;
			ex = mazeSize - 1;
			ey = mazeSize - 1;
			movementCountdown = 100000;
			attackCountdown = 0;
			angle = 0;
			attackX = -1;
			attackY = -1;
			killedEnemy = false;
			clrscr();
			render();
			do
			{
				AIMoved = false;
				PlayerMoved = false;
				key = nonblockInput();
				parseInputs();
				movementCountdown--;
				if (movementCountdown == 0)
				{
					moveAI();
					movementCountdown = 100000;
				}
				if (AIMoved == true || PlayerMoved == true)
				{
					clrscr();
					render();
				}
				if (attackX == ex && attackY == ey)
				{
					key = 27;
					killedEnemy = true;
				}
				if (attackCountdown != 0)
				{
					attackCountdown--;
				}
				if (attackCountdown == 0 && attacking == true)
				{
					attacking = false;
					attackX = -1;
					attackY = -1;
					clrscr();
					render();
				}
			}while (key != 27);
			if (killedEnemy)
			{
				printf("Good job, you killed the evil enemy!");
			}

		}
};


void Main::render() //int playerx, int playery, int enemyx, int enemyy, int attackX, int attackY, int mazeSize
{
	int i;
	int j;
	std::cout << std::string(mazeSize + 2, '-') << '\n';
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
	std::cout << std::string(mazeSize + 2, '-') << '\n';
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
			PlayerMoved = true;
		}
	}
	else if (key == KEY_LOWER_S || key == KEY_UPPER_S)
	{
		if (y != mazeSize - 1)
		{
			y++;
			angle = 1;
			PlayerMoved = true;
		}
	}
	else if (key == KEY_LOWER_A || key == KEY_UPPER_A)
	{
		if (x != 0)
		{
			x--;
			angle = 2;
			PlayerMoved = true;
		}
	}
	else if (key == KEY_LOWER_D || key == KEY_UPPER_D)
	{
		if (x != mazeSize - 1)
		{
			x++;
			angle = 0;
			PlayerMoved = true;
		}
	}
	else if (key == KEY_LOWER_O || key == KEY_UPPER_O)
	{
		PlayerMoved = true;
		attacking = true;
		attackCountdown = 1000;
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
	else
	{
		PlayerMoved = false;
	}
}


void Main::moveAI()
{
	rx = rand() % 3;
	ry = rand() % 3;
	rx--;
	ry--;
	if (rx + ex > 0 && rx + ex < mazeSize - 1)
	{
		ex = ex + rx;
		AIMoved = true;
	}
	else if (ry + ey > 0 && ry + ey < mazeSize - 1)
	{
		ey = ey + ry;
		AIMoved = true;
	}
	else
	{
		AIMoved = false;
	}
}

int main()
{
	Main mainClass;
		return 0;
}
