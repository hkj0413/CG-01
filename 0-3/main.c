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

LIST list[20] = { 0 };

int check = 0, boundary = 0;

void PrintList(LIST n[20]);

int main()
{
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
				if (list[i].exist == 0 && boundary != 20)
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

				else if (list[i].exist == 0 && boundary == 20)
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

			list[boundary - 1].exist = 0;

			boundary--;

			check--;

			PrintList(list);
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
	for (int i = 19; i>= 0; i--)
	{
		printf("%d\t", i);

		if (n[i].exist == 1)
		{
			printf("%d %d %d", n[i].x, n[i].y, n[i].z);
		}

		printf("\n");
	}
}