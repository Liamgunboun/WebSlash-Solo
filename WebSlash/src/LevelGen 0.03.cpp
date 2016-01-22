/*******************************************************************

        Xander May's randomly freezing random level generation

The freezing is most likely due to the count of 'try' going over the
  allowed number and not knowing what to do despite my best efforts.

*******************************************************************/


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include "LevelGen.h"

#define MAX_H 40
#define MAX_W 59

#define CHANCE_LOW 500
#define CHANCE_MED 150
#define CHANCE_HIGH 100

#define RM_MAXX 20
#define RM_MAXY 8

#define MIN_ROOMS 5
#define MAX_ROOMS 10


int lvlGen(lvl *level, int); //Declaring later functions
int rb (int min, int max);
void drawBoard(lvl *level);
void writeToFile (lvl *level);

//-----% LVL Class getter & Setters %-------
int lvl::nodeSet (int h, int w, char chr){
	tiles[h][w].ent = chr;

	if (tiles[h][w].ent = chr) return 1;
	return 0;
}

char lvl::nodeGet(int h, int w){
	return (tiles[h][w].ent);
}

int lvl::nodeVisited (int h, int w){
	return (tiles[h][w].visited);
}

//-----% Room Class %-----
void room::setVisit(bool status){
	visited = status;
}
int room::x1Get(){
	return (x1);
}
int room::x2Get(){
	return (x2);
}
int room::y1Get(){
	return (y1);
}
int room::y2Get(){
	return (y2);
}

//This is used to grab the points for the ogre functions later on.
void room::setPoints(int x1s, int y1s, int x2s, int y2s){
	x1 = x1s;
	x2 = x2s;
	y1 = y1s;
	y2 = y2s;
}

//-----% Room Generation Functions %------

//Recursively clear the allotted space for each room
int recurClear(lvl *level, int h, int w, int x, int y, int doH, int showGen){

	if (h && doH == 1) recurClear(level, h-1, w, x, y,1, showGen);
	if (w) recurClear(level, h, w-1, x, y,0, showGen);

	if(rb(1,CHANCE_HIGH)==1)
		level->nodeSet(y+h,x+w, '$');
	else if(rb(1,CHANCE_LOW)==1)
		level->nodeSet(y+h,x+w, '*');
	else if(rb(1,CHANCE_MED)==1)
		level->nodeSet(y+h,x+w, 'o');
	else
		level->nodeSet(y+h,x+w, ' ');

	if (showGen){
		system("CLS");
		for (int i = 0; i < MAX_H; i++){
			for (int j = 0; j < MAX_W; j++){
					printf("%c", level->nodeGet(i,j));
			}
				printf("\n");
		}
	}
	return 1;
}

//Make sure the level has the desired qualities
int validLevel(lvl *level){
	int count = 0;
	for (int i=1; i <= MAX_H; i++){
		for (int j=1; j <= MAX_W; j++){
			if (level->nodeGet(i,j) == 'o') count++;
		}
	}
	if (count > 3) return 1;

	return 0;
}

//Make sure it does not intersect with any other rooms
int validRoom(lvl *level, int h, int w, int x, int y, int doH, int showGen){
	for (int i=1; i <= h+1; i++){
		for (int j=1; j <= w+1; j++){
			if (level->nodeGet(y+i,x+j) !='#') return 0;
		}
	}
	return 1;
}

//Generate the paths between rooms
void genPath(lvl *level, int x1, int y1, int x2, int y2){

	while (x1!=x2 || y1!=y2){
		if (abs(x2 - x1) >= abs(y2-y1)){
			level->nodeSet(y1,x1, ' ');
			if ((x2-x1)>0)
				x1++;
			else
				x1--;
		}
		else{
			level->nodeSet(y1,x1, ' ');
			if ((y2-y1)>0)
				y1++;
			else
				y1--;
		}
	}
}

//This is used to create a new room. This is where the freezing comes from.
//If we had more time im sure I could fix it. If a room fails to create then
//it will crash...
//Increasing the amount of tries decreased failure rate but wil put a larger load on the
//system and caused some school computers to crash.
int addRoom(lvl *level, int showGen, room *rooms, int tries){
	int x = rb(1, MAX_W-RM_MAXX-2);
	int y = rb(1, MAX_H-RM_MAXY-2);
	int w = rb(3, RM_MAXX);
	int h = rb(3, RM_MAXY);

	if (validRoom(level, h+2, w+2, x-2, y-2, 1, showGen)){
		rooms->setPoints(x,y,x+w,y+h);
		recurClear(level, h, w, x, y, 1, showGen);
		return (1);
	}
	else if(tries<=50){
		return (addRoom(level, showGen, rooms, ++tries));
	}
	return 0;
}


//-----------------------------------------------------------------
//  This is what is called in the main file when it wants to create
//a new level for the player.
int genNewLvl(lvl *level, int showgen){
	lvlGen(level, showgen);
	drawBoard(level);
	writeToFile(level);
	return 0;
}

//-----% Generate The Level %-------
int lvlGen (lvl *level, int showGen){
	int numRooms = rb(MIN_ROOMS,MAX_ROOMS);
	char temp;
	int x1,x2,y1,y2;
	room rooms[numRooms];

	//Make the entire level solid
	for (int i = 0; i < MAX_H; i++){
		for (int j = 0; j < MAX_W; j++){
			level->nodeSet(i,j,'#');
		}
	}



	while (!validLevel(level)){
		for (int i = 0; i < MAX_H; i++){
			for (int j = 0; j < MAX_W; j++){
				level->nodeSet(i,j,'#');
			}
		}
		for (int i = 0; i < numRooms; i++)	{
			printf("Trynna make a new room\n");
			if (addRoom(level, showGen, &rooms[i],0)){
				x1 = (rooms[i].x1Get()+rooms[i].x2Get())/2;
				x2 = (rooms[i-1].x1Get()+rooms[i-1].x2Get())/2;
				y1 = (rooms[i].y1Get()+rooms[i].y2Get())/2;
				y2 = (rooms[i-1].y1Get()+rooms[i-1].y2Get())/2;

				if (i>0 )
					genPath(level,x1,y1,x2,y2);

				if (i == 0)
					level->nodeSet(y1,x1,'e');
				else if(i==numRooms-1)
					level->nodeSet(y1,x1,'E');
			}
		}
		printf("Bad level...");
		//getch();
	}
	writeCoords(rooms, numRooms);
	return 1;
}

//-----% Draw & Save Level %-------
void drawBoard(lvl *level){
	system("cls");
	for (int i = 0; i < MAX_H; i++){
			for (int j = 0; j < MAX_W; j++){
					printf("%c", level->nodeGet(i,j));
			}
			printf("\n");
		}
}

void writeToFile(lvl *level){
	FILE *lvlFile;
	lvlFile = fopen("../lvlFiles/lvl.txt","w");
	for (int i = 0; i < MAX_H; i++){
			for (int j = 0; j < MAX_W; j++){
					fprintf(lvlFile,"%c",level->nodeGet(i,j));
			}
			fprintf(lvlFile,"\n");
		}
    fclose(lvlFile);
}

void writeCoords(room *rooms, int numRooms){
    FILE *lvlCoords;
    lvlCoords = fopen("../lvlFiles/lvlcoords.txt","w");
    for (int i=0;i<numRooms;i++){
        fprintf(lvlCoords,"%i,(%i,%i)(%i,%i)\n",i,rooms[i].x1Get(),rooms[i].y1Get(),rooms[i].x2Get(),rooms[i].y2Get());
    }
     fclose(lvlCoords);
}
//-----% Rand Function %-------
int rb (int min, int max)
{
	return rand() % (max - min + 1) + min;
}





