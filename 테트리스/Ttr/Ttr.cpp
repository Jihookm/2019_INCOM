// Ttr.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "stdio.h"
#include "windows.h"		//콘솔 정보변경, system함수, exit함수
#include "time.h"			//랜덤 설정
#include "conio.h"			//kbhit() 입력버퍼에 값이 있는지 확인, getch() 입력버퍼에서 값을 읽어옴
#include "stdlib.h"
#include "stdafx.h"
//key ASCII code
#define ARROW_KEY -32
#define UP_KEY 72
#define LEFT_KEY 75
#define RIGHT_KEY 77
#define DOWN_KEY 80

#define MAP_WIDTH 9
#define MAP_HEIGHT 21

void gotoxy(int x, int y) {
	COORD pos = { 2 * x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int map[MAP_HEIGHT + 2][MAP_WIDTH + 2] = { 0 };		//-1:wall, 0:empty, 1:block, 2:stack block
const int block_list[][4][4] = {
	//ㅁㅁㅁㅁ
	{ { 0,0,0,0 },
{ 1,1,1,1 },
{ 0,0,0,0 },
{ 0,0,0,0 } },
//ㅁ
//ㅁㅁㅁ
{ { 1,0,0,0 },
{ 1,1,1,0 },
{ 0,0,0,0 },
{ 0,0,0,0 } },
//    ㅁ
//ㅁㅁㅁ
{ { 0,0,1,0 },
{ 1,1,1,0 },
{ 0,0,0,0 },
{ 0,0,0,0 } },
//ㅁㅁ
//ㅁㅁ
{ { 0,0,0,0 },
{ 0,1,1,0 },
{ 0,1,1,0 },
{ 0,0,0,0 } },
//  ㅁㅁ
//ㅁㅁ
{ { 0,0,0,0 },
{ 0,1,1,0 },
{ 1,1,0,0 },
{ 0,0,0,0 } },
//  ㅁ
//ㅁㅁㅁ
{ { 0,1,0,0 },
{ 1,1,1,0 },
{ 0,0,0,0 },
{ 0,0,0,0 } },
//ㅁㅁ
//  ㅁㅁ
{ { 0,0,0,0 },
{ 1,1,0,0 },
{ 0,1,1,0 },
{ 0,0,0,0 } }
};
int current_state = 0;		//0~6
int current_block[4][4];
int x, y;
int score = 0;
bool is_gameover = false;

bool collison_check(int x, int y, int arr[4][4]);
void rotate();
void drop_block();
void scoring_check();
void death_check();
bool falling();

int main()
{
	/*setting*/
	//set Random
	srand(time(NULL));
	//set cursor invisible
	CONSOLE_CURSOR_INFO CurInfo;
	CurInfo.dwSize = 1;
	CurInfo.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
	//set wall
	for (int i = 0; i<MAP_HEIGHT + 2; i++) {
		for (int j = 0; j<MAP_WIDTH + 2; j++) {
			if (i == MAP_HEIGHT + 1 || j == 0 || j == MAP_WIDTH + 1) map[i][j] = -1;
		}
	}
	//drop first block
	drop_block();
	//clear console
	system("cls");

	//start loop
	while (true) {
		//key check
		char key;
		if (_kbhit()) {
			key = _getch();
			if (key == 'q' || key == 'Q') {
				system("cls");
				exit(0);
			}
			else if (key == ' ') {
				while (!falling());
			}
			else if (key == ARROW_KEY) {
				key = _getch();
				if (key == UP_KEY) {
					rotate();
				}
				else if (key == LEFT_KEY) {
					if (!collison_check(x - 1, y, current_block))
						x--;
				}
				else if (key == RIGHT_KEY) {
					if (!collison_check(x + 1, y, current_block))
						x++;
				}
				else if (key == DOWN_KEY) {
					falling();
				}
			}
		}
		if (!is_gameover) {
			falling();

			/*set block to map for remove flicker*/
			//remove prev block
			for (int i = 0; i<MAP_HEIGHT + 2; i++)
				for (int j = 0; j<MAP_WIDTH + 2; j++)
					if (map[i][j] == 1) map[i][j] = 0;
			//set current block
			for (int i = 0; i<4; i++)
				for (int j = 0; j<4; j++)
					if (current_block[i][j]) map[y + i][x + j] = 1;
			/*draw*/
			gotoxy(5, 1);
			printf("SCORE : %d", score);
			for (int i = 0; i<MAP_HEIGHT + 2; i++) {
				for (int j = 0; j<MAP_WIDTH + 2; j++) {
					gotoxy(j + 5, i + 3);
					if (map[i][j] == -1) printf("▣");
					else if (map[i][j] == 1) printf("□");
					else if (map[i][j] == 2) printf("■");
					else if (i == 1 && 0<j && j<MAP_WIDTH + 1) printf("__");
					else printf("  ");
					//printf("%d\n", map[i][j]);
				}
			}
		}
		else if (is_gameover) {
			gotoxy(8, 15);
			printf("GAME OVER");
		}
		gotoxy(5, 27);
		printf("PRESS 'Q' TO EXIT GAME");

		//delay
		Sleep(100);
	}
	return 0;
}

bool collison_check(int x, int y, int arr[4][4]) {
	for (int i = 0; i<4; i++) {
		for (int j = 0; j<4; j++) {
			if ((map[y + i][x + j] == -1 || map[y + i][x + j] == 2) && arr[i][j] == 1) return true;
		}
	}
	return false;
}

void rotate() {
	if (current_state == 0) {
		int tmp[4][4] = { 0 };
		if (current_block[0][1]) {
			for (int i = 0; i<4; i++)
				for (int j = 0; j<4; j++)
					tmp[j][3 - i] = current_block[i][j];
			if (!collison_check(x, y, tmp)) {
				for (int i = 0; i<4; i++)
					for (int j = 0; j<4; j++)
						current_block[i][j] = tmp[i][j];
			}
		}
		else if (current_block[1][0]) {
			for (int i = 0; i<4; i++)
				for (int j = 0; j<4; j++)
					tmp[3 - j][i] = current_block[i][j];
			if (!collison_check(x, y, tmp)) {
				for (int i = 0; i<4; i++)
					for (int j = 0; j<4; j++)
						current_block[i][j] = tmp[i][j];
			}
		}
	}
	else if (current_state == 1 || current_state == 2 || current_state == 5) {
		int tmp[4][4] = { 0 };
		for (int i = 0; i<3; i++)
			for (int j = 0; j<3; j++)
				tmp[j][2 - i] = current_block[i][j];
		if (!collison_check(x, y, tmp)) {
			for (int i = 0; i<4; i++)
				for (int j = 0; j<4; j++)
					current_block[i][j] = tmp[i][j];
		}
	}
	else if (current_state == 4 || current_state == 6) {
		int tmp[4][4] = { 0 };
		if (current_block[0][0] == 0 && current_block[0][1] == 0 && current_block[0][2] == 0) {
			for (int i = 0; i<3; i++)
				for (int j = 0; j<3; j++)
					tmp[j][2 - i] = current_block[i][j];
			if (!collison_check(x, y, tmp)) {
				for (int i = 0; i<4; i++)
					for (int j = 0; j<4; j++)
						current_block[i][j] = tmp[i][j];
			}
		}
		else if (current_block[0][2] == 0 && current_block[1][2] == 0 && current_block[2][2] == 0) {
			for (int i = 0; i<3; i++)
				for (int j = 0; j<3; j++)
					tmp[2 - j][i] = current_block[i][j];
			if (!collison_check(x, y, tmp)) {
				for (int i = 0; i<4; i++)
					for (int j = 0; j<4; j++)
						current_block[i][j] = tmp[i][j];
			}
		}
	}
}

void drop_block() {
	//set start position
	x = 3; y = 0;
	//set block
	current_state = rand() % 7;
	for (int i = 0; i<4; i++)
		for (int j = 0; j<4; j++)
			current_block[i][j] = block_list[current_state][i][j];
}

void scoring_check() {
	for (int i = MAP_HEIGHT; i>0; i--) {
		bool flag = true;
		for (int j = 1; j<MAP_WIDTH + 1; j++) {
			if (map[i][j] == 0) flag = false;
		}
		if (flag) {
			score++;
			for (int k = i; k>1; k--) {
				for (int l = 1; l<MAP_WIDTH + 1; l++) {
					map[k][l] = map[k - 1][l];
				}
			}
			i++;
		}
	}
}

void death_check() {
	for (int i = 1; i<MAP_WIDTH + 1; i++)
		if (map[1][i] == 2) is_gameover = true;
}

bool falling() {
	if (collison_check(x, y + 1, current_block)) {
		for (int i = 0; i<4; i++)
			for (int j = 0; j<4; j++)
				if (current_block[i][j]) map[y + i][x + j] = 2;
		scoring_check();
		death_check();
		drop_block();
		return true;
	}
	else {
		y++;
		return false;
	}
}


