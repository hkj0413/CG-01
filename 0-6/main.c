#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#pragma warning(disable:6031)

struct Board
{
    int entity;
    int state;

}typedef Board;

Board board[30][30] = { 0 };

void SetBoard(Board n[30][30]);

void SetRoute(Board n[30][30]);

void PrintBoard(Board n[30][30]);

int ox = 0, oy = 0;

int main(void)
{
    int object = 0;

    SetBoard(board);

    SetRoute(board);

    PrintBoard(board);

    while (1)
    {
        char order = '\0';

        printf("command : ");

        scanf("%c", &order);

        if (order == 's')
        {
            getchar();

            SetRoute(board);

            PrintBoard(board);
        }

        else if (order == 'r')
        {
            getchar();

            if (!object)
            {
                board[oy][ox].state = 1;

                object = 1;
            }

            else if (object)
            {
                board[oy][ox].state = 0;

                object = 0;
            }

            PrintBoard(board);
        }

        else if (order == 'w' && object)
        {
            getchar();

            PrintBoard(board);
        }

        else if (order == 'a' && object)
        {
            getchar();

            PrintBoard(board);
        }

        else if (order == 's' && object)
        {
            getchar();

            PrintBoard(board);
        }

        else if (order == 'd' && object)
        {
            getchar();

            PrintBoard(board);
        }

        else if (order == 'q')
        {
            break;
        }

        else
        {
            printf("This command does not exist.\n");
        }
    }

    return 0;
}

void SetBoard(Board n[30][30])
{
    int count = 0, x = 0, y = 0;

    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            board[i][j].entity = 1;
        }
    }

    srand((unsigned)time(NULL));

    while (count < 30)
    {
        x = rand() % 29, y = rand() % 29;

        if (board[x][y].entity == 1 && !(x == 0 && y == 0) && !(x == 29 && y == 29) && (!(x == 1 && y == 0) || !(x == 0 && y == 1)) && (!(x == 28 && y == 29) || !(x == 29 && y == 28)))
        {
            board[x][y].entity = 2;

            count++;
        }
    }
}

void SetRoute(Board n[30][30])
{
    board[0][0].entity = 0;
    board[29][29].entity = 0;
}

void PrintBoard(Board n[30][30])
{
    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            if (board[i][j].entity == 0 && board[i][j].state == 0)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);

                printf("0 ");
            }

            else if (board[i][j].entity == 0 && board[i][j].state == 1)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);

                printf("* ");
            }

            else if (board[i][j].entity == 1)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

                printf("1 ");
            }

            else if (board[i][j].entity == 2)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);

                printf("X ");
            }
        }

        printf("\n");
    }
}