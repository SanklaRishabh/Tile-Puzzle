#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>

/* Obtains the scan code of arrow keys */
int getkey()
{
	int ch = getch();

	if (ch == 0)
	{
		ch = getch();
		return ch;
	}
	return ch;
}

/* Checks if the matrix is sorted */
bool checkMatrix(short (*matrix)[4], short *row, short *col)
{
	for (short i = 0, containedValue = 1; i < 4; i++)
	{
		for (short j = 0; j < 4; j++)
		{
			if (*(*matrix + i * 4 + j) != containedValue)
			{
				if (i * 4 + j == 15)
				{
					return true;
				}
				return false;
			}
			containedValue++;
		}
	}
}

/* Swaps the values on key press */
void swap(short (*matrix)[4], short *input, short *row, short *col)
{
	short temp;

	switch (*input)
	{
	case 0x48: // UP Arrow key
		if (*row != 3)
		{
			temp = *(*matrix + 4 * *row + *col);
			*(*matrix + 4 * *row + *col) = *(*matrix + 4 * (*row + 1) + *col);
			*(*matrix + 4 * (*row + 1) + *col) = temp;
			*row += 1;
		}
		break;

	case 0x4B: // LEFT Arrow key
		if (*col != 3)
		{
			temp = *(*matrix + 4 * *row + *col);
			*(*matrix + 4 * *row + *col) = *(*matrix + 4 * *row + (*col + 1));
			*(*matrix + 4 * *row + (*col + 1)) = temp;
			*col += 1;
		}
		break;

	case 0x4D: // RIGHT Arrow key
		if (*col != 0)
		{
			temp = *(*matrix + 4 * *row + *col);
			*(*matrix + 4 * *row + *col) = *(*matrix + 4 * *row + (*col - 1));
			*(*matrix + 4 * *row + (*col - 1)) = temp;
			*col -= 1;
		}
		break;

	case 0x50: // DOWN arrow key
		if (*row != 0)
		{
			temp = *(*matrix + 4 * *row + *col);
			printf("%hi", temp);
			*(*matrix + 4 * *row + *col) = *(*matrix + 4 * (*row - 1) + *col);
			*(*matrix + 4 * (*row - 1) + *col) = temp;
			*row -= 1;
		}
		break;

	default:
		break;
	}
}

void main()
{
	short puzzle[4][4] = {{1, 4, 15, 7}, {8, 10, 2, 11}, {14, 3, 6, 13}, {12, 9, 5, -1}}, cellRow = 3, cellCol = 3, input, completion = false;

	do
	{
	LAST_ITERATION:
		system("cls");
		printf("USE ARROW KEYS TO PLAY THE PUZZLE\n\n");

		for (short i = 0; i < 4; i++)
		{
			for (short j = 0; j < 4; j++)
			{
				printf("\t");

				if (puzzle[i][j] >= 0)
				{
					printf("%hi", puzzle[i][j]);
				}
			}
			printf("\n");
		}
		if (completion == false)
		{
			input = getkey();
			swap(puzzle, &input, &cellRow, &cellCol);
		}
	} while (!checkMatrix(puzzle, &cellRow, &cellCol));

	if (completion == false)
	{
		completion = true;
		goto LAST_ITERATION;    // To print the completed puzzle before exiting the program.
	}
}