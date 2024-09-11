#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable:6031)

struct Size
{
	int size;
	int start;
	int end;

}typedef Size;

struct String
{
	char text[10][150];
	int state[10][150];

}typedef String;

void PrintCapital(String n);

int Capital = 0, capword = 0, check = 0;

int main(void)
{
	FILE* fp;

	int X = 0, space = 0, word[10] = { 0 }, copy = 0, Upside = 0, Insert = 0, Down = 0, point = 0, Change = 0, Sort = 0, big = 0, once = 0, sor = 0, Word = 0;

	Size sortword[10][30] = { 0 };

	String str = { 0 }, temp = { 0 }, Ups = { 0 }, Ins = { 0 }, Dow = { 0 }, Sea = { 0 };

	char chaword = '\0', anoword = '\0', searword[50] = "\0";

	fp = fopen("data.txt", "r");

	while (fgets(temp.text[X], sizeof(temp.text[X]), fp) != NULL)
	{
		X++;
	}

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 150; j++)
		{
			if (temp.text[i][j] == ' ' && !space)
			{
				str.text[i][copy++] = temp.text[i][j];

				space = 1;
			}

			else if (temp.text[i][j] == ' ' && space)
			{

			}

			else
			{
				str.text[i][copy++] = temp.text[i][j];

				space = 0;
			}
		}

		copy = 0;
	}

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 150; j++)
		{
			temp.text[i][j] = str.text[i][j];
		}
	}

	for (int i = 0; i < 10; i++)
	{
		printf("%s", str.text[i]);
	}

	printf("\n");

	while (1)
	{
		char order = '\0';

		printf("command : ");

		scanf("%c", &order);

		if (order == 'c' && !Capital)
		{
			getchar();

			PrintCapital(str);
		}

		else if (order == 'c' && Capital)
		{
			getchar();

			for (int i = 0; i < 10; i++)
			{
				printf("%s", str.text[i]);
			}

			printf("\n");

			Capital = 0;
		}

		else if (order == 'd' && !Upside)
		{
			getchar();

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 150; j++)
				{
					if (str.text[i][149 - j] != '\0')
					{
						Ups.text[i][copy] = str.text[i][149 - j];

						Ups.state[i][copy++] = str.state[i][149 - j];
					}
				}

				if (i == 8)
				{
					Ups.text[i][copy] = '\n';
				}

				else if (i == 9)
				{
					Ups.text[i][copy] = '\n';
				}

				copy = 0;
			}

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 150; j++)
				{
					str.text[i][j] = Ups.text[i][j];

					str.state[i][j] = Ups.state[i][j];
				}
			}

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 150; j++)
				{
					Ups.text[i][j] = temp.text[i][j];

					Ups.state[i][j] = temp.state[i][j];
				}
			}

			if (Capital)
			{
				PrintCapital(str);
			}

			else
			{
				for (int i = 0; i < 10; i++)
				{
					printf("%s", str.text[i]);
				}
			}

			Upside = 1;
		}

		else if (order == 'd' && Upside)
		{
			getchar();

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 150; j++)
				{
					if (str.text[i][149 - j] != '\0' && str.text[i][149 - j] != '\n')
					{
						Ups.text[i][copy] = str.text[i][149 - j];

						Ups.state[i][copy++] = str.state[i][149 - j];
					}
				}

				if (Insert && i < 9)
				{
					Ups.text[i][copy] = '\n';
				}
				
				copy = 0;
			}

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 150; j++)
				{
					str.text[i][j] = Ups.text[i][j];

					str.state[i][j] = Ups.state[i][j];
				}
			}

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 150; j++)
				{
					Ups.text[i][j] = temp.text[i][j];

					Ups.state[i][j] = temp.state[i][j];
				}
			}

			if (Capital)
			{
				PrintCapital(str);
			}

			else
			{
				for (int i = 0; i < 10; i++)
				{
					printf("%s", str.text[i]);
				}

				printf("\n");
			}

			Upside = 0;
		}

		else if (order == 'e' && !Insert)
		{
			getchar();

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 120; j++)
				{
					if (j % 3 == 0 && j != 0 && str.text[i][j] != '\0')
					{
						Ins.text[i][copy++] = '@';
					}

					Ins.text[i][copy] = str.text[i][j];

					Ins.state[i][copy++] = str.state[i][j];
				}

				copy = 0;
			}

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 150; j++)
				{
					str.text[i][j] = Ins.text[i][j];

					str.state[i][j] = Ins.state[i][j];
				}
			}

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 150; j++)
				{
					Ins.text[i][j] = temp.text[i][j];

					Ins.state[i][j] = temp.state[i][j];
				}
			}

			if (Capital)
			{
				PrintCapital(str);
			}

			else
			{
				for (int i = 0; i < 10; i++)
				{
					printf("%s", str.text[i]);
				}
			}

			printf("\n");

			Insert = 1;
		}

		else if (order == 'e' && Insert)
		{
			getchar();

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 150; j++)
				{
					if (str.text[i][j] == anoword && str.state[i][j] == 1)
					{
						Ins.state[i][copy] = 1;
					}

					if (str.text[i][j] != '@')
					{
						Ins.text[i][copy++] = str.text[i][j];
					}
				}

				copy = 0;
			}

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 150; j++)
				{
					str.text[i][j] = Ins.text[i][j];

					str.state[i][j] = Ins.state[i][j];
				}
			}

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 150; j++)
				{
					Ins.text[i][j] = temp.text[i][j];

					Ins.state[i][j] = temp.state[i][j];
				}
			}

			if (Capital)
			{
				PrintCapital(str);
			}

			else
			{
				for (int i = 0; i < 10; i++)
				{
					printf("%s", str.text[i]);
				}
			}

			printf("\n");

			Insert = 0;
		}

		else if (order == 'f' && !Down)
		{
			getchar();

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 150; j++)
				{
					if (str.text[i][j] == ' ' || (str.text[i][j] == '\n' && j != 0) || (str.text[i][j] == '\0' && Upside))
					{
						check = j - 1;

						point = check;

						if (str.text[i][copy] == '\n')
						{
							copy++;
							
							for (int k = copy; k <= check; k++)
							{
								Dow.text[i][copy] = str.text[i][point];

								Dow.state[i][copy++] = str.state[i][point--];
							}

							Dow.text[i][0] = '\n';
						}

						else
						{
							for (int k = copy; k <= check; k++)
							{
								Dow.text[i][copy] = str.text[i][point];

								Dow.state[i][copy++] = str.state[i][point--];
							}
						}

						Dow.text[i][copy++] = str.text[i][j];
					}
				}

				copy = 0;
			}

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 150; j++)
				{
					str.text[i][j] = Dow.text[i][j];

					str.state[i][j] = Dow.state[i][j];
				}
			}

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 150; j++)
				{
					Dow.text[i][j] = temp.text[i][j];

					Dow.state[i][j] = temp.state[i][j];
				}
			}

			if (Capital)
			{
				PrintCapital(str);
			}

			else
			{
				for (int i = 0; i < 10; i++)
				{
					printf("%s", str.text[i]);
				}
			}

			printf("\n");

			Down = 1;
		}

		else if (order == 'f' && Down)
		{
			getchar();

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 150; j++)
				{
					if (str.text[i][j] == ' ' || (str.text[i][j] == '\n' && j != 0) || (str.text[i][j] == '\0' && Upside))
					{
						check = j - 1;

						point = check;

						if (str.text[i][copy] == '\n')
						{
							copy++;

							for (int k = copy; k <= check; k++)
							{
								Dow.text[i][copy] = str.text[i][point];

								Dow.state[i][copy++] = str.state[i][point--];
							}

							Dow.text[i][0] = '\n';
						}

						else
						{
							for (int k = copy; k <= check; k++)
							{
								Dow.text[i][copy] = str.text[i][point];

								Dow.state[i][copy++] = str.state[i][point--];
							}
						}

						Dow.text[i][copy++] = str.text[i][j];
					}
				}

				copy = 0;
			}

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 150; j++)
				{
					str.text[i][j] = Dow.text[i][j];

					str.state[i][j] = Dow.state[i][j];
				}
			}

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 150; j++)
				{
					Dow.text[i][j] = temp.text[i][j];

					Dow.state[i][j] = temp.state[i][j];
				}
			}

			if (Capital)
			{
				PrintCapital(str);
			}

			else
			{
				for (int i = 0; i < 10; i++)
				{
					printf("%s", str.text[i]);
				}
			}

			printf("\n");

			Down = 0;
		}

		else if (order == 'g' && !Change)
		{
			getchar();

			printf("Before : ");

			scanf("%c", &chaword);

			getchar();

			printf("After : ");

			scanf("%c", &anoword);

			getchar();

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 150; j++)
				{
					if (str.text[i][j] == chaword)
					{
						str.text[i][j] = anoword;

						str.state[i][j] = 1;
					}
				}
			}

			if (Capital)
			{
				PrintCapital(str);
			}

			else
			{
				for (int i = 0; i < 10; i++)
				{
					printf("%s", str.text[i]);
				}
			}

			printf("\n");

			Change = 1;
		}

		else if (order == 'g' && Change)
		{
			getchar();

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 150; j++)
				{
					if (str.text[i][j] == anoword && str.state[i][j] == 1)
					{
						str.text[i][j] = chaword;

						str.state[i][j] = 0;
					}
				}
			}

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 150; j++)
				{
					temp.state[i][j] = 0;
				}
			}

			if (Capital)
			{
				PrintCapital(str);
			}

			else
			{
				for (int i = 0; i < 10; i++)
				{
					printf("%s", str.text[i]);
				}
			}

			printf("\n");

			Change = 0;
		}

		else if (order == 'h')
		{
			getchar();

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 150; j++)
				{
					if (str.text[i][j] == ' ')
					{
						word[i]++;
					}
				}

				copy = 0;
			}

			for (int i = 0; i < 10; i++)
			{
				printf("%d words\n", word[i] + 1);

				word[i] = 0;
			}
		}

		else if (order == 'r' && Sort == 0)
		{
			getchar();

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 150; j++)
				{
					if (str.text[i][j] == ' ' || str.text[i][j] == '\n')
					{
						sortword[i][copy].size = big;

						sortword[i][copy].end = j - 1;

						sortword[i][copy++].start = j - big;

						big = 0;
					}

					else if (i == 9 && str.text[i][j] == '\0')
					{
						sortword[i][copy].size = big;

						sortword[i][copy].end = j - 1;

						sortword[i][copy++].start = j - big;

						i = 10;

						big = 0;
					}

					else
					{
						big++;
					}
				}

				big = 0;

				copy = 0;
			}

			for (int i = 0; i < 10; i++)
			{
				sor = 30;

				for (int j = 0; j < 30; j++)
				{
					if (sortword[i][j].size == sor)
					{
						for (int k = sortword[i][j].start; k <= sortword[i][j].end; k++)
						{
							if (Capital)
							{
								if (str.text[i][k] >= 65 && str.text[i][k] <= 90 && (str.text[i][k - 1] == ' ' || k == 0))
								{
									check = 1;

									capword++;
								}

								else if (str.text[i][k + 1] == ' ' || str.text[i][k + 1] == '\n')
								{
									check = 0;
								}

								if (check)
								{
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);

									printf("%c", str.text[i][k]);
								}

								else if (!check)
								{
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

									printf("%c", str.text[i][k]);
								}
							}

							else
							{
								printf("%c", str.text[i][k]);
							}
						}

						printf(" ");
					}

					else if (j == 29 && sor != 0)
					{
						sor--;

						j = -1;
					}

					else if (sor == 0)
					{
						j = 30;
					}
				}

				printf("\n");
			}

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

			printf("Capital : %d\n", capword);

			capword = 0;

			Sort = 1;
		}

		else if (order == 'r' && Sort == 1)
		{
			getchar();

			for (int i = 0; i < 10; i++)
			{
				sor = 1;

				for (int j = 0; j < 30; j++)
				{
					if (sortword[i][j].size == sor)
					{
						for (int k = sortword[i][j].start; k <= sortword[i][j].end; k++)
						{
							if (Capital)
							{
								if (str.text[i][k] >= 65 && str.text[i][k] <= 90 && (str.text[i][k - 1] == ' ' || k == 0))
								{
									check = 1;

									capword++;
								}

								else if (str.text[i][k + 1] == ' ' || str.text[i][k + 1] == '\n')
								{
									check = 0;
								}

								if (check)
								{
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);

									printf("%c", str.text[i][k]);
								}

								else if (!check)
								{
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

									printf("%c", str.text[i][k]);
								}
							}

							else
							{
								printf("%c", str.text[i][k]);
							}
						}

						printf(" ");
					}

					else if (j == 29 && sor != 31)
					{
						sor++;

						j = -1;
					}

					else if (sor == 31)
					{
						j = 30;
					}
				}

				printf("\n");
			}

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

			printf("Capital : %d\n", capword);

			capword = 0;

			Sort = 2;
		}

		else if (order == 'r' && Sort == 2)
		{
			getchar();

			if (Capital)
			{
				PrintCapital(str);
			}

			else
			{
				for (int i = 0; i < 10; i++)
				{
					printf("%s", str.text[i]);
				}
			}

			printf("\n");

			Sort = 0;
		}

		else if (order == 's')
		{
			getchar();

			printf("Search : ");

			scanf("%s", &searword);

			getchar();

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 150; j++)
				{
					if (str.text[i][j] == ' ' || (str.text[i][j] == '\n' && j != 0) || (str.text[i][j] == '\0' && Upside))
					{
						check = j - 1;

						for (int k = copy; k <= check; k++)
						{
							Sea.text[i][copy] = str.text[i][copy++];
						}

						if (_strnicmp(Sea.text[i], searword, 50) == 0)
						{
							printf("Search :");

							Word++;

							for (int l = 0; l < 150; l++)
							{
								if (str.text[i][l] == searword[point++])
								{
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);

									printf("%c", str.text[i][l]);
								}

								else
								{
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

									printf("%c", str.text[i][l]);
								}
							}

							i = 10, j = 150, point = 0;
						}
					}
				}

				copy = 0;
			}

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 150; j++)
				{
					Sea.text[i][j] = temp.text[i][j];

					Sea.state[i][j] = temp.state[i][j];
				}
			}

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

			printf("Search Word : %d", Word);

			Word = 0;

			printf("\n");
		}

		else if (order == 'q')
		{
			break;
		}

		else
		{
			getchar();

			printf("This command does not exist.\n");
		}
	}

	fclose(fp);

	return 0;
}

void PrintCapital(String n)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 150; j++)
		{
			if (n.text[i][j] >= 65 && n.text[i][j] <= 90 && (n.text[i][j - 1] == ' ' || j == 0))
			{
				check = 1;

				capword++;
			}

			else if (n.text[i][j] == ' ' || n.text[i][j] == '\n')
			{
				check = 0;
			}

			if (check)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);

				printf("%c", n.text[i][j]);
			}

			else if (!check)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

				printf("%c", n.text[i][j]);
			}
		}
	}

	printf("\n");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	printf("Capital : %d\n", capword);

	Capital = 1;

	capword = 0;
}