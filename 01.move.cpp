#include<iostream>
#include<conio.h>
#include<cstdlib>
#include<windows.h>
using namespace std;

int main(){
    system("cls");
    char current='1';
    int x=3;
    int y=3;
    int sizex=10;
    int sizey=10;
    char grid[sizex][sizey];
    for(int i=0;i<sizex;i++){
        for(int j=0;j<sizey;j++){
            if(i==x && j==y){grid[i][j]='S';continue;}
            grid[i][j]='-';
        }
    }
    while(current!='0'){
        if (_kbhit()) {
            current=_getch();
        if(current=='w'){
            x--;
            if(x==-1){x=sizex-1;}
        }
        else if(current=='s'){
            x++;
            if(x==sizex){x=0;}
        }
        else if(current=='a'){
            y--;
            if(y==-1){y=sizey-1;}
        }
        else if(current=='d'){
            y++;
            if(y==sizey){y=0;}
        }
        else{}
    }
        system("cls");
         for(int i=0;i<sizex;i++){
        for(int j=0;j<sizey;j++){
            if(i==x && j==y){grid[i][j]='S';}
            else{grid[i][j]='-';}
            cout<<grid[i][j]<<"  ";
        }
        cout<<endl<<endl;
    }
    Sleep(200);
    }
    
    return 0;
 }