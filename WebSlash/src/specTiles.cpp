#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include "specTiles.h"

int isCollision (itemType *item, player *playr){
    if (item->x == playr->getX() && item->y == playr->getY()){

        printf ("yes\n");
        system ("PAUSE");
        return 1;
    }
    return 0;
}
