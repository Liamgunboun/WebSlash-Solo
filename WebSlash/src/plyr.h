#ifndef PLYR_H_INCLUDED
#define PLYR_H_INCLUDED

class player{
    int x,y;
    int hp, atk, def, atkBoost, defBoost;
    bool alive;

    public:
        void setHp(int);
        int getHp();
        void changeHp(int);
        void movePlayer(int,int);
        void setPos(int,int);
        int getX();
        int getY();
};


#endif // PLYR_H_INCLUDED
