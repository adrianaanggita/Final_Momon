#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#define PROPERTY_COUNT 20

/* DATA */

typedef struct {
	char date[26];
	char time[10];
	char name[10];
	char enter;
	int score;
}score;

typedef struct {
	char date[26];
	char time[10];
	char name[10];
	char enter;
	int score;
} high;

typedef enum playerType {
	none = -1, user, ez, med, hd
} playerType;

typedef enum blocktype {
	start, property, tax, punish, fortune
} blocktype;

typedef struct player {
	playerType type;
	int position;
	int blockOwned[PROPERTY_COUNT];
	int account; 
	int skipTurn;
	char *name;
} player;

typedef struct block {
	int blockID;
	char *name;
	int price;
	int rent;
	int rent1;
	int rent2;
	int rent3;
	int rent4;
	int housePrice;
	int houseOwned;
	blocktype type;
	player owner;
	struct block *next;
} block;

/* VARIABEL GLOBAL */

char name[5];

/* MODUL MAIN MENU */

void help();
void scoreHistory();
void highScore();
void credit();
void menuGame();
void gameChoice();
void entryScore(player *player1);
void entryName();

/* MODUL MAP/PRINT */

void gotoxy(int x, int y);
void printMenuAwal();
void printTitle(int i, int j);
void menuGame();
void initBoard(block *board);
void boardName(block *board, int j, bool baris);
void printPlayerMoney(player* player1, player* player2);
void printMenuGame();
void printKartu(block *board);
void printBoard(block *board, player player1, player player2);

/* MODUL PLAY GAME */

int  rollDice();
int  buildHouse(block*atmBlock, player* activePlayer);
void addOwned(player* activePlayer);
void copyOwner(player * old, player * new);
void buyProp(block *atmBlock, player *activePlayer);
int  countProp(player activePlayer);
int  showProp(block *board, struct player activePlayer);
void sellProp(block *board, player* activePlayer);
int  insufficientFund(block *board, player* activePlayer, int requiredMoney); 
void payRent(block *board, player* activePlayer,player * owner);	
void askBuy(block *board, player* activePlayer);
void afterDiceUser(block *board, player* activePlayer, player* passivePlayer);
int  averagePropPrice(block *board,player *activePlayer);
void turn(block *board, player* activePlayer, player * passivePlayer);
void afterDicePC(block *board, player* activePlayer, player* passivePlayer);	
int  checkFinish(player activePlayer);
void playGame(block *board, player* player1, player* player2);
int  startGame(int option);

/* ALGORITMA */

int main() {
	int option;
	
	do 
	{
		system("mode 131, 31");
		system("cls");
		printMenuAwal();
		gotoxy(55, 22); scanf("%d", &option);
		
		if (option == 1)
		{
			gameChoice();
		}
		else if (option == 2)
		{
			highScore();
		}
		else if (option == 3)
		{
			scoreHistory();
		}
		else if (option == 4)
		{
			help();
		}
		else if (option == 5)
		{
			credit();
		}
	}
	while (option != 6);
	
}

/*BODY PROCEDURE AND FUNCTION MAIN MENU */

void help() {
	system("cls");
	system("mode 130, 90");
	FILE *fhelp;
	fhelp = fopen("Help.txt", "r");
	int help = getc(fhelp);
	while (help != EOF)
	{
		putchar(help);
		help = getc(fhelp);
	}
	fclose(fhelp);
	printf ("\n");
	system ("pause");
}

void scoreHistory() {	
	system("cls");
	FILE *fscore;
	int iscore = 1;
	int i, j;
	score skor;

	if ((fscore = fopen("HighScore.txt", "rb")) == NULL) 
	{
		printf("File tidak dapat dibuka\n");
		exit(1);
	}
	gotoxy(32, 3);
	for (i = 0; i < 3; i++) 
	{
		switch (i) 
		{
			case 0:
				printf ("%c", 201); break;
			case 1:
				for (j = 0; j < 63; j++) 
				{
					printf ("%c", 205);
				} 
				break;
			case 2:
				printf ("%c", 187); break;
		}
	}
	gotoxy(32, 4)	; printf("%c                                                               %c\n", 186, 186);
	gotoxy(54, 4); printf ("MONOPOLY SCORE HISTORY");
	gotoxy(32, 5); for (i = 0; i < 65; i++) 
	{
		switch (i) 
		{
			case 0:
				printf ("%c", 204); break;
			case 7:
				printf("%c", 203); break;
			case 30:
				printf("%c", 203); break;
			case 40:
				printf("%c", 203); break;
			case 64:
				printf("%c", 185); break;
			default :
				printf("%c", 205); break;
		}

	}
	gotoxy(32, 6); printf ("%c  NO  %c     DATES & TIMES    %c  NAMES\t%c  \t SCORES\t\t%c\n",186,186,186,186,186);
	gotoxy(32, 7); for (i = 0; i < 65; i++) 
	{
		switch (i) 
		{
			case 0:
				printf("%c", 204); break;
			case 7:
				printf("%c", 206); break;
			case 30:
				printf("%c", 206); break;
			case 40:
				printf("%c", 206); break;
			case 64:
				printf("%c", 185); break;
			default :
				printf("%c", 205); break;
		}
	}
	printf("\n");
	fscanf (fscore, "%s %s %s %d%c", &skor.date, &skor.time, &skor.name, &skor.score, &skor.enter);
	
	gotoxy(32, 8);
	i = 8;
	while (!feof(fscore)) 
	{
	gotoxy(32, i);
		printf ("%c %d    %c %s %s  %c  %s\t%c\t\t\t%c\n", 186, iscore, 186, skor.date, skor.time, 186, skor.name, 186, 186);
		fscanf (fscore, "%s %s %s %d%c", &skor.date, &skor.time, &skor.name, &skor.score, &skor.enter);
		iscore++;
		i++;
	}
	gotoxy(32, i);
	for (i = 0; i < 65; i++) 
	{
		switch(i){
			case 0:
				printf("%c", 200); break;
			case 7:
				printf("%c", 202); break;
			case 30:
				printf("%c", 202); break;
			case 40:
				printf("%c", 202); break;
			case 64:
				printf("%c", 188); break;
			default :
				printf("%c", 205); break;
		}
	}

	rewind(fscore);
	iscore = 0;
	fscanf(fscore, "%s %s %s %d%c", &skor.date, &skor.time, &skor.name, &skor.score, &skor.enter);
	while (!feof(fscore)) 
	{
		gotoxy(80, 8 + iscore);
		printf("$%d", skor.score);
		fscanf(fscore, "%s %s %s %d%c",&skor.date,&skor.time,&skor.name,&skor.score,&skor.enter);
		iscore++;
	}
	
	gotoxy(32, 12 + iscore); system ("pause");
}

void highScore() {	
	system("cls");
	system("mode 131, 16");
	int i, j;
	FILE *fhigh;
	int tempsc;
	char tempdat[26];
	char temptim[10];
	char tempnam[10];
	high high;	

	if((fhigh = fopen("HighScore.txt", "rb")) == NULL) { 
		printf("File tidak dapat dibuka\n");
		exit(1);
	}
	gotoxy(30, 3)	; for (i = 0; i < 3; i++) {
		switch (i) 
		{
			case 0:
				printf ("%c", 201); break;
			case 1:
				for (j = 0; j < 68; j++) 
				{
					printf ("%c", 205);
				} break;
			case 2:
				printf ("%c", 187); break;
		}
	}
	gotoxy(30, 4)	; printf("%c                                                                    %c\n", 186, 186);
	gotoxy(30, 5)	; printf("%c                                                                    %c\n", 186, 186);
	gotoxy(30, 6)	; printf("%c                                                                    %c\n", 186, 186);
	gotoxy(30, 7)	; printf("%c                                                                    %c\n", 186, 186);
	gotoxy(58, 5)	; printf("SKOR TERTINGGI");                           
	fscanf(fhigh, "%s %s %s %d%c", &high.date, &high.time, &high.name, &high.score, &high.enter);
	tempsc = high.score;
	strcpy(tempdat, high.date);
	strcpy(temptim, high.time);
	strcpy(tempnam, high.name);
	while (!feof(fhigh)) 
	{
		if(high.score>tempsc)
		{
			tempsc = high.score;
			strcpy(tempdat,high.date);
			strcpy(temptim,high.time);
			strcpy(tempnam,high.name);
		}
		fscanf (fhigh, "%s %s %s %d%c", &high.date, &high.time, &high.name, &high.score, &high.enter);
	}
	gotoxy(45, 6);
	printf("$%d oleh %s - %s %s", tempsc, tempnam, tempdat, temptim);
	fclose(fhigh);
	gotoxy(30, 8)  ; for (i = 0; i < 3; i++) {
		switch (i) {
			case 0:
				printf ("%c", 200); break;
			case 1:
				for (j = 0; j < 68; j++) 
				{
					printf ("%c", 205);
				} 
				break;
			case 2:
				printf ("%c", 188); break;
		}
	}
	printf ("\n");
	gotoxy(30, 12); system("pause");
}

void credit() {
	system ("cls");
	system("mode 131, 25");
	FILE *fptr;
	fptr = fopen("Credits.txt", "r");
	int ch = getc(fptr);
	
	printf ("\n");
	while(ch != EOF)
	{	
		putchar(ch);
		ch = getc(fptr);
		
	}
	fclose(fptr);
	printf ("\n");
	gotoxy(8, 16);
	system ("pause");
	
}

void gameChoice() {
	int option;
	entryName();
	do 
	{
		system("mode 131, 22");
		system("cls");
		menuGame();
		gotoxy(75, 14)	; scanf ("%d", &option);
		
		if (option == 1 || option == 2 || option == 3)
		{
			startGame(option);
		}
	}
	while (option != 4);
}
	
void entryScore(player *player1){ 
	FILE *fentryscore;
	char date[20];
	char waktu[20];
	char space='\n';
	time_t t;
	struct tm* tm_info;
	t = time(NULL);
	tm_info = localtime(&t);
	
	//Konversi tanggal DD/MM/YYYY ke string
	strftime(date,sizeof(date), "%d/%m/%Y", tm_info);
	//Konversi waktu HH:MM:SS ke string
	strftime(waktu,sizeof(waktu), "%H:%M:%S", tm_info);
	
	fentryscore = fopen("HighScore.txt", "ab");
	fprintf(fentryscore, "%s %s %s %d%c",date,waktu,name,player1->account,space);
	fclose(fentryscore);
}

void entryName(){
	system("mode 131, 22");
		system("cls");
	int i, j;
	
		gotoxy(50, 6)	; for (i = 0; i < 3; i++) {
		switch (i) {
			case 0:
				printf ("%c", 201); break;
			case 1:
				for (j = 0; j < 31; j++) {
					printf ("%c", 205);
				} break;
			case 2:
				printf ("%c", 187); break;
		}
	}
	
	gotoxy(50, 7)	; printf ("%c   Masukkan Nama (5 Karakter)  %c", 186, 186);
	gotoxy(50, 8)	; for (i = 0; i < 3; i++) {
		switch (i) 
		{
			case 0:
				printf ("%c", 204); break;
			case 1:
				for (j = 0; j < 31; j++) 
				{
					printf ("%c", 205);
				} 
				break;
			case 2:
				printf ("%c", 185); break;
		}
	}
	
	gotoxy(50, 10)	; for (i = 0; i < 3; i++) {
		switch (i) 
		{
			case 0:
				printf ("%c", 200); break;
			case 1:
				for (j = 0; j < 31; j++) 
				{
					printf ("%c", 205);
				} 
				break;
			case 2:
				printf ("%c", 188); break;
		}
	}
	
	
	for(;;){
	gotoxy(50, 9)	; printf ("%c                               %c", 186, 186);
	gotoxy(63,9) ; printf("%c     %c", 186, 186);
	gotoxy(64, 9)	; scanf("%s", name);
	if(strlen(name)<6){
		break;
	}
	system("pause");
	}
	
}

/* BODY PROCEDURE AND FUNCTION FOR MAP */

void gotoxy(int x, int y) {
	//Mencari posisi suatu koordinat pada layar	
  	COORD coord;
  	coord.X = x;
  	coord.Y = y;
  	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void printMenuAwal() {
	int i, j;
	
	//gotoxy untuk box
	gotoxy(30, 7)	; 	for (i = 0; i < 3; i++) {
		switch (i) {
			case 0:
				printf ("%c", 201); break;
			case 1:
				for (j = 0; j < 68; j++) {
					printf ("%c", 205);
				} break;
			case 2:
				printf ("%c", 187); break;
		}
	}
	for (i = 8; i < 12; i++) {
		gotoxy(30, i)	; printf("%c                                                                    %c\n", 186, 186);
	}
	gotoxy(30, 12)	; for (i = 0; i < 3; i++) {
		switch (i) 
		{
			case 0:
				printf ("%c", 204); break;
			case 1:
				for (j = 0; j < 68; j++) 
				{
					printf ("%c", 205);
				} 
				break;
			case 2:
				printf ("%c", 185); break;
		}
	}
	gotoxy(30, 13)	; printf("%c                                                                    %c\n", 186, 186);
	gotoxy(30, 14)	; for (i = 0; i < 3; i++) {
		switch (i) 
		{
			case 0:
				printf ("%c", 204); break;
			case 1:
				for (j = 0; j < 68; j++) 
				{
					printf ("%c", 205);
				} 
				break;
			case 2:
				printf ("%c", 185); break;
		}
	}
	for (i = 15; i < 21; i++) {
		gotoxy(30, i)	; printf("%c                                                                    %c\n", 186, 186);
	}
	gotoxy(30, 21)	; for (i = 0; i < 3; i++) {
		switch (i) 
		{
			case 0:
				printf ("%c", 204); break;
			case 1:
				for (j = 0; j < 68; j++) 
				{
					printf ("%c", 205);
				}  
				break;
			case 2:
				printf ("%c", 185); break;
		}
	}
 	gotoxy(30, 22)	; printf("%c                                                                    %c\n", 186, 186);
	gotoxy(30, 23)  ; for (i = 0; i < 3; i++) {
		switch (i) 
		{
			case 0:
				printf ("%c", 200); break;
			case 1:
				for (j = 0; j < 68; j++) 
				{
					printf ("%c", 205);
				} 
				break;
			case 2:
				printf ("%c", 188); break;
		}
	}

	//gotoxy untuk isi menu
	gotoxy(63, 13)	; printf ("MENU");
	gotoxy(33, 15)	; printf ("1 - Mulai permainan");
	gotoxy(33, 16)	; printf ("2 - Skor tertinggi");
	gotoxy(33, 17)	; printf ("3 - Riwayat skor");
	gotoxy(33, 18)	; printf ("4 - Bantuan");
	gotoxy(33, 19)	; printf ("5 - Kredit");
	gotoxy(33, 20)	; printf ("6 - Keluar");
	gotoxy(33, 22)	; printf ("Masukkan nomor menu : ");
	
	//gotoxy untuk judul game
	i = 43;
	j = 8;
	printTitle(i, j);
}

void printTitle(int i, int j) {
	
	gotoxy (i, j); printf ("%c%c%c%c%c %c%c%c%c%c %c%c%c%c%c %c%c%c%c%c %c%c%c%c%c %c%c%c%c%c %c    %c   %c",
	201, 205, 203, 205, 187, 201, 205, 205, 205, 187,
	201, 205, 205, 205, 187, 201, 205, 205, 205, 187,
	201, 205, 205, 205, 187, 201, 205, 205, 205, 187,
	186, 186, 186);

	gotoxy (i, j + 1); printf ("%c %c %c %c   %c %c   %c %c   %c %c%c%c%c%c %c   %c %c    %c%c%c%c%c",
	186, 186, 186, 186, 186,
	186, 186, 186, 186,
	204, 205, 205, 205, 188, 186, 186, 186,
	200, 205, 205, 205, 185);

	gotoxy (i, j + 2); printf ("%c %c %c %c%c%c%c%c %c   %c %c%c%c%c%c %c     %c%c%c%c%c %c%c%c%c %c%c%c%c%c",
	186, 186, 186, 200, 205, 205, 205, 188,
	186, 186, 200, 205, 205, 205, 188,
	186, 200, 205, 205, 205, 188,
	200, 205, 205, 205, 205, 205, 205, 205, 188);
	
	gotoxy (i + 22, j + 3); printf ("/ Adriana Pamudya 2021 /");
	
}

void menuGame () {
	
	int i, j, option;

	gotoxy(50, 6)	; for (i = 0; i < 3; i++) {
		switch (i) {
			case 0:
				printf ("%c", 201); break;
			case 1:
				for (j = 0; j < 31; j++) {
					printf ("%c", 205);
				} break;
			case 2:
				printf ("%c", 187); break;
		}
	}
	gotoxy(50, 7)	; printf ("%c             Level             %c", 186, 186);
	gotoxy(50, 8)	; for (i = 0; i < 3; i++) {
		switch (i) 
		{
			case 0:
				printf ("%c", 204); break;
			case 1:
				for (j = 0; j < 31; j++) 
				{
					printf ("%c", 205);
				} 
				break;
			case 2:
				printf ("%c", 185); break;
		}
	}
	gotoxy(50, 9)	; printf ("%c  1 - First Timer              %c", 186, 186);
	gotoxy(50, 10)	; printf ("%c  2 - Entepreneur              %c", 186, 186);
	gotoxy(50, 11)	; printf ("%c  3 - Tycoon                   %c", 186, 186);
	gotoxy(50, 12)	; printf ("%c  4 - Kembali                  %c", 186, 186);
	gotoxy(50, 13)	; for (i = 0; i < 3; i++) {
		switch (i) 
		{
			case 0:
				printf ("%c", 204); break;
			case 1:
				for (j = 0; j < 31; j++) 
				{
					printf ("%c", 205);
				} 
				break;
			case 2:
				printf ("%c", 185); break;
		}
	}
	gotoxy(50, 14)	; printf ("%c  Masukan nomor level :        %c", 186, 186);
	gotoxy(50, 15)	; for (i = 0; i < 3; i++) {
		switch (i) 
		{
			case 0:
				printf ("%c", 200); break;
			case 1:
				for (j = 0; j < 31; j++) 
				{
					printf ("%c", 205);
				} 
				break;
			case 2:
				printf ("%c", 188); break;
		}
	}
	
}

void initBoard(block *board) {
  	int i = 0;

	//Mulai
	board->blockID = i;
	board->name = "Mulai";
	board->price = 0;
	board->rent = 0;
	board->rent1 = 0;
	board->rent2 = 0;
	board->rent3 = 0;
	board->rent4 = 0;
	board->housePrice = 0;
	board->type = 0;
	board->houseOwned = 0;
	board->owner.type = none;
	
  	block *iter;
  	iter = board;
  	iter->next = (block*)malloc(sizeof(block));
  	iter = iter->next;
  	i++;
  	
	//Solo
	iter->blockID = i;
  	iter->name = "Solo";
	iter->price = 6000;
	iter->rent = 200;
	iter->rent1 = 1000;
	iter->rent2 = 3000;
	iter->rent3 = 9000;
	iter->rent4 = 16000;
	iter->housePrice = 5000;
	iter->type = 1;
	iter->houseOwned = 0;
	iter->owner.type = none;
	
  	iter->next = (block*)malloc(sizeof(block));
	iter = iter->next;
	i++;
	
 	//Blitar
	iter->blockID = i;
  	iter->name = "Blitar";
	iter->price = 6000;
	iter->rent = 400;
	iter->rent1 = 2000;
	iter->rent2 = 6000;
	iter->rent3 = 18000;
	iter->rent4 = 32000;
	iter->housePrice = 5000;
	iter->type = 1;
  	iter->houseOwned = 0;
	iter->owner.type = none;

  	iter->next = (block*)malloc(sizeof(block));
  	iter = iter->next;
  	i++;
  	
	//Beli Bensin
	iter->blockID = i;
	iter->name = "Beli";
	iter->price = 0;
	iter->rent = 1500;
	iter->rent1 = 0;
	iter->rent2 = 0;
	iter->rent3 = 0;
	iter->rent4 = 0;
	iter->housePrice = 0;
	iter->type = 2;
  	iter->houseOwned = 0;
	iter->owner.type = none;

	iter->next = (block*)malloc(sizeof(block));
  	iter = iter->next;
  	i++;
  	
  	//Banjar
  	iter->blockID = i;
	iter->name = "Banjar";
	iter->price = 10000;
	iter->rent = 600;
	iter->rent1 = 3000;
	iter->rent2 = 9000;
	iter->rent3 = 27000;
	iter->rent4 = 40000;
	iter->housePrice = 5000;
	iter->type = 1;
  	iter->houseOwned = 0;
	iter->owner.type = none;

	iter->next = (block*)malloc(sizeof(block));
  	iter = iter->next;
  	i++;
  	
  	//Serang
  	iter->blockID = i;
	iter->name = "Serang";
	iter->price = 10000;
	iter->rent = 600;
	iter->rent1 = 3000;
	iter->rent2 = 9000;
	iter->rent3 = 27000;
	iter->rent4 = 40000;
	iter->housePrice = 5000;
	iter->type = 1;
  	iter->houseOwned = 0;
	iter->owner.type = none;

  	iter->next = (block*)malloc(sizeof(block));
  	iter = iter->next;
  	i++;
  	
  	//Dana Umum
  	iter->blockID = i;
	iter->name = "Dana";
	iter->price = 0;
	iter->rent = 0;
	iter->rent1 = 0;
	iter->rent2 = 0;
	iter->rent3 = 0;
	iter->rent4 = 0;
	iter->housePrice = 0;
	iter->type = 4;
  	iter->houseOwned = 0;
	iter->owner.type = none;

  	iter->next = (block*)malloc(sizeof(block));
  	iter = iter->next;
  	i++;
  	
  	//Subang
  	iter->blockID = i;
	iter->name = "Subang";
	iter->price = 12000;
	iter->rent = 800;
	iter->rent1 = 4000;
	iter->rent2 = 10000;
	iter->rent3 = 30000;
	iter->rent4 = 45000;
	iter->housePrice = 5000;
	iter->type = 1;
  	iter->houseOwned = 0;
	iter->owner.type = none;

  	iter->next = (block*)malloc(sizeof(block));
  	iter = iter->next;
  	i++;
  	
  	//Penjara
  	iter->blockID = i;
	iter->name = "Penjara";
	iter->price = 0;
	iter->rent = 1;
	iter->rent1 = 0;
	iter->rent2 = 0;
	iter->rent3 = 0;
	iter->rent4 = 0;
	iter->housePrice = 0;
	iter->type = 3;
  	iter->houseOwned = 0;
	iter->owner.type = none;

  	iter->next = (block*)malloc(sizeof(block));
  	iter = iter->next;
  	i++;
  
  	//Tegal
	iter->blockID = i;
	iter->name = "Tegal";
	iter->price = 14000;
	iter->rent = 1000;
	iter->rent1 = 5000;
	iter->rent2 = 15000;
	iter->rent3 = 45000;
	iter->rent4 = 62500;
	iter->housePrice = 10000;
	iter->type = 1;
  	iter->houseOwned = 0;
	iter->owner.type = none;

  	iter->next = (block*)malloc(sizeof(block));
  	iter = iter->next;
  	i++;
  	
	 //Jambi
	iter->blockID = i;
	iter->name = "Jambi";
	iter->price = 16000;
	iter->rent = 1200;
	iter->rent1 = 6000;
	iter->rent2 = 18000;
	iter->rent3 = 50000;
	iter->rent4 = 70000;
	iter->housePrice = 10000;
	iter->type = 1;
  	iter->houseOwned = 0;
	iter->owner.type = none;

  	iter->next = (block*)malloc(sizeof(block));
  	iter = iter->next;
  	i++;
  	
 	//Kesempatan
	iter->blockID = i;
	iter->name = "Kesem";
	iter->price = 0;
	iter->rent = 0;
	iter->rent1 = 0;
	iter->rent2 = 0;
	iter->rent3 = 0;
	iter->rent4 = 0;
	iter->housePrice = 0;
	iter->type = 4;
  	iter->houseOwned = 0;
	iter->owner.type = none;

  	iter->next = (block*)malloc(sizeof(block));
  	iter = iter->next;
  	i++;
  	
	//Gianyar
	iter->blockID = i;
	iter->name = "Gianyar";
	iter->price = 18000;
	iter->rent = 1400;
	iter->rent1 = 7000;
	iter->rent2 = 20000;
	iter->rent3 = 55000;
	iter->rent4 = 75000;
	iter->housePrice = 10000;
	iter->type = 1;
  	iter->houseOwned = 0;
	iter->owner.type = none;

  	iter->next = (block*)malloc(sizeof(block));
  	iter = iter->next;
  	i++;

	//Bayar Listrik
	iter->blockID = i;
	iter->name = "Bayar";
	iter->price = 0;
	iter->rent = 7500;
	iter->rent1 = 0;
	iter->rent2 = 0;
	iter->rent3 = 0;
	iter->rent4 = 0;
	iter->housePrice = 0;
	iter->type = 2;
  	iter->houseOwned = 0;
	iter->owner.type = none;

  	iter->next = (block*)malloc(sizeof(block));
  	iter = iter->next;
  	i++;
  	
  	//Medan
	iter->blockID = i;
	iter->name = "Medan";
	iter->price = 18000;
	iter->rent = 1400;
	iter->rent1 = 7000;
	iter->rent2 = 20000;
	iter->rent3 = 55000;
	iter->rent4 = 75000;
	iter->housePrice = 10000;
	iter->type = 1;
  	iter->houseOwned = 0;
	iter->owner.type = none;

  	iter->next = (block*)malloc(sizeof(block));
  	iter = iter->next;
  	i++;
  	
  	//Bogor
	iter->blockID = i;
	iter->name = "Bogor";
	iter->price = 20000;
	iter->rent = 1600;
	iter->rent1 = 8000;
	iter->rent2 = 22000;
	iter->rent3 = 60000;
	iter->rent4 = 80000;
	iter->housePrice = 10000;
	iter->type = 1;
  	iter->houseOwned = 0;
	iter->owner.type = none;

  	iter->next = (block*)malloc(sizeof(block));
  	iter = iter->next;
  	i++;
  	
  	//Hanya Lewat
	iter->blockID = i;
	iter->name = "Hanya";
	iter->price = 0;
	iter->rent = 0;
	iter->rent1 = 0;
	iter->rent2 = 0;
	iter->rent3 = 0;
	iter->rent4 = 0;
	iter->housePrice = 0;
	iter->type = 0;
  	iter->houseOwned = 0;
	iter->owner.type = none;

  	iter->next = (block*)malloc(sizeof(block));
  	iter = iter->next;
  	i++;
  	
  	//Kediri
	iter->blockID = i;
	iter->name = "Kediri";
	iter->price = 22000;
	iter->rent = 1800;
	iter->rent1 = 90000;
	iter->rent2 = 25000;
	iter->rent3 = 70000;
	iter->rent4 = 87500;
	iter->housePrice = 15000;
	iter->type = 1;
  	iter->houseOwned = 0;
	iter->owner.type = none;

  	iter->next = (block*)malloc(sizeof(block));
  	iter = iter->next;
  	i++;
  	
  	//Lovina
	iter->blockID = i;
	iter->name = "Lovina";
	iter->price = 22000;
	iter->rent = 1800;
	iter->rent1 = 90000;
	iter->rent2 = 25000;
	iter->rent3 = 70000;
	iter->rent4 = 87500;
	iter->housePrice = 15000;
	iter->type = 1;
  	iter->houseOwned = 0;
	iter->owner.type = none;

  	iter->next = (block*)malloc(sizeof(block));
  	iter = iter->next;
  	i++;
  	
  	//Bekasi
	iter->blockID = i;
	iter->name = "Bekasi";
	iter->price = 24000;
	iter->rent = 2000;
	iter->rent1 = 10000;
	iter->rent2 = 30000;
	iter->rent3 = 750000;
	iter->rent4 = 92500;
	iter->housePrice = 15000;
	iter->type = 1;
  	iter->houseOwned = 0;
	iter->owner.type = none;

  	iter->next = (block*)malloc(sizeof(block));
  	iter = iter->next;
  	i++;
  	
  	//Dana Umum
  	iter->blockID = i;
	iter->name = "Dana";
	iter->price = 0;
	iter->rent = 0;
	iter->rent1 = 0;
	iter->rent2 = 0;
	iter->rent3 = 0;
	iter->rent4 = 0;
	iter->housePrice = 0;
	iter->type = 4;
  	iter->houseOwned = 0;
	iter->owner.type = none;

  	iter->next = (block*)malloc(sizeof(block));
  	iter = iter->next;
  	i++;
  	
  	//Madiun
	iter->blockID = i;
	iter->name = "Madiun";
	iter->price = 26000;
	iter->rent = 2200;
	iter->rent1 = 11000;
	iter->rent2 = 33000;
	iter->rent3 = 80000;
	iter->rent4 = 97500;
	iter->housePrice = 15000;
	iter->type = 1;
  	iter->houseOwned = 0;
	iter->owner.type = none;

  	iter->next = (block*)malloc(sizeof(block));
  	iter = iter->next;
  	i++;
  	
  	//Beli Bensin
	iter->blockID = i;
	iter->name = "Beli";
	iter->price = 0;
	iter->rent = 1500;
	iter->rent1 = 0;
	iter->rent2 = 0;
	iter->rent3 = 0;
	iter->rent4 = 0;
	iter->housePrice = 0;
	iter->type = 2;
  	iter->houseOwned = 0;
	iter->owner.type = none;
	
	iter->next = (block*)malloc(sizeof(block));
  	iter = iter->next;
  	i++;
	
	//Malang
	iter->blockID = i;
	iter->name = "Malang";
	iter->price = 28000;
	iter->rent = 2400;
	iter->rent1 = 12000;
	iter->rent2 = 36000;
	iter->rent3 = 85000;
	iter->rent4 = 102500;
	iter->housePrice = 15000;
	iter->type = 1;
  	iter->houseOwned = 0;
	iter->owner.type = none;

  	iter->next = (block*)malloc(sizeof(block));
  	iter = iter->next;
  	i++;
  	
  	//Masuk Penjara
  	iter->blockID = i;
	iter->name = "Penjara";
	iter->price = 0;
	iter->rent = 2;
	iter->rent1 = 0;
	iter->rent2 = 0;
	iter->rent3 = 0;
	iter->rent4 = 0;
	iter->housePrice = 0;
	iter->type = 3;
  	iter->houseOwned = 0;
	iter->owner.type = none;

  	iter->next = (block*)malloc(sizeof(block));
  	iter = iter->next;
  	i++;
  	
	//Depok
	iter->blockID = i;
	iter->name = "Depok";
	iter->price = 30000;
	iter->rent = 2600;
	iter->rent1 = 13000;
	iter->rent2 = 39000;
	iter->rent3 = 90000;
	iter->rent4 = 110000;
	iter->housePrice = 20000;
	iter->type = 1;
  	iter->houseOwned = 0;
	iter->owner.type = none;

  	iter->next = (block*)malloc(sizeof(block));
  	iter = iter->next;
  	i++;  
	  
	//Ambon
	iter->blockID = i;
	iter->name = "Ambon";
	iter->price = 30000;
	iter->rent = 2600;
	iter->rent1 = 13000;
	iter->rent2 = 39000;
	iter->rent3 = 90000;
	iter->rent4 = 110000;
	iter->housePrice = 20000;
	iter->type = 1;
  	iter->houseOwned = 0;
	iter->owner.type = none;

  	iter->next = (block*)malloc(sizeof(block));
  	iter = iter->next;
  	i++;  	
  	
  	//Kesempatan
	iter->blockID = i;
	iter->name = "Kesem";
	iter->price = 0;
	iter->rent = 0;
	iter->rent1 = 0;
	iter->rent2 = 0;
	iter->rent3 = 0;
	iter->rent4 = 0;
	iter->housePrice = 0;
	iter->type = 4;
  	iter->houseOwned = 0;
	iter->owner.type = none;

  	iter->next = (block*)malloc(sizeof(block));
  	iter = iter->next;
  	i++;
  	
  	//Metro
	iter->blockID = i;
	iter->name = "Metro";
	iter->price = 32000;
	iter->rent = 2800;
	iter->rent1 = 15000;
	iter->rent2 = 45000;
	iter->rent3 = 100000;
	iter->rent4 = 120000;
	iter->housePrice = 20000;
	iter->type = 1;
  	iter->houseOwned = 0;
	iter->owner.type = none;

  	iter->next = (block*)malloc(sizeof(block));
  	iter = iter->next;
  	i++; 
  	
  	//Bayar Listrik
	iter->blockID = i;
	iter->name = "Bayar";
	iter->price = 0;
	iter->rent = 7500;
	iter->rent1 = 0;
	iter->rent2 = 0;
	iter->rent3 = 0;
	iter->rent4 = 0;
	iter->housePrice = 0;
	iter->type = 2;
  	iter->houseOwned = 0;
	iter->owner.type = none;

  	iter->next = (block*)malloc(sizeof(block));
  	iter = iter->next;
  	i++;
  	
  	//Bandung
	iter->blockID = i;
	iter->name = "Bandung";
	iter->price = 35000;
	iter->rent = 3500;
	iter->rent1 = 17000;
	iter->rent2 = 50000;
	iter->rent3 = 110000;
	iter->rent4 = 130000;
	iter->housePrice = 20000;
	iter->type = 1;
  	iter->houseOwned = 0;
	iter->owner.type = none;

  	iter->next = (block*)malloc(sizeof(block));
  	iter = iter->next;
  	i++;
  	
  	//Jakarta
	iter->blockID = i;
	iter->name = "Jakarta";
	iter->price = 40000;
	iter->rent = 5000;
	iter->rent1 = 20000;
	iter->rent2 = 60000;
	iter->rent3 = 140000;
	iter->rent4 = 170000;
	iter->housePrice = 20000;
	iter->type = 1;
  	iter->houseOwned = 0;
	iter->owner.type = none;
}

void boardName(block *board, int j, bool baris) {

	int i, jarak;
	
	int namelength = strlen(board->name);
	if (baris == false) {
		if (j == 0 || j == 8 || j == 24 || j == 16){
			jarak = 9 - namelength;
		} else { //daerah tengah
			jarak = 8 - namelength;		
		}
 	} else if ( baris == true) {
 		jarak = 9 - namelength;
	}
	//penempatan nama
	if (jarak == 4) {
		printf ("  %s  ",board->name);		
	} else {
		printf (" %s ",board->name);
	}
	printf ("%c", 186);
}

void printPlayerMoney(player* player1, player* player2) {
	int i, j;
	
	//gotoxy untuk print box uang player
	gotoxy(88, 0)	; for (i = 0; i < 3; i++) {
		switch (i) {
			case 0:
				printf ("%c", 201); break;
			case 1:
				for (j = 0; j < 29; j++) {
					printf ("%c", 205);
				} break;
			case 2:
				printf ("%c", 187); break;
		}
	}
	gotoxy(88, 1)	; printf ("%c         Uang Pemain         %c", 186, 186);
	gotoxy(88, 2)	; for (i = 0; i < 5; i++) {
		switch (i) {
			case 0:
				printf ("%c", 204); break;
			case 1:
				for (j = 0; j < 14; j++) {
					printf ("%c", 205);
				} break;
			case 2:
				printf ("%c", 203);
				break;
			case 3:
				for (j = 0; j < 14; j++) {
					printf ("%c", 205);
				} 
				break;
			case 4: 
				printf ("%c", 185);
				break;
		}
	}
	gotoxy(88, 3)	; printf ("%c              %c              %c", 186, 186, 186);
	gotoxy(88, 4)	; printf ("%c              %c              %c", 186, 186, 186);
	gotoxy(88, 5)	; for (i = 0; i < 5; i++) {
		switch (i) {
			case 0:
				printf ("%c", 200); break;
			case 1:
				for (j = 0; j < 14; j++) {
					printf ("%c", 205);
				} break;
			case 2:
				printf ("%c", 202);
				break;
			case 3:
				for (j = 0; j < 14; j++) {
					printf ("%c", 205);
				} break;
			case 4:
				printf ("%c", 188); break;
		}
	}
	
	//gotoxy untuk print uang player
	gotoxy(90, 3)	; printf ("%s(%s)", player1->name, name);
	gotoxy(105, 3)	; printf ("%s(Computer)", player2->name);
	gotoxy(90, 4)	; printf ("$%d", player1->account);
	gotoxy(105, 4)	; printf ("$%d", player2->account);

}

void printMenuGame() {
	int i, j;
	
	//gotoxy untuk box menu
	gotoxy(88, 6)	; for (i = 0; i < 3; i++) {
		switch (i) {
			case 0:
				printf ("%c", 201); break;
			case 1:
				for (j = 0; j < 29; j++) {
					printf ("%c", 205);
				} break;
			case 2:
				printf ("%c", 187); break;
		}
	}
	gotoxy(88, 7)	; printf ("%c            Menu             %c", 186, 186);
	gotoxy(88, 8)	; for (i = 0; i < 3; i++) {
		switch (i) 
		{
			case 0:
				printf ("%c", 204); break;
			case 1:
				for (j = 0; j < 29; j++) 
				{
					printf ("%c", 205);
				} 
				break;
			case 2:
				printf ("%c", 185); break;
		}
	}
	gotoxy(88, 9)	; printf ("%c  1 - Kocok dadu             %c", 186, 186);
	gotoxy(88, 10)	; for (i = 0; i < 3; i++) {
		switch (i) 
		{
			case 0:
				printf ("%c", 204); break;
			case 1:
				for (j = 0; j < 29; j++) 
				{
					printf ("%c", 205);
				} 
				break;
			case 2:
				printf ("%c", 185); break;
		}
	}
	gotoxy(88, 11)	; printf ("%c  Masukan nomor menu :       %c", 186, 186);
	gotoxy(88, 12)	; for (i = 0; i < 3; i++) {
		switch (i) 
		{
			case 0:
				printf ("%c", 200); break;
			case 1:
				for (j = 0; j < 29; j++) 
				{
					printf ("%c", 205);
				} 
				break;
			case 2:
				printf ("%c", 188); break;
		}
	}

}

void printKartu(block *board) {
	int i, j, jarak, namelength;
	
	
	switch (board->type) {
		
		//print kartu properti
		case property:
		
			//print box
			gotoxy(123, 0)	; for (i = 0; i < 3; i++) {
				switch (i) 
				{
					case 0:
						printf ("%c", 201); break;
					case 1:
						for (j = 0; j < 29; j++) {
							printf ("%c", 205);
						} 
						break;
					case 2:
					printf ("%c", 187); break;
				}	
			}
			gotoxy(123, 1)	; printf ("%c       KARTU HAK MILIK       %c", 186, 186);
			gotoxy(123, 2)	; printf ("%c           PROPERTI          %c", 186, 186);
			gotoxy(123, 3)	; for (i = 0; i < 3; i++) {
				switch (i) {
					case 0:
						printf ("%c", 204); break;
					case 1:
						for (j = 0; j < 29; j++) {
							printf ("%c", 205);
						} 
						break;
					case 2:
						printf ("%c", 185); break;
				}
			}
			for (i = 4; i < 7; i++) {
					gotoxy(123, i); printf ("%c                             %c", 186, 186);
			}
			gotoxy(123, 7)	; printf ("%c  Harga Tanah       $        %c", 186, 186);
			gotoxy(123, 8)	; printf ("%c  Harga Sewa                 %c", 186, 186);
			gotoxy(123, 9)	; printf ("%c  Hanya Tanah       $        %c", 186, 186);
			gotoxy(123, 10)	; printf ("%c  1 Rumah           $        %c", 186, 186);
			gotoxy(123, 11)	; printf ("%c  2 Rumah           $        %c", 186, 186);
			gotoxy(123, 12)	; printf ("%c  3 Rumah           $        %c", 186, 186);
			gotoxy(123, 13)	; printf ("%c  4 Rumah           $        %c", 186, 186);
			gotoxy(123, 14)	; printf ("%c                             %c", 186, 186);
			gotoxy(123, 15)	; printf ("%c  Memiliki 1 kompleks tanah  %c", 186, 186);
			gotoxy(123, 16)	; printf ("%c  Harga sewa 2x lipat        %c", 186, 186);
			gotoxy(123, 17)	; printf ("%c                             %c", 186, 186);
			gotoxy(123, 18)	; printf ("%c  Harga 1 Rumah     $        %c", 186, 186);
			gotoxy(123, 19)	; printf ("%c  Harga 1 Hotel     $        %c", 186, 186);
			gotoxy(123, 20)	; printf ("%c                             %c", 186, 186);
			gotoxy(123, 21)	; for (i = 0; i < 3; i++) {
				switch (i) {
					case 0:
						printf ("%c", 200); break;
					case 1:
						for (j = 0; j < 29; j++) {
							printf ("%c", 205);
						} 
						break;
					case 2:
						printf ("%c", 188); break;
					}
			}
		
			//print isi box kartu (nama tempat, harga sewa, harga tanah dan rumah)		
			namelength = strlen(board->name);
			jarak = 29 - namelength;
			jarak /= 2;
			gotoxy(124 + jarak, 5); printf ("%s", board->name);
			gotoxy(145, 7)	; printf ("%d", board->price);
			gotoxy(145, 9) 	; printf ("%d", board->rent);
			gotoxy(145, 10)	; printf ("%d", board->rent1);
			gotoxy(145, 11)	; printf ("%d", board->rent2);
			gotoxy(145, 12)	; printf ("%d", board->rent3);
			gotoxy(145, 13)	; printf ("%d", board->rent4);
			gotoxy(145, 18)	; printf ("%d", board->housePrice);
			gotoxy(145, 19)	; printf ("%d", board->housePrice);
			break;
		
		//print kartu tagihan	
		case tax: 
			
			//print box
			gotoxy(123, 0)	; for (i = 0; i < 3; i++) {
				switch (i) {
					case 0:
						printf ("%c", 201); break;
					case 1:
						for (j = 0; j < 29; j++) {
							printf ("%c", 205);
						} 
						break;
					case 2:
					printf ("%c", 187); break;
				}	
			}	
			gotoxy(123, 1)	; printf ("%c        KARTU TAGIHAN        %c", 186, 186);
			gotoxy(123, 2)	; printf ("%c     Anda harus membayar     %c", 186, 186);
			gotoxy(123, 3)	; printf ("%c     uang sejumlah $         %c", 186, 186);
			gotoxy(123, 4)	; for (i = 0; i < 3; i++) {
				switch (i) {
					case 0:
						printf ("%c", 200); break;
					case 1:
						
						for (j = 0; j < 29; j++) {
							printf ("%c", 205);
						} 
						break;
					case 2:
						printf ("%c", 188); break;
					}
			}
			
			//print isi box harga
			gotoxy(144, 3)	; printf ("%d", board->rent);
			break;
			
		//print kartu penjara
		case punish:
			
			//print box
			gotoxy(123, 0)	; for (i = 0; i < 3; i++) {
				switch (i) 
				{
					case 0:
						printf ("%c", 201); break;
					case 1:
						for (j = 0; j < 29; j++) {
							printf ("%c", 205);
						} 
						break;
					case 2:
					printf ("%c", 187); break;
				}	
			}	
			gotoxy(123, 1)	; printf ("%c        Kartu Tahanan        %c", 186, 186);
			gotoxy(123, 2)	; printf ("%c    Anda  distop sebanyak    %c", 186, 186);
			gotoxy(123, 3)	; printf ("%c          %d giliran          %c", 186, board->rent, 186);
			gotoxy(123, 4)	; for (i = 0; i < 3; i++) {
				switch (i) {
					case 0:
						printf ("%c", 200); break;
					case 1:
						for (j = 0; j < 29; j++) {
							printf ("%c", 205);
						} 
						break;
					case 2:
						printf ("%c", 188); break;
					}
			}
			break;
		
		//print kartu kesempatan / dana umum
		case fortune:
			
			//print box
			gotoxy(123, 2)	; for (i = 0; i < 3; i++) {
				switch (i) 
				{
					case 0:
						printf ("%c", 201); break;
					case 1:
						for (j = 0; j < 29; j++) {
							printf ("%c", 205);
						} 
						break;
					case 2:
					printf ("%c", 187); break;
				}	
			}	
			for (i = 3; i < 5; i++) {
					gotoxy(123, i); printf ("%c                             %c", 186, 186);
			}
			gotoxy(123, 5)	; for (i = 0; i < 3; i++) {
				switch (i) {
					case 0:
						printf ("%c", 200); break;
					case 1:
						for (j = 0; j < 29; j++) {
							printf ("%c", 205);
						} 
						break;
					case 2:
						printf ("%c", 188); break;
					}
			}
			break;
	
	}
}

void printBoard(block *board, player player1, player player2) {
	int i, j, t, h, a, b;
	int l = 31, k = 9;
	bool baris;

	system("cls") ;
	block *temp = board;
    temp = (block*)malloc(sizeof(block));
    temp = board;
	
	//BARIS PETAK ATAS******************************
	baris = false;
	
	//BEMBUKA BARIS ATAS
	printf ("%c", 201);	
	for (j = 0; j < 9; j++) {
		if (j == 0 || j == 8) {
			for( i = 0; i < 9; i++) {
				printf ("%c", 205);
			}
		} else {
			for( i = 0; i < 8; i++) {	
				printf ("%c", 205);
			}
		}
		if ( j != 8) {
			printf ("%c", 203);
		}
	}
	printf ("%c", 187);	
	printf("\n");
	
	//NAMA TEMPAT
  	printf ("%c", 186);
	for (i = 0; i < 9; i++) {
    	boardName(board, i, baris);
    	board = board->next;
	}
 	printf ("\n");
    
	board = temp;
	
	//LETAK PEMAIN
	printf ("%c", 186);
	for (i = 0; i < 9; i++) {
		//Petak pinggir kanan kiri
		if (i == 0 || i == 8) {
			if (i == player1.position && i == player2.position) {
				printf("   %s %s   %c",player1.name,player2.name, 186);
			}
   			if (i == player1.position && i != player2.position) {
				printf("   %s     %c",player1.name, 186);
    		}
   			if (i == player2.position && i != player1.position){
				printf("   %s     %c",player2.name, 186);
    		}
			if (i == 8 && i != player1.position && i != player2.position){
				printf("         %c", 186); //Tidak ada pemain yang berdiam disana
			}
			if (i != 8 && i!= player1.position && i != player2.position){
				printf("         %c", 186);
			}
		} 
  		//Petak tengah
		else {
			if (i == player1.position && i == player2.position) {
				printf("  %s  %s  %c",player1.name,player2.name, 186);
			}
   			if (i == player1.position && i != player2.position) {
				printf("  %s     %c",player1.name, 186);
    		}
   			if (i == player2.position && i != player1.position){
				printf("  %s     %c",player2.name, 186);
    		}
			if (i == 8 && i != player1.position && i != player2.position){
				printf("        %c", 186);
			}
			if (i != 8 && i!= player1.position && i != player2.position){
				printf("        %c", 186);
			}
		}
    	
	}
	printf("\n");
	
	//HARGA & KETERANGAN
	for (i = 0; i < 9; i++) {
    	
    	if (i == 1 || i == 2) {
    		printf ("%c $%d  ", 186, board->price);
			board = board->next;
		}
    	if (i != 0 && i != 1 && i != 2 && i != 3 && i != 6 && i != 8){
			printf ("%c $%d ", 186, board->price);
			board = board->next;
    	}
    	
		if (i == 0) {
			printf ("%c         ", 186);
			board = board->next;
		}
		if (i == 3) {
			printf("%c Bensin ", 186);
			board = board->next;
		}
		if (i == 6) {
			printf ("%c  Umum  ", 186, 186);
			board = board->next;
		}
    	if (i == 8) {
	      	printf ("%c stop 1x %c", 186, 186);
			board = board->next;
		}
	}
 	printf("\n");
	
	//PENUTUP BARIS PETAK ATAS
 	printf ("%c", 204);
	for (j = 0; j < 9; j++) {
		if (j == 0 || j == 8) {
			for( i = 0; i < 9; i++) {
				printf ("%c", 205);
			}
		} else {
			for (i = 0; i < 8; i++) {
				printf ("%c", 205);
			}
		}
		if ( j == 0 || j == 7 ) {
			printf ("%c", 206);
		} else if (j == 8){
			printf ("%c", 185);
		} else {
			printf ("%c", 202);
		}
	}
 	printf("\n");
		
	//BARIS PETAK TENGAH******************************
	baris =  true;
	board = temp;
    for(i = 0; i < 8; i++) {
    	
    	//ITERASI TIAP ISI BARIS PETAK
		for ( j = 0; j < 3; j++) {
			//NAMA TEMPAT
	      	if (j == 0) { 
	       		printf("%c", 186);
	       			for (h = 0; h < l; h++) {
	       				board = board->next;
					}
	       		boardName(board, i, baris);
	       		board = temp;
	       		for(t = 0; t < 62; t++) { //Jarak tengah
	       			printf(" ");
	       		}
	       		printf("%c", 186);
	       		for (h = 0; h < k; h++) {
	       			board = board->next;
				}
				boardName(board, i, baris);
				board = temp;
	       		printf("\n");
	    	}

			//LETAK PEMAIN
			if(j == 1) {
				if ((9 + i) == player1.position && (9 + i) == player2.position){ 
					printf("%c         %c", 186, 186);
					for (t = 0; t < 62; t++) {
		          		printf(" ");
		        	}
					printf ("%c   A B   %c\n", 186, 186);
					
				} else if ((31 - i) == player1.position && (31 - i)== player2.position){
					printf("%c   A B   %c", 186, 186);
					for(t = 0; t < 62; t++) {
		         		printf(" ");
		        	}
					printf("%c         %c\n", 186, 186);
				} else if((9 + i) == player1.position  && (9 + i) != player2.position){
					printf("%c         %c", 186, 186);
	    			for (t = 0; t < 62; t++) {
		          		printf(" ");
		      		}
					printf("%c   A     %c\n", 186, 186);
				} else if ((9 + i) != player1.position  && (9 + i) == player2.position){
					printf("%c         %c", 186, 186);
	    			for(t = 0; t < 62; t++) {
		  			    printf(" ");
		  			}
				    printf("%c   B     %c\n", 186, 186);
			    } else if ((31 - i) == player1.position && (31 - i)!= player2.position) {
					printf("%c   A     %c", 186, 186);
					for(t = 0; t < 62; t++) {
						printf (" ");
		        	}
					printf("%c         %c\n", 186, 186);
				} else if ((31 - i) != player1.position && (31 - i) == player2.position) {
					printf("%c   B     %c", 186, 186);
					for( t = 0; t < 62; t++) {
		        		printf(" ");
		        	}
					printf("%c         %c\n", 186, 186);
				} else {
	      			printf("%c         %c", 186, 186);
	      			for( t = 0; t < 62; t++) {
	          			printf(" ");
	        		}
					printf("%c         %c\n", 186, 186);
					}
				}

			//HARGA & KETERANGAN
			if (j == 2) {
	    		if(k == 11){
					printf("%c Listrik %c", 186, 186);
		        	board = temp;
					//jarak tengah
		        	for (t = 0; t < 62; t++) {
		          		printf(" ");
		       			}
		       		printf("%c  patan  %c\n", 186, 186);
		       		board = temp;
	        	}
	        	if(k == 13){
					printf("%c  patan  %c", 186, 186);
		        	board = temp;
					//jarak tengah
		        	for (t = 0; t < 62; t++) {
		          		printf(" ");
		       		}
		       		printf("%c   Air   %c\n", 186, 186);
		       		board = temp;
	        	}
	      		if (k == 9 || k == 10 || k == 12 || k == 14 || k == 15) {
	        		for (h = 0; h < l; h++) {
		        		board = board->next;
					}

		       	printf("%c $%d  %c", 186, board->price, 186);
		       	board = temp;
		        for (t = 0; t < 62; t++) {
		          	printf(" ");
		        }
		        for (h = 0; h < k; h++) {
		        	board = board->next;
				}
		        printf ("%c $%d  %c\n", 186, board->price, 186);
		        board = temp;
			  	}
			}
    	}

		//PEMBUKA BARIS PETAK BAWAH / PENUTUP PETAK TENGAH TERAKHIR
		if (i == 6){
	  	printf ("%c", 204);
			for (j = 0; j < 9; j++) {
				if (j == 0 || j == 8) {
					for( i = 0; i < 9; i++) {
						printf ("%c", 205);
					}
				} else {
					for (i = 0; i < 8; i++) {
						printf ("%c", 205);
					}
				}
				if ( j == 0 || j == 7 ) {
					printf ("%c", 206);
				} else if (j == 8){
					printf ("%c", 185);
				} else {
					printf ("%c", 203);
				}
			}
	  	}

		//PENUTUP TIAP PETAK TENGAH
		if (i < 6) {
			printf ("%c", 204);
			for (t = 0; t < 9; t++) {
				printf ("%c", 205);
			}
			printf("%c", 185);
		
	  	  	for(t = 0; t < 62; t++) {
	        	printf(" ");
	       	}
	        printf ("%c", 204);
			for (t = 0; t < 9; t++) {
				printf ("%c", 205);
			}
			printf("%c", 185);
	  	}
		
		printf("\n");
		k = k + 1;
		l = l - 1;
	}
	
	//BARIS PETAK BAWAH*****************************
  	baris = false;
 	board = temp;

	//NAMA TEMPAT
 	printf("%c",186);
	for (i = 24; i > 15; i--) {
		for (h = 0; h < i; h++) {
			board = board->next;
		}
		boardName(board, i, baris);
    	board = temp;
	}
	printf("\n");

	//LETAK PEMAIN
  	printf("%c", 186);
 	for (i = 0; i < 9; i++) {
		//Petak pinggir kanan kiri
		if (i == 0 || i == 8) {
			if ((24 - i) == player1.position && (24 - i) == player2.position) {
			printf("   %s %s   %c",player1.name,player2.name, 186);
			}
   			if ((24 - i) == player1.position  && (24 - i) != player2.position) {
				printf("   %s     %c",player1.name, 186);
    		}
   			if ((24 - i) == player2.position && (24 - i) != player1.position) {
				printf("   %s     %c",player2.name, 186);
    		}
			if (i == 8 && (24 - i) != player1.position && (24 - i) != player2.position) {
				printf("         %c", 186);
			}
			if (i != 8 && (24 - i) != player1.position && (24 - i) != player2.position) {
				printf("         %c", 186);
			}
		}

		//Petak tengah
		else {
			if ((24 - i) == player1.position && (24 - i) == player2.position) {
			printf("  %s  %s  %c",player1.name,player2.name, 186);
			}
   			if ((24 - i) == player1.position  && (24 - i) != player2.position) {
				printf("  %s     %c",player1.name, 186);
    		}
   			if ((24 - i) == player2.position && (24 - i) != player1.position) {
				printf("  %s     %c",player2.name, 186);
    		}
			if (i == 8 && (24 - i) != player1.position && (24 - i) != player2.position) {
				printf("        %c", 186);
			}
			if (i != 8 && (24 - i) != player1.position && (24 - i) != player2.position) {
				printf("        %c", 186);
			}
		}
 	}
	printf("\n");

	//HARGA & KETERANGAN
	for(i = 24; i > 15; i--) {
	    if(i == 24) {
			board = temp;
        	for (h = 0; h < i; h++) {
				board = board->next;
			}
			printf ("%c stop 2x ", 186);
		} else if (i == 22) {
			board = temp;
        	for(h = 0; h < i; h++){
				board = board->next;
		  	}
			printf("%c Bensin ", 186);
		} else if (i == 20) {
			board = temp;
        	for(h = 0; h < i; h++){
				board = board->next;
		  	}
			printf("%c  Umum  ", 186);
		} else if (i == 16) {
			board = temp;
        	for(h = 0; h < i; h++){
				board = board->next;
		  	}
			printf("%c  Lewat  %c", 186, 186);
		} else {
      		board = temp;
			for (h = 0; h < i; h++) {
			board = board->next;
			}
			printf("%c $%d ", 186, board->price);
			board=temp;
		}
	}
	printf("\n");

	//PENUTUP BARIS PETAK BAWAH
	printf ("%c", 200);
	for (j = 0; j < 9; j++) {
		if (j == 0 || j == 8) {
			for( i = 0; i < 9; i++) {
				printf ("%c", 205);
			}
		} else {
			for( i = 0; i < 8; i++) {
				printf ("%c", 205);
			}
		}
		if ( j != 8) {
			printf ("%c", 202);
		}
	}
	printf ("%c", 188);
	
	i = 19;
	j = 17;
	printTitle(i, j);
	printPlayerMoney(&player1, &player2);
	printMenuGame();
	printf("\n");
}

/* PLAY GAME*/

int rollDice() {
	
	int i, dice = 0;
	
	for(i = 0; i < 2; i++) {
       dice += (rand() % 6) + 1;
 	}
    return dice;
}

int buildHouse(block* atmBlock, player* activePlayer) {
    
	int flag = 0;
    
    //jika blok merukpakan milik permain
	if (activePlayer->type == atmBlock->owner.type) {
        
        //jika rumah pada blok belum mencapai 4
		if (atmBlock->houseOwned < 4) {
            
            //jika harga satu rumah masih lebih kurang dari uang pemain
			if (atmBlock->housePrice <= activePlayer->account) {
                
				flag = 1;
                
				activePlayer->account -= atmBlock->housePrice;
                atmBlock->houseOwned += 1;
                gotoxy(123, 28); printf("Anda punya %d rumah di %s.", atmBlock->houseOwned, atmBlock->name);
                
                if(atmBlock->houseOwned == 4) {
                	gotoxy(123, 29); printf("(Anda hanya dapat membangun maksimal 4 rumah)");
				}
    
                
            } else {
            	  gotoxy(123, 28); printf("Uang and tidak mencukupi untuk membeli rumah!");
         
            }
        }
    } else {
        gotoxy(123, 28); printf("Anda bukan pemiliki properti ini!");
    }
    return flag;
}

void addOwned(player* activePlayer) {	
	
	//menambah block yang dimiliki pemain
	int i;
    
	for (i = 0; i < PROPERTY_COUNT; ++i) {
        if (activePlayer->blockOwned[i] == -1) {
            activePlayer->blockOwned[i] = activePlayer->position;
            break;
        }
    }
}

void copyOwner(player * old, player * new) {	
	
	//menginisialisasi pemilik block
	int i;
	
    old -> type = new -> type;
    old -> account = new -> account;
    old -> skipTurn = new -> skipTurn;
    old -> name = new -> name;
    old -> position = new -> position;
    
    for (i = 0; i < PROPERTY_COUNT; ++i) {
        old -> blockOwned[i] = new -> blockOwned[i];
    }
}

void buyProp(block *atmBlock, player *activePlayer) {
    
    int i;
    
    //jika uang mecukupi
	if (atmBlock -> price <= activePlayer -> account)
    {
        activePlayer -> account -= atmBlock -> price;
        copyOwner (&atmBlock -> owner, activePlayer);
        addOwned (activePlayer);

        gotoxy(123, 23); printf("Selamat! %s telah membeli tanah di %s.",activePlayer->name, atmBlock->name);
        gotoxy(123, 24); printf("Tersisa uang sebanyak $%d di akun anda.",activePlayer->account);
        
	
		for (i = 25; i < 28; i++) {
        	gotoxy(123, i); printf("                                     ");	
		}
		gotoxy(88, 35); system("pause"); 
  	} 
	//jika uang tidak mencukupi
	else {
        gotoxy(123, 23); printf("Uang anda tidak cukup !");
        gotoxy(123, 24); printf("                                                              ");
        for (i = 24; i < 28; i++) {
        	gotoxy(123, i); printf("                                     ");	
		}
		gotoxy(88, 35); system("pause");     
	}
}

int countProp(player activePlayer) {         
    
	//menghitung properti yang dimiliki tiap pemain
	int i, count = 0;

	for (i = 0; i < PROPERTY_COUNT; i++) {
        if (activePlayer.blockOwned[i] != -1) {
            count++;
    	}
	}
    return count;
}

int showProp(block *board, struct player activePlayer) {
	
	block *temp;
	temp = (block*)malloc(sizeof(block));
	temp = board;
    int i = 0;
	int counter = 0;
	int j, k;
			
    gotoxy (123, 29); printf("Properti anda adalah :");
    k = 30;
        
		while (activePlayer.blockOwned[i] != -1) {

            	for (j = 0; j < activePlayer.blockOwned[i]; j++) {
                	board = board->next;
            	}
            	
				if (board->type == property) {
            		gotoxy(123, k); printf("%d - %s\n ", board->blockID, board->name);
                	counter++;
                }
	            
	            k++;
				i++;
	        	
				board=temp;
				
        	}
        if (counter == 0){
            gotoxy (123, 29); printf("Anda tidak memiliki properti.");
        }
    return k;    
	}

void sellProp(block *board, player* activePlayer) {
    
	int property_id, i, index, j, k;
	int flag = 0, is_owned =- 1, counter = 0;
    block *temp;
	temp = (block*)malloc(sizeof(block));
	temp = board;
	
    j = countProp(*activePlayer);
    
    if (j != 0) {
        k = showProp(board,*activePlayer);
        gotoxy(123, k); printf("0 - Kembali");
        gotoxy(123, k + 1); printf("Masukkan nomor menu : ");
		gotoxy(145, k + 1); scanf("%d",&property_id);
        
        //pemain memiliki 
		if (property_id != 0) {
            for(i = 0; i < PROPERTY_COUNT; i++) {
                if (activePlayer->blockOwned[i] == property_id) {
                    is_owned = 1;
                    index = i;
                    break;
                }
            }
            
			if (is_owned != -1) {
                activePlayer->blockOwned[index] = -1;
            	player temp;
                for (j = 0; j < property_id; j++) {
                		board = board->next;
            	}
                board->owner.type = none;
                if (board->houseOwned == 0) {
					activePlayer->account += board->price / 2;
				}
                if (board->houseOwned == 1) {
                    activePlayer->account += (board->price + board->housePrice) / 2;
                }
                if (board->houseOwned == 2) {
                    activePlayer->account += (board->price + (2 * board->housePrice)) / 2;
                }
                if (board->houseOwned == 3) {
                    activePlayer->account += (board->price + (3 * board->housePrice)) / 2;
                }
                if (board->houseOwned == 4) {
                    activePlayer->account += (board->price + (4 * board->housePrice)) / 2;
                }
			}
        board = temp;
		
		//pemain tidak memiliki properti
		} else {
            printf("Anda tidak memiliki properti untuk dijual.\n");
		}
    }
}

int insufficientFund(block *board, player* activePlayer, int requiredMoney) { 

    int selection = 0; 
	int flag = 1;
    while (selection != 4 && activePlayer->account < requiredMoney && countProp(*activePlayer)!= 0 && flag != 0) {
    	
        gotoxy(123, 23)	; printf("Uang anda kurang. Anda butuh uang sebanyak $%d. \n", requiredMoney - activePlayer->account);
        gotoxy(123, 24)	; printf("1 - Jual properti                   ");
        gotoxy(123, 25)	; printf("0 - Batalkan                      ");
        gotoxy(123, 26)	; printf("Masukkan nomor pilihan : ");
		gotoxy(148, 26)	; scanf("%d",&selection);
		gotoxy(123, 27)	; printf("                                                ");                
		
        switch (selection)
        {
            case 1:
                sellProp(board,activePlayer);
                break;
            case 0:
                flag = 0;
                break;
            default:
                gotoxy(127, 28); printf("Nomor salah!");
                break;

        }
    }
    return flag;
}

void payRent(block *board, player* activePlayer,player * owner) {	
	
	//modul bayar uang sewa
	block *temp;
	temp = (block*)malloc(sizeof(block));
	temp = board;
	int rent = 0, owned_property_count, j;
  	for(j = 0; j < activePlayer->position; j++) {
	  	board = board->next;
	}
	
	if (board->houseOwned == 0) {
		rent = board->rent;
	}
    if (board->houseOwned == 1) {
		rent = board->rent1;
	}
    if (board->houseOwned == 2) {
		rent = board->rent2;
	}
    if (board->houseOwned == 3) {
		rent = board->rent3;
	}
	if (board->houseOwned == 4) {
		rent = board->rent4;
	}
    
	if (rent > activePlayer->account) {
     
		owned_property_count = countProp(*activePlayer);
        
		while(rent > activePlayer->account && owned_property_count != 0) {
            insufficientFund(board,activePlayer,rent);
            owned_property_count = countProp(*activePlayer);
        }
    }
    
	if (rent < activePlayer->account) {
        activePlayer->account -= rent;
        owner->account += rent;
    } else {
        activePlayer->account = 0;
        board = temp;
    }
}

void askBuy(block *board, player* activePlayer) {
    
	int house_flag = 1;
	int insuf_flag = 1;
	int build_flag = 1;
	int selection, j;
	
    while (house_flag && build_flag && board->houseOwned < 4) {
    	
    	gotoxy(123, 23)	; printf("Apakah anda ingin membangun rumah di %s ?   ", board->name);
    	gotoxy(123, 24)	; printf("1 - Ya                                      ");
    	gotoxy(123, 25)	; printf("2 - Tidak                                   ");
    	gotoxy(123, 26)	; printf("Masukkan nomor pilihan :                    ");
    	gotoxy(148, 26)	; scanf("%d", &selection);
        gotoxy(123, 28)	; printf("                                             ");
        gotoxy(123, 29)	; printf("                                             ");
        
		//jadi membeli rumah
		if (selection == 1) {
			
			//Jika uang kurang
            if (activePlayer->account < board->housePrice) {
                
				while (countProp(*activePlayer)!= 0 && activePlayer->account < board->housePrice && insuf_flag == 1) {
                    insuf_flag = insufficientFund(board, activePlayer, board->housePrice);
				}
            }
            
            //Jika uang masih mencukupi
			if (activePlayer->account >= board->housePrice)
                build_flag = buildHouse(board, activePlayer);
                
            else {
                house_flag = 0;
			}
		
		//tidak membeli rumah
		} else if (selection == 2) {
            house_flag = 0;
    	}
	}
}
   
void afterDiceUser(block *board, player* activePlayer, player* passivePlayer) {
	
	block *temp;
	temp = (block*)malloc(sizeof(block));
	temp = board;
    int selection, j, f, id, i; 
	int insuf_flag = 1;
    
    for(j = 0; j < activePlayer -> position; j++) {
		board = board -> next;
	}
	
    switch (board -> type) {
    	
    	//berhenti di block properti
        case property:
        	
			//print kotak keterangan
			printKartu(board);
        
            gotoxy(123, 23)	; printf("%s tiba di %s.", activePlayer->name, board->name);
           
			//jika tanah belum dimiliki           
		    if (board -> owner.type == none) {
				gotoxy(123, 24)	; printf("Apakah %s ingin membeli tanah di %s ?",activePlayer->name, board->name);
                gotoxy(123, 25)	; printf("1 - Ya");
                gotoxy(123, 26)	; printf("2 - Tidak");
                gotoxy(123, 27)	; printf("Masukkan nomor pilihan : ");
				gotoxy(148, 27)	; scanf("%d",&selection);
                
				//jika ya membeli
				if (selection == 1) {
                    if (activePlayer->account < board->price) {
                        while (countProp(*activePlayer)!= 0 && activePlayer->account < board->price && insuf_flag == 1) {
                            insuf_flag = insufficientFund(board, activePlayer, board->price);
                        }
                    }
                    buyProp(board, activePlayer);
                    if (activePlayer->type == board->owner.type) {
                        askBuy(board, activePlayer);
                    }
				}
			} 
			//jika tanah orang lain
			else if (board->owner.type == passivePlayer->type){
                gotoxy(123, 23)	; printf("%s tiba di %s milik %s.", activePlayer->name, board->name, passivePlayer->name);
				payRent(board, activePlayer, passivePlayer);
            } 
            
            //jika tanah milik sendiri
            
			else if (activePlayer->type == board->owner.type) {
				gotoxy(123, 23)	; printf("%s tiba di %s miliknya.", activePlayer->name, board->name, passivePlayer->name);
				gotoxy(88, 35); system("pause");
                askBuy(board, activePlayer);
            }
            break;
        
		//berhenti di block pajak    
        case tax:
        	
        	//print kotak keterangan
        	printKartu(board);
        	
            gotoxy(123, 6); printf("%s tiba di blok pajak", activePlayer->name);
            
            if (activePlayer->account > board->rent) {
                activePlayer->account = activePlayer->account - board->rent;
            } else {
                activePlayer->account = activePlayer->account - board->rent;
            }
            
			while (countProp(*activePlayer) != 0 && activePlayer->account < board->rent) {
                insuf_flag = insufficientFund(board, activePlayer, board->price);
                
				if (insuf_flag == 0 && activePlayer->account < board->rent) {
                	gotoxy(123, 7); printf("Anda harus membayar tagihan!");
                }
            }
            gotoxy(90, 4)	; printf("$%d", activePlayer->account);
			
            break;
        
		//berhenti di block penjara    
        case punish:
            
            //print kotak keterangan
            printKartu(board);
            
			//menunjukkan keterangan block
			gotoxy(123, 6); printf("%s tiba di blok penjara", activePlayer->name);
            activePlayer->skipTurn += board->rent;
            break;
        
        //berhenti di block kesempatan / dana umum
        case fortune:
        	
        	if (board->name == "Kesem") {
        		gotoxy(123, 0); printf("%s tiba di %spatan, dapat kartu. ", activePlayer->name, board->name);
        	} else {
        		gotoxy(123, 0); printf("%s tiba di %s umum, dapat kartu. ", activePlayer->name, board->name);
			}
        	//print kotak keterangan
        	printKartu(board);
        	
        	//acak kesempatan / dana umum bagi pemain
        	f = rollDice();
        	
        		if (f == 1) {
        		gotoxy(128, 3)	; printf("Dapat komisi sebanyak");
        		gotoxy(136, 4)	; printf        ("$15000");
        		activePlayer->account += 15000;
				
				gotoxy(123, 7)	; printf("Uang pada akun %s bertambah", activePlayer->name);
        		gotoxy(123, 8)	; printf("menjadi $%d", activePlayer->account);
        		
        	
	        }
        	if (f == 2) {
        		gotoxy(132, 3)	; printf("Menang loteri");
				gotoxy(132, 4)	; printf("terima $10000");
				activePlayer->account += 10000;
				
				gotoxy(123, 7)	; printf("Uang pada akun %s bertambah", activePlayer->name);
        		gotoxy(123, 8)	; printf("menjadi $%d", activePlayer->account);
				
				
			}
			if (f == 3) {
				gotoxy(133, 3)	; printf("Menang kuis");
				gotoxy(132, 4)	; printf("terima $10000");
				activePlayer->account += 5000;
				
				gotoxy(123, 7)	; printf("Uang pada akun %s bertambah", activePlayer->name);
        		gotoxy(123, 8)	; printf("menjadi $%d", activePlayer->account);
				
				
        	}
			if (f == 4) {
				gotoxy(130, 3)	; printf("Nemu uang di jalan");
				gotoxy(132, 4)	; printf("terima $5000");
				activePlayer->account += 5000;
				
				gotoxy(123, 7)	; printf("Uang pada akun %s bertambah", activePlayer->name);
        		gotoxy(123, 8)	; printf("menjadi $%d", activePlayer->account);
			
				
			}
			if (f == 5) {
				gotoxy(130, 3)	; printf("Diberi sumbangan");
				gotoxy(131, 4)	; printf ("sebanyak $10000");
				activePlayer->account += 10000;
				
				gotoxy(123, 7)	; printf("Uang pada akun anda %s bertambah", activePlayer->name);
        		gotoxy(123, 8)	; printf("menjadi $%d", activePlayer->account);
				
				
			}
			if (f == 6) {
				gotoxy(132, 3)	; printf("Menang loteri");
				gotoxy(132, 4)	; printf("terima  $5000");
				activePlayer->account += 5000;
				
				gotoxy(123, 7)	; printf("Uang pada akun %s bertambah", activePlayer->name);
        		gotoxy(123, 8)	; printf("menjadi $%d", activePlayer->account);
				
				
			}
			break;
		
		//kembali ke kotak start
		case start:
			if (board->name == "Mulai") {
				gotoxy(88, 16)	; printf("Anda tiba di kotak awal, anda menerima $20000 dari Bank.");
				gotoxy(90, 4)	; printf("$%d", activePlayer->account);
				activePlayer->account += 20000;
			} else if (board->name == "Hanya") {
				gotoxy(88, 16)	; printf("Anda hanya lewat saja disini.");
			}
			
    }
    gotoxy(88, 35); system("pause");
}

int averagePropPrice(block *board,player *activePlayer) {
	int i;

	double toplam = 0,average;
	for (i = 0; i < 32; i++) {
        if (board->type == property) {
            toplam += board->price;
		}
		board = board->next;
	}
	average = toplam / 16;

	return average;
}

void turn(block *board, player* activePlayer, player * passivePlayer) {	

	block *temp;
	int option;
	temp = (block*)malloc(sizeof(block));
	temp = board;
    int flag = 1, next_block, j, dice;
    
	while(flag == 1) {
		
		gotoxy (89, 7); printf ("          Giliran A         ");
        gotoxy (106, 25); printf ("%s", activePlayer);
        gotoxy (112, 11); scanf("%d",&option);
        
        switch(option)
        {
        	//pilihan menu opsi kocok dadu
            case 1:
                if (activePlayer -> skipTurn == 0) {
                 	
                 	//mengocok dadu
					dice = rollDice();
					
                	gotoxy (88, 14); printf ("%s mengocok dadu sebesar : %d\n", activePlayer -> name, dice);
                	
                	//inisialisasi block letak pemain
                    next_block = (activePlayer -> position + dice);
                    
                    //sampai start kembali
                    if (next_block > 32) {
					    activePlayer -> account += 20000;
					}
                    activePlayer -> position = next_block % 32; //agar inisialisai letak pemain tidak lebih dari 32
					afterDiceUser(board, activePlayer, passivePlayer);
					
					flag = 0;
                    board = temp;
                
				} else {
                    gotoxy (88, 14); printf("Giliran anda dilewat %d kali.", activePlayer -> skipTurn);
                    activePlayer -> skipTurn -= 1;
                    flag = 0;
                }
                break;
            
            //pilihan menu opsi beli rumah di block posisi pemain
			case 2:
                for (j = 0; j < activePlayer -> position; j++) {
					board = board -> next;
				}
                if (board -> type == property && board -> owner.type == -1 && activePlayer -> account > board -> price) {
                	buyProp (board,activePlayer);
                	board = temp;
				} else {
                    printf("Tidak bisa! Anda hanya bisa membeli rumah di block yang anda miliki.\n");
                }
                gotoxy(88, 35); system("pause");
				break;
            
			case 3:
                sellProp(board,activePlayer);
                break;
            
			default:
                gotoxy(127, 8); printf("Nomor salah!");
	
        }
    }
    //gotoxy(0, 37); system ("pause");
}

void afterDicePC(block *board, player* activePlayer, player* passivePlayer) {	
	
	block *temp;
	temp = (block*)malloc(sizeof(block));
	temp = board;
    int selection, average, j, f, id, i, max; 
	int insuf_flag = 1; 
	int l = 0;
    
	average = averagePropPrice(board, activePlayer);
    board = temp;
    
	for (j = 0; j < activePlayer->position; j++) {
		board = board->next;
	}
    switch (board->type) {
    	
    	case property:
       		
       		//print kotak keterangan
			printKartu(board);
       		
       		//berhenti di properti
			gotoxy(123, 23)	; printf("%s tiba di %s", activePlayer->name, board->name);
            
            
			if (board->owner.type == none) {
                if (board->price < average) {
                	if (activePlayer->account < board->price) {
                        return;
                    }
                	buyProp(board,activePlayer);
                	board = temp;
				} else {
					i = rollDice();
					if (i < 4) {
						if (activePlayer->account < board->price) {
                        	return;
                    	}
                    	for (j = 0; j < activePlayer->position; j++) {
							board = board->next;
						}
                		buyProp(board,activePlayer);
                		board = temp;
					}
					if (i > 3) {//sýra geçsin
						return;
					}
				}
				if (activePlayer->type == board->owner.type) {
                	if (countProp(*activePlayer) == PROPERTY_COUNT / 3) {
                    	i = rollDice();
                    	if (i < 4) {
                    		for (j = 0; j < activePlayer->position; j++) {
								board = board->next;
							}
			        		if (board->houseOwned > 2) {
			        			printf("pc can't built house because block full\n");
								return;
							} else {
								printf("pc built a house\n");
			        			board->houseOwned += 1;
			        		}
						} else {
			        		return;
						}
					} else {
						return;
					}
            	}
			} else { //Jika miliknya sendiri
				board = temp;
				for(j = 0; j < activePlayer->position; j++) {
					board = board->next;
				}
                payRent(board, activePlayer, passivePlayer);
			}
        	break;
        
        //berhenti di kotak tagihan
		case tax:
			
			//print kotak keterangan
        	printKartu(board);
			
            gotoxy(123, 6)	; printf("%s tiba di %s", activePlayer->name, board->name);
            
			board = temp;
            for (j = 0; j < activePlayer->position; j++) {
				board = board->next;
			}
            f = board->rent;
            while (countProp(*activePlayer)!= 0 && activePlayer->account < f) {//parasý yetmiyorsa
                i = 0;
                max = activePlayer->blockOwned[i];
				while (activePlayer->blockOwned[i] != -1) {
					if(activePlayer->blockOwned[i] > max) {
						max = activePlayer->blockOwned[i];
					}
				i++;
				}
				board = temp;
                for (j = 0; j < max; j++) {
					board = board->next;
				}
                board->owner.type = none;
                if (board->houseOwned == 0) {
                	activePlayer->account += board->price / 2;
				}
                if (board->houseOwned == 1) {
                    activePlayer->account += (board->price+board->housePrice) / 2;
                }
                if (board->houseOwned == 2) {
                    activePlayer->account += (board->price+(2*board->housePrice)) / 2;
                }
                if (board->houseOwned == 3) {
                    activePlayer->account += (board->price+(3*board->housePrice)) / 2;
                }
    		}
            if (activePlayer->account > f) {
                activePlayer->account = activePlayer->account - f;
           	} else {
                activePlayer->account=0;
            }
            break;
       
       //berhenti di penjara
	   case punish:
            
            //print kotak keterangan
            printKartu(board);
            
			//menunjukkan keterangan block
			gotoxy(123, 6); printf("%s tiba di blok penjara", activePlayer->name);
            activePlayer->skipTurn += board->rent;
            break;
            
		//berhenti di block kesempatan / dana umum
        case fortune:
        	
        	if (board->name == "Kesem") {
        		gotoxy(123, 0); printf("%s tiba di %spatan, dapat kartu. ", activePlayer->name, board->name);
        	} else {
        		gotoxy(123, 0); printf("%s tiba di %s umum, dapat kartu. ", activePlayer->name, board->name);
			}
        	//print kotak keterangan
        	printKartu(board);
        	
        	//acak kesempatan / dana umum bagi pemain
        	f = rollDice() / 2;
        	
        	if (f == 1) {
        		gotoxy(128, 3)	; printf("Dapat komisi sebanyak");
        		gotoxy(136, 4)	; printf        ("$15000");
        		activePlayer->account += 15000;
				
				gotoxy(123, 7)	; printf("Uang pada akun %s bertambah", activePlayer->name);
        		gotoxy(123, 8)	; printf("menjadi $%d", activePlayer->account);
        		
        	
	        }
        	if (f == 2) {
        		gotoxy(132, 3)	; printf("Menang loteri");
				gotoxy(132, 4)	; printf("terima $10000");
				activePlayer->account += 10000;
				
				gotoxy(123, 7)	; printf("Uang pada akun %s bertambah", activePlayer->name);
        		gotoxy(123, 8)	; printf("menjadi $%d", activePlayer->account);
				
				
			}
			if (f == 3) {
				gotoxy(133, 3)	; printf("Menang kuis");
				gotoxy(132, 4)	; printf("terima $10000");
				activePlayer->account += 5000;
				
				gotoxy(123, 7)	; printf("Uang pada akun %s bertambah", activePlayer->name);
        		gotoxy(123, 8)	; printf("menjadi $%d", activePlayer->account);
				
				
        	}
			if (f == 4) {
				gotoxy(130, 3)	; printf("Nemu uang di jalan");
				gotoxy(132, 4)	; printf("terima $5000");
				activePlayer->account += 5000;
				
				gotoxy(123, 7)	; printf("Uang pada akun %s bertambah", activePlayer->name);
        		gotoxy(123, 8)	; printf("menjadi $%d", activePlayer->account);
			
				
			}
			if (f == 5) {
				gotoxy(130, 3)	; printf("Diberi sumbangan");
				gotoxy(131, 4)	; printf ("sebanyak $10000");
				activePlayer->account += 10000;
				
				gotoxy(123, 7)	; printf("Uang pada akun anda %s bertambah", activePlayer->name);
        		gotoxy(123, 8)	; printf("menjadi $%d", activePlayer->account);
				
				
			}
			if (f == 6) {
				gotoxy(132, 3)	; printf("Menang loteri");
				gotoxy(132, 4)	; printf("terima  $5000");
				activePlayer->account += 5000;
				
				gotoxy(123, 7)	; printf("Uang pada akun %s bertambah", activePlayer->name);
        		gotoxy(123, 8)	; printf("menjadi $%d", activePlayer->account);
				
				
			}
			break;
			
		case start:
		if (board->name == "Mulai") {
				gotoxy(88, 16)	; printf("Anda tiba di kotak awal, anda menerima $20000 dari Bank.");
				gotoxy(90, 4)	; printf("$%d", activePlayer->account);
				activePlayer->account += 20000;
			} else if (board->name == "Hanya") {
				gotoxy(88, 16)	; printf("Anda hanya lewat saja disini.");
			}
	
	}
	
	gotoxy(88, 35); system("pause");
}

int checkFinish(player activePlayer) {
    
	int ownedProp = countProp(activePlayer);
    
    if (activePlayer.account <= 0 && ownedProp == 0) {
		return 1;
	} else {
	 	return 0;
	}

}

void playGame(block *board, player* player1, player* player2) {
	block *temp;
	temp = (block*)malloc(sizeof(block));
	temp = board;
    int is_end = 0, dice, next_block, i, j;
    
	while (is_end != 1) {
        turn(board, player1, player2);
        board = temp;
        printBoard(board,*player1,*player2);
        board = temp;
        is_end = checkFinish(*player1);

		if (is_end == 0) {
			dice = 8;
					            
            if (player2->skipTurn == 0) {
            	
				gotoxy (89, 7); printf ("          Giliran B         ");	
				gotoxy (88, 14); printf ("%s mengocok dadu sebesar : %d\n", player2->name, dice);
                next_block = (player2->position + dice);
                
				if (next_block > 32) {
					player2->account += 20000;
				}
                player2->position = next_block % 32;
                
				board = temp;
                afterDicePC(board, player2, player1);
                board = temp;
            
            
			} else {
				gotoxy(88, 14); printf("Giliran %s dilewat %d kali.", player2->name, player2->skipTurn);
				player2->skipTurn -= 1;
				gotoxy(88, 35); system("pause");
			}
				
			printBoard(board,*player1,*player2);
            is_end = checkFinish(*player2);
            
			if (is_end == 1){
            	system("cls");
            	system("mode 131, 16");
            	
            	gotoxy(30, 3)	; for (i = 0; i < 3; i++) {
					switch (i) 
					{
						case 0:
							printf ("%c", 201); break;
						case 1:
							for (j = 0; j < 68; j++) 
							{
								printf ("%c", 205);
							} break;
						case 2:
							printf ("%c", 187); break;
					}
				}
				gotoxy(30, 4)	; printf("%c                                                                    %c\n", 186, 186);
				gotoxy(30, 5)	; printf("%c                                                                    %c\n", 186, 186);
				gotoxy(30, 6)	; printf("%c                                                                    %c\n", 186, 186);
				gotoxy(30, 7)	; printf("%c                                                                    %c\n", 186, 186);
				gotoxy(30, 8)   ; for (i = 0; i < 3; i++) {
					switch (i) {
						case 0:
							printf ("%c", 200); break;
						case 1:
							for (j = 0; j < 68; j++) {
								printf ("%c", 205);
							} 
							break;
						case 2:
							printf ("%c", 188); break;
					}
				}
                gotoxy(51, 5)	; printf("%s tidak cukup uang, %s kalah", player2->name, player2->name);
                gotoxy(54, 6)	; printf ("SELAMAT ANDA  MENANG!");
                
                gotoxy(30, 9)	;system("pause");
                
        	}
		} else {
			system("cls");
			system("mode 131, 16");
			
			gotoxy(30, 3)	; for (i = 0; i < 3; i++) {
					switch (i) 
					{
						case 0:
							printf ("%c", 201); break;
						case 1:
							for (j = 0; j < 68; j++) 
							{
								printf ("%c", 205);
							} break;
						case 2:
							printf ("%c", 187); break;
					}
				}
			gotoxy(30, 4)	; printf("%c                                                                    %c\n", 186, 186);
			gotoxy(30, 5)	; printf("%c                                                                    %c\n", 186, 186);
			gotoxy(30, 6)	; printf("%c                                                                    %c\n", 186, 186);
			gotoxy(30, 7)	; printf("%c                                                                    %c\n", 186, 186);
			gotoxy(30, 8)   ; for (i = 0; i < 3; i++) {
				switch (i) {
					case 0:
						printf ("%c", 200); break;
					case 1:
						for (j = 0; j < 68; j++) {
							printf ("%c", 205);
						} 
						break;
					case 2:
						printf ("%c", 188); break;
				}
			}
            gotoxy(51, 5)	; printf("%s tidak cukup uang, %s kalah!", player1->name, player1->name);
            gotoxy(57, 6)	; printf    ("MAAF ANDA  KALAH");
            
            gotoxy(30, 9)	;system("pause");
        }
	}
	entryScore(player1);
}

int startGame(int option) {
	int i;
	system("mode 250, 60");
	block *board;
	board = (block*)malloc(sizeof(block));
	block *temp;	
	temp = (block*)malloc(sizeof(block));
	temp = board;
	
	srand(time(NULL));
 	player player1 , player2;
	
	//init player 1
    player1.name = "A";//person
	player1.type = user;
	player1.position = 0;
    player1.skipTurn = 0;
  	player1.account = 150000;
  	
	  
	//init player 2
  	if (option == 1) {
		player2.type = ez;
	} else if (option == 2) {
		player2.type = med;
	} else if (option == 3) {
		player2.type = hd;
	}
	player2.name = "B";//computer
	player2.position = 0;
    player2.skipTurn = 0;
	player2.account = 150000;
	
	for (i = 0; i < 20; i++) {    
  		player1.blockOwned[i] = -1;
	}
  	for (i = 0; i < 20; i++) {
  		player2.blockOwned[i] = -1;
	}


	initBoard(board);
  	board = temp;
	printBoard(board, player1, player2);
	board = temp;
	playGame (board, &player1, &player2);
	
	return 0;
}

