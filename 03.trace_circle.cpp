#include<iostream>
#include<raylib.h>
using namespace std;

#define width 800
#define height 600

int main(){
    InitWindow(width,height,"trace_circle");
    SetTargetFPS(60);
    int radius=50;
    int x=0;int y=0;
    Color brushColor = BLACK;
    while (!WindowShouldClose()){
        Vector2 mouse = GetMousePosition();
        BeginDrawing();
        ClearBackground(WHITE);
        if (IsKeyPressed(KEY_B))
            brushColor = BLUE;
        if (IsKeyPressed(KEY_E))
            brushColor = BLACK;
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) &&
            mouse.x >= 0 && mouse.x < width &&
            mouse.y >= 0 && mouse.y < height)
        {             
            DrawCircleV(mouse, radius, brushColor);
            
        }
        EndDrawing();

    }
}