#define _WIN32_WINNT 0x0500
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <iostream>
#include "NMES.h"
#include "LevelGen.h"
#include "inv.h"

#define MAX_H 40
#define MAX_W 60
#define MAX_NMES 10
#define UP_ARROW_KEY 72
#define DOWN_ARROW_KEY 80
#define RIGHT_ARROW_KEY 77
#define LEFT_ARROW_KEY 75

typedef struct{
	bool visited;
	char ent;
}node;


int readLevel( char level[MAX_H][MAX_W]){
    FILE *levelData;
    levelData = fopen("../lvlFiles/lvl.txt","r");
    if (levelData == NULL) return 0;
    for (int i = 0; i < MAX_H; i++){
        fgets(level[i],MAX_W, levelData);
        fscanf(levelData,"\n");
    }
    fclose(levelData);
    return 1;
}

void saveLvl(char level[MAX_H][MAX_W]){
	FILE *lvlFile;
	lvlFile = fopen("../lvlFiles/lvl.txt","w");
	for (int i = 0; i < MAX_H; i++){
            fprintf(lvlFile,"%s\n",level[i]);
		}
    fclose(lvlFile);
}

void drawNMES (char level[MAX_H][MAX_W], NME *ogres, int numNMES){
    for (int i=0;i<numNMES;i++){
        level[ogres[i].y][ogres[i].x] = 'o';
    }
}

void drawPlayer (char level[MAX_H][MAX_W], NME player){
    level[player.y][player.x] = '&';
}

int drawBoard(char level[MAX_H][MAX_W], NME player, NME *ogres, int numNMES){

    system("CLS");

    drawNMES (level, ogres, numNMES);

    drawPlayer(level, player);
    for (int j = 0; j < MAX_H; j++){
        printf("%s", level[j]);
        printf("\n");
    }

    return 1;
}

int useInp(NME *player, int inp, char level[MAX_H][MAX_W]){
    if (inp == 224)
        movChar(player, getch(), level);
    return 1;
};


int setStart (NME *player, char level[MAX_H][MAX_W]){
    for (int j=0;j<MAX_H;j++){
        for (int i=0;i<MAX_W;i++){
            if (level[j][i] == 'e' || level[j][i] == '&'){
                player->y = j;
                player->x = i;
            }
        }
    }
    return 1;
}

int setNMES (NME *ogres, char level[MAX_H][MAX_W]){
    int numOgres = 0;
    for (int j=0;j<MAX_H;j++){
        for (int i=0;i<MAX_W;i++){
            if (level[j][i] == 'o'){
                ogres[numOgres].y = j;
                ogres[numOgres].x = i;
                ogres[numOgres].toMove = 1;
                numOgres++;
            }
        }
    }
    return numOgres;
}



int main(){

    NME player;
    NME dumbOgres[MAX_NMES];
    int numNMES;
    int inp = 0;
    lvl levl;
    char level[MAX_H][MAX_W];
    player.x = 19;
    player.y = 24;

   //-----% Important Initializers %-----
	srand(time(NULL));

	HWND console = GetConsoleWindow();
  	RECT r;
 	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 1280, 720, TRUE);
	SetWindowText(console,"Web Slash v0.05");
	//------------------------------------
    initInv();


    while (inp != 'n' && inp != 'c'){
        printf("\t\t\t     Greetings\n");
        printf("\t\t\tWelcome To Web Slash\n");
        printf("\t\t   New Game: n | Continue Game: c\n\n\n");
        inp = getch();
    }

    if (inp == 'n'){
        genNewLvl(&levl);
        writeToFile(&levl);
    }
    if(!readLevel(level)){
        printf("\t    No existing level found, generate one now? y/n \n\n");
        inp = getch();
        if (inp == 'n'){
           inp = 27;
           printf("\t\t\t  Have a nice day!\n\n\n\n\n");
        }
    }

    setStart (&player, level);
    numNMES = setNMES (dumbOgres, level);


    while(inp!=27){
		drawBoard(level, player, dumbOgres, numNMES);
        inp=getch();
        useInp(&player, inp, level);
        movNMES(dumbOgres, numNMES, &player, level);
    }

    system("CLS");
    printf("\t\tWould you like to save your game? y/n");
    inp=getch();
    if (inp == 'y'){
        saveLvl(level);
        printf("\n\n\n\t\t\tLevel Saved!\n\n\n\n\n");
        getch();
    }

return 0;
}
