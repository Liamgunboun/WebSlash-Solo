#ifndef PLYR_H_INCLUDED
#define PLYR_H_INCLUDED

class player{
    int x,y;
    int hp;
    bool alive;

    public:
        int setHp(int);
        int getHp();
        void changeHp(int);
        void movePlayer(int,int);
        void setPos(int,int);
        int getX();
        int getY();
};


#endif // PLYR_H_INCLUDED
