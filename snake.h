#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#include <time.h>

using namespace std;


class SnakeHead
{
private:
    int posX;
    int posY;
    int direction;

public:
    SnakeHead(int=4,int=4,int=4);
    void spawn(int=1,int=1);

    void movement();
    int getPosX();
    int getPosY();
    int getDirection();
    void setPosition(int, int);
};

class Level
{
protected:
    int sizeX;
    int sizeY;
    char field[100][50]; //Array holding info about value of an X/Y area

public:
Level(int=10,int=10);

    void setSize();
    void createField();
    void spawnScore();
    void drawLevel();
    char getField(int,int,int);
    void setField(int,int,char);

    void getSize(int&, int&);
};
