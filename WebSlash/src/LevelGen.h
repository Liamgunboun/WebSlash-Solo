#ifndef LEVELGEN_H
#define LEVELGEN_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

class lvl;
class room;

int genNewLvl(lvl*);
void writeToFile(lvl*);
void writeCoords(room*, int);

#endif
