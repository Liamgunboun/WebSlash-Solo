#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <iostream>
#include "NMES.h"

#define MAX_ROOMS 10
#define RAND_WANDER 4 //ogres will wander every 1 in RAND_WANDER movement turns (a movement turn is every other turn)
#define NME_BASE_ATK 10

//-----% Random Function %-------
int randBetween (int min, int max)
{
	return rand() % (max - min + 1) + min;
}

//-----% loads the room data from a text file %-------
int readRooms(roomType *rooms){
    FILE *roomCoords;
    int i=0;
    roomCoords = fopen("../lvlFiles/lvlcoords.txt","r");
    for (i=0;!feof(roomCoords);i++){
        fscanf(roomCoords,"%i,(%i,%i)(%i,%i)\n",&i,&rooms[i].x1,&rooms[i].y1,&rooms[i].x2,&rooms[i].y2);
    }
    return i; //returns # of rooms in file
}

//-----% function that determine which room an entity is in %-------
int inWhichRoomXY(roomType *rooms, int numRooms, int x, int y){
    for (int i=0;i<numRooms;i++)
        if (x >= rooms[i].x1 && y >= rooms[i].y1 && x <= rooms[i].x2 && y <= rooms[i].y2)
            return i;
    return -1;
}

int inSameRoom(roomType *rooms, int numRooms, NME *ogre, player *playr){
    if (inWhichRoomXY(rooms, numRooms, playr->getX(), playr->getY()) == inWhichRoomXY(rooms, numRooms, ogre->x, ogre->y)
    && inWhichRoomXY(rooms, numRooms, ogre->x, ogre->y) != -1)
        return 1;
    return 0;
}

//-----% Functions that move entities %-------
int movPlayr (player *playr, int inp, char level[MAX_H][MAX_W], NME *ogres, int numNMES){
    level[playr->getY()][playr->getX()] = ' ';
    switch(inp){
        case (UP_ARROW_KEY):
            if (level[playr->getY()-1][playr->getX()] != '#'){
                if (level[playr->getY()-1][playr->getX()] != 'o'){
                    playr->movePlayer(0,-1);
                    return 1;
                }
                else if (level[playr->getY()-1][playr->getX()] == 'o'){
                    playerAttackNME(playr, &ogres[whichOgreXY(ogres, numNMES, playr->getX(), playr->getY()-1)]);
                }
            }
            break;
        case (DOWN_ARROW_KEY):
            if (level[playr->getY()+1][playr->getX()] != '#'){
                if (level[playr->getY()+1][playr->getX()] != 'o'){
                    playr->movePlayer(0,1);
                    return 1;
                }
                else if (level[playr->getY()+1][playr->getX()] == 'o'){
                    playerAttackNME(playr, &ogres[whichOgreXY(ogres, numNMES, playr->getX(), playr->getY()+1)]);
                }
            }
            break;
        case (RIGHT_ARROW_KEY):
            if (level[playr->getY()][playr->getX()+1] != '#'){
                if (level[playr->getY()][playr->getX()+1] != 'o'){
                    playr->movePlayer(1,0);
                    return 1;
                }
                else if (level[playr->getY()][playr->getX()+1] == 'o'){
                    playerAttackNME(playr, &ogres[whichOgreXY(ogres, numNMES, playr->getX()+1, playr->getY())]);
                }
            }
            break;
        case (LEFT_ARROW_KEY):
            if (level[playr->getY()][playr->getX()-1] != '#'){
                if (level[playr->getY()][playr->getX()-1] != 'o'){
                    playr->movePlayer(-1,0);
                    return 1;
                }
                else if (level[playr->getY()][playr->getX()-1] == 'o'){
                    playerAttackNME(playr, &ogres[whichOgreXY(ogres, numNMES, playr->getX()-1, playr->getY())]);
                }
            }
            break;
    }
    return 0;
}

int movChar (NME *player, int inp, char level[MAX_H][MAX_W]){ //takes an input direction and moves an entity in that direction
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

int wanderNME (NME *ogre, char level[MAX_H][MAX_W], roomType *rooms, int numRooms){ //function that controls the random wandering of the enemies
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

int movNME (NME *ogre, player *playr, char level[MAX_H][MAX_W], roomType *rooms, int numRooms){ //determines the postition of the player relative to that of the enemy, then moves towards the player

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

void movNMES (NME *ogres, int numNMES, player *playr, char level[MAX_H][MAX_W], roomType rooms[MAX_ROOMS], int numRooms){ //tells enemies to follow the player if they are in the same room, else tells them to wander
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

//-----% Functions that determine the player's position relative to an ogre %-------
int nextToOgre (int playerX, int playerY, NME *ogre){
    if (((abs(playerX - ogre->x) <= 1 && playerY - ogre->y == 0) ||
            (playerX - ogre->x == 0 && abs(playerY - ogre->y) <= 1)))
            return 1;
    return 0;
}

int nextToWhichOgre (int playerX, int playerY, NME *ogres, int numNMES){
    for (int i=0;i<numNMES;i++){
        if (nextToOgre(playerX, playerY, &ogres[i])) return i;
    }
    return -1;
}

int whichOgreXY(NME *ogres, int numNMES, int x, int y){ //takes a pair of coords and returns the ogre in that position
    for (int i=0;i<numNMES;i++)
        if (ogres[i].x == x && ogres[i].y == y) return i;
    return -1;
}

//-----% Attack functions %-------
int playerAttackNME (player *playr, NME *ogre){
    ogre->hp = ogre->hp - playr->getAtk();
    return playr->getAtk();
}

int NMEAttackPlayer (NME *ogre, player *playr){
    playr->changeHp(-(NME_BASE_ATK-playr->getDef()));
    return NME_BASE_ATK-playr->getDef();
}

//-----% Functions that deal with death %-------
int ogreDeath (NME *ogres, int death, int *numNMES){
    for (int i=death;i<*numNMES-1;i++){
        ogres[i] = ogres[i+1];
    }
    *numNMES = *numNMES - 1;
    printf ("Ogre has been slain.\n");
    return 1;
}

void drawCombatMenu (NME *ogres, int *numNMES, player *playr, char level[MAX_H][MAX_W]){
    printf ("%\n");
    for (int i=0;i<*numNMES;i++){
        if (ogres[i].hp <= 0){
            level[ogres[i].y][ogres[i].x] = ' ';
            ogreDeath(ogres, i, numNMES);
        }
        if (nextToOgre(playr->getX(), playr->getY(), &ogres[i])){
            printf("Ogre attacks for %i\n",NMEAttackPlayer (&ogres[nextToWhichOgre(playr->getX(), playr->getY(), ogres, *numNMES)], playr));
        }
    }
}
