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
	printf("�渶����\n\n");
	printf("������ ���� ����(�ִ� 10)�� �Է��ϰ� Enter>");
	scanf_s("%d", &horse_num);
	printf("\n\n");
	printf("%d�� ���� �̸�(�ִ� �ѱ� 3��)�� �Է��ϰ� EnterŰ�� ��������.\n", horse_num);
	printf("\n");
	for (i = 0; i<horse_num; i++)
	{
		printf("%d�� �� �̸� :", i + 1);
		fflush(stdin);
		//scanf_s("%s", horse_name[i]);
		cin >> horse_name[i];
	}
	system("cls");
	printf("\n\n");
	printf("(start)  1         10         20        30        40(end) ��� �ð�(��)\n");
	printf("======================================================================\n");
	gotoxy(52, 1);
	printf("�ҿ� �ð�:");
	for (i = 0; i<horse_num; i++)
	{
		gotoxy(1, 5 + i * 2);
		printf("%-8s:>", horse_name[i]);
	}
	printf("\n\n�ƹ�Ű�� ������ ���� ����! \n");
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
				printf("   %d��    ", count);
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
		printf("%6.3f��", pst);

	}
	gotoxy(1, 20);
	printf("���� ����!\n");
	system("pause");
	return 0;
}

void gotoxy(int x, int y)
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}