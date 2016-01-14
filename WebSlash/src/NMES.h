#ifndef NMES_H
#define NMES_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <iostream>

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

int movChar(NME*, int, char[MAX_H][MAX_W]);
int movNME(NME*, NME*, char[MAX_H][MAX_W]);
void movNMES(NME*, int, NME*, char[MAX_H][MAX_W]);

#endif // NMES_H
