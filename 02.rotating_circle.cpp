#include<iostream>
#include<raylib.h>
#include<cmath>
using namespace std;

#define width 800
#define height 600

void p2c(int radius,int degree,int &x,int &y){
        float angle=degree *(PI/180.0);
        x=(int)(radius*cos(angle));
        y=(int)(radius*sin(angle));
}

int main(){
    
    InitWindow(width, height, "My First raylib ");
    SetTargetFPS(60);
    int radius=120;
    int degree=0;
    int x=0;
    int y=0;
    int x_shift=width/2;
    int y_shift=height/2;
    while (!WindowShouldClose())
    {
        BeginDrawing();
        
        p2c(radius,degree,x,y);
        x+=x_shift;
        y+=y_shift;
        DrawCircle(x, y, 60, BLUE);
        degree++;
        if (degree >= 360) degree = 0;
        
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}