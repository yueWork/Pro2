//
//  main.cpp
//  Pro2
//
//  Created by byue on 15/11/8.
//  Copyright © 2015年 byue. All rights reserved.
//
//#include <Windows.h>
//#include <GL/glut.h>
#include <GLUT/GLUT.h>
#include <iostream>
#include <math.h>
using namespace std;

#pragma comment(lib,"glut32.lib")
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

static GLfloat s_eye[]={0,0,35.0};
static GLfloat s_at[]={0.0,0.0,1.0};
static GLfloat s_angle=-90.0;
//static GLfloat s_angle = -90.0;
const GLfloat R=0.25f;
const int n=2400;
const GLfloat Pi = 3.1415926536f;
const   float   DEG2RAD   =   3.14159/180;

const GLfloat lightPosition1[] = {10.0,10.0,10.0,0.0};
const GLfloat whiteLight[] = {0.8,0.8,0.8,1.0};
GLfloat matSpecular [] = {0.3,0.3,0.3,1.0};
GLfloat matShininess [] = {20.0};
GLfloat matEmission [] = {0.3,0.3,0.3,1.0};
//金
GLfloat mat_ambient[] = { 0.25, 0.23, 0.06, 1.0};
GLfloat mat_diffuse[] = { 0.35, 0.31, 0.09, 1.0};
GLfloat mat_specular[] = { 0.80, 0.72, 0.21, 1.0};
GLfloat mat_shininess[] = { 83.2};

static int spin = 0;
GLint menu_id;
GLint menu_PDX_id;
GLint menu_HMBB_id;
GLfloat tra1=0;
GLfloat rot1=0;
GLfloat sca1=1;

GLfloat tra2=0;
GLfloat rot2=0;
GLfloat sca2=1;

GLfloat hx;
GLfloat hz=0;
GLfloat pz=0;
GLfloat hrz=0;
GLfloat prz=0;
//GLfloat ratio＝0;
int W, H;

GLuint selectedIndex=1;	 //击中对象的ID

void DrawCircle(float x,float y,float z,GLfloat R,int r,int g,int b){
    
    cout<<"Hello world!";
    
    cout<<"test";
    int i;
    glColor3ub(r,g,b);
    glMatrixMode(GL_MODELVIEW);
    glBegin(GL_POLYGON);
    for(i=0;i<n;i++)
        glVertex3f(x+R*cos(2*Pi/n*i),y+R*sin(2*Pi/n*i),z);
    glEnd();
}
void DrawCircleLine(float x,float y,float z,GLfloat R){
    int i;
    glColor3f(0,0,0);
    glBegin(GL_LINE_STRIP);
    for(i=0;i<n;i++)
        glVertex3f(x+R*cos(2*Pi/n*i),y+R*sin(2*Pi/n*i),z);
    glEnd();
    glFlush();
}
void DrawCurve(float x,float y,float z,float xradius,float yradius,int degree1,int degree2){
    int i=n*degree1/360;
    int end=n*degree2/360;
    glColor3f(0,0,0);
    glBegin(GL_LINE_STRIP);
    for(;i<=end;i++)
        glVertex3f(x+xradius*cos(2*Pi/n*i),y+yradius*sin(2*Pi/n*i),z);
    glEnd();
}
void DrawStraightLine(float xB,float yB,float zB,float xE,float yE,float zE){
    glColor3ub(0, 0, 0);
    glBegin(GL_LINES);
    glVertex3f(xB, yB, zB);
    glVertex3f(xE, yE, zE);
    glEnd();
}
void drawobjects(GLenum);

void reshape(int w,int h)
{
    W = w;
    H = h;
//    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
//    glMatrixMode(GL_PROJECTION);

//    glLoadIdentity();
//    
//    GLfloat aspectRatio = (GLfloat)W / (GLfloat)H;//计算窗口横纵比
//    
//    if (W<=H)
//        glOrtho(-20.0, 20.0, -20.0/aspectRatio, 20.0/aspectRatio, -20.0, 20.0);
//    else
//        glOrtho(-20.0*aspectRatio, 20.0*aspectRatio, -20.0, 20.0, -20.0, 20.0);
    


    GLfloat ratio = 1.0f * W/ H;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    glViewport(0, 0, w, h);
    

    gluPerspective(45,ratio,1,1000);
//    glMatrixMode(GL_MODELVIEW);
//    
//    glLoadIdentity();
//    //…Ë÷√…„œÒª˙∫Õπ‚‘¥£®’‚¡Ω∏ˆÀ≥–Ú∫‹÷ÿ“™£¨≤ªƒ‹∑¥π˝¿¥£©
    gluLookAt(s_eye[0], s_eye[1], s_eye[2],
              s_at[0], s_at[1], s_at[2],
              0.0,1.0, 0.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
}

GLvoid DrawCircleArea(float cx, float cy, float cz, float r, int num_segments)
{
    GLfloat vertex[4];
    
    const GLfloat delta_angle = 2.0*Pi/num_segments;
    glBegin(GL_TRIANGLE_FAN);
    
    vertex[0] = cx;
    vertex[1] = cy;
    vertex[2] = cz;
    vertex[3] = 1.0;
    glVertex4fv(vertex);
    
    //draw the vertex on the contour of the circle
    for(int i = 0; i < num_segments ; i++)
    {
        vertex[0] = cos(delta_angle*i) * r + cx;
        vertex[1] = sin(delta_angle*i) * r + cy;
        vertex[2] = cz;
        vertex[3] = 1.0;
        glVertex4fv(vertex);
    }
    vertex[0] = 1.0 * r + cx;
    vertex[1] = 0.0 * r + cy;
    vertex[2] = cz;
    vertex[3] = 1.0;
    glVertex4fv(vertex);
    glEnd();
}

void mySolidCylinder( GLUquadric*	quad,
                     GLdouble base,
                     GLdouble top,
                     GLdouble height,
                     GLint slices,
                     GLint stacks )
{
    
    gluCylinder(quad, base, top, height, slices, stacks);
    //top
    DrawCircleArea(0.0, 0.0, height, top, slices);
    //base
    DrawCircleArea(0.0, 0.0, 0.0, base, slices);
}
void drawSphere(GLfloat xx, GLfloat yy, GLfloat zz, GLfloat radius, GLfloat M, GLfloat N)
{
    float step_z = Pi/M;
    float step_xy = 2*Pi/N;
    float x[4],y[4],z[4];
    
    float angle_z = 0.0;
    float angle_xy = 0.0;
    int i=0, j=0;
    glColor3ub(255, 192, 203);
    glBegin(GL_QUADS);
    for(i=0; i<M; i++)
    {
        angle_z = i * step_z;
        
        for(j=0; j<N; j++)
        {
            angle_xy = j * step_xy;
            
            x[0] = radius * sin(angle_z) * cos(angle_xy);
            y[0] = radius * sin(angle_z) * sin(angle_xy);
            z[0] = radius * cos(angle_z);
            
            x[1] = radius * sin(angle_z + step_z) * cos(angle_xy);
            y[1] = radius * sin(angle_z + step_z) * sin(angle_xy);
            z[1] = radius * cos(angle_z + step_z);
            
            x[2] = radius*sin(angle_z + step_z)*cos(angle_xy + step_xy);
            y[2] = radius*sin(angle_z + step_z)*sin(angle_xy + step_xy);
            z[2] = radius*cos(angle_z + step_z);
            
            x[3] = radius * sin(angle_z) * cos(angle_xy + step_xy);
            y[3] = radius * sin(angle_z) * sin(angle_xy + step_xy);
            z[3] = radius * cos(angle_z);
            
            for(int k=0; k<4; k++)
            {
                glVertex3f(xx+x[k], yy+y[k],zz+z[k]);
            }
        }
    }
    glEnd();
}
void DrawTooth2D(float x,float y,float z){
    glColor3ub(255, 255, 255);
    glBegin(GL_POLYGON);
    glVertex3f(x, y, z);
    glVertex3f(x+0.5, y, z);
    glVertex3f(x+0.5, y-0.5, z);
    glVertex3f(x, y-0.5, z);
    glEnd();
}
void drawCube(float *a,float l,float w,float h){
    
    glBegin(GL_QUADS);
    //前面
    glVertex3f(a[0],a[1],a[2]);//A
    glVertex3f(a[0]+l,a[1],a[2]);//B
    glVertex3f(a[0]+l,a[1]-h,a[2]);//D
    glVertex3f(a[0],a[1]-h,a[2]);//C
    
    //后面
    glVertex3f(a[0],a[1],a[2]-w);//E
    glVertex3f(a[0]+l,a[1],a[2]-w);//F
    glVertex3f(a[0]+l,a[1]-h,a[2]-w);//H
    glVertex3f(a[0],a[1]-h,a[2]-w);//G
    
    //上面
    glVertex3f(a[0],a[1],a[2]);//A
    glVertex3f(a[0]+l,a[1],a[2]);//B
    glVertex3f(a[0]+l,a[1],a[2]-w);//F
    glVertex3f(a[0],a[1],a[2]-w);//E
    
    //下面
    glVertex3f(a[0]+l,a[1]-h,a[2]);//D
    glVertex3f(a[0],a[1]-h,a[2]);//C
    glVertex3f(a[0],a[1]-h,a[2]-w);//G
    glVertex3f(a[0]+l,a[1]-h,a[2]-w);//H
    
    //左边
    glVertex3f(a[0],a[1],a[2]);//A
    glVertex3f(a[0],a[1]-h,a[2]);//C
    glVertex3f(a[0],a[1]-h,a[2]-w);//G
    glVertex3f(a[0],a[1],a[2]-w);//E
    
    //右边
    glVertex3f(a[0]+l,a[1],a[2]);//B
    glVertex3f(a[0]+l,a[1]-h,a[2]);//D
    glVertex3f(a[0]+l,a[1]-h,a[2]-w);//H
    glVertex3f(a[0]+l,a[1],a[2]-w);//F
    
    glEnd();
    
    glColor3f(0,0,0);
    
    glBegin(GL_LINES);
    glVertex3f(a[0],a[1],a[2]);//A
    glVertex3f(a[0],a[1]-h,a[2]+0.001);//C
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex3f(a[0],a[1],a[2]);//A
    glVertex3f(a[0]+l,a[1],a[2]);//B
    glVertex3f(a[0]+l,a[1]-h,a[2]+0.001);//D
    glVertex3f(a[0],a[1]-h,a[2]+0.001);//C
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex3f(a[0],a[1],a[2]);//A
    glVertex3f(a[0],a[1],a[2]-w);//E
    glVertex3f(a[0]-0.001,a[1]-h,a[2]-w);//G
    glVertex3f(a[0]-0.001,a[1]-h,a[2]);//C
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex3f(a[0]+l,a[1],a[2]);//B
    glVertex3f(a[0]+l+0.001,a[1],a[2]-w);//F
    glVertex3f(a[0]+l+0.001,a[1]-h,a[2]-w);//H
    glVertex3f(a[0]+l,a[1]-h,a[2]);//D
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(a[0],a[1],a[2]-w);//E
    glVertex3f(a[0]+l+0.001,a[1],a[2]-w);//F
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(a[0],a[1]-h,a[2]-w-0.001);//G
    glVertex3f(a[0]+l,a[1]-h,a[2]-w-0.001);//H
    glEnd();
    
    
}
void DrawEllipse(float x,float y,float z,float angle_x,float a, float b, int start_angle, int end_angle){
    glBegin(GL_POLYGON);
    glColor3ub(165, 138, 12);
    glVertex3f(x,y,z);
    for (int i = start_angle; i <= end_angle; i++){
        float u = a*cos(Pi / 180 * i)*cos(Pi/180*angle_x)-b*sin(Pi / 180 * i)*sin(Pi/180*angle_x)+x;
        float v = a*cos(Pi / 180 * i)*sin(Pi/180*angle_x)+b*sin(Pi / 180 * i)*cos(Pi/180*angle_x)+y;
        glVertex3f(u,v,z);
        
        
    }
    glEnd();
}
void drawPDX()
{
    //眉毛
    glColor3ub(0,0,0);
    glPushMatrix();
    glTranslatef(-0.55,4.1, 0.6);
    glRotatef(10, 0, 0, 1);
    glScalef(1, 0.5, 1);
    glutSolidCube(0.5);
    glPopMatrix();
    
    glColor3ub(0,0,0);
    glPushMatrix();
    glTranslatef(0.55,4.1, 0.6);
    glRotatef(-10, 0, 0, 1);
    glScalef(1, 0.5, 1);
    glutSolidCube(0.5);
    glPopMatrix();
    
    //嘴
    glColor3ub(0,0,0);
    glPushMatrix();
    glTranslatef(0.6, -1.2 , 2.49);
    glRotatef(-15.1, 1, 0, 0);
    DrawCurve(0, 4, 0, 1, 0.5, 190, 280);
    glPopMatrix();
    
    //    glColor3ub(249, 126, 128);
    //    glPushMatrix();
    //    glScalef(1.2, 0.4, 1);
    //    glTranslatef(0, 5.5, 1.4);
    //    glutSolidSphere(0.5, 200, 200);
    //    glPopMatrix();
    //
    //    glPushMatrix();
    //    glScalef(1.2, 0.4, 1);
    //    glTranslatef(0, 5.3, 1.4);
    //    glutSolidSphere(0.5, 200, 200);
    //    glPopMatrix();
    
    //眼珠
    glColor3ub(255,255,255);
    glPushMatrix();
    glScalef(1, 1.2, 1);
    glTranslatef(-0.5, 2.8, 1);
    glutSolidSphere(0.4, 200, 200);
    glPopMatrix();
    
    glPushMatrix();
    glScalef(1, 1.2, 1);
    glTranslatef(0.5, 2.8, 1);
    glutSolidSphere(0.4, 200, 200);
    glPopMatrix();
    
    //黑色
    glColor3ub(0,0,0);
    glPushMatrix();
    glTranslatef(0.5, 3.4, 1.3);
    glutSolidSphere(0.2, 200, 200);
    glPopMatrix();
    
    glColor3ub(0,0,0);
    glPushMatrix();
    glTranslatef(-0.5, 3.4, 1.3);
    glutSolidSphere(0.2, 200, 200);
    glPopMatrix();
    //上身
    glColor3ub(249, 126, 128);
    GLdouble eqn0 [4]={0.0,-1.0,0.0,5};
    glClipPlane(GL_CLIP_PLANE0,eqn0);
    glEnable(GL_CLIP_PLANE0);
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glutSolidCone(2.5, 6, 200, 200);
    glPopMatrix();
    glDisable(GL_CLIP_PLANE0);
    
    glPushMatrix();
    glTranslatef(0, 4.72, 0);
    glutSolidSphere(0.5, 200, 200);
    glPopMatrix();
    //手
    
    glPushMatrix();
    glTranslatef(1.85, 1.5, 0);
    glRotatef(90, 0, 1, 0);
    glRotatef(-20, 1, 0, 0);
    GLUquadricObj *quadratic_21;
    quadratic_21=gluNewQuadric();
    mySolidCylinder(quadratic_21,0.6f,0.1f,1.5f,200,200);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(3.1, 1.96, 0);
    glutSolidSphere(0.18, 200, 200);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-1.85, 1.5, 0);
    glRotatef(90, 0, 1, 0);
    glRotatef(200, 1, 0, 0);
    GLUquadricObj *quadratic_22;
    quadratic_22=gluNewQuadric();
    mySolidCylinder(quadratic_22,0.6f,0.1f,1.5f,200,200);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-3.1, 1.96, 0);
    glutSolidSphere(0.18, 200, 200);
    glPopMatrix();
    
    //下身
    glColor3ub(165, 216, 25);
    GLdouble eqn [4]={0.0,-1.0,0.0,0.0};
    glClipPlane(GL_CLIP_PLANE0,eqn);
    glEnable(GL_CLIP_PLANE0);
    glutSolidSphere(2.5,200,200);
    //截完了之后，再撤消,防止对其他部分产生影响。
    glDisable(GL_CLIP_PLANE0);
    //腿
    glPushMatrix();
    glTranslatef(-1.0f, -2.0f, 0.0f);
    glRotatef(90, 1, 0, 0);
    glRotatef(-10, 0, 1, 0);
    GLUquadricObj *quadratic_19;
    quadratic_19=gluNewQuadric();
    mySolidCylinder(quadratic_19,0.5f,0.5f,0.8f,200,200);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(1.0f, -2.0f, 0.0f);
    glRotatef(90, 1, 0, 0);
    glRotatef(10, 0, 1, 0);
    GLUquadricObj *quadratic_20;
    quadratic_20=gluNewQuadric();
    mySolidCylinder(quadratic_20,0.5f,0.5f,0.8f,200,200);
    glPopMatrix();
    //脚
    glColor3ub(249, 126, 128);
    glPushMatrix();
    glTranslatef(-1.1, -2.7, 0);
    glRotatef(90, 1, 0, 0);
    glRotatef(-10, 0, 1, 0);
    GLdouble eqn2 [4]={0.0,0.0,-1.0,0.8};
    glClipPlane(GL_CLIP_PLANE0,eqn2);
    glEnable(GL_CLIP_PLANE0);
    glutSolidCone(0.45,1.0,200, 200);
    glDisable(GL_CLIP_PLANE0);
    glPopMatrix();
    
    glColor3ub(249, 126, 128);
    glPushMatrix();
    glTranslatef(1.1, -2.7, 0);
    glRotatef(90, 1, 0, 0);
    glRotatef(10, 0, 1, 0);
    glClipPlane(GL_CLIP_PLANE0,eqn2);
    glEnable(GL_CLIP_PLANE0);
    glutSolidCone(0.45,1.0,200, 200);
    glDisable(GL_CLIP_PLANE0);
    glPopMatrix();
}
void drawHMBB(){
    
    
    
    glColor3ub(253, 247, 62);//黄色
    glBegin(GL_QUADS);
    //    glNormal3f( 0.0F, 0.0F, 1.0F);
    //1--前面--------------------------
    glVertex3f( -2.5f,0.0f,1.0f);
    glVertex3f(2.5f,0.0f, 1.0f);
    glVertex3f( 3.0f,5.0f, 1.0f);
    glVertex3f(-3.0f,5.0f, 1.0f);
    
    
    //2--后面--------------------------
    //    glNormal3f( 0.0F, 0.0F,-1.0F);
    glVertex3f( -2.5f,0.0f,-1.0f);
    glVertex3f(2.5f,0.0f, -1.0f);
    glVertex3f( 3.0f,5.0f, -1.0f);
    glVertex3f(-3.0f,5.0f, -1.0f);
    //3--上面--------------------------
    //    glNormal3f( 0.0F, 1.0F, 0.0F);
    glVertex3f( -3.0f,5.0f,1.0f);
    glVertex3f(3.0f,5.0f, 1.0f);
    glVertex3f( 3.0f,5.0f, -1.0f);
    glVertex3f(-3.0f,5.0f, -1.0f);
    //4--下面--------------------------
    //    glNormal3f( 0.0F,-1.0F, 0.0F);
    glVertex3f(-2.5f,0.0f, 1.0f);
    glVertex3f( 2.5f,0.0f, 1.0f);
    glVertex3f(2.5f,0.0f, -1.0f);
    glVertex3f( -2.5f,0.0f,-1.0f);
    
    //5--右面--------------------------
    //    glNormal3f( 1.0F, 0.0F, 0.0F);
    glVertex3f( 2.5f,0.0f,1.0f);
    glVertex3f(2.5f,0.0f, -1.0f);
    glVertex3f(3.0f,5.0f, -1.0f);
    glVertex3f(3.0f,5.0f, 1.0f);
    
    //6--左面--------------------------*/
    //    glNormal3f(-1.0F, 0.0F, 0.0F);
    glVertex3f( -2.5f,0.0f,1.0f);
    glVertex3f(-2.5f,0.0f, -1.0f);
    glVertex3f( -3.0f,5.0f, -1.0f);
    glVertex3f(-3.0f,5.0f, 1.0f);
    
    glEnd();
    
    //1
    glColor3ub(0, 0, 0);
    glBegin(GL_LINE_STRIP);
    glVertex3f( -2.5f,0.0f,1.01f);
    glVertex3f(2.5f,0.0f, 1.01f);
    glVertex3f( 3.0f,5.0f, 1.01f);
    glVertex3f(-3.0f,5.0f, 1.01f);
    glVertex3f( -2.5f,0.0f,1.01f);
    glEnd();
    //2
    glBegin(GL_LINE_STRIP);
    glVertex3f( -2.5f,0.0f,-1.0f);
    glVertex3f(2.5f,0.0f, -1.0f);
    glVertex3f( 3.0f,5.0f, -1.0f);
    glVertex3f(-3.0f,5.0f, -1.0f);
    glEnd();
    //3
    glBegin(GL_LINE_STRIP);
    glVertex3f( -3.0f,5.0f,1.0f);
    glVertex3f(3.0f,5.0f, 1.0f);
    glVertex3f( 3.0f,5.0f, -1.0f);
    glVertex3f(-3.0f,5.0f, -1.0f);
    glEnd();
    //4
    glBegin(GL_LINE_STRIP);
    glVertex3f(-2.5f,0.0f, 1.0f);
    glVertex3f( 2.5f,0.0f, 1.0f);
    glVertex3f(2.5f,0.0f, -1.0f);
    glVertex3f( -2.5f,0.0f,-1.0f);
    glVertex3f(-2.5f,0.0f, 1.0f);
    glEnd();
    //5
    glBegin(GL_LINE_STRIP);
    glVertex3f( 2.5f,0.0f,1.0f);
    glVertex3f(2.5f,0.0f, -1.0f);
    glVertex3f(3.0f,5.0f, -1.0f);
    glVertex3f(3.0f,5.0f, 1.0f);
    glVertex3f( 2.5f,0.0f,1.0f);
    glEnd();
    //6
    glBegin(GL_LINE_STRIP);
    glVertex3f( -2.5f,0.0f,1.0f);
    glVertex3f(-2.5f,0.0f, -1.0f);
    glVertex3f( -3.0f,5.0f, -1.0f);
    glVertex3f(-3.0f,5.0f, 1.0f);
    glEnd();
    
    //绘制暗点
    
    DrawEllipse(-2.3, 4.5, 1.1, 325, 0.15, 0.2, 0, 360);
    DrawEllipse(-2.5, 3.8, 1.1, 325, 0.15, 0.2, 0, 360);
    DrawEllipse(2.5, 4.6, 1.1, 325, 0.15, 0.2, 0, 360);
    
    DrawEllipse(-1.9, 1.4, 1.1, 325, 0.15, 0.2, 0, 360);
    DrawEllipse(1.7, 1.2, 1.1, 325, 0.2, 0.4, 0, 360);
    DrawEllipse(1.7, 0.5, 1.1, 325, 0.15, 0.2, 0, 360);
    //    DrawEclipse(-2, 0.5, 1.1, 0.3, 0.4, 165, 138, 12);
    DrawEllipse(-1.6, 0.7, 1.1,325, 0.2, 0.4, 0, 360);
    //绘制眼睛外圈
    DrawCircle(1, 3.5,1.1, 1, 255, 255, 255);
    DrawCircle(-1, 3.5,1.1, 1, 255, 255, 255);
    DrawCircleLine(1, 3.5, 1.001, 1.01);
    DrawCircleLine(-1, 3.5, 1.001, 1.01);
    
    //绘制眼睛内圈
    DrawCircle(0.7, 3.5,1.12, 0.5,70,183,237);
    DrawCircle(-0.7, 3.5,1.12, 0.5,70,183,237);
    DrawCircleLine(0.7, 3.5, 1.12, 0.51);
    DrawCircleLine(-0.7, 3.5, 1.12, 0.51);
    
    //绘制眼睛最内圈
    DrawCircle(0.7, 3.5,1.14, 0.3,0,0,0);
    DrawCircle(-0.7, 3.5,1.14, 0.3,0,0,0);
    
    //绘制睫毛
    DrawStraightLine(1, 4.5, 1.1, 1, 4.9, 1.1);
    DrawStraightLine(-1, 4.5, 1.1, -1, 4.9, 1.1);
    DrawStraightLine(1.3, 4.3, 1.1, 1.5, 4.8, 1.1);
    DrawStraightLine(-1.3, 4.3, 1.1, -1.5, 4.8, 1.1);
    DrawStraightLine(0.7, 4.3, 1.1, 0.5, 4.8, 1.1);
    DrawStraightLine(-0.7, 4.3, 1.1, -0.5, 4.8, 1.1);
    
    //绘制嘴巴
    DrawCurve(0, 1.8,1.1, 1.8, 0.1, 30 , 150);
    
    DrawTooth2D(0.1, 1.9, 1.1);
    DrawTooth2D(-0.6, 1.9, 1.1);
    DrawStraightLine(0.1, 1.9, 1.1, 0.1, 1.4, 1.1);
    DrawStraightLine(0.6, 1.9, 1.11, 0.6, 1.4, 1.11);
    DrawStraightLine(0.1, 1.4, 1.11, 0.6, 1.4, 1.11);
    DrawStraightLine(-0.1, 1.9, 1.1, -0.1, 1.4, 1.1);
    DrawStraightLine(-0.6, 1.9, 1.11, -0.6, 1.4, 1.11);
    DrawStraightLine(-0.1, 1.4, 1.11, -0.6, 1.4, 1.11);
    
    //身子1
    float A_1[3]={-2.5f,0.0f,1.0f};
    glColor3ub(255, 255, 255);//
    drawCube(A_1,5,2,0.5);
    
    //领带
    glColor3ub(0, 0, 0);
    glBegin(GL_LINE_STRIP);
    glVertex3f(-0.9f, 0.0f, 1.01f);
    glVertex3f(-0.45f, -0.4f, 1.01f);
    glVertex3f(-0.2f, 0.0f, 1.01f);
    glEnd();
    
    glColor3ub(200, 0, 5);
    glBegin(GL_POLYGON);
    glVertex3f(-0.2f, 0.0f, 1.01f);
    glVertex3f(-0.05f, -0.3f, 1.01f);
    glVertex3f(0.05f, -0.3f, 1.01f);
    glVertex3f(0.2f, 0.0f, 1.01f);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex3f(-0.05f, -0.3f, 1.01f);
    glVertex3f(-0.3f, -0.7f, 1.01f);
    glVertex3f(0.0f, -1.0f, 1.01f);
    glVertex3f(0.3f, -0.7f, 1.01f);
    glVertex3f(0.05f, -0.3f, 1.01f);
    glEnd();
    glColor3ub(0, 0, 0);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.9f, 0.0f, 1.01f);
    glVertex3f(0.45f, -0.4f, 1.01f);
    glVertex3f(0.2f, 0.0f, 1.01f);
    glEnd();
    
    //身子2
    float A_2[3]={-2.5f,-0.5f,1.0f};
    glColor3ub(170, 97, 0);//棕色
    drawCube(A_2,5,2,0.6f);
    
    //前面
    glColor3ub(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-2.3f, -0.6f, 1.01);
    glVertex3f(-1.5f, -0.6f, 1.01);
    glVertex3f(-1.5f, -0.8f, 1.01);
    glVertex3f(-2.3f, -0.8f, 1.01);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex3f(-1.0f, -0.6f, 1.01);
    glVertex3f(1.0f, -0.6f, 1.01);
    glVertex3f(1.0f, -0.8f, 1.01);
    glVertex3f(-1.0f, -0.8f, 1.01);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex3f(2.3f, -0.6f, 1.01);
    glVertex3f(1.5f, -0.6f, 1.01);
    glVertex3f(1.5f, -0.8f, 1.01);
    glVertex3f(2.3f, -0.8f, 1.01);
    glEnd();
    //左面
    glBegin(GL_POLYGON);
    glVertex3f(-2.501f, -0.6f, 0.8);
    glVertex3f(-2.501f, -0.6f, 0.3);
    glVertex3f(-2.501f, -0.8f, 0.3);
    glVertex3f(-2.501f, -0.8f, 0.8);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex3f(-2.501f, -0.6f, -0.8);
    glVertex3f(-2.501f, -0.6f, -0.3);
    glVertex3f(-2.501f, -0.8f, -0.3);
    glVertex3f(-2.501f, -0.8f, -0.8);
    glEnd();
    //后面
    glBegin(GL_POLYGON);
    glVertex3f(-2.3f, -0.6f, -1.01);
    glVertex3f(-1.5f, -0.6f, -1.01);
    glVertex3f(-1.5f, -0.8f, -1.01);
    glVertex3f(-2.3f, -0.8f, -1.01);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex3f(-1.0f, -0.6f, -1.01);
    glVertex3f(-0.2f, -0.6f, -1.01);
    glVertex3f(-0.2f, -0.8f, -1.01);
    glVertex3f(-1.0f, -0.8f, -1.01);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex3f(1.0f, -0.6f, -1.01);
    glVertex3f(0.2f, -0.6f, -1.01);
    glVertex3f(0.2f, -0.8f, -1.01);
    glVertex3f(1.0f, -0.8f, -1.01);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex3f(2.3f, -0.6f, -1.01);
    glVertex3f(1.5f, -0.6f, -1.01);
    glVertex3f(1.5f, -0.8f, -1.01);
    glVertex3f(2.3f, -0.8f, -1.01);
    glEnd();
    
    
    //右边
    glBegin(GL_POLYGON);
    glVertex3f(2.501f, -0.6f, 0.8);
    glVertex3f(2.501f, -0.6f, 0.3);
    glVertex3f(2.501f, -0.8f, 0.3);
    glVertex3f(2.501f, -0.8f, 0.8);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex3f(2.501f, -0.6f, -0.8);
    glVertex3f(2.501f, -0.6f, -0.3);
    glVertex3f(2.501f, -0.8f, -0.3);
    glVertex3f(2.501f, -0.8f, -0.8);
    glEnd();
    //左手臂
    glColor3ub(255, 255, 255);
    
    glPushMatrix();
    glTranslatef(-2.6f, 2.0f, 0.0);
    glutSolidSphere(0.4, 120, 120);
    glPopMatrix();
    
    glColor3ub(253, 247, 62);//黄色
    glPushMatrix();
    glTranslatef(-3.0f, -0.4f, 0.0f);
    
    glRotatef(80, 0, 0, 1);
    glRotatef(90,0,1,0);
    
    
    GLUquadricObj *quadratic_17;
    quadratic_17=gluNewQuadric();
    mySolidCylinder(quadratic_17,0.2f,0.2f,2.8f,32,32);
    glPopMatrix();
    
    
    glColor3ub(253, 247, 62);//黄色
    glPushMatrix();
    glTranslatef(-3.1f, -0.7f, 0.0);
    glutSolidSphere(0.4, 120, 120);
    glPopMatrix();
    
    //右胳膊
    glColor3ub(255, 255, 255);
    
    glPushMatrix();
    glTranslatef(2.6f, 2.0f, 0.0);
    glutSolidSphere(0.4, 120, 120);
    glPopMatrix();
    
    glColor3ub(253, 247, 62);//黄色
    glPushMatrix();
    glTranslatef(3.0f, -0.4f, 0.0f);
    
    glRotatef(100, 0, 0, 1);
    glRotatef(90,0,1,0);
    
    
    GLUquadricObj *quadratic_18;
    quadratic_18=gluNewQuadric();
    mySolidCylinder(quadratic_18,0.2f,0.2f,2.8f,32,32);
    glPopMatrix();
    
    
    glColor3ub(253, 247, 62);//黄色
    glPushMatrix();
    glTranslatef(3.1f, -0.7f, 0.0);
    glutSolidSphere(0.4, 120, 120);
    glPopMatrix();
    
    
    
    //左裤子
    glColor3ub(175, 100, 0);
    
    glPushMatrix();
    glTranslatef(-1.0f, -1.1f, 0.0f);
    
    glRotatef(90,1,0,0);
    
    GLUquadricObj *quadratic_1;
    quadratic_1=gluNewQuadric();
    mySolidCylinder(quadratic_1,0.7f,0.7f,0.5f,32,32);
    glPopMatrix();
    
    //右裤子
    glPushMatrix();
    glTranslatef(1.0f, -1.1f, 0.0f);
    
    glRotatef(90,1,0,0);
    
    GLUquadricObj *quadratic_2;
    quadratic_2=gluNewQuadric();
    mySolidCylinder(quadratic_2,0.7f,0.7f,0.5f,32,32);
    glPopMatrix();
    //左腿
    glColor3ub(253, 247, 62);//黄色
    glPushMatrix();
    glTranslatef(-1.0f, -1.6f, 0.0f);
    
    glRotatef(90,1,0,0);
    
    GLUquadricObj *quadratic_3;
    quadratic_3=gluNewQuadric();
    mySolidCylinder(quadratic_3,0.3f,0.3f,0.7f,32,32);
    glPopMatrix();
    //右腿
    glColor3ub(253, 247, 62);//黄色
    glPushMatrix();
    glTranslatef(1.0f, -1.6f, 0.0f);
    
    glRotatef(90,1,0,0);
    
    GLUquadricObj *quadratic_4;
    quadratic_4=gluNewQuadric();
    mySolidCylinder(quadratic_4,0.3f,0.3f,0.7f,32,32);
    glPopMatrix();
    //左袜子
    glColor3ub(255, 255, 255);//
    glPushMatrix();
    glTranslatef(-1.0f, -2.3f, 0.0f);
    
    glRotatef(90,1,0,0);
    
    GLUquadricObj *quadratic_5;
    quadratic_5=gluNewQuadric();
    mySolidCylinder(quadratic_5,0.3f,0.3f,0.2f,32,32);
    glPopMatrix();
    
    glColor3ub(62, 108, 186);//
    glPushMatrix();
    glTranslatef(-1.0f, -2.5f, 0.0f);
    
    glRotatef(90,1,0,0);
    
    GLUquadricObj *quadratic_6;
    quadratic_6=gluNewQuadric();
    mySolidCylinder(quadratic_6,0.3f,0.3f,0.1f,32,32);
    glPopMatrix();
    
    glColor3ub(255, 255, 255);//
    glPushMatrix();
    glTranslatef(-1.0f, -2.6f, 0.0f);
    
    glRotatef(90,1,0,0);
    
    GLUquadricObj *quadratic_7;
    quadratic_7=gluNewQuadric();
    mySolidCylinder(quadratic_7,0.3f,0.3f,0.15f,32,32);
    glPopMatrix();
    
    glColor3ub(220, 0, 13);//
    glPushMatrix();
    glTranslatef(-1.0f, -2.75f, 0.0f);
    
    glRotatef(90,1,0,0);
    
    GLUquadricObj *quadratic_8;
    quadratic_8=gluNewQuadric();
    mySolidCylinder(quadratic_8,0.3f,0.3f,0.1f,32,32);
    glPopMatrix();
    
    glColor3ub(255, 255, 255);//
    glPushMatrix();
    glTranslatef(-1.0f, -2.85f, 0.0f);
    
    glRotatef(90,1,0,0);
    
    GLUquadricObj *quadratic_9;
    quadratic_9=gluNewQuadric();
    mySolidCylinder(quadratic_9,0.3f,0.3f,0.6f,32,32);
    glPopMatrix();
    
    //右袜子
    glColor3ub(255, 255, 255);//
    glPushMatrix();
    glTranslatef(1.0f, -2.3f, 0.0f);
    
    glRotatef(90,1,0,0);
    
    GLUquadricObj *quadratic_10;
    quadratic_10=gluNewQuadric();
    mySolidCylinder(quadratic_10,0.3f,0.3f,0.2f,32,32);
    glPopMatrix();
    
    glColor3ub(62, 108, 186);//
    glPushMatrix();
    glTranslatef(1.0f, -2.5f, 0.0f);
    
    glRotatef(90,1,0,0);
    
    GLUquadricObj *quadratic_11;
    quadratic_11=gluNewQuadric();
    mySolidCylinder(quadratic_11,0.3f,0.3f,0.1f,32,32);
    glPopMatrix();
    
    glColor3ub(255, 255, 255);//
    glPushMatrix();
    glTranslatef(1.0f, -2.6f, 0.0f);
    
    glRotatef(90,1,0,0);
    
    GLUquadricObj *quadratic_12;
    quadratic_12=gluNewQuadric();
    mySolidCylinder(quadratic_12,0.3f,0.3f,0.15f,32,32);
    glPopMatrix();
    
    glColor3ub(220, 0, 13);//
    glPushMatrix();
    glTranslatef(1.0f, -2.75f, 0.0f);
    
    glRotatef(90,1,0,0);
    
    GLUquadricObj *quadratic_13;
    quadratic_13=gluNewQuadric();
    mySolidCylinder(quadratic_13,0.3f,0.3f,0.1f,32,32);
    glPopMatrix();
    
    glColor3ub(255, 255, 255);//
    glPushMatrix();
    glTranslatef(1.0f, -2.85f, 0.0f);
    
    glRotatef(90,1,0,0);
    
    GLUquadricObj *quadratic_14;
    quadratic_14=gluNewQuadric();
    mySolidCylinder(quadratic_14,0.3f,0.3f,0.6f,32,32);
    glPopMatrix();
    
    //左脚
    glColor3ub(0,0,0);//
    glPushMatrix();
    glTranslatef(-1.0f, -3.5f, 0.0f);
    
    //   glRotatef(30,0,1,0);
    
    GLUquadricObj *quadratic_15;
    quadratic_15=gluNewQuadric();
    mySolidCylinder(quadratic_15,0.3f,0.5f,1.0f,32,32);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-1.0f, -3.5f, 1.0f);
    glutSolidSphere(0.5, 120, 120);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-1.0f, -3.5f, 0.0f);
    glutSolidSphere(0.3, 120, 120);
    glPopMatrix();
    //右脚
    glColor3ub(0,0,0);//
    glPushMatrix();
    glTranslatef(1.0f, -3.5f, 0.0f);
    
    
    GLUquadricObj *quadratic_16;
    quadratic_16=gluNewQuadric();
    mySolidCylinder(quadratic_16,0.3f,0.5f,1.0f,32,32);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(1.0f, -3.5f, 1.0f);
    glutSolidSphere(0.5, 120, 120);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(1.0f, -3.5f, 0.0f);
    glutSolidSphere(0.3, 120, 120);
    glPopMatrix();
    
    
    // glEnd();
    
    
    
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glRotated(spin,1.0,0.0,0.0);
	glLightfv(GL_LIGHT1,GL_POSITION,lightPosition1);
    glLightfv(GL_LIGHT1,GL_DIFFUSE,whiteLight);
    glLightfv(GL_LIGHT1,GL_SPECULAR,whiteLight);
	glPopMatrix();
    drawobjects(GL_RENDER);
    glutSwapBuffers();
}
void specialKeys(int key,int x,int y){
    //如果初始角度设置为0则初始面向X轴正方向，设置为-90面向
    //Z轴负方向，符合默认情况下的设计习惯。
    
    
    float PI=3.14159f;
    // 旋转请求
    if(key==GLUT_KEY_LEFT)
    {
        rot1-= 12.0;//每按一次左键，旋转2度。
        rot2-=12.0;
        cout<<"test turn left";
    }
    if (key==GLUT_KEY_RIGHT)
    {
        rot1+= 12.0;//每按一次左键，旋转2度。
        rot2+=12.0;                       //每按一次右键，旋转2度。
        cout<<"test turn right";
    }
    float rad =float(PI*s_angle/180.0f);                    //计算SIN和COS函数中需要的参数。
    // 前进,后退请求
    if(key==GLUT_KEY_UP)
    {
        s_eye[0] += 0.5;
        cout<<"test turn up";
    }
    if(key==GLUT_KEY_DOWN)
    {
        s_eye[0]-=0.5;
        cout<<"test turn down";
    }
    glLoadIdentity();
    gluLookAt(s_eye[0], s_eye[1], s_eye[2],
                  s_at[0], s_at[1], s_at[2],
                  0.0,1.0, 0.0);
    display();
}
void normal(unsigned char key,int x,int y){
    if(key==117){
        s_at[1]+=0.5;
        cout<<"at";
    }
    if(key==100){
        s_at[1]-=0.5;
    }
    if(key==102){
        s_eye[2]-=1;
    }

    if(key==98){
        s_eye[2]+=1;
    }
    glLoadIdentity();
    gluLookAt(s_eye[0], s_eye[1], s_eye[2],
              s_at[0], s_at[1], s_at[2],
              0.0,1.0, 0.0);
    display();
}
void drawobjects(GLenum mode){
    
    if(mode==GL_SELECT)
        glLoadName(1);   //接下来绘制的对象ID为1

 //   glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT,GL_SPECULAR,matSpecular);
    glMaterialfv(GL_FRONT,GL_SHININESS,matShininess);
    glMaterialfv(GL_FRONT,GL_EMISSION,matEmission);

    glPushMatrix();
    glTranslatef(tra1,0,pz);
    glRotatef(rot1,0,1,0);
    glScalef(sca1,sca1,sca1);
    drawPDX();
    glPopMatrix();
	//glDisable(GL_COLOR_MATERIAL);
    
	
    glPushMatrix();
    if(mode==GL_SELECT)
        glLoadName(2);   //接下来绘制的对象ID为2

	//glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);

    glTranslatef(tra2-10.0f, 0.0,hz-3.0f);
    glRotatef(rot2,0,1,0);
    glScalef(sca2,sca2,sca2);
    
    drawHMBB();
    glPopMatrix();
	//glDisable(GL_COLOR_MATERIAL);
    
    
    
}

void processHits (GLint hits, GLuint buffer[]){
    GLuint mindepth=0;
    mindepth=~mindepth;			// GLuint 的最大值
    
    // hit 产生的数据链
    GLuint *ptr, nums, zmin, zmax, name;
    ptr = buffer;
    
    selectedIndex = 0; //初始化为0
    for (int i = 0; i < hits; i++)
    {
        // number of names for this hit
        // 在本程序中 nums=1
        nums = *ptr;
        
        ptr++;	zmin = *ptr;
        ptr++;	zmax = *ptr;
        
        // 在本程序中 nums=1, 无需循环
        ptr++;  name = *ptr;
        
        // 选择离视点最近的对象
        if(mindepth>zmin)
        {
            mindepth=zmin;
            selectedIndex=name;
        }
        
        // 下一个 hit
        ptr++;
    }
    
    cout<<selectedIndex<<endl;
}
#define SIZE 512
void mouse(int button, int state, int x, int y)
{
    GLuint selectBuf[SIZE];
    GLint hits;
    GLint viewport[4];
    
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) //鼠标左键按下进入选择模式
    {
        glGetIntegerv (GL_VIEWPORT, viewport); //获得当前的viewport,用于gluPickMatrix
        
        glSelectBuffer (SIZE, selectBuf);    //设定缓存
        glRenderMode(GL_SELECT); //进入选择模式
        
        glInitNames();  //初始化名称堆栈
        glPushName(-1); //名称缓冲区中放入id (没有绘制任何对象,所以用-1表示)
        
        glMatrixMode (GL_PROJECTION);
        glPushMatrix (); //保存当前投影矩阵（因为后面重设视景体，把视景体设为鼠标附近）
        
        glLoadIdentity (); //把当前投影矩阵置为单位矩阵
        /* create 2x2 pixel picking region near cursor location */
        gluPickMatrix ((GLdouble) x, (GLdouble) (viewport[3] - y),
                       2.0, 2.0, viewport);  //改变视图参数，使得只有靠近鼠标指针的对象位于新的视景体中
        
        GLfloat aspectRatio = (GLfloat)W / (GLfloat)H;//计算窗口横纵比
        
        if (W<=H)
            glOrtho(-10.0, 10.0, -10.0/aspectRatio, 10.0/aspectRatio, -10.0, 10.0);
        else
            glOrtho(-10.0*aspectRatio, 10.0*aspectRatio, -10.0, 10.0, -10.0, 10.0);
        
        
        drawobjects(GL_SELECT);		//在选择模式下重绘对象，这时候对象拥有ID
        
        glMatrixMode (GL_PROJECTION);
        glPopMatrix ();  //恢复原来的投影矩阵
        
        
        glMatrixMode(GL_MODELVIEW);  //恢复当前矩阵模式为Modelview
        
        hits = glRenderMode (GL_RENDER); //退出选择模式，得到击中对象个数
        cout<<"hits"<<hits<<endl;
        processHits (hits, selectBuf);   //根据击中对象个数，和击中记录缓存，得到当前选中的对象
        
        glutPostRedisplay();
    }
}
void init()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glClearDepth(1.0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT1);
    
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void forward(){
    if(selectedIndex==1){
        for(;tra1<=10;){
            tra1+=0.2f;
            display();
        }
    }
    else if(selectedIndex==2){
        for(;tra2<=10;){
            tra2+=0.2f;
            display();
        }
    }
}
void retreat(){
    if(selectedIndex==1){
        for(;tra1>=-5;){
            tra1-=0.2f;
            display();
        }
    }
    else if(selectedIndex==2){
        for(;tra2>=-5;){
            tra2-=0.2f;
            display();
        }
    }
}
void turn(){
    if(selectedIndex==1){
        for(;rot1>=-90;){
            rot1-=1.0f;
            display();
        }
    }
    else if(selectedIndex==2){
        for(;rot2>=-90;){
            rot2-=1.0f;
            display();
        }
    }
}
void enlarge(){
    if(selectedIndex==1){
        for(;sca1<1.3;){
            sca1+=0.1f;
            display();
        }
    }
    else if(selectedIndex==2){
        for(;sca2<1.3;){
            sca2+=0.3f;
            display();
        }
    }
}
void narrow(){
    if(selectedIndex==1){
        for(;sca1>0.7;){
            sca1-=0.1f;
            display();
        }
    }
    else if(selectedIndex==2){
        for(;sca2>0.7;){
            sca2-=0.3f;
            display();
        }
    }
}
void back(){
    if(selectedIndex==1){
        tra1=0;
        rot1=0;
        sca1=1;
        display();
    }
    else if(selectedIndex==2){
        tra2=0;
        rot2=0;
        sca2=1;
        display();
    }
    
}

void go(){
    int count=0;
    
    s_eye[0]=0;
    s_eye[1]=0;
    s_eye[2]=5;
    
    s_at[0]=0;
    s_at[1]=0;
    s_at[2]=1;
    
    s_angle=-90.0;
    
    float rad;
    while (count<10) {
        s_at[1]-=0.5;
        display();
//        Sleep(100);
        sleep(1);
        count++;
    }
    while(count<20){
        s_angle+=6;
        rad =float(Pi*s_angle/180.0f);
        s_at[0] = float(s_eye[0] + 4*cos(rad));
        s_at[2] = float(s_eye[2] + 4*sin(rad));
        
        display();
//        Sleep(100);
        sleep(1);
        count++;
    }
    while(count<30){
        s_eye[0]-=0.5;
        display();
        cout<<"go";
//        Sleep(100);
        sleep(1);
        count++;
    }
    while (count<40) {
        s_angle-=9;
        rad=float(Pi*s_angle/180.0f);
        s_at[0]=float(s_eye[0]+4*cos(rad));
        s_at[2]=float(s_eye[2]+4*sin(rad));
        
        display();
//        Sleep(100);
        sleep(1);
        count++;
    }
    while(count<50){
        s_at[1]+=0.5;
        display();
//       Sleep(100);
        sleep(1);
        count++;
    }
}
void recover(){
    //    s_eye[]={0,0,5.0};
    //    s_at[]={0.0,0.0,1.0};
    s_eye[0]=0;
    s_eye[1]=0;
    s_eye[2]=5;
    
    s_at[0]=0;
    s_at[1]=0;
    s_at[2]=1;
    
    s_angle=-90.0;
}

void light(){
	for(int i=1;i<60;i++){
	spin=(spin+6)%360;
	display();
	}
}

void menu(int id){
    switch (id)
    {
        case 13:exit(0);
            break;
        case 14:
            go();
            break;
        case 15:
            recover();
            break;
		case 16:
            light();
            break;
    }
    glutPostRedisplay();
}

void menu_PDX(int id){
    selectedIndex=1;
    switch (id)
    {
        case 1:
            glPushMatrix();
            forward();
            glPopMatrix();
            break;
        case 2:
            glPushMatrix();
            retreat();
            glPopMatrix();
            break;
        case 3:
            glPushMatrix();
            turn();
            glPopMatrix();
            break;
        case 4:
            glPushMatrix();
            enlarge();
            glPopMatrix();
            break;
        case 5:
            glPushMatrix();
            narrow();
            glPopMatrix();
            break;
        case 6:
            glPushMatrix();
            back();
            glPopMatrix();
            break;
    }
}

void menu_HMBB(int id){
    selectedIndex=2;
    switch (id)
    {
        case 7:
            glPushMatrix();
            forward();
            glPopMatrix();
            break;
        case 8:
            glPushMatrix();
            retreat();
            glPopMatrix();
            break;
        case 9:
            glPushMatrix();
            turn();
            glPopMatrix();
            break;
        case 10:
            glPushMatrix();
            enlarge();
            glPopMatrix();
            break;
        case 11:
            glPushMatrix();
            narrow();
            glPopMatrix();
            break;
        case 12:
            glPushMatrix();
            back();
            glPopMatrix();
            break;
    }
    
}

int main(int argc, char * argv[]) {
    // insert code here...
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (600, 600);
    glutInitWindowPosition(200, 0);
    glutCreateWindow("海绵宝宝");
    glutDisplayFunc(display);
//    glutMouseFunc (mouse);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(normal);
    glutReshapeFunc(reshape);
    
    menu_PDX_id=glutCreateMenu(menu_PDX);
    glutAddMenuEntry("Forward",1);
    glutAddMenuEntry("Retreat",2);
    glutAddMenuEntry("Turn",3);
    glutAddMenuEntry("Enlarge",4);
    glutAddMenuEntry("Narrow",5);
    glutAddMenuEntry("Back",6);
    
    menu_HMBB_id=glutCreateMenu(menu_HMBB);
    glutAddMenuEntry("Forward",7);
    glutAddMenuEntry("Retreat",8);
    glutAddMenuEntry("Turn",9);
    glutAddMenuEntry("Enlarge",10);
    glutAddMenuEntry("Narrow",11);
    glutAddMenuEntry("Back",12);
    
    menu_id=glutCreateMenu(menu);
    glutAddSubMenu("PDX",menu_PDX_id);
    glutAddSubMenu("HMBB",menu_HMBB_id);
    glutAddMenuEntry("Exit",13);
    glutAddMenuEntry("Go", 14);
    glutAddMenuEntry("Recover", 15);
	glutAddMenuEntry("Light", 16);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    init();
    glutMainLoop();
    
    return 0;
    
}






