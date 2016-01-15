#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <iostream>
#include "NMES.h"

#define MAX_ROOMS 10

int readRooms(roomType *rooms){
    FILE *roomCoords;
    int i=0;
    roomCoords = fopen("../lvlFiles/lvlcoords.txt","r");
    for (i=0;!feof(roomCoords);i++){
        fscanf(roomCoords,"%i,(%i,%i)(%i,%i)\n",&i,&rooms[i].x1,&rooms[i].y1,&rooms[i].x2,&rooms[i].y2);
    }
    return i; //returns # of rooms in file
}

int inWhichRoom(roomType *rooms, int numRooms, NME *ogre){
    for (int i=0;numRooms;i++)
        if (ogre->x >= rooms[i].x1 && ogre->y >= rooms[i].y1 && ogre->x <= rooms[i].x2 && ogre->y <= rooms[i].y2)
            return i;
    return -1;
}

int inSameRoom(roomType *rooms, int numRooms, NME *ogre, NME *player){
    if (inWhichRoom(rooms, numRooms, player) == inWhichRoom(rooms, numRooms, ogre)
    && inWhichRoom(rooms, numRooms, ogre))
        return 1;
    return 0;
}

int movChar (NME *player, int inp, char level[MAX_H][MAX_W]){
    level[player->y][player->x] = ' ';
    switch(inp){
        case (UP_ARROW_KEY):
            if (level[player->y-1][player->x] != '#'){
                player->y --;
                return 1;
            }
            break;
        case (DOWN_ARROW_KEY):
            if (level[player->y+1][player->x] != '#'){
                player->y ++;
                return 1;
            }
            break;
        case (RIGHT_ARROW_KEY):
            if (level[player->y][player->x+1] != '#'){
                player->x ++;
                return 1;
            }
            break;
        case (LEFT_ARROW_KEY):
            if (level[player->y][player->x-1] != '#'){
                player->x --;
                return 1;
            }
            break;
    }
    return 0;
}

int movNME (NME *ogre, NME *player, char level[MAX_H][MAX_W]){

    if(abs(ogre->x-player->x) > abs(ogre->y-player->y)){
        if (ogre->x > player->x){
            return movChar(ogre, LEFT_ARROW_KEY, level);
        }
        else if (ogre->x < player->x){
            return movChar(ogre, RIGHT_ARROW_KEY, level);
        }
    }
    else {
        if (ogre->y > player->y){
            return movChar(ogre, UP_ARROW_KEY, level);
        }
        else if (ogre->y < player->y){
            return movChar(ogre, DOWN_ARROW_KEY, level);
        }
    }
}

void movNMES (NME *ogres, int numNMES, NME *player, char level[MAX_H][MAX_W]){
    roomType rooms[MAX_ROOMS];
    int numRooms = readRooms(rooms);
    for (int i=0;i<numNMES;i++){
        if (ogres[i].toMove == 1 && inSameRoom(rooms, numRooms, &ogres[i], player)){
            movNME (&ogres[i], player, level);
            ogres[i].toMove = 0;
        }
        else ogres[i].toMove = 1;
    }
}
