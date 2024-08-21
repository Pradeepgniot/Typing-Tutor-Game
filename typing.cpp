#include<iostream>
#include<conio.h>
#include<dos.h>
#include<windows.h>
#include<time.h>
#include<stdio.h>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

char keys[10];
int keyPos[10][12];
int score = 0;
int highscore  = 0;

void gotoxy(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size)
{
	if(size ==0)
		size = 20;
	
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console, &lpCursor);
}

void drawBorder()
{
	for(int i=0; i<SCREEN_WIDTH; i++)
	{gotoxy(i, SCREEN_HEIGHT); 
	printf("*");
	}
	for(int i=0; i<SCREEN_HEIGHT; i++)
	{gotoxy(SCREEN_WIDTH, i);
	printf("*");
	}
	for(int i=0; i<SCREEN_HEIGHT; i++)
	{gotoxy(WIN_WIDTH, i);
	printf("*");
	}
}
	
void genAlphabet(int ind)
{	keys[ind] = 65+rand()%25;
	keyPos[ind][0] = 2 +rand()%(WIN_WIDTH -2);
	keyPos[ind][1] = 1;
}	
	
void drawAlphabet(int ind)
{	if( keyPos[ind][0]!= 0)
	{gotoxy(keyPos[ind][0], keyPos[ind][1]);
	printf("%c",keys[ind]);
	}
}	
	
void eraseAlphabet (int ind)
{	if(keyPos[ind][0]!= 0)
	{ gotoxy(keyPos[ind][0], keyPos[ind][1]);
	printf(" ");
	}
}	
	
void resetAlphabet(int ind)	
{	eraseAlphabet(ind);
	genAlphabet(ind);
}
	
void gameover()
{   system("cls");
	printf("\n\t\t---------------------------------------");
	printf("\n\t\t-------------GAME OVER-----------------");
	printf("\n\t\t---------------------------------------");
	printf("\n\n\t\t PRESS ANY KEY TO GO BACK TO MENU.");
	getch();
	}	
	
void updateScore()
{	gotoxy(WIN_WIDTH +7, 5);
	printf("SCORE: ",score);
	printf("\n");
}

void updatehighscore()
{	system("cls");
	if(score>highscore)
	 highscore = score;
	printf("\n\n\n\tYour High Score is : ",highscore);
	getch();
}
	
void instruction()
{	system("cls");
	printf("\t\tINSTRUCTIONS:");
	printf("\n\t\t---------------");
	printf("\n\t\t On the left side you will see falling characters ");
	printf("\n\t\t You have to keep them away from touching the floor ");
	printf("\n\t\t Press the respective key from your keyboard to keep playing ");
	printf("\n\n\t\t Press 'escape' to exit.");
	printf("\n\n\t\t press any key to go back to menu ");
	getch();
}	
	
void play()
{	score = 0;
	for(int i=0; i<10; i++)
	{ keyPos[i][0] = keyPos[i][1] = 1;
	}
	system("cls");
	drawBorder();
	updateScore();
	for(int i=0; i<10; i++)
		genAlphabet(i);
	gotoxy(WIN_WIDTH + 5, 2);
	printf("TYPING TUTOR");
	gotoxy(WIN_WIDTH + 6, 4);
	printf("------------");
	gotoxy(WIN_WIDTH +6, 6);
	printf("------------");
	
	gotoxy(18, 5);
	printf("Press any key to start");
	getch();
	gotoxy(18, 5);
	printf("                                    ");
	
	while(1)
	{	if(kbhit())
		{	char ch = getch();
			for(int i=0; i<10; i++)
			{ if(ch==keys[i] || ch-32 ==keys[i])
				{resetAlphabet(i);
				 score++;
			 	updateScore();
				}
			}
			if(ch==27)
			{break;
			}
		}
		for(int i=0; i<10; i++)
			drawAlphabet(i);
		
		Sleep(300);
		
		for(int i=0;i<10; i++)
		{	eraseAlphabet(i);
			keyPos[i][1] += 1;
			if( keyPos[i][1] > SCREEN_HEIGHT)
			{	gameover();
			return;
			}
		}
	}
}	
	
int main()
{
	setcursor(0,0);
	srand ((unsigned) time(NULL));
	
	do{
		system("cls");
		gotoxy(10,5);
		printf("#############################################");
		gotoxy(10,6);
		printf("  ##            TYPING TUTOR             ## ");
		gotoxy(10,7);
		printf("#############################################");
		gotoxy(10,10);
		printf("1. START GAME");
		gotoxy(10,11);
		printf("2. INSTRUCTIONS");
		gotoxy(10,12);
		printf("3. HIGHSCORE");
		gotoxy(10,13);
		printf("4. QUIT");
		
		gotoxy(10,15);
		printf("CHOOSE ANY ONE OPTION:");
		char ch = getchar();
		
		if (ch=='1') play();
		else if(ch=='2') instruction();
		else if (ch=='3') updatehighscore();
		else if (ch=='4') exit(0);
		else printf("ENTER VALID CHOICE!");
	}while(1);
	return 0;
}



















	
	
	
	
	
	
	
	

