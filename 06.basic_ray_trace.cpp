#include<raylib.h>
#include<cmath>
#include <limits>
using namespace std;

#define width 800
#define height 600
#define ray_count 360

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

//line circle collide
class collide_LC{           
public:
    int cx;
    int cy;
    int radius;
    int px1;
    int py1;
    int px2;
    int py2;
    int degree;

    //setvalues
    void setline(int x,int y,int degree){
        this->px1=x;
        this->py1=y;
        this->degree=degree;
        intersect(x,y,degree,px2,py2);
    }
    void setcircle(int x,int y,int radius){
        this->cx=x;
        this->cy=y;
        this->radius=radius;
    }

    //find collition point
    void findpoint(){
        double dx=px2-px1;
        double dy=py2-py1;
        double ux=px1-cx;
        double uy=py1-cy;
        double a=dx*dx + dy*dy;
        double b=2*(ux*dx + uy*dy);
        double cc=ux*ux + uy*uy - radius*radius;
        double D=b*b - 4*a*cc;

        if (D<0 || a==0) {
            return;
        }
        double t1=(-b-sqrt(D))/(2*a);
        double t2=(-b+sqrt(D))/(2*a);
        double t=INFINITY;
        if (t1>=0 && t1<=1)
            t=t1;
        if (t2>=0 && t2<=1 && t2<t)
            t=t2;
        if (t==INFINITY) {
            return; 
        }

        px2 = (int)round(px1 + t*dx);
        py2 = (int)round(py1 + t*dy);
    }
};


int main(){

    InitWindow(width,height,"shadow");
    SetTargetFPS(60);

    int radius=50;
    int x=width/2;
    x+=50;  //initial shift
    int y=height/2;
    int x2=width/2;
    int y2=height/2;
    x2-=50; //initial shift
    int xi[ray_count]={0};
    int yi[ray_count]={0};
    int degree[ray_count]={0};
    bool setcolor=true;
    Color c1;

    for(int i=1;i<ray_count;i++){
        degree[i]=degree[i-1]+(360/ray_count);
    }
    
    while (!WindowShouldClose()){
        Vector2 mouse = GetMousePosition();
        BeginDrawing();
        ClearBackground(BLACK);     
        //handling circles  
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
        //finding intersects
        for(int i=0;i<ray_count;i++){
            intersect(x,y,degree[i],xi[i],yi[i]);
            if(CheckCollisionCircleLine({(float)x2,(float)y2},radius,{(float)x,(float)y},{(float)xi[i],(float)yi[i]})){
                collide_LC c;
                c.setline(x,y,degree[i]);
                c.setcircle(x2,y2,radius);
                c.findpoint();
                xi[i]=c.px2;
                yi[i]=c.py2;
                
            }
            if(setcolor){
                c1=WHITE;
            }
            else{
                c1=YELLOW;
            }
            DrawLine(x,y,xi[i],yi[i],c1);
            setcolor=!setcolor;    
        }
        
        DrawCircle(x,y,radius,WHITE);
        DrawCircle(x2,y2,radius,ORANGE);
        EndDrawing();

    }
}