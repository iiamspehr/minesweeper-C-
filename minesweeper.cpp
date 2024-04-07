#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

const int SIZE=10;
const int BOMBS=10;
 
void menu()
{
    int choice; 
    do
    { 
        cout<<"1.PLAY\n2.EXIT\n";
        cin>>choice;      
        switch (choice)
        {
            case 1: {
            //     string waiting_str = "LOADING...";
            //     cout<<"starting the game"<<endl;
            //     for(char ch : waiting_str)
            //     {
            //         cout<<ch<<flush;
            //         this_thread::sleep_for(chrono::milliseconds(250)); 
            //     }
                // cout<<endl;
                return;
                break;
            }
            case 2: {
                exit(0);
            }
            default:{
                cout<<"invalid selection . please choose one of the options in the menu ."<<endl;
                menu();
                break;
            }
        }
    } while(choice != 2);
}

int randrange(int low , int high);
void bombspots(char board [][SIZE] , int size , int bombs);
int bombcounter(char board[][SIZE] , int size , int x , int y);
bool bombcheck(char board[][SIZE] , int size ,  int x , int y);
void bombdefuse(char board[][SIZE] , int size , int x , int y , int bomb);

void displayboard(char board [][SIZE] , int size , int bombs)
{
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            cout<<board[i][j]<<" | ";
        }
        cout<<endl;
    }

}


int main()
{
    // creating a random number generator
    unsigned int seed = static_cast<unsigned int>(time(nullptr));
    srand(seed);
    // performing menu
    menu(); 
    // loading with the peoload :)
    int bombs_remaning=10;
    int selection;
    char game_board[SIZE][SIZE];
    bombspots(game_board , SIZE , BOMBS);
    // start
    displayboard(game_board , SIZE , BOMBS);
    cout<<"choose one of the options below\n1.choose a unit\n2.insert a flag\n3.exit the game";
    do
    {
        cin>>selection;
        cout<<endl;
        switch(selection)
        {
            case 1: {
                int unit_x , unit_y;
                cout<<"enter the coordinates of your indeeded unit to understand how many bombs are aroound it with the distance of one unit\n( hoizontal , vertical or diagonal)";
                cout<<endl<<"ATTENTION ! the number of cordinate must be a digit ( in range [ 0 , 9 ] )"<<endl;
                cout<<"\nunit x :";
                cin>>unit_x;
                cout<<"\nunit y :";
                cin>>unit_y;
                if(bombcheck(game_board , SIZE , unit_x , unit_y))
                {
                    cout<<"you lost the game .\nbetter luck next time.";
                    return 0;
                }
                else
                {
                    int count=bombcounter(game_board , 10 , unit_x , unit_y);
                    cout<<"there are "<<count<<" bombs around this unit\n";
                    cout<<"bombs remaning = "<<bombs_remaning;
                    cout<<"\nwhat do you want to do for your next move ?\n1.choose a unit\n2.insert a flag\n3.exit the game";
                }
                displayboard(game_board, SIZE , BOMBS);
                }break;
            case 2: {
                int flag_x , flag_y;
                cout<<"enter the cordinants of the unit which you think there might be a bomb on it . if your guess is true , the bomb will be defused . \n";
                cout<<"flag x : ";
                cin>>flag_x;
                cout<<endl<<"flag y : ";
                cin>>flag_y;
                bombdefuse(game_board , SIZE , flag_x , flag_y , bombs_remaning);
                cout<<"bombs remaning="<<bombs_remaning;
                cout<<"\nwhat do you want to do for your next move ?\n1.choose a unit\n2.insert a flag\n3.exit the game";
                if(bombs_remaning==0)
                {
                    cout<<"congrats!!you won the game";
                    return 0;
                }
                displayboard(game_board, SIZE , BOMBS);
                }break;
            case 3: exit(0);
                break; 
            default : continue;
                break;
        }
    }while(selection != 3);
    return 0;    
}

int randrange(int low , int high) {
    return rand() % (high - low + 1)+low;
}
void bombspots(char board [][SIZE] , int size , int bombs)
{
    for(int i=0;i<SIZE;i++)
    {
        for (int j=0;j<SIZE;j++)    board[i][j]='.';
    }
    for(int i=0;i<BOMBS;i++)
    {
        int x=randrange(0 , SIZE-1);
        int y=randrange(0 , SIZE-1);
        if(board[x][y]== '.')
        {
            board[x][y]= 'b';
        }
        else {
            i--;
        }
    }
    for(int i=0;i<SIZE;i++)
    {
        for (int j=0;j<SIZE;j++)
        {
            int bombs_around=bombcounter(board , size , i , j);
            if(bombs_around>0)
            {
                board[i][j]='0' + bombs_around;
            }
        }
    }
}
int bombcounter(char board[][SIZE] , int size , int x , int y)
{
    int count=0;
    if(bombcheck(board , size , x-1 , y-1)) count++;
    if(bombcheck(board , size , x-1 , y)) count++;
    if(bombcheck(board , size , x-1 , y+1)) count++;
    if(bombcheck(board , size , x , y-1)) count++;
    if(bombcheck(board , size , x , y+1)) count++;
    if(bombcheck(board , size , x+1 , y-1)) count++;
    if(bombcheck(board , size , x+1 , y)) count++;
    if(bombcheck(board , size , x+1 , y+1)) count++;
    return count;
}
bool bombcheck(char board[][SIZE] , int size , int x , int y)
{
    if(x<0) return false;
    if(y<0) return false;
    if(x>=size) return false;
    if(y>=size) return false;
    if(board[x][y]=='b')    return true;
    return false;
}

void bombdefuse(char board[][SIZE] , int size , int x , int y , int bomb)
{
    if(bombcheck(board , size , x , y ))
    {
        board[x][y]='f';
        bomb--;
    }
}