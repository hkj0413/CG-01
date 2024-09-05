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

	fp = fopen("data.txt", "r");

	while (1)
	{
		char order = '\0';

		printf("command : ");

		scanf("%c", &order);

		if (order == 'q')
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