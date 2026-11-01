#include<raylib.h>
#include<cmath>
#include <limits>
using namespace std;

#define width 800
#define height 600
#define ray_count 360

void intersect(int x, int y, int degree, int &xi, int &yi);
class solid_circle;
class collide_LC;
class light_source;

void intersect(int x,int y,int degree,int &xi,int &yi){
    double theta=degree * PI / 180.0;
    double dx=cos(theta);
    double dy=sin(theta);
    double tx=INFINITY;
    double ty=INFINITY;
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

bool mouse_valid(Vector2 mouse){
    return (mouse.x >= 0 && mouse.x < width &&mouse.y >= 0 && mouse.y < height);
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
class solid_circle{
    public:
    int x;
    int y;
    int radius;

    void set(int x,int y,int radius){
        this->x=x;
        this->y=y;
        this->radius=radius;
    }
    bool check_mouse(Vector2 mouse,int factor=1){
        return CheckCollisionPointCircle(mouse,{(float)x,(float)y}, radius*factor);
    }
    void draw(Color COLOR){
        DrawCircle(x,y,radius,COLOR);
    }
};
class light_source{
    public:
    int x;
    int y;
    int radius;
    int degree[ray_count];
    int xi[ray_count]={0};
    int yi[ray_count]={0};
    Color c[ray_count];

    void set(int x,int y,int radius){
        this->x=x;
        this->y=y;
        this->radius=radius;
        bool setcolor=true;
        degree[0]=0;
        c[0]=YELLOW;
        for(int i=1;i<ray_count;i++){
            degree[i]=degree[i-1]+(360/ray_count);
            if(setcolor){
                c[i]=WHITE;
            }
            else{
                c[i]=YELLOW;
            }
            setcolor=!setcolor;
        }
        
    }
    
    bool check_mouse(Vector2 mouse,int factor=1){
        return CheckCollisionPointCircle(mouse,{(float)x,(float)y}, radius*factor);
    }
    void boundary_intersect(){
        for(int i=0;i<ray_count;i++){
            intersect(x,y,degree[i],xi[i],yi[i]);
        }
    }
    void trace(solid_circle &s){
        for(int i=0;i<ray_count;i++){
            if(CheckCollisionCircleLine({(float)s.x,(float)s.y},s.radius,{(float)x,(float)y},{(float)xi[i],(float)yi[i]})){
                collide_LC c;
                c.setline(x,y,degree[i]);
                c.setcircle(s.x,s.y,s.radius);
                c.findpoint();
                xi[i]=c.px2;
                yi[i]=c.py2;
                
            } 
        }
    }
    void draw(Color COLOR){
        for(int i=0;i<ray_count;i++){
            DrawLine(x,y,xi[i],yi[i],c[i]);
        }
        DrawCircle(x,y,radius,COLOR);
    }
    
};

int main(){

    InitWindow(width,height,"shadow");
    SetTargetFPS(60);

    int radius=50;
    int x=width/2;
    int y=height/2;
    light_source l1;
    light_source l2;
    solid_circle s1;
    solid_circle s2;

    l1.set(x+100,y,radius);
    l2.set(x-100,y,radius);
    s1.set(x,y+100,radius);
    s2.set(x,y-100,radius);
    

    while (!WindowShouldClose()){
        Vector2 mouse = GetMousePosition();
        BeginDrawing();
        ClearBackground(BLACK);     
        //handling circles with mouse 
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && mouse_valid(mouse)){
              if ((l1.check_mouse(mouse)) && !(l2.check_mouse(mouse,2)) &&
                    !(s1.check_mouse(mouse,2)) && !(s2.check_mouse(mouse,2)))
            {
                l1.x=mouse.x;
                l1.y=mouse.y; 
            }
            if (!(l1.check_mouse(mouse,2)) && (l2.check_mouse(mouse)) &&
                    !(s1.check_mouse(mouse,2)) && !(s2.check_mouse(mouse,2)))
            {
                l2.x=mouse.x;
                l2.y=mouse.y; 
            }
            if (!(l1.check_mouse(mouse,2)) && !(l2.check_mouse(mouse,2)) &&
                    (s1.check_mouse(mouse)) && !(s2.check_mouse(mouse,2)))
            {
                s1.x=mouse.x;
                s1.y=mouse.y; 
            }
            if (!(l1.check_mouse(mouse,2)) && !(l2.check_mouse(mouse,2)) &&
                    !(s1.check_mouse(mouse,2)) && (s2.check_mouse(mouse)))
            {
                s2.x=mouse.x;
                s2.y=mouse.y; 
            }
        }
        //finding intersects
        l1.boundary_intersect();
        l2.boundary_intersect();
        l1.trace(s1);
        l1.trace(s2);
        l2.trace(s1);
        l2.trace(s2);

        //draw
        l1.draw(WHITE);
        l2.draw(WHITE);
        s1.draw(RED);
        s2.draw(ORANGE);
        EndDrawing();

    }
}