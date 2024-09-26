#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable:6031)

int main(void)
{
	int a[16] = { 0 }, b[16] = { 0 }, c[16] = { 0 }, enable = 0, x = 0, y = 0, z = 0, w = 0;

	srand((unsigned)time(0));

	for (int i = 0; i < 16; i++)
	{
		a[i] = rand() % 2;

		b[i] = rand() % 2;
	}

	x = rand() % 16;

	while (1)
	{
		y = rand() % 16;

		if (y == x)
		{
			continue;
		}

		else
		{
			break;
		}
	}

	z = rand() % 16;

	while (1)
	{
		w = rand() % 16;

		if (w == z)
		{
			continue;
		}

		else
		{
			break;
		}
	}

	a[x] = 2, a[y] = 2, b[z] = 2, b[w] = 2;

	printf("%d %d %d %d   %d %d %d %d\n%d %d %d %d   %d %d %d %d\n%d %d %d %d   %d %d %d %d\n%d %d %d %d   %d %d %d %d\n",
		a[0], a[1], a[2], a[3], b[0], b[1], b[2], b[3], a[4], a[5], a[6], a[7], b[4], b[5], b[6], b[7],
		a[8], a[9], a[10], a[11], b[8], b[9], b[10], b[11], a[12], a[13], a[14], a[15], b[12], b[13], b[14], b[15]);

	while (1)
	{
		char order = '\0';

		printf("command : ");

		scanf("%c", &order);

		if (order == 'm')
		{
			getchar();

			c[0] = a[0] * b[0] + a[1] * b[4] + a[2] * b[8] + a[3] * b[12];
			c[1] = a[0] * b[1] + a[1] * b[5] + a[2] * b[9] + a[3] * b[13];
			c[2] = a[0] * b[2] + a[1] * b[6] + a[2] * b[10] + a[3] * b[14];
			c[3] = a[0] * b[3] + a[1] * b[7] + a[2] * b[11] + a[3] * b[15];
			c[4] = a[4] * b[0] + a[5] * b[4] + a[6] * b[8] + a[7] * b[12];
			c[5] = a[4] * b[1] + a[5] * b[5] + a[6] * b[9] + a[7] * b[13];
			c[6] = a[4] * b[2] + a[5] * b[6] + a[6] * b[10] + a[7] * b[14];
			c[7] = a[4] * b[3] + a[5] * b[7] + a[6] * b[11] + a[7] * b[15];
			c[8] = a[8] * b[0] + a[9] * b[4] + a[10] * b[8] + a[11] * b[12];
			c[9] = a[8] * b[1] + a[9] * b[5] + a[10] * b[9] + a[11] * b[13];
			c[10] = a[8] * b[2] + a[9] * b[6] + a[10] * b[10] + a[11] * b[14];
			c[11] = a[8] * b[3] + a[9] * b[7] + a[10] * b[11] + a[11] * b[15];
			c[12] = a[12] * b[0] + a[13] * b[4] + a[14] * b[8] + a[15] * b[12];
			c[13] = a[12] * b[1] + a[13] * b[5] + a[14] * b[9] + a[15] * b[13];
			c[14] = a[12] * b[2] + a[13] * b[6] + a[14] * b[10] + a[15] * b[14];
			c[15] = a[12] * b[3] + a[13] * b[7] + a[14] * b[11] + a[15] * b[15];

			printf("%d %d %d %d\n%d %d %d %d\n%d %d %d %d\n%d %d %d %d\n",
				c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7], c[8], c[9], c[10], c[11], c[12], c[13], c[14], c[15]);
		}

		else if (order == 'a')
		{
			getchar();

			for (int i = 0; i < 16; i++)
			{
				c[i] = a[i] + b[i];
			}

			printf("%d %d %d %d\n%d %d %d %d\n%d %d %d %d\n%d %d %d %d\n",
				c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7], c[8], c[9], c[10], c[11], c[12], c[13], c[14], c[15]);
		}

		else if (order == 'd')
		{
			getchar();

			for (int i = 0; i < 16; i++)
			{
				c[i] = a[i] - b[i];
			}

			printf("%d %d %d %d\n%d %d %d %d\n%d %d %d %d\n%d %d %d %d\n",
				c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7], c[8], c[9], c[10], c[11], c[12], c[13], c[14], c[15]);
		}

		else if (order == 'r')
		{
			getchar();

			printf("%d, %d\n", (a[0] * a[5] * a[10] * a[15] + a[0] * a[6] * a[11] * a[13] + a[0] * a[7] * a[9] * a[14]
				- a[0] * a[7] * a[10] * a[13] - a[0] * a[6] * a[9] * a[15] - a[0] * a[5] * a[11] * a[14]
				- a[1] * a[4] * a[10] * a[15] - a[2] * a[4] * a[11] * a[13] - a[3] * a[4] * a[9] * a[14]
				+ a[3] * a[4] * a[10] * a[13] + a[2] * a[4] * a[9] * a[15] + a[1] * a[4] * a[11] * a[14]
				+ a[1] * a[6] * a[8] * a[15] + a[2] * a[7] * a[8] * a[13] + a[3] * a[5] * a[8] * a[14]
				- a[3] * a[6] * a[8] * a[13] - a[2] * a[5] * a[8] * a[15] - a[1] * a[7] * a[8] * a[14]
				- a[1] * a[6] * a[11] * a[12] - a[2] * a[7] * a[9] * a[12] - a[3] * a[5] * a[10] * a[12]
				+ a[3] * a[6] * a[9] * a[12] + a[2] * a[5] * a[11] * a[12] + a[1] * a[7] * a[10] * a[12]),
				(b[0] * b[5] * b[10] * b[15] + b[0] * b[6] * b[11] * b[13] + b[0] * b[7] * b[9] * b[14]
					- b[0] * b[7] * b[10] * b[13] - b[0] * b[6] * b[9] * b[15] - b[0] * b[5] * b[11] * b[14]
					- b[1] * b[4] * b[10] * b[15] - b[2] * b[4] * b[11] * b[13] - b[3] * b[4] * b[9] * b[14]
					+ b[3] * b[4] * b[10] * b[13] + b[2] * b[4] * b[9] * b[15] + b[1] * b[4] * b[11] * b[14]
					+ b[1] * b[6] * b[8] * b[15] + b[2] * b[7] * b[8] * b[13] + b[3] * b[5] * b[8] * b[14]
					- b[3] * b[6] * b[8] * b[13] - b[2] * b[5] * b[8] * b[15] - b[1] * b[7] * b[8] * b[14]
					- b[1] * b[6] * b[11] * b[12] - b[2] * b[7] * b[9] * b[12] - b[3] * b[5] * b[10] * b[12]
					+ b[3] * b[6] * b[9] * b[12] + b[2] * b[5] * b[11] * b[12] + b[1] * b[7] * b[10] * b[12]));
		}

		else if (order == 't')
		{
			getchar();

			for (int i = 0; i < 16; i++)
			{
				c[i] = a[i];
			}

			a[1] = c[4];
			a[2] = c[8];
			a[3] = c[12];
			a[4] = c[1];
			a[6] = c[9];
			a[7] = c[13];
			a[8] = c[2];
			a[9] = c[6];
			a[11] = c[14];
			a[12] = c[3];
			a[13] = c[7];
			a[14] = c[11];

			for (int i = 0; i < 16; i++)
			{
				c[i] = b[i];
			}

			b[1] = c[4];
			b[2] = c[8];
			b[3] = c[12];
			b[4] = c[1];
			b[6] = c[9];
			b[7] = c[13];
			b[8] = c[2];
			b[9] = c[6];
			b[11] = c[14];
			b[12] = c[3];
			b[13] = c[7];
			b[14] = c[11];

			printf("%d %d %d %d   %d %d %d %d\n%d %d %d %d   %d %d %d %d\n%d %d %d %d   %d %d %d %d\n%d %d %d %d   %d %d %d %d\n",
				a[0], a[1], a[2], a[3], b[0], b[1], b[2], b[3], a[4], a[5], a[6], a[7], b[4], b[5], b[6], b[7],
				a[8], a[9], a[10], a[11], b[8], b[9], b[10], b[11], a[12], a[13], a[14], a[15], b[12], b[13], b[14], b[15]);

			printf("%d, %d\n", (a[0] * a[5] * a[10] * a[15] + a[0] * a[6] * a[11] * a[13] + a[0] * a[7] * a[9] * a[14]
				- a[0] * a[7] * a[10] * a[13] - a[0] * a[6] * a[9] * a[15] - a[0] * a[5] * a[11] * a[14]
				- a[1] * a[4] * a[10] * a[15] - a[2] * a[4] * a[11] * a[13] - a[3] * a[4] * a[9] * a[14]
				+ a[3] * a[4] * a[10] * a[13] + a[2] * a[4] * a[9] * a[15] + a[1] * a[4] * a[11] * a[14]
				+ a[1] * a[6] * a[8] * a[15] + a[2] * a[7] * a[8] * a[13] + a[3] * a[5] * a[8] * a[14]
				- a[3] * a[6] * a[8] * a[13] - a[2] * a[5] * a[8] * a[15] - a[1] * a[7] * a[8] * a[14]
				- a[1] * a[6] * a[11] * a[12] - a[2] * a[7] * a[9] * a[12] - a[3] * a[5] * a[10] * a[12]
				+ a[3] * a[6] * a[9] * a[12] + a[2] * a[5] * a[11] * a[12] + a[1] * a[7] * a[10] * a[12]),
				(b[0] * b[5] * b[10] * b[15] + b[0] * b[6] * b[11] * b[13] + b[0] * b[7] * b[9] * b[14]
					- b[0] * b[7] * b[10] * b[13] - b[0] * b[6] * b[9] * b[15] - b[0] * b[5] * b[11] * b[14]
					- b[1] * b[4] * b[10] * b[15] - b[2] * b[4] * b[11] * b[13] - b[3] * b[4] * b[9] * b[14]
					+ b[3] * b[4] * b[10] * b[13] + b[2] * b[4] * b[9] * b[15] + b[1] * b[4] * b[11] * b[14]
					+ b[1] * b[6] * b[8] * b[15] + b[2] * b[7] * b[8] * b[13] + b[3] * b[5] * b[8] * b[14]
					- b[3] * b[6] * b[8] * b[13] - b[2] * b[5] * b[8] * b[15] - b[1] * b[7] * b[8] * b[14]
					- b[1] * b[6] * b[11] * b[12] - b[2] * b[7] * b[9] * b[12] - b[3] * b[5] * b[10] * b[12]
					+ b[3] * b[6] * b[9] * b[12] + b[2] * b[5] * b[11] * b[12] + b[1] * b[7] * b[10] * b[12]));
		}


		else if (order == 'e' && enable == 0)
		{
			getchar();

			int l = 0, h = 0;

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (a[l] % 2 == 0)
					{
						printf("%d ", a[l]);
					}

					else
					{
						printf("X ");
					}

					l++;
				}

				printf("  ");

				for (int k = 0; k < 4; k++)
				{
					if (b[h] % 2 == 0)
					{
						printf("%d ", b[h]);
					}

					else
					{
						printf("X ");
					}

					h++;
				}

				printf("\n");
			}

			enable++;
		}

		else if (order == 'e' && enable == 1)
		{
			getchar();

			int l = 0, h = 0;

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (a[l] % 2 == 1)
					{
						printf("%d ", a[l]);
					}

					else
					{
						printf("X ");
					}

					l++;
				}

				printf("  ");

				for (int k = 0; k < 4; k++)
				{
					if (b[h] % 2 == 1)
					{
						printf("%d ", b[h]);
					}

					else
					{
						printf("X ");
					}

					h++;
				}

				printf("\n");
			}

			enable++;
		}

		else if (order == 'e' && enable == 2)
		{
			getchar();

			printf("%d %d %d %d   %d %d %d %d\n%d %d %d %d   %d %d %d %d\n%d %d %d %d   %d %d %d %d\n%d %d %d %d   %d %d %d %d\n",
				a[0], a[1], a[2], a[3], b[0], b[1], b[2], b[3], a[4], a[5], a[6], a[7], b[4], b[5], b[6], b[7],
				a[8], a[9], a[10], a[11], b[8], b[9], b[10], b[11], a[12], a[13], a[14], a[15], b[12], b[13], b[14], b[15]);

			enable = 0;
		}

		else if (order == 's')
		{
			getchar();

			for (int i = 0; i < 16; i++)
			{
				a[i] = rand() % 2;

				b[i] = rand() % 2;
			}

			x = rand() % 16;

			while (1)
			{
				y = rand() % 16;

				if (y == x)
				{
					continue;
				}

				else
				{
					break;
				}
			}

			z = rand() % 16;

			while (1)
			{
				w = rand() % 16;

				if (w == z)
				{
					continue;
				}

				else
				{
					break;
				}
			}

			a[x] = 2, a[y] = 2, b[z] = 2, b[w] = 2;

			printf("%d %d %d %d   %d %d %d %d\n%d %d %d %d   %d %d %d %d\n%d %d %d %d   %d %d %d %d\n%d %d %d %d   %d %d %d %d\n",
				a[0], a[1], a[2], a[3], b[0], b[1], b[2], b[3], a[4], a[5], a[6], a[7], b[4], b[5], b[6], b[7],
				a[8], a[9], a[10], a[11], b[8], b[9], b[10], b[11], a[12], a[13], a[14], a[15], b[12], b[13], b[14], b[15]);
		}

		else if (order >= 49 && order <= 57)
		{
			getchar();

			for (int i = 0; i < 16; i++)
			{
				a[i] *= (int)order - 48;

				b[i] *= (int)order - 48;
			}

			printf("%d %d %d %d   %d %d %d %d\n%d %d %d %d   %d %d %d %d\n%d %d %d %d   %d %d %d %d\n%d %d %d %d   %d %d %d %d\n",
				a[0], a[1], a[2], a[3], b[0], b[1], b[2], b[3], a[4], a[5], a[6], a[7], b[4], b[5], b[6], b[7],
				a[8], a[9], a[10], a[11], b[8], b[9], b[10], b[11], a[12], a[13], a[14], a[15], b[12], b[13], b[14], b[15]);
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