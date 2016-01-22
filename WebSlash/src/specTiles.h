#ifndef SPECTILES_H
#define SPECTILES_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include "plyr.h"

typedef struct{
    int x;
    int y;
    int collision;
}itemType;

int isCollision(itemType*, player*);

#endif
