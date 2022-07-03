#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include<iostream>
#include <windows.h>
using namespace std;
void gotoxy(int x, int y);

int main(void)
{
	int horse_num, i, number, k, max = 0, count = 0, rank[10] = { 0 };
	int horse[5] = { 0 }, race;
	char horse_name[10][10];
	clock_t start, end;
	double pst;
	srand(time(NULL));
	printf("경마게임\n\n");
	printf("경주할 말의 숫자(최대 10)를 입력하고 Enter>");
	scanf_s("%d", &horse_num);
	printf("\n\n");
	printf("%d개 말의 이름(최대 한글 3자)을 입력하고 Enter키를 누르세요.\n", horse_num);
	printf("\n");
	for (i = 0; i<horse_num; i++)
	{
		printf("%d번 말 이름 :", i + 1);
		fflush(stdin);
		//scanf_s("%s", horse_name[i]);
		cin >> horse_name[i];
	}
	system("cls");
	printf("\n\n");
	printf("(start)  1         10         20        30        40(end) 등수 시간(초)\n");
	printf("======================================================================\n");
	gotoxy(52, 1);
	printf("소요 시간:");
	for (i = 0; i<horse_num; i++)
	{
		gotoxy(1, 5 + i * 2);
		printf("%-8s:>", horse_name[i]);
	}
	printf("\n\n아무키나 누르면 경주 시작! \n");
	_getch();
	start = clock();
	while (count != horse_num)
	{

		number = rand() % horse_num;
		if (rank[number] != 0)
			continue;
		race = rand() % 2 + 1;
		horse[number] = horse[number] + race;
		Sleep(300);
		if (horse[number]>39)
		{
			horse[number] = 40;
			if (!rank[number])
			{
				count++;
				rank[number] = count;
				gotoxy(10, 5 + number * 2);
				for (k = 0; k<horse[number]; k++)
					printf(" ");
				if (horse[number])
					printf(">%d", horse[number]);
				gotoxy(55, 5 + number * 2);
				printf("   %d등    ", count);
				end = clock();
				pst = (double)(end - start) / CLK_TCK;
				printf("%6.3f", pst);

			}
		}
		else
		{
			gotoxy(10, 5 + number * 2);
			for (k = 0; k<horse[number]; k++)
				printf(" ");
			if (horse[number])
				printf(">%d", horse[number]);
		}
		gotoxy(62, 1);
		end = clock();
		pst = (double)(end - start) / CLK_TCK;
		printf("%6.3f초", pst);

	}
	gotoxy(1, 20);
	printf("게임 종료!\n");
	system("pause");
	return 0;
}

void gotoxy(int x, int y)
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}