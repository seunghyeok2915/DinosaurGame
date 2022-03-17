#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

#define DINO_BOTTOM_Y 12
#define TREE_BOTTOM_X 45
#define TREE_BOTTOM_Y 20
#define BIRD_BOTTOM_X 45
#define BIRD_BOTTOM_Y 10
#define BULLET_BOTTOM_DOWN_X 5
#define BULLET_BOTTOM_DOWN_Y 23
#define BULLET_BOTTOM_UP_X 5
#define BULLET_BOTTOM_UP_Y 10

void gotoXY(int x, int y)
{
	HANDLE hOut;
	COORD Cur;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Cur.X = x * 2;
	Cur.Y = y;
	SetConsoleCursorPosition(hOut, Cur);
}

	void clrscr()
	{
		system("cls");
	}

/*
"        $$$$$$$ "
"       $$ $$$$$$"
"       $$$$$$$$$"
"$      $$$      "
"$$     $$$$$$$  "
"$$$   $$$$$     "
" $$  $$$$$$$$$$ "
" $$$$$$$$$$$    "
"  $$$$$$$$$$    "
"    $$$$$$$$    "
"     $$$$$$     "
"     $    $$$   "
"     $$         "

"        $$$$$$$ "
"       $$ $$$$$$"
"       $$$$$$$$$"
"$      $$$      "
"$$     $$$$$$$  "
"$$$   $$$$$     "
" $$  $$$$$$$$$$ "
" $$$$$$$$$$$    "
"  $$$$$$$$$$    "
"    $$$$$$$$    "
"     $$$$$$     "
"     $$$  $     "
"          $$    "
*/


void setConsoleView()
{
	system("mode con:cols=100 lines=25");
	system("title 공룡 게임");
}

bool legFlag = false;
void drawDino(int dinoY)
{
	gotoXY(0, dinoY);

	cout << "        $$$$$$$ " << endl;
	cout << "       $$ $$$$$$" << endl;
	cout << "       $$$$$$$$$" << endl;
	cout << "$      $$$      " << endl;
	cout << "$$     $$$$$$$  " << endl;
	cout << "$$$   $$$$$     " << endl;
	cout << " $$  $$$$$$$$$$ " << endl;
	cout << " $$$$$$$$$$$    " << endl;
	cout << "  $$$$$$$$$$    " << endl;
	cout << "    $$$$$$$$    " << endl;
	cout << "     $$$$$$     " << endl;

	if (legFlag)
	{
		cout << "     $    $$$   " << endl;
		cout << "     $$         ";
	}
	else
	{
		cout << "     $$$  $     " << endl;
		cout << "          $$    ";
	}

	legFlag = !legFlag;
}

void drawTree(int treeX)
{
	gotoXY(treeX, TREE_BOTTOM_Y);
	cout << "$$$$";
	gotoXY(treeX, TREE_BOTTOM_Y + 1);
	cout << " $$ ";
	gotoXY(treeX, TREE_BOTTOM_Y + 2);
	cout << " $$ ";
	gotoXY(treeX, TREE_BOTTOM_Y + 3);
	cout << " $$ ";
	gotoXY(treeX, TREE_BOTTOM_Y + 4);
	cout << " $$ ";
}

void drawBird(int BirdX)
{
	gotoXY(BirdX, BIRD_BOTTOM_Y);
	cout << " $$$";
	gotoXY(BirdX, BIRD_BOTTOM_Y + 1);
	cout << "$$ ";

}

void drawBulletDown(int bulletX)
{
	gotoXY(bulletX, BULLET_BOTTOM_DOWN_Y);
	cout << "====>";
}

void drawBulletUp(int bulletX)
{
	gotoXY(bulletX, BULLET_BOTTOM_UP_Y);
	cout << "====>";
}

int getKeyDown()
{
	if (_kbhit() != 0)
	{
		return _getch();
	}

	return 0;
}

int main(void)
{
	bool isJumping = false;
	bool isBottom = true;
	bool isBulletDown = false;
	bool isBulletUp = false;
	bool isOver = false;
	const int gravity = 3;

	int score = 0;

	int dinoY = DINO_BOTTOM_Y;
	int treeX = TREE_BOTTOM_X;
	int birdX = BIRD_BOTTOM_X;
	int birdY = BIRD_BOTTOM_Y;
	int bulletDownX = BULLET_BOTTOM_DOWN_X;
	int bulletUpX = BULLET_BOTTOM_UP_X;

	setConsoleView();

	while (true)
	{
		int temp = getKeyDown();
		if (temp == 'j' && isBottom)
		{
			isJumping = true;
			isBottom = false;
		}
		else if (temp == 'a' && !isJumping && !isBulletDown)
		{
			isBulletDown = true;
		}
		else if (temp == 'u' && !isJumping && !isBulletUp)
		{
			isBulletUp = true;
		}
		else if (temp == 'r')
		{
			isOver = false;
			dinoY = DINO_BOTTOM_Y;
			treeX = TREE_BOTTOM_X;
			bulletDownX = BULLET_BOTTOM_DOWN_X;
			score = 0;
		}

		if (isJumping)
		{
			dinoY -= gravity;
		}
		else
		{
			dinoY += gravity;
		}

		if (dinoY >= DINO_BOTTOM_Y)
		{
			dinoY = DINO_BOTTOM_Y;
			isBottom = true;
		}
		else if (dinoY <= 4)
		{
			isJumping = false;
		}

		if (isBulletDown)
		{
			bulletDownX += 1;
			if (bulletDownX >= 45)
			{
				bulletDownX = BULLET_BOTTOM_DOWN_X;
				isBulletDown = false;
			}
			if (bulletDownX == treeX || bulletDownX == treeX + 1 || bulletDownX == treeX + 2)
			{
				score++;
				treeX = TREE_BOTTOM_X;
				bulletDownX = BULLET_BOTTOM_DOWN_X;
				isBulletDown = false;
			}
			drawBulletDown(bulletDownX);
		}

		if (isBulletUp)
		{
			bulletUpX += 1;
			if (bulletUpX >= 45)
			{
				bulletUpX = BULLET_BOTTOM_UP_X;
				isBulletUp = false;
			}
			if (bulletUpX == birdX || bulletUpX == birdX + 1 || bulletUpX == birdX + 2)
			{
				score+=2;
				birdX = BIRD_BOTTOM_X;
				bulletUpX = BULLET_BOTTOM_UP_X;
				isBulletUp = false;
			}
			drawBulletUp(bulletUpX);
		}


		treeX -= 2;
		if (treeX <= 0)
		{
			treeX = TREE_BOTTOM_X;
		}

		birdX--;
		if (birdX <= 0)
		{
			birdX = BIRD_BOTTOM_X;
		}

		if (treeX <= 3 && dinoY > 9)
		{
			isOver = true;
		}

		if (!isOver)
		{
			drawDino(dinoY);
			drawTree(treeX);
			drawBird(birdX);
		}
		else
		{
			clrscr();
			gotoXY(10, 10);
			cout << "GameOver";
		}
		gotoXY(1, 1);
		cout << "Score : " << score;

		Sleep(80);
		clrscr();
	}

	return 0;
}
