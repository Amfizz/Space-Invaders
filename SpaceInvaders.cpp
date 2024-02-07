#include <iostream>
#include "mygraphics.h"
#include "myconsole.h"
#include<fstream>

using namespace std;



void PlayerMovement(char input);
void Border();
void Fire();
void alien();
void SingleAlien(int enemyID);
void MovementControll();
void Player();
void Game();
void alienCollision();
void Playerlives();
void PlayerScore();
void highscore();
void UI();
bool checkWin();
bool flag = true;

char score[] = "Score: ";
char lives[] = "Lives = ";
char high[] = "HighScore";

int playerLivesCounter = 3;
int enemyDeadCount = 0;

char userInput;

// Title

char Title[] = "Space Invaders";

// Dimensions
int WinX = 960;
int WinY = 490;

// Player Dimensions
struct Player {
	int x1;
	int y1;
	int x2;
	int y2;

	int speed;
}player;

struct alien {

	int x1;
	int x2;
	int y1;
	int y2;

	bool isAlive = true;

	COLORREF color = RGB(255, 0, 0);
	COLORREF blue = RGB(0, 0, 255);



}enemy[50];

struct PlayerScore
{
	int X1;
	int Y1;
	int X2;
	int Y2;

}pscore;

// Grid MoveMent
float horizontalMoveMent = 0;
int verticalMovement = 0;
int mspeed = 2;

bool isHit = false;

COLORREF black = RGB(0, 0, 0);

int enemystartpoint = 30;
void PlayerMovement(char input)
{

	if (player.x1 >= 31)
	{
		if (input == LEFTKEY) // A
		{
			player.x1 -= player.speed; // player.x1 = player.x1 - player.speed;
			player.x2 -= player.speed;
		}
	}

	if (player.x2 <= 920)
	{
		if (input == RIGHTKEY) // D
		{
			player.x1 += player.speed;
			player.x2 += player.speed;
		}
	}
	if (player.y2 <= 460)
	{
		if (input == DOWNKEY) // S
		{
			player.y1 += player.speed;
			player.y2 += player.speed;
		}
	}
	if (input == UPKEY) // W
	{
		player.y1 -= player.speed;
		player.y2 -= player.speed;
	}
	else if (input == 32)
	{
		Fire();
	}

	// pause
	else if (input == 'P')
	{
		while (true)
		{
			char Str[] = " Game Paused ";
			myDrawTextWithFont(280, 200, 40, Str, RGB(255, 100, 10), black);
			userInput = CheckKeyPressed();
			if (userInput == 'P')
			{
				break;
			}

		}
	}

	Player();

}


void Border() {
	myRect(0, 0, 960, 480, RGB(200, 200, 55), black);
	//myLine(0,400,960,400, RGB(255,255,0));
}


void Fire()
{
	int p1 = player.y1 + 10;
	int p2 = player.y2 - 10;
	int p3 = player.x1 + 30;




	while (p1 > 0 && (!isHit))
	{
		p1 -= 10;
		p2 -= 10;
		myLine(player.x1 + 20, p1, player.x2 - 20, p2, RGB(255, 255, 255));

		Sleep(10);
		Border();
		alien();
		UI();
		Player();

		// Bullet Collision
		for (int i = 0; i < 50; i++)
		{

			if ((p3 <= enemy[i].x2 + 15) && (p3 >= enemy[i].x1 - 5) && (p1 == enemy[i].y1))
			{
				isHit = false;

				if (enemy[i].isAlive == true)
				{
					enemy[i].color = RGB(0, 0, 0);
					enemy[i].blue = RGB(0, 0, 0);
					enemy[i].isAlive = false;
					enemyDeadCount++;
					isHit = true;
					Beep(100, 400);
				}


				break;
			}
		}

		Sleep(10);
		MovementControll();
	}


}
void alien() // Alien Grid
{
	for (int i = 0; i < 50; i++)
	{
		SingleAlien(i);
	}
}


void SingleAlien(int enemyID)
{

	if (enemyID < 10)
	{
		enemy[enemyID].x1 = (40 + (60 * enemyID)) + horizontalMoveMent;
		enemy[enemyID].x2 = (70 + (60 * enemyID)) + horizontalMoveMent;
		enemy[enemyID].y1 = 40 + verticalMovement;
		enemy[enemyID].y2 = 70 + verticalMovement;
	}
	else if (enemyID < 20)
	{
		enemy[enemyID].x1 = 40 + (60 * (enemyID - 10)) + horizontalMoveMent;
		enemy[enemyID].x2 = 70 + (60 * (enemyID - 10)) + horizontalMoveMent;
		enemy[enemyID].y1 = 110 + verticalMovement;
		enemy[enemyID].y2 = 140 + verticalMovement;
	}
	else if (enemyID < 30)
	{
		enemy[enemyID].x1 = 40 + (60 * (enemyID - 20)) + horizontalMoveMent;
		enemy[enemyID].x2 = 70 + (60 * (enemyID - 20)) + horizontalMoveMent;
		enemy[enemyID].y1 = 180 + verticalMovement;
		enemy[enemyID].y2 = 210 + verticalMovement;
	}
	else if (enemyID < 40)
	{
		enemy[enemyID].x1 = 40 + (60 * (enemyID - 30)) + horizontalMoveMent;
		enemy[enemyID].x2 = 70 + (60 * (enemyID - 30)) + horizontalMoveMent;
		enemy[enemyID].y1 = 250 + verticalMovement;
		enemy[enemyID].y2 = 280 + verticalMovement;
	}
	else if (enemyID < 50)
	{
		enemy[enemyID].x1 = 40 + (60 * (enemyID - 40)) + horizontalMoveMent;
		enemy[enemyID].x2 = 70 + (60 * (enemyID - 40)) + horizontalMoveMent;
		enemy[enemyID].y1 = 320 + verticalMovement;
		enemy[enemyID].y2 = 350 + verticalMovement;
	}

	// alien
	myRect(enemy[enemyID].x1, enemy[enemyID].y1, enemy[enemyID].x2, enemy[enemyID].y2, enemy[enemyID].color, black);
	myEllipse(enemy[enemyID].x1, enemy[enemyID].y1, enemy[enemyID].x2, enemy[enemyID].y2 - 10, enemy[enemyID].blue, black);

}

void MovementControll()  // EnemyMoveMent Control
{

	if (enemy[9].x2 >= 950)
	{
		verticalMovement += 20;
		mspeed = -1;
	}
	else if (enemy[0].x1 <= 10)
	{
		verticalMovement += 20;
		mspeed = 1;
	}
	horizontalMoveMent += mspeed;


}


bool checkWin()

{

	bool Won = false;
	for (int i = 0; i < 49; i++)
	{
		if (enemy[i].isAlive == false && enemy[i + 1].isAlive == false)
		{
			Won = true;


		}
		else
		{
			Won = false;
			break;
		}
	}

	return Won;
}
void Player()
{
	/*
	player.x1 = 450;
	player.y1 = 410;
	player.x2 = 510;
	player.y2 = 470;*/

	myEllipse(player.x1 + 10, player.y1 + 10, player.x2 - 10, player.y2, RGB(255, 255, 255), RGB(225, 255, 225));

	myRect(player.x1 - 10, player.y1 + 25, player.x2 + 10, player.y2, RGB(0, 255, 0), RGB(0, 255, 0));


}

void alienCollision() // Aien Collision
{
	char DeadStr[] = " You Dead";

	for (int i = 0; i < 50; i++)
	{
		if ((enemy[i].x1 - 25 <= player.x1 && enemy[i].y2 >= player.y1 && enemy[i].x2 - 25 >= player.x1) && (enemy[i].isAlive == true))
		{
			Beep(400, 400);
			while (playerLivesCounter == 1)
			{
				Border();
				myDrawTextWithFont(380, 150, 50, DeadStr, RGB(255, 255, 0), black);


			}
			--playerLivesCounter;
			player.x1 = 450;
			player.y1 = 400;
			player.x2 = 490;
			player.y2 = 450;

		}

		else if ((enemy[i].y2 >= 400) && (enemy[i].isAlive == true)) // if Alien Reaches to End
		{
			while (true)
			{
				Border();
				myDrawTextWithFont(380, 150, 50, DeadStr, RGB(255, 255, 0), black);

			}
		}

	}
}


void Playerlives()
{
	if (playerLivesCounter == 3)
	{

		PlaceCursor(6, 1);
		cout << playerLivesCounter;
	}
	else if (playerLivesCounter == 2)
	{
		PlaceCursor(6, 1);
		cout << playerLivesCounter;
	}
	else if (playerLivesCounter == 1)
	{
		PlaceCursor(6, 1);
		cout << playerLivesCounter;
	}
}
void PlayerScore()
{
	int hscore = 0;
	int score = 0;
	int line;

	for (int i = 0; i <= enemyDeadCount; i++)
	{
		PlaceCursor(6, 0);
		cout << score;
		score += 100;

	}
	hscore = score - 100;
	std::ifstream input("Score.txt");
	int bestscore;
	input >> bestscore;
	std::ofstream myfile;

	myfile.open("Score.txt");
	if (hscore > bestscore) {
		myfile << hscore;
	}
	else {
		myfile << bestscore;
	}
	myfile.close();



}

void highscore()
{




}

void UI() {

	myDrawText(1, 1, 60, score, RGB(2, 255, 0), black);
	myDrawText(1, 20, 60, lives, RGB(255, 0, 0), black);


	PlayerScore();
	Playerlives();

}

void Game()
{
	userInput = CheckKeyPressed();
	Border();
	alien();
	UI();
	Player();
	PlayerMovement(userInput);
	MovementControll();

	// enemy Grid
	isHit = false;

	if (checkWin())
	{
		Border();
		char WinStr[] = "You Won";
		myDrawTextWithFont(380, 150, 50, WinStr, RGB(255, 255, 0), black);
		while (true)
		{

		}
	}
	alienCollision();
}

// ================================================================       Main         ====================================================================================================
int main()
{



	SetWindowTitle(Title);
	GetWindowDimensions(WinX, WinY);
	SetWindowSize(WinX, WinY);



	// Player
	player.x1 = 450;
	player.y1 = 400;
	player.x2 = 490;
	player.y2 = 450;
	player.speed = 30;

	// Score
	pscore.X1 = 50;
	pscore.Y1 = 5;
	pscore.X2 = 60;
	pscore.Y2 = 15;






	while (true)
	{
		char startStr[] = "Press AnY Key To Continue )";
		char name[] = "SPACE INVADERS BY ESSA AND FIZA";
		myDrawTextWithFont(280, 200, 40, startStr, RGB(255, 255, 10), black);
		myDrawTextWithFont(245, 100, 40, name, RGB(0, 255, 0), black);

		if (CheckKeyPressed())
		{
			break;
		}

	}
	// Spawn Player

	//Player();

	while (true && flag)
	{
		std::ifstream input("Score.txt");
		int read;
		input >> read;

		PlaceCursor(60, 0);
		cout << read;

		Game();
		myDrawText(525, 1, 60, high, RGB(2, 255, 0), black);
	}
}