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
#include "plyr.h"
#include "specTiles.h"

#define MAX_H 40
#define MAX_W 60

#define MAX_MON 10
#define MAX_STAR 10

#define BASE_ATK 5
#define BASE_DEF 5

#define MAX_NMES 10
#define UP_ARROW_KEY 72
#define DOWN_ARROW_KEY 80
#define RIGHT_ARROW_KEY 77
#define LEFT_ARROW_KEY 75

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

void drawExit (char level[MAX_H][MAX_W], itemType item){
    level[item.y][item.x] = 'E';
}

void drawItems (char level[MAX_H][MAX_W], itemType *items, char c, int numItems){
    for (int i=0;i<numItems;i++){
        level[items[i].y][items[i].x] = c;
    }
}

void drawPlayer (char level[MAX_H][MAX_W], player playr){
    level[playr.getY()][playr.getX()] = '&';
}

void printMenu(){
    printf("\t\t\t Menu:\n Inventory: i \tExit   Game: esc\t Character Sheet: c");
}

int drawBoard(char level[MAX_H][MAX_W], player playr, NME *ogres, int numNMES, itemType exitTile){
    system("CLS");
    drawExit (level, exitTile);
    drawNMES (level, ogres, numNMES);
    drawPlayer(level, playr);

    for (int j = 0; j < MAX_H; j++){
        printf("%s", level[j]);
        if(j==0){
            printf("\tHp: %i", playr.getHp());
        } else if (j == 2){
            printf(" Atk: %i   Def: %i", playr.getAtk(), playr.getDef());
        } else if (j == 4)
            printf(" POINTS: %i", playr.getPoints());
        printf("\n");
    }
    printMenu();

    return 1;
}

int useInp(player *playr, int inp, char level[MAX_H][MAX_W], NME *ogres, int numNMES){
    if (inp == 224)
        movPlayr(playr, getch(), level, ogres, numNMES);
    else if (inp == 'i'){
        dispInv(playr);
    }

    return 1;
};


int setStart (player *playr, char level[MAX_H][MAX_W]){
    for (int j=0;j<MAX_H;j++){
        for (int i=0;i<MAX_W;i++){
            if (level[j][i] == 'e' || level[j][i] == '&'){
                playr->setPos(i,j);
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
                ogres[numOgres].hp = 10;
                ogres[numOgres].toMove = 1;
                numOgres++;
            }
        }
    }
    return numOgres;
}

int setItem (itemType *item, char key, char level[MAX_H][MAX_W]){
    int numItems=0;
    for (int j=0;j<MAX_H;j++){
        for (int i=0;i<MAX_W;i++){
            if (level[j][i] == key){
                item->x = i;
                item->y = j;
                item->collision = 0;
                numItems++;
            }
        }
    }
    return numItems;
}

int main(){

    player playr;
    NME dumbOgres[MAX_NMES];
    int numNMES;
    int inp = 0;
    lvl levl;
    int numLvl=0;
    char level[MAX_H][MAX_W];
    roomType rooms[MAX_ROOMS];
    int numRooms;
    itemType exitTile;
    itemType money[MAX_MON];
    itemType magicals[MAX_STAR];
    int showGen=0;

   //-----% Important Initializers %-----
    srand(time(NULL));

    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, 1280, 720, TRUE);
    SetWindowText(console,"Web Slash v0.05");
    //------------------------------------



    while (inp != 'n' && inp != 'c'){
        printf("\t\t\t     Greetings\n");
        printf("\t\t\tWelcome To Web Slash\n");
        printf("\t\t   New Game: n | Continue Game: c\n\n\n");
        inp = getch();
    }

    if (inp == 'n'){
        printf("\t\tBefore playing a new level must be generated \n \t\tDo you want to be shown the generation process? y/n \n\t\t(warning, a lot of flashing will occur)\n\n ");
        printf("\t\t(Also due to some hidden bug, this will fail 1/10 times)\n");
        printf("\t\t(If it happens just restart the program and all will be well)\n");
        inp=getch();
        if (inp == 'y') showGen = 1;
        genNewLvl(&levl, showGen);
        writeToFile(&levl);
        initInv();
        makeStartInv();
        playr.setAtkBon(0);
        playr.setDefBon(0);
        playr.setAtk(BASE_ATK);
        playr.setDef(BASE_DEF);
        playr.setHp(30);
        playr.setAlive();
        } else if (inp == 'c'){
            playr.readPlayer();
        }

    if(!readLevel(level)){
        printf("\t    No existing level found, generate one now? y/n \n\n");
        inp = getch();
        if (inp == 'n'){
           inp = 27;
           printf("\t\t\t  Have a nice day!\n\n\n\n\n");
        }
    }

    while (inp!=27 && playr.getHp()>0){ //loop that generates new rooms when one is completed
        if (numLvl){
            genNewLvl(&levl,0);
            writeToFile(&levl);
            readLevel(level);
            numLvl++;
        }
        setStart (&playr, level);
        setItem (&exitTile, 'E', level);
        setItem (magicals, '*', level);
        numNMES = setNMES (dumbOgres, level);

        numRooms = readRooms (rooms);

        while((inp!=27 && playr.getHp()>0 && !exitTile.collision) || numNMES > 0){ //primary game loop. controls player movement, enemy movement, etc
            drawBoard(level, playr, dumbOgres, numNMES, exitTile);
            drawCombatMenu(dumbOgres, &numNMES, &playr, level);
            exitTile.collision = isCollision(&exitTile, &playr);
            inp=getch();
            if (playr.getHp()<30)playr.changeHp(1);
            useInp(&playr, inp, level, dumbOgres, numNMES);
            movNMES(dumbOgres, numNMES, &playr, level, rooms, numRooms);
        }
        numLvl++;
    }

    system("CLS");
    if (playr.getHp()>0){
        printf("\t\tWould you like to save your game? y/n");
        inp=getch();
        if (inp == 'y'){
            saveLvl(level);
            playr.savePlayer();
            printf("\n\n\n\t\t\tLevel Saved!\n\n\n\n\n");
            getch();
        }
    } else {
        printf("Oh Dear you seem to have died . . . .");
        getch();
    }


return 0;
}
