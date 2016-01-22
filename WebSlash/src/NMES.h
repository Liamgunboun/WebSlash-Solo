#ifndef NMES_H
#define NMES_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <iostream>
#include "plyr.h"

#define MAX_ROOMS 10
#define MAX_H 40
#define MAX_W 60
#define MAX_NMES 10
#define UP_ARROW_KEY 72
#define DOWN_ARROW_KEY 80
#define RIGHT_ARROW_KEY 77
#define LEFT_ARROW_KEY 75

typedef struct{
    int x;
    int y;
    int hp;
    int toMove;
}NME;

typedef struct{
    int x1;
    int y1;
    int x2;
    int y2;
}roomType;

int movPlayr (player*, int, char level[MAX_H][MAX_W], NME*, int);
int movChar(NME*, int, char[MAX_H][MAX_W]);
int movNME(NME*, NME*, char[MAX_H][MAX_W]);
int readRooms(roomType*);
int nextToWhichOgre (int, int, NME*, int);
int whichOgreXY(NME*, int, int, int);
void movNMES(NME*, int, player*, char[MAX_H][MAX_W], roomType rooms[MAX_ROOMS], int);
int playerAttackNME (player*, NME*);
void drawCombatMenu (NME*, int*, player*, char[MAX_H][MAX_W]);

#endif // NMES_H
