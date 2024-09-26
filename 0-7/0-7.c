#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#pragma warning(disable:6031)

int board[30][30] = { 0 };

void PrintBoard(int n[30][30]);

int main(void)
{
	int start = 0, x1 = 0, y1 = 0, x2 = 0, y2 = 0, x3 = 0, y3 = 0, x4 = 0, y4 = 0;

	PrintBoard(board);

	while (1)
	{
		if (!start)
		{
			int temp = 0;

			printf("input coord value1 : ");

			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

			getchar();

			printf("input coord value2 : ");

			scanf("%d %d %d %d", &x3, &y3, &x4, &y4);

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

			if (x3 > x4)
			{
				temp = x3;
				x3 = x4;
				x4 = temp;
			}

			if (y3 > y4)
			{
				temp = y3;
				y3 = y4;
				y4 = temp;
			}

			if (x1 >= 0 && x2 < 30 && (x1 != y1 || x2 != y2) && x3 >= 0 && x4 < 30 && (x3 != y3 || x4 != y4))
			{
				if (y1 >= 0 && y2 < 30 && y3 >= 0 && y4 < 30)
				{
					for (int i = y1; i <= y2; i++)
					{
						for (int j = x1; j <= x2; j++)
						{
							board[i][j] += 1;
						}
					}

					for (int i = y3; i <= y4; i++)
					{
						for (int j = x3; j <= x4; j++)
						{
							board[i][j] += 2;
						}
					}
				}
			}

			else
			{
				printf("Error (0 <= n <= 29, x1 != x2 and y1 != y2 and x3 != x4 and y3 != y4)\n");

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
				for (int i = y1; i <= y2; i++)
				{
					for (int j = x1; j <= x2; j++)
					{
						board[i][j] -= 1;
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
							board[i][j] += 1;
						}
					}
				}

				else if (x2 == 29 && x1 == 29)
				{
					x1 = 0;

					x2 = 0;

					for (int i = y1; i <= y2; i++)
					{
						board[i][0] += 1;

						board[i][29] -= 1;
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
							board[i][j] += 1;
						}
					}

					for (int i = y1; i <= y2; i++)
					{
						for (int j = x2 + 1; j < x1; j++)
						{
							board[i][j] -= 1;
						}
					}
				}

				else if (x1 == 29 && x2 != 29)
				{
					x1 = 0;

					x2 += 1;

					for (int i = y1; i <= y2; i++)
					{
						board[i][29] -= 1;

						for (int j = x1; j <= x2; j++)
						{
							if (board[i][j] != 1)
							{
								board[i][j] += 1;
							}
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
							if (board[i][j] != 1)
							{
								board[i][j] += 1;
							}
						}
					}

					for (int i = y1; i <= y2; i++)
					{
						for (int j = x2 + 1; j < x1; j++)
						{
							board[i][j] -= 1;
						}
					}
				}
			}

			else if (order == 'X')
			{
				for (int i = y1; i <= y2; i++)
				{
					for (int j = x1; j <= x2; j++)
					{
						board[i][j] -= 1;
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
							board[i][j] += 1;
						}
					}
				}

				else if (x2 == 0 && x1 == 0)
				{
					x1 = 29;

					x2 = 29;

					for (int i = y1; i <= y2; i++)
					{
						board[i][29] += 1;

						board[i][0] -= 1;
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
							board[i][j] += 1;
						}
					}

					for (int i = y1; i <= y2; i++)
					{
						for (int j = x2 + 1; j < x1; j++)
						{
							board[i][j] -= 1;
						}
					}
				}

				else if (x2 == 0 && x1 != 0)
				{
					x1 -= 1;

					x2 = 29;

					for (int i = y1; i <= y2; i++)
					{
						board[i][0] -= 1;

						for (int j = x1; j <= x2; j++)
						{
							if (board[i][j] != 1)
							{
								board[i][j] += 1;
							}
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
							if (board[i][j] != 1)
							{
								board[i][j] += 1;
							}
						}
					}

					for (int i = y1; i <= y2; i++)
					{
						for (int j = x2 + 1; j < x1; j++)
						{
							board[i][j] -= 1;
						}
					}
				}
			}

			else if (order == 'y')
			{
				for (int i = y1; i <= y2; i++)
				{
					for (int j = x1; j <= x2; j++)
					{
						board[i][j] -= 1;
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
							board[i][j] += 1;
						}
					}
				}

				else if (y2 == 29 && y1 == 29)
				{
					y1 = 0;

					y2 = 0;

					for (int i = x1; i <= x2; i++)
					{
						board[0][i] += 1;

						board[29][i] -= 1;
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
							board[i][j] += 1;
						}
					}

					for (int i = y2 + 1; i < y1; i++)
					{
						for (int j = x1; j <= x2; j++)
						{
							board[i][j] -= 1;
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
							board[29][j] -= 1;

							if (board[i][j] != 1)
							{
								board[i][j] += 1;
							}
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
							if (board[i][j] != 1)
							{
								board[i][j] += 1;
							}
						}
					}

					for (int i = y2 + 1; i < y1; i++)
					{
						for (int j = x1; j <= x2; j++)
						{
							board[i][j] -= 1;
						}
					}
				}
			}

			else if (order == 'Y')
			{
				for (int i = y1; i <= y2; i++)
				{
					for (int j = x1; j <= x2; j++)
					{
						board[i][j] -= 1;
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
							board[i][j] += 1;
						}
					}
				}

				else if (y2 == 0 && y1 == 0)
				{
					y1 = 29;

					y2 = 29;

					for (int i = x1; i <= x2; i++)
					{
						board[29][i] += 1;

						board[0][i] -= 1;
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
							board[i][j] += 1;
						}
					}

					for (int i = y2 + 1; i < y1; i++)
					{
						for (int j = x1; j <= x2; j++)
						{
							board[i][j] -= 1;
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
							board[0][j] -= 1;

							if (board[i][j] != 1)
							{
								board[i][j] += 1;
							}
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
							if (board[i][j] != 1)
							{
								board[i][j] += 1;
							}
						}
					}

					for (int i = y2 + 1; i < y1; i++)
					{
						for (int j = x1; j <= x2; j++)
						{
							board[i][j] -= 1;
						}
					}
				}
			}

			else if (order == 's')
			{
				for (int i = y1; i <= y2; i++)
				{
					for (int j = x1; j <= x2; j++)
					{
						board[i][j] -= 1;
					}
				}

				if (x2 < 29)
				{
					x2 += 1;
				}

				else if (x2 == 29 && x1 != 0)
				{
					x1 -= 1;
				}

				if (y2 < 29)
				{
					y2 += 1;
				}

				else if (y2 == 29 && y1 != 0)
				{
					y1 -= 1;
				}

				for (int i = y1; i <= y2; i++)
				{
					for (int j = x1; j <= x2; j++)
					{
						board[i][j] += 1;
					}
				}
			}

			else if (order == 'S')
			{
				for (int i = y1; i <= y2; i++)
				{
					for (int j = x1; j <= x2; j++)
					{
						board[i][j] -= 1;
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
						board[i][j] += 1;
					}
				}
			}

			else if (order == 'w')
			{
				for (int i = y3; i <= y4; i++)
				{
					for (int j = x3; j <= x4; j++)
					{
						board[i][j] -= 2;
					}
				}

				if (x4 >= x3 && x4 < 29)
				{
					x3 += 1;

					x4 += 1;

					for (int i = y3; i <= y4; i++)
					{
						for (int j = x3; j <= x4; j++)
						{
							board[i][j] += 2;
						}
					}
				}

				else if (x4 == 29 && x3 == 29)
				{
					x3 = 0;

					x4 = 0;

					for (int i = y3; i <= y4; i++)
					{
						board[i][0] += 2;

						board[i][29] -= 2;
					}
				}

				else if (x4 == 29 && x3 != 29)
				{
					x3 += 1;

					x4 = 0;

					for (int i = y3; i <= y4; i++)
					{
						for (int j = 0; j <= 29; j++)
						{
							board[i][j] += 2;
						}
					}

					for (int i = y3; i <= y4; i++)
					{
						for (int j = x4 + 1; j < x3; j++)
						{
							board[i][j] -= 2;
						}
					}
				}

				else if (x3 == 29 && x4 != 29)
				{
					x3 = 0;

					x4 += 1;

					for (int i = y3; i <= y4; i++)
					{
						board[i][29] -= 2;

						for (int j = x3; j <= x4; j++)
						{
							if (board[i][j] != 2)
							{
								board[i][j] += 2;
							}
						}
					}
				}

				else if (x4 < x3)
				{
					x3 += 1;

					x4 += 1;

					for (int i = y3; i <= y4; i++)
					{
						for (int j = 0; j <= 29; j++)
						{
							if (board[i][j] != 2)
							{
								board[i][j] += 2;
							}
						}
					}

					for (int i = y3; i <= y4; i++)
					{
						for (int j = x4 + 1; j < x3; j++)
						{
							board[i][j] -= 2;
						}
					}
				}
			}

			else if (order == 'W')
			{
				for (int i = y3; i <= y4; i++)
				{
					for (int j = x3; j <= x4; j++)
					{
						board[i][j] -= 2;
					}
				}

				if (x4 >= x3 && x3 > 0)
				{
					x3 -= 1;

					x4 -= 1;

					for (int i = y3; i <= y4; i++)
					{
						for (int j = x3; j <= x4; j++)
						{
							board[i][j] += 2;
						}
					}
				}

				else if (x4 == 0 && x3 == 0)
				{
					x3 = 29;

					x4 = 29;

					for (int i = y3; i <= y4; i++)
					{
						board[i][29] += 2;

						board[i][0] -= 2;
					}
				}

				else if (x3 == 0 && x4 != 0)
				{
					x3 = 29;

					x4 -= 1;

					for (int i = y3; i <= y4; i++)
					{
						for (int j = 0; j <= 29; j++)
						{
							board[i][j] += 2;
						}
					}

					for (int i = y3; i <= y4; i++)
					{
						for (int j = x4 + 1; j < x3; j++)
						{
							board[i][j] -= 2;
						}
					}
				}

				else if (x4 == 0 && x3 != 0)
				{
					x3 -= 1;

					x4 = 29;

					for (int i = y3; i <= y4; i++)
					{
						board[i][0] -= 2;

						for (int j = x3; j <= x4; j++)
						{
							if (board[i][j] != 2)
							{
								board[i][j] += 2;
							}
						}
					}
				}

				else if (x4 < x3)
				{
					x3 -= 1;

					x4 -= 1;

					for (int i = y3; i <= y4; i++)
					{
						for (int j = 0; j <= 29; j++)
						{
							if (board[i][j] != 2)
							{
								board[i][j] += 2;
							}
						}
					}

					for (int i = y3; i <= y4; i++)
					{
						for (int j = x4 + 1; j < x3; j++)
						{
							board[i][j] -= 2;
						}
					}
				}
			}

			else if (order == 'a')
			{
				for (int i = y3; i <= y4; i++)
				{
					for (int j = x3; j <= x4; j++)
					{
						board[i][j] -= 2;
					}
				}

				if (y4 >= y3 && y4 < 29)
				{
					y3 += 1;

					y4 += 1;

					for (int i = y3; i <= y4; i++)
					{
						for (int j = x3; j <= x4; j++)
						{
							board[i][j] += 2;
						}
					}
				}

				else if (y4 == 29 && y3 == 29)
				{
					y3 = 0;

					y4 = 0;

					for (int i = x3; i <= x4; i++)
					{
						board[0][i] += 2;

						board[29][i] -= 2;
					}
				}

				else if (y4 == 29 && y3 != 29)
				{
					y3 += 1;

					y4 = 0;

					for (int i = 0; i <= 29; i++)
					{
						for (int j = x3; j <= x4; j++)
						{
							board[i][j] += 2;
						}
					}

					for (int i = y4 + 1; i < y3; i++)
					{
						for (int j = x3; j <= x4; j++)
						{
							board[i][j] -= 2;
						}
					}
				}

				else if (y3 == 29 && y4 != 29)
				{
					y3 = 0;

					y4 += 1;

					for (int i = y3; i <= y4; i++)
					{
						for (int j = x3; j <= x4; j++)
						{
							board[29][j] -= 2;

							if (board[i][j] != 2)
							{
								board[i][j] += 2;
							}
						}
					}
				}

				else if (y4 < y3)
				{
					y3 += 1;

					y4 += 1;

					for (int i = 0; i <= 29; i++)
					{
						for (int j = x3; j <= x4; j++)
						{
							if (board[i][j] != 2)
							{
								board[i][j] += 2;
							}
						}
					}

					for (int i = y4 + 1; i < y3; i++)
					{
						for (int j = x3; j <= x4; j++)
						{
							board[i][j] -= 2;
						}
					}
				}
			}

			else if (order == 'A')
			{
				for (int i = y3; i <= y4; i++)
				{
					for (int j = x3; j <= x4; j++)
					{
						board[i][j] -= 2;
					}
				}

				if (y4 >= y3 && y3 > 0)
				{
					y3 -= 1;

					y4 -= 1;

					for (int i = y3; i <= y4; i++)
					{
						for (int j = x3; j <= x4; j++)
						{
							board[i][j] += 2;
						}
					}
				}

				else if (y4 == 0 && y3 == 0)
				{
					y3 = 29;

					y4 = 29;

					for (int i = x3; i <= x4; i++)
					{
						board[29][i] += 2;

						board[0][i] -= 2;
					}
				}

				else if (y3 == 0 && y4 != 0)
				{
					y3 = 29;

					y4 -= 1;

					for (int i = 0; i <= 29; i++)
					{
						for (int j = x3; j <= x4; j++)
						{
							board[i][j] += 2;
						}
					}

					for (int i = y4 + 1; i < y3; i++)
					{
						for (int j = x3; j <= x4; j++)
						{
							board[i][j] -= 2;
						}
					}
				}

				else if (y4 == 0 && y3 != 0)
				{
					y3 -= 1;

					y4 = 29;

					for (int i = y3; i <= y4; i++)
					{
						for (int j = x3; j <= x4; j++)
						{
							board[0][j] -= 2;

							if (board[i][j] != 2)
							{
								board[i][j] += 2;
							}
						}
					}
				}

				else if (y4 < y3)
				{
					y3 -= 1;

					y4 -= 1;

					for (int i = 0; i <= 29; i++)
					{
						for (int j = x3; j <= x4; j++)
						{
							if (board[i][j] != 2)
							{
								board[i][j] += 2;
							}
						}
					}

					for (int i = y4 + 1; i < y3; i++)
					{
						for (int j = x3; j <= x4; j++)
						{
							board[i][j] -= 2;
						}
					}
				}
			}

			else if (order == 'd')
			{
				for (int i = y3; i <= y4; i++)
				{
					for (int j = x3; j <= x4; j++)
					{
						board[i][j] -= 2;
					}
				}

				if (x4 < 29)
				{
					x4 += 1;
				}

				else if (x4 == 29 && x3 != 0)
				{
					x3 -= 1;
				}

				if (y4 < 29)
				{
					y4 += 1;
				}

				else if (y4 == 29 && y3 != 0)
				{
					y3 -= 1;
				}

				for (int i = y3; i <= y4; i++)
				{
					for (int j = x3; j <= x4; j++)
					{
						board[i][j] += 2;
					}
				}
			}

			else if (order == 'D')
			{
				for (int i = y3; i <= y4; i++)
				{
					for (int j = x3; j <= x4; j++)
					{
						board[i][j] -= 2;
					}
				}

				if (x3 != x4)
				{
					x4 -= 1;
				}

				if (y3 != y4)
				{
					y4 -= 1;
				}

				for (int i = y3; i <= y4; i++)
				{
					for (int j = x3; j <= x4; j++)
					{
						board[i][j] += 2;
					}
				}
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

			else if (board[i][j] == 2)
			{
				printf("X ");
			}

			else if (board[i][j] == 3)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);

				printf("# ");

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}

			else
			{
				printf(". ");
			}
		}

		printf("\n");
	}
}