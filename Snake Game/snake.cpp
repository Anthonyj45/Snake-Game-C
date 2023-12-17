#include <stdio.h>

//Constant Declarations
const int kRows = 20;
const int kColumns = 20;

//Functions Prototypes
void printBoard(void);

int main(void)
{
	printBoard();
	return 0;
}

void printBoard(void)
{
	for (int counter = 0; counter < kRows; counter++)
	{
		for (int sCounter = 0; sCounter < kColumns; sCounter++)
		{
			if (counter == 0 || counter == kRows - 1)
			{
				printf("-");
			}
			else if (sCounter == 0 || sCounter == kColumns - 1)
			{
				printf("|");
			}
			else
			{
				printf(" ");
			}
		}
		printf("\n");
	}
}