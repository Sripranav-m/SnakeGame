//g++ game.cpp -lGL -lGLU -lglut -lm
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<bits/stdc++.h>
#include<ctime>


#define COLUMNS 40
#define ROWS 40
#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2
#define CLASSICMODE 0
#define BOXMODE 1
#define NOPASS 1
#define PASS 0

using namespace std;

int gridx;
int gridy;
vector<int> snakex={20,20};
vector<int> snakey={19,20};
int snakedir=2;
bool gameover=false;
int foodx;
int foody;
bool food=true;
int score=0;
int snake_length=2;
int mode=CLASSICMODE;
int FPS=5;
int collision=NOPASS;

void init();
void display();
void reshape(int w,int h);
void initgrid(int x,int y);
void drawgrid();
void unit(int x,int y);
void timer(int);
void keyboard(int,int,int);
void drawsnake();
void drawfood();
void random(int &x,int &y);

int main(int argc,char **argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    string disp="SCORE : ";
    disp+=to_string(score);
    char const *dis = disp.c_str();
    glutCreateWindow(dis);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0,timer,0);
    glutSpecialFunc(keyboard);
    init();
    glutMainLoop();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    drawgrid();
    drawsnake();
    drawfood();
    string disp="SCORE : ";
    disp+=to_string(score);
    char const *dis = disp.c_str();
    glutSetWindowTitle(dis);
    glutSwapBuffers();
    if(gameover){
        cout<<"DONE";
        exit(0);
    }
}

void reshape(int w,int h){
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,COLUMNS,0,ROWS,-1,1);
    glMatrixMode(GL_MODELVIEW);
}

void init(){
    glClearColor(0,0,0,0.5);
    initgrid(COLUMNS,ROWS);
}

void initgrid(int x,int y){
    gridx=x;
    gridy=y;
}

void drawgrid(){
    for(int i=0;i<gridx;i++){
        for(int j=0;j<gridy;j++){
            unit(i,j);
        }
    }
}

void unit(int x,int y){
    if(x==0 || y==0 || x==gridx-1 || y==gridy-1){
        glLineWidth(2);
        glColor3f(0,0,1);
    }
    else{
        glLineWidth(0.5);
        glColor3f(0,0,0);
    }

    glBegin(GL_LINE_LOOP);

    glVertex2f(x,y);
    glVertex2f(x+1,y);
    glVertex2f(x+1,y+1);
    glVertex2f(x,y+1);

    glEnd();
}

void timer(int){
    glutPostRedisplay();
    glutTimerFunc(1000/FPS,timer,0);
}

void keyboard(int key,int , int ){
    switch(key){
        case GLUT_KEY_UP:
            if(snakedir!=DOWN){
                snakedir=UP;
            }
            break;
        case GLUT_KEY_DOWN:
            if(snakedir!=UP){
                snakedir=DOWN;
            }
            break;
        case GLUT_KEY_RIGHT:
            if(snakedir!=LEFT){
                snakedir=RIGHT;
            }
            break;
        case GLUT_KEY_LEFT:
            if(snakedir!=RIGHT){
                snakedir=LEFT;
            }
            break;
    }
}

void drawsnake(){
    int tempx=snakex[0];
    int tempy=snakey[0];
    for(int i=0;i<snake_length-1;i++){
        snakex[i]=snakex[i+1];
        snakey[i]=snakey[i+1];
    }
    if(snakedir==UP){
        snakey[snake_length-1]++;
    }
    else if(snakedir==DOWN){
        snakey[snake_length-1]--;
    }
    else if(snakedir==RIGHT){
        snakex[snake_length-1]++;
    }
    else if(snakedir==LEFT){
        snakex[snake_length-1]--;
    }
    if(collision==NOPASS){
        for(int i=0;i<snake_length-1;i++){
            if(snakex[i]==snakex[snake_length-1] && snakey[i]==snakey[snake_length-1]){
                cout<<"fcncncgnhc";
                gameover;
            }
        }
    }
    if(snakex[snake_length-1]>gridx-1 || snakey[snake_length-1]>gridy-1 || snakex[snake_length-1]<1 || snakey[snake_length-1]<1  ){
        if(mode==CLASSICMODE){
            if(snakex[snake_length-1]==gridx){
                snakex[snake_length-1]=1;
            }
            if(snakey[snake_length-1]==gridy){
                snakey[snake_length-1]=1;
            }
            if(snakex[snake_length-1]==0){
                snakex[snake_length-1]=gridx-2;
            }
            if(snakey[snake_length-1]==0){
                snakey[snake_length-1]=gridx-2;
            }
        }
        if(mode==BOXMODE){
            gameover=true;
        }
    }
    for(int i=0;i<snake_length;i++){
        if(i==snake_length-1){
            glColor3f(0,1,0);
        }
        else{
            glColor3f(0,0,1);
        }
        glRectd(snakex[i],snakey[i],snakex[i]+1,snakey[i]+1);
    }
    if(snakex[snake_length-1]==foodx && snakey[snake_length-1]==foody){
        food=true;
        snake_length++;
        snakex.insert(snakex.begin(),1,tempx);
        snakey.insert(snakey.begin(),1,tempy);
        score++;
    }
}
void random(int &x,int &y){
    int maxx=gridx-2;
    int maxy=gridy-2;
    int mini=1;
    srand(time(NULL));
    x=mini+rand()%(maxx-mini);
    y=mini+rand()%(maxy-mini);
}

void drawfood(){
    if(food==true){
        random(foodx,foody);
    }
    food=false;
    glColor3f(1,0,0);
    glRectf(foodx,foody,foodx+1,foody+1);
}