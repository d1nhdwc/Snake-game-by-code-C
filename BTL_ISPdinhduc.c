#include <stdio.h>					//Dinh Van Duc D24
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <windows.h>

int Length = 30;
int Height = 10;

enum state {MENU , MAP , LEVEL, GUIDE, INGAME} state;

void menu(){
	system("cls");
	printf("========== Snake Game ==========\n");
	printf("1. Choose the map\n");
	printf("2. Choose the level\n");
	printf("3. How to play!\n");
	printf("4. Start game!\n");
	printf("5. Exit game.\n");
	printf("Your choice: ");
	scanf("%d", &state);
}
 
int size = 1;
void map(){
	system("cls");
	printf("Select map size:\n");
	printf("- SMALL (1)\n");
	printf("- MEDIUM (2)\n");
	printf("- LARGE (3)\n \n");
	printf("Your choice: ");
	scanf("%d", &size);
	state = 0;
}

int difficult = 1;
void level(){
	system("cls");
	printf("Select difficulty:\n");
	printf("- EASY (1)\n");
	printf("- NORMAL (2)\n");
	printf("- HARD (3)\n \n");
	printf("Your choice: ");
	scanf("%d", &difficult);
	state = 0;
}

void guide(){
	system("cls");
	int cd = 20;
	while (cd > 0){
		printf("=");
		cd --;
	}
	int cd1 = 20;
	printf("Tutorial");
	while (cd1 > 0){
		printf("=");
		cd1 --;
	}
	Sleep(1000);
	printf("\n \n");
	printf("- Remember to switch Unikey to English\n");
	Sleep(1000);
	printf("- Use the W, A, S, D keys to control the snake (up, left, down, right)\n");
	Sleep(1000);
	printf("- After pressing Start Game, you will begin playing immediately\n");
	Sleep(1000);
	printf("- Control the snake and try to eat as much food as possible\n \n");
	Sleep(1000);
	printf("HAVE FUN !!!\n \n");
	Sleep(1000);
	printf("Type 0 to back to the MENU: ");
	scanf("%d", &state);
}

int snakeTX[100], snakeTY[100];
int snakeLen;
int gameover, dir, score, high_score = 0;
int snakeHX, snakeHY, moneyX, moneyY;

void initgame(){
	gameover = 0;
	snakeHX = Length / 2;
	snakeHY = Height / 2;
	moneyX = rand() % Length;
	moneyY = rand() % Height;
	while (moneyX == 0){
		moneyX = rand() % Length;
	}
	while (moneyY == 0){
		moneyY = rand() % Height;
	}
	score = 0;
}

void draw(){
	system("cls");
	int i = 0;
	for (i; i < Length + 2; i++) printf("=");
	printf("\n");
	i = 0;
	for (i; i < Height; i++){
		int j = 0;
		for (j; j <= Length; j++){
			if (j == 0 || j == Length) printf("#");
			if (j == snakeHX && i == snakeHY ){
				printf("O");
			}
			else if (j == moneyX && i == moneyY){
				printf("$");
			}else {
                int prTail = 0, k = 0;
                for (k; k < snakeLen; k++) {
                    if (snakeTX[k] == j && snakeTY[k] == i) {
                        printf("o");
                        prTail = 1;
                    }
                }
                if (!prTail)
                    printf(" ");
            }
		}
		printf("\n");
	}
	i = 0;
	for (i; i < Length + 2; i++) printf("=");
	printf(" \nMap: ");
	switch (size){
		case 1:
			printf("Small\n");
			break;
		case 2:
			printf("Medium\n");
			break;
		case 3:
			printf("Large\n");
			break;
	}
	printf("Difficult: ");
	switch (difficult){
		case 1:
			printf("Easy\n");
			break;
		case 2:
			printf("Normal\n");
			break;
		case 3:
			printf("Hard\n");
			break;
	}
	printf("Score = %d", score);
	printf("\t");
	printf("High Score: %d", high_score);
    printf("\n");
}

void inp_key(){
	if (kbhit()){
		switch (tolower(getch())){
			case 'a':
				if (dir != 2) dir = 1;
				break;
			case 'd':
				if (dir != 1) dir = 2;
				break;
			case 'w':
				if (dir != 4) dir = 3;
				break;
			case 's':
				if (dir != 3) dir = 4;
				break;			
		}
	}
}

void move(){
	int prevX = snakeTX[0];
    int prevY = snakeTY[0];
    int prev2X, prev2Y;
    snakeTX[0] = snakeHX;
    snakeTY[0] = snakeHY;
    int i = 1;
    for (i; i < snakeLen; i++) {
        prev2X = snakeTX[i];
        prev2Y = snakeTY[i];
        snakeTX[i] = prevX;
        snakeTY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
	switch(dir){
		case 1:
			snakeHX--;
			break;
		case 2:
			snakeHX++;
			break;
		case 3:
			snakeHY--;
			break;
		case 4:
			snakeHY++;
			break;
		default:
			break;
	}
	if (snakeHX < 0 || snakeHX >= Length || snakeHY < 0 || snakeHY >= Height){
		gameover = 1;
	}
	i = 0;
	for (i; i < snakeLen; i++){
		if (snakeTX[i] == snakeHX && snakeTY[i] == snakeHY){
			gameover = 1;
		}
	}
	if (snakeHX == moneyX && snakeHY == moneyY){
		moneyX = rand() % Length;
		moneyY = rand() % Height;
		while (moneyX == 0){
			moneyX = rand() % Length;
		}
		while (moneyY == 0){
			moneyY = rand() % Height;
		}
		score += 10;
		snakeLen ++;
		if (score > high_score){
			high_score = score;
		}
	}
}


void ingame(){
	switch (size){
		case 1:
			Length = 30;
			Height = 10;
			break;
		case 2:
			Length = 40;
			Height = 13;
			break;
		case 3:
			Length = 50;
			Height = 15;
			break;
	}
	draw();
	inp_key();
	move();
	switch (difficult){
		case 1:
			Sleep(60);
			break;
		case 2:
			Sleep(30);
			break;
		case 3:
			Sleep(2);
			break;
	}
}

int main(){
	state = 0;
	while(1){
		switch(state){
			case MENU:
				menu();
				break;
			case MAP:
				map();
				break;
			case LEVEL:
				level();
				break;
			case GUIDE: 
				guide();
				break;
			case INGAME:
				initgame();
				while (!gameover){
					ingame();
				}
				printf("\nGAMEOVER !!!! \n \n");
				printf("1. Play again\n2. Exit\n");
				printf("Your Choice: ");
				int again;
				scanf("%d", &again);
				switch(again){
					case 1:
						system("cls");					
						snakeLen = 0;
						state = 4;
						break;
					default:
						system("cls");					
						snakeLen = 0;
						state = 0;
				}
				break;
			default:
				return 0;
		}
	}
	return 0;
}
