#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <iostream>
#include "LevelGen.h"

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

class lvl{
		node tiles[MAX_H][MAX_W];
	public:
		int nodeSet (int, int, char);
		char nodeGet(int, int);
		int nodeVisited (int, int);
};

typedef struct{
    int x;
    int y;
    int hp;
    int toMove;
}NME;


int readLevel( char level[MAX_H][MAX_W]){
    FILE *levelData;
    levelData = fopen("../lvlFiles/lvl.txt","r");

    for (int i = 0; i < MAX_H; i++){
        fgets(level[i],MAX_W, levelData);
        fscanf(levelData,"\n");
    }
    fclose(levelData);
}

int drawNMES (char level[MAX_H][MAX_W], NME *ogres, int numNMES){
    for (int i=0;i<numNMES;i++){
        level[ogres[i].y][ogres[i].x] = 'o';
    }
}

int drawPlayer (char level[MAX_H][MAX_W], NME player){
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


int movChar (NME *player, int inp, char level[MAX_H][MAX_W]){
    level[player->y][player->x] = ' ';
    switch(inp){
        case (UP_ARROW_KEY):
            if (level[player->y-1][player->x] != '#')
            player->y --;
            break;
        case (DOWN_ARROW_KEY):
            if (level[player->y+1][player->x] != '#')
            player->y ++;
            break;
        case (RIGHT_ARROW_KEY):
            if (level[player->y][player->x+1] != '#')
            player->x ++;
            break;
        case (LEFT_ARROW_KEY):
            if (level[player->y][player->x-1] != '#')
            player->x --;
            break;
    }

    return 1;
}


int useInp(NME *player, int inp, char level[MAX_H][MAX_W]){

    if (inp == 224)
        movChar(player, getch(), level);


    return 1;
}

int movNME (NME *ogre, NME *player, char level[MAX_H][MAX_W]){

    if(abs(ogre->x-player->x) > abs(ogre->y-player->y)) {
        if (ogre->x > player->x)
            movChar(ogre, LEFT_ARROW_KEY, level);
        else if (ogre->x < player->x)
            movChar(ogre, RIGHT_ARROW_KEY, level);
    }
    else {
        if (ogre->y > player->y)
            movChar(ogre, UP_ARROW_KEY, level);
        else if (ogre->y < player->y)
            movChar(ogre, DOWN_ARROW_KEY, level);
    }

    return 1;
}

int movNMES (NME *ogres, int numNMES, NME *player, char level[MAX_H][MAX_W]){
    for (int i=0;i<numNMES;i++){
        if (ogres[i].toMove == 1){
            movNME (&ogres[i], player, level);
            ogres[i].toMove = 0;
        }
        else ogres[i].toMove = 1;
    }
}

int setStart (NME *player, char level[MAX_H][MAX_W]){
    for (int j=0;j<MAX_H;j++){
        for (int i=0;i<MAX_W;i++){
            if (level[j][i] == 'e'){
                player->y = j;
                player->x = i;
                return 1;
            }
        }
    }
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
    int inp;
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
	SetWindowText(console,"Web Slash v0.03");
	//------------------------------------

    genNewLvl(&levl);
    writeToFile(&levl);

    readLevel(level);
    setStart (&player, level);
    numNMES = setNMES (dumbOgres, level);

    do{
		drawBoard(level, player, dumbOgres, numNMES);
        inp=getch();
        useInp(&player, inp, level);
        movNMES(dumbOgres, numNMES, &player, level);
    }while(inp!=27);


return 0;
}
