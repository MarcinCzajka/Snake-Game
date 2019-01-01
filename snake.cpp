#include "snake.h"

using namespace std;


Level::Level(int x, int y) //Custom size is 10x10
{
    sizeX = x;
    sizeY = y;
}

void Level::setSize()
{
int choice;
system("cls");
    cout<<"Witaj, wybierz wielkosc planszy"<<endl;
    cout<<"-------------------------------"<<endl;
    cout<<"1. 10x10"<<endl;
    cout<<"2. 15x10"<<endl;
    cout<<"3. 20x15"<<endl;
    cout<<"4. 70x25"<<endl;
    cin>>choice;
        switch(choice)
        {
        case 1:{
                sizeX=10;
                sizeY=10;
                break;
            }
            case 2:{
                sizeX=15;
                sizeY=10;
                break;
            }
            case 3:{
                sizeX=20;
                sizeY=15;
                break;
            }
            case 4:{
                sizeX=70;
                sizeY=20;
                break;
            }
        }
    system("cls");
}

void Level::createField()
{
    //Fill field array with ' '
    for (int i=0;i<=sizeX-1;i++)
    {
        for (int y=0;y<=sizeY-1;y++)
            field[i][y]=' ';
    }
    //Fill in walls (#) into field array
    for (int i=0; i<sizeX; i++)
    {
        field[i][0]='#';
        field[i][sizeY-1]='#';

    }
    for (int i=0; i<sizeY; i++)
    {
        field[0][i]='#';
        field[sizeX-1][i]='#';
    }
}

void Level::spawnScore()
{
int x,y;
srand (time(NULL));
do
{
x=rand()%(sizeX-2)+1;
y=rand()%(sizeY-2)+1;
}while(field[x][y]!=' ');

    field[x][y]='*';

    //Set console cursor at given coords and draw score symbol
    COORD cord;
    cord.X = x;
    cord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
    cout<<'*';
}

void Level::drawLevel()
{
    int y=0;
    for (int i=0; i<=sizeX-1; i++)
    {
        cout << field[i][y];
            if (i == sizeX-1)
            {
                cout << endl;
                y++;
                i = -1;
                if(y == sizeY) break;
            }
    }
}

char Level::getField(int posX, int posY, int direction) //Return value of a field in front of Snake
{
    if (direction==1) posY--;
    else if (direction==2) posY++;
    else if (direction==3) posX--;
    else if (direction==4) posX++;

    return field[posX][posY];
}
void Level::setField(int x, int y, char c)
{
    field[x][y] = c;
}


SnakeHead::SnakeHead(int x, int y, int z)
{
    posX=x;
    posY=y;
    direction=z;
}



void SnakeHead::movement()
{
    //code for movement taken from stackoverflow.com/questions/14192230/wait-for-input-for-a-certain-time
    //author: birubisht
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
    int c;
    int waitSec =5; // number of cycles to wait for user input.

    while(1)
    {
     Sleep(50);
     waitSec--;

        if(kbhit())
        {
           c=getch();//This line is doubled because if its not, movement will happen twice.
            c=getch();//I believe above is one of many issues with conio.h library
           break;
        }

     if(waitSec==0)   // wait complete.
     break;
    }

    //Second contition in if forbids Snake from going backwards
    if (c==72&&direction!=2) direction=1;
    else if (c==80&&direction!=1) direction=2;
    else if (c==75&&direction!=4) direction=3;
    else if (c==77&&direction!=3) direction=4;
}

void Level::getSize(int& x, int& y)
{
    x = sizeX;
    y = sizeY;
}

void SnakeHead::spawn(int xx, int yy)
{
    int x,y;
    x=xx;
    y=yy;

//Spawn Snake roughly in the middle
    posX=((x-2)/2)+1;
    posY=((y-2)/2)+1;


    COORD cord;
    cord.X = posX;
    cord.Y = posY;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
    cout<<'@';
}

void SnakeHead::setPosition(int x, int y)
{
    posX=x;
    posY=y;
}

    int SnakeHead::getPosX() {return posX;};
    int SnakeHead::getPosY() {return posY;};
    int SnakeHead::getDirection() {return direction;};
