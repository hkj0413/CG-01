#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#pragma warning(disable:6031)

struct Board
{
	int word;
	int state;

}typedef Board;

void SetBoard(Board n[5][5]);

void PrintBoard(Board n[5][5]);

Board board[5][5] = { 0 };

int main(void)
{
	int score = 0, chance = 10;

	SetBoard(board);

	PrintBoard(board);

	while (1)
	{
		char a = '\0', b = '\0', x = '\0', y = '\0';

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

		printf("input : ");

		scanf("%c%c, %c%c", &a, &x, &b, &y);

		if (a >= 97 && a <= 108 && x >= 49 && x <= 53 && b >= 97 && b <= 108 && y >= 49 && y <= 53 && chance > 0)
		{
			getchar();

			if (a == b && x == y)
			{
				printf("Error\n");

				continue;
			}

			if (board[x - 49][a - 97].state == 0)
			{
				board[x - 49][a - 97].state = 1;
			}

			if (board[y - 49][b - 97].state == 0)
			{
				board[y - 49][b - 97].state = 1;
			}

			PrintBoard(board);

			Sleep(500);

			if (board[x - 49][a - 97].word == 64 && board[y - 49][b - 97].word != 64)
			{
				for (int i = 0; i < 5; i++)
				{
					for (int j = 0; j < 5; j++)
					{
						if (board[i][j].word == board[y - 49][b - 97].word)
						{
							board[i][j].state = 1;
						}
					}
				}

				score++;
				chance--;

				Sleep(500);
			}

			else if (board[x - 49][a - 97].word != 64 && board[y - 49][b - 97].word == 64)
			{
				for (int i = 0; i < 5; i++)
				{
					for (int j = 0; j < 5; j++)
					{
						if (board[i][j].word == board[x - 49][a - 97].word)
						{
							board[i][j].state = 1;
						}
					}
				}

				score++;
				chance--;

				Sleep(500);
			}

			else if (board[x - 49][a - 97].word != board[y - 49][b - 97].word)
			{
				if (board[x - 49][a - 97].state == 1)
				{
					board[x - 49][a - 97].state = 0;
				}

				if (board[y - 49][b - 97].state == 1)
				{
					board[y - 49][b - 97].state = 0;
				}

				chance--;
			}

			else
			{
				if (board[x - 49][a - 97].state == 1 && board[y - 49][b - 97].state == 1)
				{
					board[x - 49][a - 97].state = 2;

					board[y - 49][b - 97].state = 2;

					score++;
				}

				chance--;
			}

			PrintBoard(board);

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

			printf("socre : %d, chance : %d\n", score, chance);
		}

		else if (a == 'r' && x == '\n' && b == '\0' && y == '\0')
		{
			getchar();

			SetBoard(board);

			PrintBoard(board);

			score = 0;

			chance = 10;
		}

		else if (a == 'o' && x == '\n' && b == '\0' && y == '\0')
		{
			getchar();

			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					board[i][j].state = 3;
				}
			}

			PrintBoard(board);
		}

		else if (a == 'p' && x == '\n' && b == '\0' && y == '\0')
		{
			getchar();

			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					board[i][j].state = 0;
				}
			}

			PrintBoard(board);
		}

		else if (a == 'q' && x == '\n' && b == '\0' && y == '\0')
		{
			getchar();

			break;
		}

		else if (chance == 0)
		{
			getchar();

			printf("You no longer have a chance.\n");
		}

		else
		{
			printf("This command does not exist.\n");
		}
	}

	return 0;
}

void SetBoard(Board n[5][5])
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			board[i][j].word = 64;
		}
	}

	srand((unsigned)time(NULL));

	for (int i = 1; i <= 12; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			while (1)
			{
				int x = rand() % 5, y = rand() % 5;

				if (n[x][y].word == 64)
				{
					n[x][y].word += i;

					break;
				}
			}
		}
	}
}

void PrintBoard(Board n[5][5])
{
	printf("  a b c d e\n");

	for (int i = 1; i <= 5; i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

		printf("%d ", i);

		for (int j = 0; j < 5; j++)
		{
			if (n[i - 1][j].state > 0)
			{
				if (n[i - 1][j].word == 65)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);

					printf("%c ", n[i - 1][j].word);
				}

				else if (n[i - 1][j].word == 66)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);

					printf("%c ", n[i - 1][j].word);
				}

				else if (n[i - 1][j].word == 67)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);

					printf("%c ", n[i - 1][j].word);
				}

				else if (n[i - 1][j].word == 68)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);

					printf("%c ", n[i - 1][j].word);
				}

				else if (n[i - 1][j].word == 69)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);

					printf("%c ", n[i - 1][j].word);
				}

				else if (n[i - 1][j].word == 70)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);

					printf("%c ", n[i - 1][j].word);
				}

				else if (n[i - 1][j].word == 71)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);

					printf("%c ", n[i - 1][j].word);
				}

				else if (n[i - 1][j].word == 72)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);

					printf("%c ", n[i - 1][j].word);
				}

				else if (n[i - 1][j].word == 73)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);

					printf("%c ", n[i - 1][j].word);
				}

				else if (n[i - 1][j].word == 74)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);

					printf("%c ", n[i - 1][j].word);
				}

				else if (n[i - 1][j].word == 75)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);

					printf("%c ", n[i - 1][j].word);
				}

				else if (n[i - 1][j].word == 76)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);

					printf("%c ", n[i - 1][j].word);
				}

				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);

					printf("%c ", n[i - 1][j].word);
				}
			}

			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

				printf("* ");
			}
		}

		printf("\n");
	}
}