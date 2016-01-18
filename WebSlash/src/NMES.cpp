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

int inWhichRoomO(roomType *rooms, int numRooms, NME *ogre){
    for (int i=0;numRooms;i++)
        if (ogre->x >= rooms[i].x1 && ogre->y >= rooms[i].y1 && ogre->x <= rooms[i].x2 && ogre->y <= rooms[i].y2)
            return i;
    return -1;
}

int inWhichRoomP(roomType *rooms, int numRooms, player *playr){
    for (int i=0;numRooms;i++)
        if (playr->getX() >= rooms[i].x1 && playr->getY() >= rooms[i].y1 && playr->getX() <= rooms[i].x2 && playr->getY() <= rooms[i].y2)
            return i;
    return -1;
}

int inSameRoom(roomType *rooms, int numRooms, NME *ogre, player *playr){
    if (inWhichRoomP(rooms, numRooms, playr) == inWhichRoomO(rooms, numRooms, ogre)
    && inWhichRoomO(rooms, numRooms, ogre))
        return 1;
    return 0;
}

int movPlayr (player *playr, int inp, char level[MAX_H][MAX_W]){
    level[playr->getY()][playr->getX()] = ' ';
    switch(inp){
        case (UP_ARROW_KEY):
            if (level[playr->getY()-1][playr->getX()] != '#'){
                playr->movePlayer(0,-1);
                return 1;
            }
            break;
        case (DOWN_ARROW_KEY):
            if (level[playr->getY()+1][playr->getX()] != '#'){
                playr->movePlayer(0,1);
                return 1;
            }
            break;
        case (RIGHT_ARROW_KEY):
            if (level[playr->getY()][playr->getX()+1] != '#'){
                playr->movePlayer(1,0);
                return 1;
            }
            break;
        case (LEFT_ARROW_KEY):
            if (level[playr->getY()][playr->getX()-1] != '#'){
                playr->movePlayer(-1,0);
                return 1;
            }
            break;
    }
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

int movNME (NME *ogre, player *playr, char level[MAX_H][MAX_W]){

    if(abs(ogre->x-playr->getX()) > abs(ogre->y-playr->getY())){
        if (ogre->x > playr->getX()){
            return movChar(ogre, LEFT_ARROW_KEY, level);
        }
        else if (ogre->x < playr->getX()){
            return movChar(ogre, RIGHT_ARROW_KEY, level);
        }
    }
    else {
        if (ogre->y > playr->getY()){
            return movChar(ogre, UP_ARROW_KEY, level);
        }
        else if (ogre->y < playr->getY()){
            return movChar(ogre, DOWN_ARROW_KEY, level);
        }
    }
}

void movNMES (NME *ogres, int numNMES, player *playr, char level[MAX_H][MAX_W]){
    roomType rooms[MAX_ROOMS];
    int numRooms = readRooms(rooms);
    for (int i=0;i<numNMES;i++){
        if (ogres[i].toMove == 1 && inSameRoom(rooms, numRooms, &ogres[i], playr)){
            movNME (&ogres[i], playr, level);
            ogres[i].toMove = 0;
        }
        else ogres[i].toMove = 1;
    }
}
