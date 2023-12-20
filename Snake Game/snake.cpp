#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

//Constant Declarations
const int width = 40;
const int height = 20;
const int body_length = 50;

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
	int bodyX[body_length];
	int bodyY[body_length];
};

struct myFruit
{
	int positionX;
	int positionY;
};

//Prototypes Declarations
void print_board(struct mySnake snake, int fruitX, int fruitY);
void generate_fruit(struct mySnake* snake, int* fruitX, int* fruitY);
int get_input(void);
void move_snake(struct mySnake* snake);
int check_collision(struct mySnake snake);
void increase_snake_length(struct mySnake* snake);

/*ALERT:
* The code is not displaying the tail properly. So it is necessary make
* some modifications to make the tail follow the head of the Snake.
*/

int main(void)
{
	struct mySnake snake = { width / 2, height / 2, 1, 0, {0}, {0} };
	struct myFruit fruit = { 0, 0 };

	int game_over = 0;

	generate_fruit(&snake, &fruit.positionX, &fruit.positionY);

	while (!game_over)
	{

		if (snake.headX == fruit.positionX && snake.headY == fruit.positionY)
		{
			increase_snake_length(&snake);
			generate_fruit(&snake, &fruit.positionX, &fruit.positionY);
		}

		move_snake(&snake);

		print_board(snake, fruit.positionX, fruit.positionY);

		int direction = get_input();
		if (direction)
		{
			snake.direction = direction;
		}

		game_over = check_collision(snake);

		Sleep(100);
	}

	return 0;
}

/*
* Print_board function will take three parameters and will create a Board
* Where the player will play the Snake Game. Also it will create the
* Snake's body
*/

void print_board(struct mySnake snake, int fruitX, int fruitY)
{
	system("cls");

	for (int counter = 0; counter < height; counter++)
	{
		for (int sCounter = 0; sCounter < width; sCounter++)
		{
			int isBodyPart = 0;

			if (counter == snake.headY && sCounter == snake.headX)
			{
				printf("O");
			}
			else
			{
				for (int tCounter = 0; tCounter < snake.length; tCounter++)
				{
					if (snake.bodyX[tCounter] == sCounter && snake.bodyY[tCounter] == counter)
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

		}
		printf("\n");
	}

}

/*
* This function will generate a fruit randomnly that will be eaten by
* the snake
*/


void generate_fruit(struct mySnake* snake, int* fruitX, int* fruitY)
{
	int collision = 0;

	//Srand function seeds the random number generator that is used by the function
	//rand
	srand((unsigned int)time(NULL));

	do
	{
		collision = 0;

		*fruitX = rand() % (width - 2) + 1;
		*fruitY = rand() % (height - 2) + 1;

		if (*fruitX == snake->headX && *fruitY == snake->headY)
		{
			collision = 1;
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

int get_input(void)
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

void move_snake(struct mySnake* snake)
{
	int previousTailX = snake->bodyX[snake->length - 1];
	int previousTailY = snake->bodyY[snake->length - 1];

	switch (snake->direction)
	{
	case 1:
		snake->headY--;
		snake->bodyY[0]--;
		break;
	case 2:
		snake->headY++;
		snake->bodyY[0]++;
		break;
	case 3:
		snake->headX--;
		snake->bodyX[0]--;
		break;
	case 4:
		snake->headX++;
		snake->bodyX[0]++;
		break;
	}

	for (int counter = snake->length - 1; counter > 0; counter--)
	{
		snake->bodyX[counter] = snake->bodyX[counter - 1];
		snake->bodyY[counter] = snake->bodyY[counter - 1];
	}
	snake->bodyX[0] = previousTailX;
	snake->bodyY[0] = previousTailY;

}

/*
* It is necessary to use this function to check the colition with the Wall.
* If the snake collides with the Wall, is Game Over
*/

int check_collision(struct mySnake snake)
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
* While more you eat, bigger you will be
*/

void increase_snake_length(struct mySnake* snake)
{
	snake->length++;
	switch (snake->direction)
	{
	case 1:
		snake->bodyX[snake->length - 1] = snake->headX;
		snake->bodyY[snake->length - 1] = snake->headY + 1;
		break;
	case 2:
		snake->bodyX[snake->length - 1] = snake->headX;
		snake->bodyY[snake->length - 1] = snake->headY - 1;
		break;
	case 3:
		snake->bodyX[snake->length - 1] = snake->headX + 1;
		snake->bodyY[snake->length - 1] = snake->headY;
		break;
	case 4:
		snake->bodyX[snake->length - 1] = snake->headX - 1;
		snake->bodyY[snake->length - 1] = snake->headY;
		break;
	}
}