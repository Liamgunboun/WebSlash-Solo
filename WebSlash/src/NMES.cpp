#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <iostream>
#include "NMES.h"

#define MAX_ROOMS 10
#define RAND_WANDER 3 //ogres will wander every 1 in RAND_WANDER movement turns (a movement turn is every other turn)

int randBetween (int min, int max)
{
	return rand() % (max - min + 1) + min;
}

int readRooms(roomType *rooms){
    FILE *roomCoords;
    int i=0;
    roomCoords = fopen("../lvlFiles/lvlcoords.txt","r");
    for (i=0;!feof(roomCoords);i++){
        fscanf(roomCoords,"%i,(%i,%i)(%i,%i)\n",&i,&rooms[i].x1,&rooms[i].y1,&rooms[i].x2,&rooms[i].y2);
    }
    return i; //returns # of rooms in file
}

int inWhichRoomXY(roomType *rooms, int numRooms, int x, int y){
    for (int i=0;i<numRooms;i++)
        if (x >= rooms[i].x1 && y >= rooms[i].y1 && x <= rooms[i].x2 && y <= rooms[i].y2)
            return i;
    return -1;
}

int inWhichRoomO(roomType *rooms, int numRooms, NME *ogre){
    for (int i=0;i<numRooms;i++)
        if (ogre->x >= rooms[i].x1 && ogre->y >= rooms[i].y1 && ogre->x <= rooms[i].x2 && ogre->y <= rooms[i].y2)
            return i;
    return -1;
}

int inWhichRoomP(roomType *rooms, int numRooms, player *playr){
    for (int i=0;i<numRooms;i++)
        if (playr->getX() >= rooms[i].x1 && playr->getY() >= rooms[i].y1 && playr->getX() <= rooms[i].x2 && playr->getY() <= rooms[i].y2)
            return i;
    return -1;
}

int inSameRoom(roomType *rooms, int numRooms, NME *ogre, player *playr){
    if (inWhichRoomP(rooms, numRooms, playr) == inWhichRoomO(rooms, numRooms, ogre)
    && inWhichRoomO(rooms, numRooms, ogre) != -1)
        return 1;
    return 0;
}

int movPlayr (player *playr, int inp, char level[MAX_H][MAX_W]){
    level[playr->getY()][playr->getX()] = ' ';
    switch(inp){
        case (UP_ARROW_KEY):
            if (level[playr->getY()-1][playr->getX()] != '#' && level[playr->getY()-1][playr->getX()] != 'o'){
                playr->movePlayer(0,-1);
                return 1;
            }
            break;
        case (DOWN_ARROW_KEY):
            if (level[playr->getY()+1][playr->getX()] != '#' && level[playr->getY()+1][playr->getX()] != 'o'){
                playr->movePlayer(0,1);
                return 1;
            }
            break;
        case (RIGHT_ARROW_KEY):
            if (level[playr->getY()][playr->getX()+1] != '#' && level[playr->getY()][playr->getX()+1] != 'o'){
                playr->movePlayer(1,0);
                return 1;
            }
            break;
        case (LEFT_ARROW_KEY):
            if (level[playr->getY()][playr->getX()-1] != '#' && level[playr->getY()][playr->getX()-1] != 'o'){
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
            if (level[player->y-1][player->x] != '#' && level[player->y-1][player->x] != 'o'){
                player->y --;
                return 1;
            }
            break;
        case (DOWN_ARROW_KEY):
            if (level[player->y+1][player->x] != '#' && level[player->y+1][player->x] != 'o'){
                player->y ++;
                return 1;
            }
            break;
        case (RIGHT_ARROW_KEY):
            if (level[player->y][player->x+1] != '#' && level[player->y][player->x+1] != 'o'){
                player->x ++;
                return 1;
            }
            break;
        case (LEFT_ARROW_KEY):
            if (level[player->y][player->x-1] != '#' && level[player->y][player->x-1] != 'o'){
                player->x --;
                return 1;
            }
            break;
    }
    return 0;
}

int wanderNME (NME *ogre, char level[MAX_H][MAX_W], roomType *rooms, int numRooms){
    if (randBetween(1,RAND_WANDER) == 1){
        switch (randBetween(1,4)){ //1 is up, 2 is down, 3 is left, 4 is right
            case 1 : //up
                if (inWhichRoomXY(rooms, numRooms, ogre->x, ogre->y-1) != -1)
                    return movChar (ogre, UP_ARROW_KEY, level);
                break;
            case 2 : //down
                if (inWhichRoomXY(rooms, numRooms, ogre->x, ogre->y+1) != -1)
                    return movChar (ogre, DOWN_ARROW_KEY, level);
                break;
            case 3 : //left
                if (inWhichRoomXY(rooms, numRooms, ogre->x-1, ogre->y) != -1)
                    return movChar (ogre, LEFT_ARROW_KEY, level);
                break;
            case 4 : //right
                if (inWhichRoomXY(rooms, numRooms, ogre->x+1, ogre->y) != -1)
                    return movChar (ogre, RIGHT_ARROW_KEY, level);
                break;
        }
    }
    return 0;
}

int movNME (NME *ogre, player *playr, char level[MAX_H][MAX_W], roomType *rooms, int numRooms){

    if(abs(ogre->x-playr->getX()) > abs(ogre->y-playr->getY())){
        if (ogre->x - playr->getX() > 1 && (inWhichRoomXY(rooms, numRooms, ogre->x-1, ogre->y) != -1)){
            return movChar(ogre, LEFT_ARROW_KEY, level);
        }
        else if (ogre->x - playr->getX() < -1 && (inWhichRoomXY(rooms, numRooms, ogre->x+1, ogre->y) != -1)){
            return movChar(ogre, RIGHT_ARROW_KEY, level);
        }
    }
    else {
        if (ogre->y - playr->getY() > 1 && (inWhichRoomXY(rooms, numRooms, ogre->x, ogre->y-1) != -1)){
            return movChar(ogre, UP_ARROW_KEY, level);
        }
        else if (ogre->y - playr->getY() < -1 && (inWhichRoomXY(rooms, numRooms, ogre->x, ogre->y+1) != -1)){
            return movChar(ogre, DOWN_ARROW_KEY, level);
        }
    }
}

void movNMES (NME *ogres, int numNMES, player *playr, char level[MAX_H][MAX_W], roomType rooms[MAX_ROOMS], int numRooms){
    for (int i=0;i<numNMES;i++){
        if (ogres[i].toMove == 1){
            if (inSameRoom(rooms, numRooms, &ogres[i], playr)){
                movNME (&ogres[i], playr, level, rooms, numRooms);
                ogres[i].toMove = 0;
            }
            else wanderNME (&ogres[i], level, rooms, numRooms);
        }
        else ogres[i].toMove = 1;
    }
}

int nextToAnyOgreXY (int playerX, int playerY, NME *ogres, int numNMES){
    for (int i=0;i<numNMES;i++){
        if ((abs(playerX - ogres[i].x) <= 1 && playerY - ogres[i].y == 0) ||
            (playerX - ogres[i].x == 0 && abs(playerY - ogres[i].y) <= 1)){
            return 1;
        }
    }
    return 0;
}

void drawCombatMenu (NME *ogres, int numNMES, player *playr){
    printf ("%\n");
    if (nextToAnyOgreXY(playr->getX(), playr->getY(), ogres, numNMES)){
        printf("move towards ogre to attack");
    }
}
