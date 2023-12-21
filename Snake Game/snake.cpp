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
};

struct snakeBody
{
	int tailX[body_length];
	int tailY[body_length];
};

struct myFruit
{
	int positionX;
	int positionY;
	int eaten;
};

//Prototypes Declarations
void generate_fruit(struct mySnake* snake, struct myFruit* fruit, struct snakeBody* body);
void print_board(struct mySnake snake, struct snakeBody body, struct myFruit fruit);
int get_input(void);
void move_snake(struct mySnake* snake);
int check_collision(struct mySnake snake, struct snakeBody body);

int main(void)
{
	struct mySnake snake = { width / 2, height / 2, 1, 0 };
	struct snakeBody body = { {0}, {0} };
	struct myFruit fruit = { 0, 0, 0 };

	int game_over = 0;

	generate_fruit(&snake, &fruit, &body);

	while (!game_over)
	{
		int direction = get_input();
		if (direction)
		{
			snake.direction = direction;
		}
		move_snake(&snake);

		if (snake.headX == fruit.positionX && snake.headY == fruit.positionY)
		{
			fruit.eaten = 1;
			snake.length++;
			generate_fruit(&snake, &fruit, &body);
		}

		print_board(snake, body, fruit);

		game_over = check_collision(snake, body);

		Sleep(100);
	}

	return 0;
}

void print_board(struct mySnake snake, struct snakeBody body, struct myFruit fruit)
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
				isBodyPart = 1;
				int counterTailX = counter;
				int counterTailY = sCounter;
				if (fruit.eaten == 1)
				{
					for (int tCounter = 0; tCounter < snake.length; tCounter++)
					{
						printf("o");
					}
					isBodyPart = 1;
				}
			}
			if (!isBodyPart)
			{
				if (counter == 0 || counter == height - 1 || sCounter == 0 || sCounter == width - 1)
				{
					printf("#");
				}
				else if (counter == fruit.positionY && sCounter == fruit.positionX)
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

void generate_fruit(struct mySnake* snake, struct myFruit* fruit, struct snakeBody* body)
{
	int collision = 0;

	srand((unsigned int)time(NULL));

	do
	{
		fruit->positionX = rand() % (width - 2) + 1;
		fruit->positionY = rand() % (height - 2) + 1;

		if (fruit->positionX == snake->headX && fruit->positionY == snake->headY)
		{
			collision = 1;
		}

		for (int counter = 0; counter < snake->length; counter++)
		{
			if (fruit->positionX == body->tailX[counter] && fruit->positionY == body->tailY[counter])
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

int check_collision(struct mySnake snake, struct snakeBody body)
{
	if (snake.headX == 0 || snake.headX == width - 1 || snake.headY == 0 || snake.headY == height - 1)
	{
		return 1;
	}

	for (int counter = 0; counter < snake.length; counter++)
	{
		if (snake.headX == body.tailX[counter] && snake.headY == body.tailY[counter])
		{
			return 1;
		}
	}
	return 0;
}