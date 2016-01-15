#ifndef LEVELGEN_H
#define LEVELGEN_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>


#define MAX_H 40
#define MAX_W 59

#define RM_MAXX 20
#define RM_MAXY 8

#define MIN_ROOMS 5
#define MAX_ROOMS 10


typedef struct{
	bool visited;
	char ent;
}node;

class lvl{
		node tiles[MAX_H][MAX_W];
	public:
		int nodeSet (int, int, char);
		char nodeGet(int, int);
		int nodeVisited (int, int);
};

class room{
	int x1,x2,y1,y2;
	bool visited;
	public:
		void setVisit(bool);
		int x1Get();
		int x2Get();
		int y1Get();
		int y2Get();
		void setPoints(int, int, int, int);
};


int genNewLvl(lvl*);
void writeToFile(lvl*);
void writeCoords(room*, int);

#endif
