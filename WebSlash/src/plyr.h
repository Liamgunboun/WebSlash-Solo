#ifndef PLYR_H_INCLUDED
#define PLYR_H_INCLUDED

class player{
    int x,y,hp, atk, def, atkBoost, defBoost, points;
    bool alive;

    public:
        void setHp(int);
        int getHp();
        void changeHp(int);
        void movePlayer(int,int);
        void setPos(int,int);
        int getX();
        int getY();
        void setAtkBon(int);
        void setDefBon(int);
        void addAtkBon(int);
        void addDefBon(int);
        int getAtk();
        int getDef();
        void setAtk(int);
        void setDef(int);
        void savePlayer ();
        void readPlayer ();
        int isAlive();
        void setAlive();
        void setDead();
        void addPoints(int);
        int getPoints();
};


#endif // PLYR_H_INCLUDED
