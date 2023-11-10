#include <conio.h>
#include <iostream>
#include <windows.h>
using namespace std;
const int width = 80;
const int height = 20;
int x, y;
int fruitCordX, fruitCordY;
int playerScore;
int snakeTailX[100], snakeTailY[100];
int snakeTailLen;
enum snakesDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
snakesDirection sDir;
bool isGameOver;
void GameInit()
{
	isGameOver = false;
	sDir = STOP;
	x = width / 2;
	y = height / 2;
	fruitCordX = rand() % width;
	fruitCordY = rand() % height;
	playerScore = 0;
}
void GameRender(string playerName)
{
	system("cls");
	for (int i = 0; i < width + 2; i++)
		cout << "-";
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j <= width; j++) {
			if (j == 0 || j == width)
				cout << "|";
			// Creating snake's head with 'O'
			if (i == y && j == x)
				cout << "O";
			// Creating the sanke's food with '$'
			else if (i == fruitCordY && j == fruitCordX)
				cout << "$";
			// Creating snake's head with 'O'
			else {
				bool prTail = false;
				for (int k = 0; k < snakeTailLen; k++) {
					if (snakeTailX[k] == j
						&& snakeTailY[k] == i) {
						cout << "o";
						prTail = true;
					}
				}
				if (!prTail)
					cout << " ";
			}
		}
		cout << endl;
	}

	// Creating bottom walls with '-'
	for (int i = 0; i < width + 2; i++)
		cout << "-";
	cout << endl;

	// Display player's score
	cout << playerName << "'s Score: " << playerScore
		<< endl;
}
void UpdateGame()
{
	int prevX = snakeTailX[0];
	int prevY = snakeTailY[0];
	int prev2X, prev2Y;
	snakeTailX[0] = x;
	snakeTailY[0] = y;

	for (int i = 1; i < snakeTailLen; i++) {
		prev2X = snakeTailX[i];
		prev2Y = snakeTailY[i];
		snakeTailX[i] = prevX;
		snakeTailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (sDir) {
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
	if (x >= width || x < 0 || y >= height || y < 0)
		isGameOver = true;
	for (int i = 0; i < snakeTailLen; i++) {
		if (snakeTailX[i] == x && snakeTailY[i] == y)
			isGameOver = true;
	}

	// Checks for snake's collision with the food (#)
	if (x == fruitCordX && y == fruitCordY) {
		playerScore += 10;
		fruitCordX = rand() % width;
		fruitCordY = rand() % height;
		snakeTailLen++;
	}
}
int SetDifficulty()
{
	int dfc, choice;
	cout << "\nSET DIFFICULTY\n1: Easy\n2: Medium\n3: hard "
			"\nNOTE: if not chosen or pressed any other "
			"key, the difficulty will be automatically set "
			"to medium\nChoose difficulty level: ";
	cin >> choice;
	switch (choice) {
	case '1':
		dfc = 50;
		break;
	case '2':
		dfc = 100;
		break;
	case '3':
		dfc = 150;
		break;
	default:
		dfc = 100;
	}
	return dfc;
}
void UserInput()
{
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			sDir = LEFT;
			break;
		case 'd':
			sDir = RIGHT;
			break;
		case 'w':
			sDir = UP;
			break;
		case 's':
			sDir = DOWN;
			break;
		case 'x':
			isGameOver = true;
			break;
		}
	}
}

int main()
{
	string playerName;
	cout << "enter your name: ";
	cin >> playerName;
	int dfc = SetDifficulty();

	GameInit();
	while (!isGameOver) {
		GameRender(playerName);
		UserInput();
		UpdateGame();
	        Sleep(dfc);
	}

	return 0;
}
