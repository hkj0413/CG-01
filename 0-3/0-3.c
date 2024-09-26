#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#pragma warning(disable:6031)

	struct LIST
{
	int x;
	int y;
	int z;
	double sqrt;
	int exist;

}typedef LIST;

LIST list[20] = { 0 }, Biglist[20] = { 0 }, Smalllist[20] = { 0 };

void PrintList(LIST n[20]);

void SortBigList(LIST n[20]);

void SortSmallList(LIST n[20]);

int main()
{
	int check = 0, boundary = 0, big = 0, small = 0;

	while (1)
	{
		char order = '\0';

		int coordx = 0, coordy = 0, coordz = 0;

		printf("command : ");

		scanf("%c", &order);

		if (order == '+')
		{
			getchar();

			printf("coordinate (x, y, z) : ");

			scanf("%d, %d, %d", &coordx, &coordy, &coordz);

			for (int i = boundary; i >= 0; i--)
			{
				if (list[i].exist == 0 && boundary != 19)
				{
					list[i].x = coordx;
					list[i].y = coordy;
					list[i].z = coordz;
					list[i].sqrt = sqrt(coordx * coordx + coordy * coordy + coordz * coordz);
					list[i].exist = 1;

					boundary++;

					check++;

					break;
				}

				else if (list[i].exist == 0 && boundary == 19)
				{
					list[i].x = coordx;
					list[i].y = coordy;
					list[i].z = coordz;
					list[i].sqrt = sqrt(coordx * coordx + coordy * coordy + coordz * coordz);
					list[i].exist = 1;

					check++;

					break;
				}

				else
				{
					list[19].x = coordx;
					list[19].y = coordy;
					list[19].z = coordz;
					list[19].sqrt = sqrt(coordx * coordx + coordy * coordy + coordz * coordz);

					break;
				}
			}

			PrintList(list);

			getchar();
		}

		else if (order == '-')
		{
			getchar();

			if (check != 0)
			{
				list[boundary].exist = 0;

				boundary--;

				check--;

				PrintList(list);
			}

			else
			{
				printf("There is nothing in list.\n");
			}
		}

		else if (order == 'e')
		{
			getchar();

			printf("coordinate (x, y, z) : ");

			scanf("%d, %d, %d", &coordx, &coordy, &coordz);

			for (int i = 18; i >= 0; i--)
			{
				list[i + 1].x = list[i].x;
				list[i + 1].y = list[i].y;
				list[i + 1].z = list[i].z;
				list[i + 1].sqrt = list[i].sqrt;
				list[i + 1].exist = list[i].exist;
			}

			list[0].x = coordx;
			list[0].y = coordy;
			list[0].z = coordz;
			list[0].sqrt = sqrt(coordx * coordx + coordy * coordy + coordz * coordz);
			list[0].exist = 1;

			check = 1;

			for (int i = 19; i >= 1; i--)
			{
				if (list[i].exist == 1)
				{
					check++;
				}
			}

			boundary = check;

			PrintList(list);

			getchar();
		}

		else if (order == 'd')
		{
			getchar();

			if (check != 0)
			{
				for (int i = 0; i <= boundary; i++)
				{
					if (list[i].exist == 1)
					{
						list[i].exist = 0;

						boundary--;

						break;
					}
				}

				if (list[0].exist == 0 && list[1].exist == 0 && list[2].exist == 0 && list[3].exist == 0 && list[4].exist == 0 && list[5].exist == 0 && list[6].exist == 0 && list[7].exist == 0 && list[8].exist == 0 && list[9].exist == 0 && list[10].exist == 0 && list[11].exist == 0 && list[12].exist == 0 && list[13].exist == 0 && list[14].exist == 0 && list[15].exist == 0 && list[16].exist == 0 && list[17].exist == 0 && list[18].exist == 0 && list[19].exist == 0)
				{
					boundary = 0;
				}

				check--;

				PrintList(list);
			}

			else
			{
				printf("There is nothing in list.\n");
			}
		}

		else if (order == 'l')
		{
			getchar();

			printf("%d count(s)\n", check);
		}

		else if (order == 'c')
		{
			getchar();

			for (int i = 0; i < 20; i++)
			{
				list[i].exist = 0;
			}

			boundary = 0;

			check = 0;

			PrintList(list);
		}

		else if (order == 'm')
		{
			getchar();

			double Max = list[0].sqrt;

			for (int i = 1; i < boundary; i++)
			{
				if (list[i].sqrt > Max && list[i].exist == 1)
				{
					Max = list[i].sqrt;
				}
			}

			for (int i = 0; i < boundary; i++)
			{
				if (list[i].sqrt == Max && list[i].exist == 1)
				{
					printf("(%d, %d, %d)\n", list[i].x, list[i].y, list[i].z);
				}
			}
		}

		else if (order == 'n')
		{
			getchar();

			double Min = list[0].sqrt;

			for (int i = 1; i < boundary; i++)
			{
				if (list[i].sqrt < Min && list[i].exist == 1)
				{
					Min = list[i].sqrt;
				}
			}

			for (int i = 0; i < boundary; i++)
			{
				if (list[i].sqrt == Min && list[i].exist == 1)
				{
					printf("(%d, %d, %d)\n", list[i].x, list[i].y, list[i].z);
				}
			}
		}

		else if (order == 'a')
		{
			getchar();

			if (!big)
			{
				big = 1;

				SortBigList(list);
			}

			else if (big)
			{
				big = 0;

				PrintList(list);
			}
		}

		else if (order == 's')
		{
			getchar();

			if (!small)
			{
				small = 1;

				SortSmallList(list);
			}

			else if (small)
			{
				small = 0;

				PrintList(list);
			}
		}

		else if (order == 'q')
		{
			getchar();

			break;
		}

		else
		{
			getchar();

			printf("This command does not exist.\n");
		}
	}

	return 0;
}

void PrintList(LIST n[20])
{
	for (int i = 19; i >= 0; i--)
	{
		printf("%d\t", i);

		if (n[i].exist == 1)
		{
			printf("%d %d %d", n[i].x, n[i].y, n[i].z);
		}

		printf("\n");
	}
}

void SortBigList(LIST n[20])
{
	LIST temp[20] = { 0 };

	for (int i = 0; i < 20; i++)
	{
		temp[i] = n[i];
	}

	int x = 0;

	while (1)
	{
		double Max = 0;

		for (int i = 0; i < 20; i++)
		{
			if (temp[i].sqrt > Max && temp[i].exist == 1)
			{
				Max = temp[i].sqrt;
			}
		}

		for (int i = 0; i < 20; i++)
		{
			if (temp[i].sqrt == Max && temp[i].exist == 1)
			{
				Biglist[x].x = temp[i].x;
				Biglist[x].y = temp[i].y;
				Biglist[x].z = temp[i].z;
				Biglist[x].sqrt = temp[i].sqrt;
				Biglist[x].exist = temp[i].exist;

				temp[i].exist = 0;

				x++;
			}
		}

		if (temp[0].exist == 0 && temp[1].exist == 0 && temp[2].exist == 0 && temp[3].exist == 0 && temp[4].exist == 0 && temp[5].exist == 0 && temp[6].exist == 0 && temp[7].exist == 0 && temp[8].exist == 0 && temp[9].exist == 0 && temp[10].exist == 0 && temp[11].exist == 0 && temp[12].exist == 0 && temp[13].exist == 0 && temp[14].exist == 0 && temp[15].exist == 0 && temp[16].exist == 0 && temp[17].exist == 0 && temp[18].exist == 0 && temp[19].exist == 0)
		{
			break;
		}
	}

	for (int i = 19; i >= 0; i--)
	{
		printf("%d\t", i);

		if (Biglist[i].exist == 1)
		{
			printf("%d %d %d", Biglist[i].x, Biglist[i].y, Biglist[i].z);
		}

		printf("\n");
	}
}

void SortSmallList(LIST n[20])
{
	LIST temp[20] = { 0 };

	for (int i = 0; i < 20; i++)
	{
		temp[i] = n[i];
	}

	int x = 0;

	while (1)
	{
		double Min = 10000;

		for (int i = 0; i < 20; i++)
		{
			if (temp[i].sqrt < Min && temp[i].exist == 1)
			{
				Min = temp[i].sqrt;
			}
		}

		for (int i = 0; i < 20; i++)
		{
			if (temp[i].sqrt == Min && temp[i].exist == 1)
			{
				Smalllist[x].x = temp[i].x;
				Smalllist[x].y = temp[i].y;
				Smalllist[x].z = temp[i].z;
				Smalllist[x].sqrt = temp[i].sqrt;
				Smalllist[x].exist = temp[i].exist;

				temp[i].exist = 0;

				x++;
			}
		}

		if (temp[0].exist == 0 && temp[1].exist == 0 && temp[2].exist == 0 && temp[3].exist == 0 && temp[4].exist == 0 && temp[5].exist == 0 && temp[6].exist == 0 && temp[7].exist == 0 && temp[8].exist == 0 && temp[9].exist == 0 && temp[10].exist == 0 && temp[11].exist == 0 && temp[12].exist == 0 && temp[13].exist == 0 && temp[14].exist == 0 && temp[15].exist == 0 && temp[16].exist == 0 && temp[17].exist == 0 && temp[18].exist == 0 && temp[19].exist == 0)
		{
			break;
		}
	}

	for (int i = 19; i >= 0; i--)
	{
		printf("%d\t", i);

		if (Smalllist[i].exist == 1)
		{
			printf("%d %d %d", Smalllist[i].x, Smalllist[i].y, Smalllist[i].z);
		}

		printf("\n");
	}
}