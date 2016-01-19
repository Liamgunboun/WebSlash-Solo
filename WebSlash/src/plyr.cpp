#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <iostream>
#include "plyr.h"


void player::setHp(int c){
    hp = c;
}
int player::getHp(){
    return hp;
}
int player::getX(){
    return x;
}
int player::getY(){
    return y;
}
void player::changeHp(int c){
    hp = hp + c;
}
void player::movePlayer(int cX, int cY){
    x = x + cX; y = y + cY;
}
void player::setPos(int cX, int cY){
    x = cX; y = cY;
}
void player::setAtkBon(int bonus){
    atkBoost = bonus;
}
void player::setDefBon(int bonus){
    defBoost = bonus;
}
void player::addAtkBon(int bonus){
    atkBoost = atkBoost + bonus;
}
void player::addDefBon(int bonus){
    defBoost = atkBoost + bonus;
}
int player::getAtk(){
    return (atk+atkBoost);
}
int player::getDef(){
    return (def+defBoost);
}
void player::setAtk(int a){
    atk = a;
}
void player::setDef(int d){
    def = d;
}
