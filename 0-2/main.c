#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable:6031)

int main(void)
{
	FILE* fp;

	int X = 0, space = 0, word[10] = { 0 }, copy = 0, Cap = 0, Upside = 0;

	char str[10][100] = { 0 }, temp[10][100] = { 0 }, Ups[10][100] = { 0 };

	fp = fopen("data.txt", "r");

	while (fgets(temp[X], sizeof(temp[X]), fp) != NULL)
	{
		X++;
	}

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (temp[i][j] == ' ' && !space)
			{
				str[i][copy++] = temp[i][j];

				word[i]++;

				space = 1;
			}

			else if (temp[i][j] == ' ' && space)
			{
				
			}

			else
			{
				str[i][copy++] = temp[i][j];

				space = 0;
			}
		}

		word[i]++;

		copy = 0;
	}

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (str[i][99 - j] != '\0')
			{
				Ups[i][copy++] = str[i][99 - j];
			}
		}

		if (i == 8)
		{
			Ups[i][copy++] = '\n';
		}

		else if (i == 9)
		{
			Ups[i][copy++] = '\n';
		}

		copy = 0;
	}
	
	for (int i = 0; i < 10; i++)
	{
		printf("%s", str[i]);
	}

	printf("\n");

	while (1)
	{
		char order = '\0';

		printf("command : ");

		scanf("%c", &order);

		if (order == 'c')
		{
			getchar();

			
		}

		else if (order == 'd' && !Upside)
		{
			getchar();

			for (int i = 0; i < 10; i++)
			{
				printf("%s", Ups[i]);
			}

			Upside = 1;
		}

		else if (order == 'd' && Upside)
		{
			getchar();

			for (int i = 0; i < 10; i++)
			{
				printf("%s", str[i]);
			}

			printf("\n");

			Upside = 0;
		}

		else if (order == 'h')
		{
			getchar();

			for (int i = 0; i < 10; i++)
			{
				printf("%d words\n", word[i]);
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

	fclose(fp);

	return 0;
}