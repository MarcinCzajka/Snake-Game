#include "snake.h"

using namespace std;

static void gotoxy(int,int); //Set console cursor in given x,y coordinates
void headMovement(int,int,int, int&, int&); //Handles drawing and sending old position to bodyStructure
void bodyMovement(int&,int&,int&,int&); //Handles drawing of Snake's body
int collision(char, int&, int&, int&); //Checks if snake stepped on an empty field or a Score

struct bodyStructure //Array holding coordinates of consecutive elements of Snake's body
{
    int bodyX=0;
    int bodyY=0;
    int tempOgonX=0; //Coordinates passed to the next instance of body
    int tempOgonY=0; //
};
int main()
{
while(true)
{
    int bodyCounter=0; //Holds size of Snake's length
    int x,y; //Holds size of a Level
    int tempX=0,tempY=0; //Previous coordinates of Snake's head
    int existScore=0; //keep track if '*' exists
    int score=0;
    int moveCounter=0;
    char temp=' '; //Holds value of a field on which a player stepped

    //Create objects
    Level level1;
    SnakeHead snake1;

        level1.setSize();


            //Counting down to start just for convenience
            system("cls");
            cout<<3;
            Sleep(500);
            gotoxy(0,0);
            cout<<2;
            Sleep(500);
            gotoxy(0,0);
            cout<<1;
            Sleep(500);
            gotoxy(0,0);

    //Following lines call methods responsible for fulfilling 2D array of objects on a level and drawing it
    level1.createField();
    level1.getSize(x,y); //get size of a created level and put it in x/y variables
    level1.drawLevel();
    level1.spawnScore();
    snake1.spawn(x,y);

    bodyStructure body[x*y]; //Create a structure a size of maximum Level size

    //Create first instance of Snake's body
    body[0].bodyX=snake1.getPosX();
    body[0].bodyY=snake1.getPosY();


        while(true)
        {
        snake1.movement();
        temp = level1.getField(snake1.getPosX(),snake1.getPosY(),snake1.getDirection());
        level1.setField(snake1.getPosX(),snake1.getPosY(),' ');

            //Automatically move first element of body on a previous Head position
            body[0].tempOgonX = body[0].bodyX;
            body[0].tempOgonY = body[0].bodyY;
            body[0].bodyX = snake1.getPosX();
            body[0].bodyY = snake1.getPosY();

            level1.setField(body[0].tempOgonX,body[0].tempOgonY,' ');
            level1.setField(body[0].bodyX,body[0].bodyY,'o');

                //Draw changes
                headMovement(snake1.getPosX(),snake1.getPosY(),snake1.getDirection(), tempX, tempY);
                bodyMovement(body[0].bodyX, body[0].bodyY,body[0].tempOgonX,body[0].tempOgonY);
                moveCounter++;

        //Refresh data in objects. TempX/Y are actual coordinates of snake right now. They will be old after next move.
        snake1.setPosition(tempX, tempY);
        level1.setField(tempX, tempY,'@');

            if (bodyCounter > 0) //Refresh coords of every instance of body from pushing data from body[0] till the end
            {
                for(int i=1;i<=bodyCounter;i++)
                {
                    body[i].tempOgonX = body[i].bodyX;
                    body[i].tempOgonY = body[i].bodyY;
                    body[i].bodyX = body[i-1].tempOgonX;
                    body[i].bodyY = body[i-1].tempOgonY;

                    //Redraw every instance of a body[i]
                    bodyMovement(body[i].bodyX,body[i].bodyY,body[i].tempOgonX,body[i].tempOgonY);
                    level1.setField(body[i].bodyX,body[i].bodyY,'o');
                        if(i == bodyCounter) //In the end clear last field in 2D array
                        {
                            if(body[i].tempOgonX != 0 && body[i].tempOgonY != 0) //checks if destination is not 0,0
                            level1.setField(body[i].tempOgonX,body[i].tempOgonY,' ');
                        }
                }
            }
/* Debug allowing to move only on a keyboard click and showing current coordinates of Snake Head as well as coordinates passed to body[0]
    gotoxy(0,y+2);
    cout<<"X: "<<body[0].bodyX<<endl<<"Y: "<<body[0].bodyY<<endl<<"Temp X: "<<body[0].tempOgonX<<endl<<"Temp Y:"<<body[0].tempOgonY;
    getch();
*/


    if(collision(temp,existScore,score,bodyCounter) == 1) break; //Exit infinite loop if temp is not '*' or else is not char ' '
        if (existScore == 1)
        {
            level1.spawnScore();
            existScore = 0;

            gotoxy(0,y+1); cout<<"Score: "<<score;
        }

    } //End of infinite loop

    //Clearing console screen after 'death', That way is faster than "system("cls")"
    gotoxy(0,0);
    for (int i=1;i<30;i++)
    {
        cout<<"                                                                           "<<endl;
    }

gotoxy(0,3);
level1.drawLevel();

gotoxy(0,0);
cout<<"Zdobyles "<<score<<" punktow. Sprobuj jeszcze raz :)";
cout<<endl<<"Snake ruszyl sie "<<moveCounter<<" razy.";

Sleep(1000);
getch();
getch();
}
    return 0;
}



static void gotoxy(int x, int y)
{
    COORD cord;
    cord.X = x;
    cord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
}

void headMovement(int posX, int posY, int direction, int& tempX,int& tempY)
{
    gotoxy(posX,posY);
    cout<<' ';
    if (direction==1) posY--;
    else if (direction==2) posY++;
    else if (direction==3) posX--;
    else if (direction==4) posX++;

    tempX = posX; //Assign new values to variables in main
    tempY = posY;

    gotoxy(posX,posY);
    cout<<'@';
}

void bodyMovement(int& X,int& Y,int& tempX, int&tempY)
{
    //overwrite previous position with space symbol and draw 'o' symbol in new position
    if(tempX!=0&&tempY!=0) //checks if destination is not 0,0
    {
    gotoxy(tempX,tempY);
    cout<<' ';
    }
    gotoxy(X,Y);
    cout<<'o';
}

int collision(char obiekt, int& existScore, int& score, int& bodyCounter)
{
    if (obiekt=='*')
    {
        existScore=1;
        score++;
        bodyCounter++;
        return 2;
    }
    else if(obiekt!=' ')
    {
        return 1;
    }
}
