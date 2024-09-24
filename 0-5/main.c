#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#pragma warning(disable:6031)

int board[30][30] = { 0 };

void PrintBoard(int n[30][30]);

int main(void)
{
	int start = 0, x1 = 0, y1 = 0, x2 = 0, y2 = 0;

	PrintBoard(board);

	while (1)
	{
		if (!start)
		{
			int temp = 0;

			printf("input coord value : ");

			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

			if (x1 > x2)
			{
				temp = x1;
				x1 = x2;
				x2 = temp;
			}

			if (y1 > y2)
			{
				temp = y1;
				y1 = y2;
				y2 = temp;
			}

			if (x1 >= 0 && x2 < 30 && (x1 != y1 || x2 != y2))
			{
				if (y1 >= 0 && y2 < 30)
				{
					for (int i = y1; i <= y2; i++)
					{
						for (int j = x1; j <= x2; j++)
						{
							board[i][j] = 1;
						}
					}
				}
			}

			else
			{
				printf("Error (0 <= n <= 29, x1 != x2 and y1 != y2)\n");

				continue;
			}

			start = 1;
		}

		else if (start)
		{
			getchar();

			PrintBoard(board);

			char order = '\0';

			printf("input order : ");

			scanf("%c", &order);

			if (order == 'x')
			{
				for (int i = 0; i < 30; i++)
				{
					for (int j = 0; j < 30; j++)
					{
						board[i][j] = 0;
					}
				}

				if (x2 >= x1 && x2 < 29)
				{
					x1 += 1;

					x2 += 1;

					for (int i = y1; i <= y2; i++)
					{
						for (int j = x1; j <= x2; j++)
						{
							board[i][j] = 1;
						}
					}
				}

				else if (x2 == 29 && x1 == 29)
				{
					x1 = 0;

					x2 = 0;

					for (int i = y1; i <= y2; i++)
					{
						board[i][0] = 0;

						board[i][29] = 1;
					}
				}

				else if (x2 == 29 && x1 != 29)
				{
					x1 += 1;

					x2 = 0;

					for (int i = y1; i <= y2; i++)
					{
						for (int j = 0; j <= 29; j++)
						{
							board[i][j] = 1;
						}
					}

					for (int i = y1; i <= y2; i++)
					{
						for (int j = x2 + 1; j < x1; j++)
						{
							board[i][j] = 0;
						}
					}
				}

				else if (x1 == 29 && x2 != 29)
				{
					x1 = 0;

					x2 += 1;

					for (int i = y1; i <= y2; i++)
					{
						for (int j = x1; j <= x2; j++)
						{
							board[i][j] = 1;
						}
					}
				}

				else if (x2 < x1)
				{
					x1 += 1;

					x2 += 1;

					for (int i = y1; i <= y2; i++)
					{
						for (int j = 0; j <= 29; j++)
						{
							board[i][j] = 1;
						}
					}

					for (int i = y1; i <= y2; i++)
					{
						for (int j = x2 + 1; j < x1; j++)
						{
							board[i][j] = 0;
						}
					}
				}
			}

			else if (order == 'X')
			{
				for (int i = 0; i < 30; i++)
				{
					for (int j = 0; j < 30; j++)
					{
						board[i][j] = 0;
					}
				}

				if (x2 >= x1 && x1 > 0)
				{
					x1 -= 1;

					x2 -= 1;

					for (int i = y1; i <= y2; i++)
					{
						for (int j = x1; j <= x2; j++)
						{
							board[i][j] = 1;
						}
					}
				}

				else if (x2 == 0 && x1 == 0)
				{
					x1 = 29;

					x2 = 29;

					for (int i = y1; i <= y2; i++)
					{
						board[i][29] = 0;

						board[i][0] = 1;
					}
				}

				else if (x1 == 0 && x2 != 0)
				{
					x1 = 29;

					x2 -= 1;

					for (int i = y1; i <= y2; i++)
					{
						for (int j = 0; j <= 29; j++)
						{
							board[i][j] = 1;
						}
					}

					for (int i = y1; i <= y2; i++)
					{
						for (int j = x2 + 1; j < x1; j++)
						{
							board[i][j] = 0;
						}
					}
				}

				else if (x2 == 0 && x1 != 0)
				{
					x1 -= 1;

					x2 = 29;

					for (int i = y1; i <= y2; i++)
					{
						for (int j = x1; j <= x2; j++)
						{
							board[i][j] = 1;
						}
					}
				}

				else if (x2 < x1)
				{
					x1 -= 1;

					x2 -= 1;

					for (int i = y1; i <= y2; i++)
					{
						for (int j = 0; j <= 29; j++)
						{
							board[i][j] = 1;
						}
					}

					for (int i = y1; i <= y2; i++)
					{
						for (int j = x2 + 1; j < x1; j++)
						{
							board[i][j] = 0;
						}
					}
				}
			}

			else if (order == 'y')
			{
				for (int i = 0; i < 30; i++)
				{
					for (int j = 0; j < 30; j++)
					{
						board[i][j] = 0;
					}
				}

				if (y2 >= y1 && y2 < 29)
				{
					y1 += 1;

					y2 += 1;

					for (int i = y1; i <= y2; i++)
					{
						for (int j = x1; j <= x2; j++)
						{
							board[i][j] = 1;
						}
					}
				}

				else if (y2 == 29 && y1 == 29)
				{
					y1 = 0;

					y2 = 0;

					for (int i = x1; i <= x2; i++)
					{
						board[0][i] = 1;

						board[29][i] = 0;
					}
				}

				else if (y2 == 29 && y1 != 29)
				{
					y1 += 1;

					y2 = 0;

					for (int i = 0; i <= 29; i++)
					{
						for (int j = x1; j <= x2; j++)
						{
							board[i][j] = 1;
						}
					}

					for (int i = y2 + 1; i < y1; i++)
					{
						for (int j = x1; j <= x2; j++)
						{
							board[i][j] = 0;
						}
					}
				}

				else if (y1 == 29 && y2 != 29)
				{
					y1 = 0;

					y2 += 1;

					for (int i = y1; i <= y2; i++)
					{
						for (int j = x1; j <= x2; j++)
						{
							board[i][j] = 1;
						}
					}
				}

				else if (y2 < y1)
				{
					y1 += 1;

					y2 += 1;

					for (int i = 0; i <= 29; i++)
					{
						for (int j = x1; j <= x2; j++)
						{
							board[i][j] = 1;
						}
					}

					for (int i = y2 + 1; i < y1; i++)
					{
						for (int j = x1; j <= x2; j++)
						{
							board[i][j] = 0;
						}
					}
				}
			}

			else if (order == 'Y')
			{
				for (int i = 0; i < 30; i++)
				{
					for (int j = 0; j < 30; j++)
					{
						board[i][j] = 0;
					}
				}

				if (y2 >= y1 && y1 > 0)
				{
					y1 -= 1;

					y2 -= 1;

					for (int i = y1; i <= y2; i++)
					{
						for (int j = x1; j <= x2; j++)
						{
							board[i][j] = 1;
						}
					}
				}

				else if (y2 == 0 && y1 == 0)
				{
					y1 = 29;

					y2 = 29;

					for (int i = x1; i <= x2; i++)
					{
						board[29][i] = 1;

						board[0][i] = 0;
					}
				}

				else if (y1 == 0 && y2 != 0)
				{
					y1 = 29;

					y2 -= 1;

					for (int i = 0; i <= 29; i++)
					{
						for (int j = x1; j <= x2; j++)
						{
							board[i][j] = 1;
						}
					}

					for (int i = y2 + 1; i < y1; i++)
					{
						for (int j = x1; j <= x2; j++)
						{
							board[i][j] = 0;
						}
					}
				}

				else if (y2 == 0 && y1 != 0)
				{
					y1 -= 1;

					y2 = 29;

					for (int i = y1; i <= y2; i++)
					{
						for (int j = x1; j <= x2; j++)
						{
							board[i][j] = 1;
						}
					}
				}

				else if (y2 < y1)
				{
					y1 -= 1;

					y2 -= 1;

					for (int i = 0; i <= 29; i++)
					{
						for (int j = x1; j <= x2; j++)
						{
							board[i][j] = 1;
						}
					}

					for (int i = y2 + 1; i < y1; i++)
					{
						for (int j = x1; j <= x2; j++)
						{
							board[i][j] = 0;
						}
					}
				}
			}

			else if (order == 's')
			{
				if (x2 < 29)
				{
					x2 += 1;
				}

				if (y2 < 29)
				{
					y2 += 1;
				}

				for (int i = y1; i <= y2; i++)
				{
					for (int j = x1; j <= x2; j++)
					{
						board[i][j] = 1;
					}
				}
			}

			else if (order == 'S')
			{
				for (int i = 0; i < 30; i++)
				{
					for (int j = 0; j < 30; j++)
					{
						board[i][j] = 0;
					}
				}

				if (x1 != x2)
				{
					x2 -= 1;
				}

				if (y1 != y2)
				{
					y2 -= 1;
				}

				for (int i = y1; i <= y2; i++)
				{
					for (int j = x1; j <= x2; j++)
					{
						board[i][j] = 1;
					}
				}
			}

			else if (order == 'i')
			{
				if (x2 < 29)
				{
					x2 += 1;
				}

				for (int i = y1; i <= y2; i++)
				{
					for (int j = x1; j <= x2; j++)
					{
						board[i][j] = 1;
					}
				}
			}

			else if (order == 'I')
			{
				for (int i = 0; i < 30; i++)
				{
					for (int j = 0; j < 30; j++)
					{
						board[i][j] = 0;
					}
				}

				if (x1 != x2)
				{
					x2 -= 1;
				}

				for (int i = y1; i <= y2; i++)
				{
					for (int j = x1; j <= x2; j++)
					{
						board[i][j] = 1;
					}
				}
			}

			else if (order == 'j')
			{
				if (y2 < 29)
				{
					y2 += 1;
				}

				for (int i = y1; i <= y2; i++)
				{
					for (int j = x1; j <= x2; j++)
					{
						board[i][j] = 1;
					}
				}
			}

			else if (order == 'J')
			{
				for (int i = 0; i < 30; i++)
				{
					for (int j = 0; j < 30; j++)
					{
						board[i][j] = 0;
					}
				}

				if (y1 != y2)
				{
					y2 -= 1;
				}

				for (int i = y1; i <= y2; i++)
				{
					for (int j = x1; j <= x2; j++)
					{
						board[i][j] = 1;
					}
				}
			}

			else if (order == 'a')
			{
				for (int i = 0; i < 30; i++)
				{
					for (int j = 0; j < 30; j++)
					{
						board[i][j] = 0;
					}
				}
				if (x2 < 29)
				{
					x2 += 1;
				}

				if (y1 != y2)
				{
					y2 -= 1;
				}

				for (int i = y1; i <= y2; i++)
				{
					for (int j = x1; j <= x2; j++)
					{
						board[i][j] = 1;
					}
				}
			}

			else if (order == 'A')
			{
				for (int i = 0; i < 30; i++)
				{
					for (int j = 0; j < 30; j++)
					{
						board[i][j] = 0;
					}
				}

				if (x1 != x2)
				{
					x2 -= 1;
				}

				if (y2 < 29)
				{
					y2 += 1;
				}

				for (int i = y1; i <= y2; i++)
				{
					for (int j = x1; j <= x2; j++)
					{
						board[i][j] = 1;
					}
				}
			}

			else if (order == 'm')
			{
				printf("area : %d\n", (x2 - x1 + 1) * (y2 - y1 + 1));
			}

			else if (order == 'n')
			{
				printf("area ratio : %lf%%\n", (x2 - x1 + 1.0) * (y2 - y1 + 1.0) / 9.0);
			}

			else if (order == 'r')
			{
				for (int i = 0; i < 30; i++)
				{
					for (int j = 0; j < 30; j++)
					{
						board[i][j] = 0;
					}
				}

				start = 0;
			}

			else if (order == 'q')
			{
				break;
			}

			else
			{
				printf("This command does not exist.\n");

				Sleep(500);
			}
		}
	}

	return 0;
}

void PrintBoard(int n[30][30])
{
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			if (board[i][j] == 1)
			{
				printf("0 ");
			}

			else
			{
				printf(". ");
			}
		}

		printf("\n");
	}
}