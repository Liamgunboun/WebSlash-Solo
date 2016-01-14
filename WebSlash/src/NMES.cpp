#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <iostream>
#include "NMES.h"


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

    if(abs(ogre->x-player->x) > abs(ogre->y-player->y)) {
        if (ogre->x > player->x){
            if (!movChar(ogre, LEFT_ARROW_KEY, level))
                movChar(ogre, RIGHT_ARROW_KEY, level);
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
    for (int i=0;i<numNMES;i++){
        if (ogres[i].toMove == 1){
            movNME (&ogres[i], player, level);
            ogres[i].toMove = 0;
        }
        else ogres[i].toMove = 1;
    }
}
