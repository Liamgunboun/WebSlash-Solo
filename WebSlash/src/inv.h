#ifndef INV_H
#define INV_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include "plyr.h"

#define MAX_HOARD 50
#define MAX_NAME_LEN 60

typedef struct{
    char name[MAX_NAME_LEN];
    bool isMagical;
    int type;
}item;

void dispInv(player*);
void addRandToInv();
int initInv();
void addToInv (char* , int);
#endif
