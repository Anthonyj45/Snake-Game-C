#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>

//Constant Declarations
const int width = 40;
const int height = 20;

//Prototypes Declarations
void printBoard(struct mySnake snake, int fruitX, int fruitY);
void generateFruit(struct mySnake *snake, int* fruitX, int* fruitY);
int getInput(void);
void moveSnake(struct mySnake* snake);
int checkCollision(struct mySnake snake);
void updateSnakeBody(struct mySnake* snake);
void increaseSnakeLength(struct mySnake* snake);

/*
* A struct to declare the most important aspects
* of the Snake that will necessary to play
* this game
*/

struct mySnake
{
	int headX;
	int headY;
	int length;
	int direction;
	int bodyX[50];
	int bodyY[50];
};

int main(void)
{
	struct mySnake snake = { width / 2, height / 2, 1, 0, {0}, {0} };
	int fruitX = 0;
	int fruitY = 0;
	int gameOver = 0;

	while (!gameOver)
	{
		printBoard(snake, fruitX, fruitY);

		if (snake.headX == fruitX && snake.headY == fruitY)
		{
			increaseSnakeLength(&snake);
			generateFruit(&snake, &fruitX, &fruitY);
		}

		int direction = getInput();
		if (direction)
		{
			snake.direction = direction;
		}

		//Calling of Functions to Move, confirm and Update Snake status
		moveSnake(&snake);
		gameOver = checkCollision(snake);
		updateSnakeBody(&snake);

		//This function will give a delay to the system according the time given.
		Sleep(100);

		if (_kbhit())
		{
			char key = _getch();
			if (key == 'q' || key == 'Q')
			{
				gameOver = 1;
			}
		}
	}
	
	return 0;
}

/*
* PrintBoard function will take three parameters and will create a Board
* Where the player will play the Snake Game. Also it will create the
* Snake's body
*/

void printBoard(struct mySnake snake, int fruitX, int fruitY)
{
	system("cls");

	for (int counter = 0; counter < height; counter++)
	{
		for (int sCounter = 0; sCounter < width; sCounter++)
		{
			int isBodyPart = 0;

			for (int i = 0; i < snake.length; i++)
			{
				if (snake.bodyX[i] == sCounter && snake.bodyY[i] == counter)
				{
					printf("o");
					isBodyPart = 1;
				}
			}

			if (!isBodyPart)
			{
				if (counter == 0 || counter == height - 1 || sCounter == 0 || sCounter == width - 1)
				{
					printf("#");
				}
				else if (counter == snake.headY && sCounter == snake.headX)
				{
					printf("O");
				}
				else if (counter == fruitY && sCounter == fruitX)
				{
					printf("*");
				}
				else
				{
					printf(" ");
				}
			}
		}
		printf("\n");
	}
}

/*
* This function will generate a fruit randomnly that will be eaten by
* the snake
*/

//ALERT:
/*
* This function has a serious problem that generate the fruit but it
* doesn't stop until the fruit appears in the same place of the Snake.
*/

void generateFruit(struct mySnake *snake, int* fruitX, int* fruitY)
{
	int collision = 0;

	do
	{
		collision = 0;

		*fruitX = rand() % (width - 2) + 1;
		*fruitY = rand() % (height - 2) + 1;

		if (*fruitX == snake->headX && *fruitY == snake->headY)
		{
			collision = 1;
			continue;
		}

		for (int counter = 0; counter < snake->length; counter++)
		{
			if (*fruitX == snake->bodyX[counter] && *fruitY == snake->bodyY[counter])
			{
				collision = 1;
				break;
			}
		}

	} while (collision);
}

/*
* getInput is needed to get the movement of Snake using wasd standard control
* It will also return a specific number that will be stored in a variable and
* will modify the place of the Snake
*/

int getInput(void)
{
	int key = 0;

	if (_kbhit())
	{
		char move = _getch();
		switch (move)
		{
		case 'w':
			key = 1;
			break;
		case 's':
			key = 2;
			break;
		case 'a':
			key = 3;
			break;
		case 'd':
			key = 4;
			break;
		}
	}

	return key;
}

/*
* After receive the Input from the User. The Snake
* will be moved, adding or removing a place according
* to wich the user press
*/

void moveSnake(struct mySnake* snake)
{
	switch (snake->direction)
	{
	case 1:
		snake->headY--;
		break;
	case 2:
		snake->headY++;
		break;
	case 3:
		snake->headX--;
		break;
	case 4:
		snake->headX++;
		break;
	}
}

/*
* It is necessary to use this function to check the colition with the Wall.
* If the snake collides with the Wall, is Game Over
*/

int checkCollision(struct mySnake snake)
{
	if (snake.headX == 0 || snake.headX == width - 1 || snake.headY == 0 || snake.headY == height - 1)
	{
		return 1;
	}

	for (int counter = 0; counter < snake.length; counter++)
	{
		if (snake.headX == snake.bodyX[counter] && snake.headY == snake.bodyY[counter])
		{
			return 1;
		}
	}

	return 0;
}

/*
* The updateSnakeBody is responsible to do that, update the Snake
* and adding more body each time the snake eat the fruit
*/

void updateSnakeBody(struct mySnake* snake)
{
	for (int counter = snake->length - 1; counter > 0; counter--)
	{
		snake->bodyX[counter] = snake->bodyX[counter - 1];
		snake->bodyY[counter] = snake->bodyY[counter - 1];
	}
	snake->bodyX[0] = snake->headX;
	snake->bodyY[0] = snake->headY;
}

/*
* While more you eat, bigger you will be
*/

void increaseSnakeLength(struct mySnake* snake)
{
	snake->length++;
}