#include<raylib.h>
#include<cmath>
using namespace std;

#define width 800
#define height 600

void intersect(int x,int y,int degree,int &xi,int &yi){
    double theta = degree * PI / 180.0;
    double dx = cos(theta);
    double dy = sin(theta);
    double tx = INFINITY;
    double ty = INFINITY;
    if (dx > 1e-10)
        tx = (width - x) / dx;
    else if (dx < -1e-10)
        tx = (0 - x) / dx;
    if (dy > 1e-10)
        ty = (height - y) / dy;
    else if (dy < -1e-10)
        ty = (0 - y) / dy;
    double t = min(tx, ty);
    xi =(int)(x+t*dx);
    yi =(int)(y+t*dy);
}

int main(){

    InitWindow(width,height,"shadow");
    SetTargetFPS(80);
    int radius=50;
    int x=width/2;
    int y=height/2;
    int xi;int yi;
    int degree=0;
    
    while (!WindowShouldClose()){
        Vector2 mouse = GetMousePosition();
        BeginDrawing();
        ClearBackground(WHITE);       
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) &&
            mouse.x >= 0 && mouse.x < width &&
            mouse.y >= 0 && mouse.y < height){
              if (CheckCollisionPointCircle(mouse,{(float)x,(float)y}, radius))
            {
                x=mouse.x;
                y=mouse.y; 
            }            
        }
        intersect(x,y,degree,xi,yi);
        DrawLine(x,y,xi,yi,RED);
        DrawCircle(x,y,radius,RED);
        degree++;
        EndDrawing();

    }
}