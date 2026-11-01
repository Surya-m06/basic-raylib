#include<iostream>
#include<raylib.h>
using namespace std;

#define width 800
#define height 600

int main(){

    InitWindow(width,height,"shadow");
    SetTargetFPS(80);
    int radius=50;
    int x=width/2;int y=height/2;
    x+=50;
    int x2=width/2;int y2=height/2;
    x2-=50;
    
    while (!WindowShouldClose()){
        Vector2 mouse = GetMousePosition();
        BeginDrawing();
        ClearBackground(WHITE);       
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) &&mouse.x >= 0 && mouse.x < width &&mouse.y >= 0 && mouse.y < height){
              if (CheckCollisionPointCircle(mouse,{(float)x,(float)y}, radius)&&
                    !CheckCollisionPointCircle(mouse,{(float)x2,(float)y2}, radius*2))
            {
                x=mouse.x;
                y=mouse.y; 
            }
            if (!CheckCollisionPointCircle(mouse,{(float)x,(float)y}, radius*2)&&
                CheckCollisionPointCircle(mouse,{(float)x2,(float)y2}, radius))
            {
                x2=mouse.x;
                y2=mouse.y; 
            }
        }
         DrawCircleV({(float)x,(float)y}, radius, BLACK);
         DrawCircleV({(float)x2,(float)y2}, radius, ORANGE);
        EndDrawing();

    }
}