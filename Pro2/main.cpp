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

static GLfloat s_eye[]={0,0,25.0};
static GLfloat s_at[]={0.0,0.0,1.0};
static GLfloat s_angle=-90.0;
//static GLfloat s_angle = -90.0;
const GLfloat R=0.25f;
const int n=2400;
const GLfloat Pi = 3.1415926536f;
const   float   DEG2RAD   =   3.14159/180;

const GLfloat lightPosition1[] = {-10.0,10.0,50.0,1.0};
const GLfloat whiteLight[] = {0.8,0.8,0.8,1.0};
const GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f };  //环境光
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

GLfloat hleft=0;
GLfloat hright=0;

GLfloat hxh=-2.6f;
GLfloat hyh=2.0f;
GLfloat hzh=0.0;

GLfloat hxb=-2.8f;
GLfloat hyb=1.9f;
GLfloat hzb=0.0;
GLfloat ballx=0.0f;
GLfloat bally=0.0f;
GLfloat ballz=0.0f;
GLfloat balltempx=0;
GLfloat balltempy=0;
GLfloat balltempz=0;

int hlzdegree=-100;
int hlxdegree=0;
bool flag=true;

int W, H;
#define BMP_Header_Length 54
GLuint texGround;
GLuint texHMBB_face_front;
GLuint texHMBB_face_back;
GLuint texHMBB_cloth_front;
GLuint texHMBB_cloth_back;
GLuint texHMBB_sock;
GLuint texFront;
GLuint texLeft;
GLuint texRight;
GLuint texUp;

GLuint selectedIndex=1;	 //击中对象的ID

void DrawCurve(float x,float y,float z,float xradius,float yradius,int degree1,int degree2){
    int i=n*degree1/360;
    int end=n*degree2/360;
    glColor3f(0,0,0);
    glBegin(GL_LINE_STRIP);
    for(;i<=end;i++)
        glVertex3f(x+xradius*cos(2*Pi/n*i),y+yradius*sin(2*Pi/n*i),z);
    glEnd();
}

void drawobjects(GLenum);

void reshape(int w,int h)
{
    W = w;
    H = h;

    GLfloat ratio = 1.0f * W/ H;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    glViewport(0, 0, w, h);
    

    gluPerspective(45,ratio,1,1000);

    gluLookAt(s_eye[0], s_eye[1], s_eye[2],
              s_at[0], s_at[1], s_at[2],
              0.0,1.0, 0.0);

//    gluLookAt(0, 0, 40, 0, 0, 0, 0, 1, 0);//30,40
    
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
    glColor4f(1.0f,1.0f,1.0f,1.0f);  //创建图形，alpha值为0.5f，表示半透明
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);//进行混合
    //身子前面
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texHMBB_face_front);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.5f,0.0f,1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-3.0f,5.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 3.0f,5.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(2.5f,0.0f, 1.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    //身子后面
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texHMBB_face_back);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.5f,0.0f,-1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-3.0f,5.0f,-1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 3.0f,5.0f,-1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(2.5f,0.0f,-1.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    //身子左面
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texHMBB_face_back);
    glBegin(GL_QUADS);
    glNormal3f(-1.0, 0.0, 0.0);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.5f,0.0f,1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.5f,0.0f, -1.0f);
    glTexCoord2f(0.5f, 1.0f); glVertex3f(-3.0f,5.0f,-1.0f);
    glTexCoord2f(0.5f, 0.0f); glVertex3f(-3.0f,5.0f, 1.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    //身子右面
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texHMBB_face_back);
    glBegin(GL_QUADS);
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(2.5f,0.0f,1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(2.5f,0.0f,-1.0f);
    glTexCoord2f(0.5f, 1.0f); glVertex3f(3.0f,5.0f,-1.0f);
    glTexCoord2f(0.5f, 0.0f); glVertex3f(3.0f,5.0f, 1.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    //身子上面
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texHMBB_face_back);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-3.0f,5.0f,1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(3.0f,5.0f, 1.0f);
    glTexCoord2f(0.5f, 1.0f); glVertex3f(3.0f,5.0f,-1.0f);
    glTexCoord2f(0.5f, 0.0f); glVertex3f(-3.0f,5.0f,-1.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    //身子下面
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texHMBB_face_back);
    glBegin(GL_QUADS);
    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.5f,-1.2f,1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(2.5f,-1.2f, 1.0f);
    glTexCoord2f(0.5f, 1.0f); glVertex3f(2.5f,-1.2f,-1.0f);
    glTexCoord2f(0.5f, 0.0f); glVertex3f(-2.5f,-1.2f,-1.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    //衣服前面
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texHMBB_cloth_front);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.5f,-1.2f,1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.5f,0.0f,1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(2.5f,0.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(2.5f,-1.2f,1.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    //衣服后面
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texHMBB_cloth_back);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.5f,-1.2f,-1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.5f,0.0f,-1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(2.5f,0.0f,-1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(2.5f,-1.2f,-1.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    //衣服左面
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texHMBB_cloth_back);
    glBegin(GL_QUADS);
    glNormal3f(-1.0, 0.0, 0.0);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.5f,-1.2f,-1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.5f,0.0f,-1.0f);
    glTexCoord2f(0.5f, 1.0f); glVertex3f(-2.5f,0.0f,1.0f);
    glTexCoord2f(0.5f, 0.0f); glVertex3f(-2.5f,-1.2f,1.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    //衣服右面
    glEnable(GL_TEXTURE_2D);
    glNormal3f(1.0, 0.0, 0.0);
    glBindTexture(GL_TEXTURE_2D, texHMBB_cloth_back);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(2.5f,-1.2f,-1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(2.5f,0.0f,-1.0f);
    glTexCoord2f(0.5f, 1.0f); glVertex3f(2.5f,0.0f,1.0f);
    glTexCoord2f(0.5f, 0.0f); glVertex3f(2.5f,-1.2f,1.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    //左手臂
    glBegin(GL_POLYGON);
    glVertex3f(2.501f, -0.6f, -0.8);
    glVertex3f(2.501f, -0.6f, -0.3);
    glVertex3f(2.501f, -0.8f, -0.3);
    glVertex3f(2.501f, -0.8f, -0.8);
    glEnd();

    glColor3ub(255, 255, 255);
    
    glPushMatrix();
    glTranslatef(hxb,hyb,hzb);
    glutSolidSphere(0.4, 120, 120);
    glPopMatrix();
    
    glColor3ub(253, 247, 62);//黄色
    glPushMatrix();
    glTranslatef(-2.7f, 1.8f, 0.0f);
    
    glRotatef(hlxdegree, 1, 0, 0);
    glRotatef(hlzdegree, 0, 0, 1);
    glRotatef(90,0,1,0);


    GLUquadricObj *quadratic_17;
    quadratic_17=gluNewQuadric();
    mySolidCylinder(quadratic_17,0.2f,0.2f,2.8f,32,32);
    glPopMatrix();
    
    float rad=((float)hlzdegree)/180;
//    cout<<cos(rad*Pi)<<endl;
    hxh=hxb+2.8*cos(rad*Pi);
    hyh=hyb+2.8*sin(rad*Pi);
    
    rad=((float)hlxdegree)/180;
    hyh=hyh-2.8*(1-cos(rad*Pi));
    hzh=2.8*sin(rad*Pi);
//    cout<<hxh<<" "<<hyh<<endl;
    glColor3ub(253, 247, 62);//黄色
    
    glPushMatrix();
    glTranslatef(hxh,hyh,hzh);
    glutSolidSphere(0.4, 120, 120);
    glPopMatrix();
    
    //左手球
    glColor3ub(0, 0, 0);
    if(flag){
        glPushMatrix();
        glTranslatef(ballx, bally, ballz);
        glTranslatef(hxh-0.6f,hyh, hzh);
        glutSolidSphere(0.4, 400, 400);
        glPopMatrix();
        balltempx=hxh-0.6f;
        balltempy=hyh;
        balltempz=hzh;
    }
    else{
        
        glPushMatrix();
        glTranslatef(ballx, bally, ballz);
        glTranslatef(balltempx,balltempy, balltempz);
        glutSolidSphere(0.4, 400, 400);
        glPopMatrix();
    }
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
    glRotatef(hright, 1, 0, 0);
    
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
    glTranslatef(-1.0f, -3.4f, 0.0f);
    
    glRotatef(-90,1,0,0);
    
    GLUquadricObj *quadratic_3;
    quadratic_3=gluNewQuadric();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texHMBB_sock);
    gluQuadricTexture(quadratic_3, GL_TRUE);
    mySolidCylinder(quadratic_3,0.2f,0.2f,1.85f,32,32);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    //右腿
    glColor3ub(253, 247, 62);//黄色
    glPushMatrix();
    glTranslatef(1.0f, -3.4f, 0.0f);
    glRotatef(-90,1,0,0);
    
    GLUquadricObj *quadratic_4;
    quadratic_4=gluNewQuadric();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texHMBB_sock);
    gluQuadricTexture(quadratic_4, GL_TRUE);
    mySolidCylinder(quadratic_4,0.2f,0.2f,1.85f,32,32);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    //左脚
    glColor3ub(0,0,0);//
    glPushMatrix();
    glTranslatef(-1.0f, -3.5f, 0.0f);
    
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
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
    glEnable(GL_LIGHT1);
	glRotated(spin,1.0,0.0,0.0);
	glLightfv(GL_LIGHT1,GL_POSITION,lightPosition1);
    glLightfv(GL_LIGHT1,GL_DIFFUSE,whiteLight);
    glLightfv(GL_LIGHT1,GL_SPECULAR,whiteLight);
	glPopMatrix();
    
    glLoadIdentity();
    gluLookAt(s_eye[0], s_eye[1], s_eye[2],
              s_at[0], s_at[1], s_at[2],
              0.0,1.0, 0.0);
    
    drawobjects(GL_RENDER);
    
    
    //绘制沙滩背景
    glColor4f(4.0f,4.0f,4.0f,0.5f);  //创建图形，alpha值为0.5f，表示半透明
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);//进行混合

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texGround);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-50.0f, -3.8f, 20.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-50.0f, -3.8f, -50.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(50.0f, -3.8f, -50.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(50.0f, -3.8f, 20.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    //场景上面
    glColor4f(4.0f,4.0f,4.0f,0.5f);  //创建图形，alpha值为0.5f，表示半透明
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);//进行混合
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texUp);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-50.0f, 30.0f, 20.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-50.0f, 30.0f, -50.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(50.0f, 30.0f, -50.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(50.0f, 30.0f, 20.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    //场景前面
    glColor4f(4.0f,4.0f,4.0f,0.5f);  //创建图形，alpha值为0.5f，表示半透明
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);//进行混合
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texFront);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-50.0f, -3.8f, -50.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-50.0f, 30.0f, -50.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(50.0f, 30.0f, -50.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(50.0f, -3.8f, -50.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    //场景右面
    glColor4f(4.0f,4.0f,4.0f,0.5f);  //创建图形，alpha值为0.5f，表示半透明
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);//进行混合
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texRight);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(50.0f, -3.8f, -50.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(50.0f, 30.0f, -50.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(50.0f, 30.0f, 20.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(50.0f, -3.8f, 20.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    //场景左面
    glColor4f(4.0f,4.0f,4.0f,0.5f);  //创建图形，alpha值为0.5f，表示半透明
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);//进行混合
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texLeft);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-50.0f, -3.8f, 20.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-50.0f, 30.0f, 20.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-50.0f, 30.0f, -50.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-50.0f, -3.8f, -50.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);

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
//        cout<<"test turn left";
    }
    if (key==GLUT_KEY_RIGHT)
    {
        rot1+= 12.0;//每按一次左键，旋转2度。
        rot2+=12.0;                       //每按一次右键，旋转2度。
//        cout<<"test turn right";
    }
    float rad =float(PI*s_angle/180.0f);                    //计算SIN和COS函数中需要的参数。
    // 前进,后退请求
    if(key==GLUT_KEY_UP)
    {
        s_eye[0] += 0.5;
//        cout<<"test turn up";
    }
    if(key==GLUT_KEY_DOWN)
    {
        s_eye[0]-=0.5;
//        cout<<"test turn down";
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
//        cout<<"at";
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
    
    glMaterialfv(GL_FRONT,GL_SPECULAR,matSpecular);
    glMaterialfv(GL_FRONT,GL_SHININESS,matShininess);
    glMaterialfv(GL_FRONT,GL_EMISSION,matEmission);

    glPushMatrix();
    glTranslatef(tra1+5.0f,0,pz);
    glRotatef(rot1,0,1,0);
    glScalef(sca1,sca1,sca1);
    drawPDX();
    glPopMatrix();
    
	
    glPushMatrix();
    glTranslatef(tra2-15.0f, 0.0,hz-3.0f);
    glRotatef(rot2,0,1,0);
    glScalef(sca2,sca2,sca2);
    drawHMBB();
    glPopMatrix();

}


void init()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glClearDepth(1.0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);

    
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int power_of_two(int n)
{
    if( n <= 0 )
        return 0;
    return (n & (n-1)) == 0;
}
GLuint load_texture(const char* file_name)
{
    GLint width, height, total_bytes;
    GLubyte* pixels = 0;
    GLuint last_texture_ID, texture_ID = 0;
    
    // 打开文件，如果失败，返回
    FILE* pFile = fopen(file_name, "rb");
    if( pFile == 0 )
        return 0;
    
    // 读取文件中图象的宽度和高度
    fseek(pFile, 0x0012, SEEK_SET);
    fread(&width, 4, 1, pFile);
    fread(&height, 4, 1, pFile);
    fseek(pFile, BMP_Header_Length, SEEK_SET);
    
    // 计算每行像素所占字节数，并根据此数据计算总像素字节数
    {
        GLint line_bytes = width * 3;
        while( line_bytes % 4 != 0 )
            ++line_bytes;
        total_bytes = line_bytes * height;
    }
    
    // 根据总像素字节数分配内存
    pixels = (GLubyte*)malloc(total_bytes);
    if( pixels == 0 )
    {
        fclose(pFile);
        return 0;
    }
    
    // 读取像素数据
    if( fread(pixels, total_bytes, 1, pFile) <= 0 )
    {
        free(pixels);
        fclose(pFile);
        return 0;
    }
    
    // 在旧版本的OpenGL中
    // 如果图象的宽度和高度不是的整数次方，则需要进行缩放
    // 这里并没有检查OpenGL版本，出于对版本兼容性的考虑，按旧版本处理
    // 另外，无论是旧版本还是新版本，
    // 当图象的宽度和高度超过当前OpenGL实现所支持的最大值时，也要进行缩放
    {
        GLint max;
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
        if( !power_of_two(width)
           || !power_of_two(height)
           || width > max
           || height > max )
        {
            const GLint new_width = 256;
            const GLint new_height = 256; // 规定缩放后新的大小为边长的正方形
            GLint new_line_bytes, new_total_bytes;
            GLubyte* new_pixels = 0;
            
            // 计算每行需要的字节数和总字节数
            new_line_bytes = new_width * 3;
            while( new_line_bytes % 4 != 0 )
                ++new_line_bytes;
            new_total_bytes = new_line_bytes * new_height;
            
            // 分配内存
            new_pixels = (GLubyte*)malloc(new_total_bytes);
            if( new_pixels == 0 )
            {
                free(pixels);
                fclose(pFile);
                return 0;
            }
            
            // 进行像素缩放
            gluScaleImage(GL_RGB,
                          width, height, GL_UNSIGNED_BYTE, pixels,
                          new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);
            
            // 释放原来的像素数据，把pixels指向新的像素数据，并重新设置width和height
            free(pixels);
            pixels = new_pixels;
            width = new_width;
            height = new_height;
        }
    }
    
    // 分配一个新的纹理编号
    glGenTextures(1, &texture_ID);
    if( texture_ID == 0 )
    {
        free(pixels);
        fclose(pFile);
        return 0;
    }
    
    // 在绑定前，先获得原来绑定的纹理编号，以便在最后进行恢复
    glGetIntegerv(GL_TEXTURE_BINDING_2D, (GLint*)&last_texture_ID);
    glBindTexture(GL_TEXTURE_2D, texture_ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODELVIEW);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
                 GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
    glBindTexture(GL_TEXTURE_2D, last_texture_ID);
    
    // 之前为pixels分配的内存可在使用glTexImage2D以后释放
    // 因为此时像素数据已经被OpenGL另行保存了一份（可能被保存到专门的图形硬件中）
    free(pixels);
    return texture_ID;
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
    
    rot1=0;
    rot2=0;
    
    int count=0;
    int ball_angle=0;
    while(count<10){
        rot1-=10;
        rot2+=10;
        display();
//        sleep(1);
        count++;
    }
    while(count<20){
        hlzdegree-=15;
        
        display();
//        sleep(1);
        count++;
    }
    while(count<30){
        hlxdegree+=10;
        display();
//        sleep(1);
        count++;
    }
    while(count<35){
        hlxdegree-=10;
        display();
        count++;
        
    }
    float rad;
    while(count<45){
        ball_angle+=18;
        rad=((float)ball_angle/180);
//        cout<<rad<<endl;
        ballz=10-10*cos(rad*Pi);
        bally=5*sin(rad*Pi);
        flag=false;
        
        hlxdegree+=13;
//        bally+=0.5f;
        display();
//        sleep(1);
        count++;
    }
    
}
void recover(){
    //    s_eye[]={0,0,5.0};
    //    s_at[]={0.0,0.0,1.0};
    s_eye[0]=0;
    s_eye[1]=0;
    s_eye[2]=15;
    
    s_at[0]=0;
    s_at[1]=0;
    s_at[2]=1;
    
//    s_eye[]={0,0,15.0};
//    static GLfloat s_at[]={0.0,0.0,1.0};
    s_angle=-90.0;
    rot1=0;
    rot2=0;
    hlzdegree=-100;
    hlxdegree=0;
    ballx=0;
    bally=0;
    ballz=0;
    flag=true;
    
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
    glutInitWindowSize (1000, 600);
    glutInitWindowPosition(200, 0);
    glutCreateWindow("海绵宝宝");
    texGround = load_texture("/Users/yue/Desktop/Computer Graphics/Pro2/Pro2/ground1.bmp");
    texHMBB_face_front = load_texture("/Users/yue/Desktop/Computer Graphics/Pro2/Pro2/HMBB_face_front.bmp");
    texHMBB_face_back = load_texture("/Users/yue/Desktop/Computer Graphics/Pro2/Pro2/HMBB_face_back.bmp");
    texHMBB_cloth_front = load_texture("/Users/yue/Desktop/Computer Graphics/Pro2/Pro2/HMBB_cloth_front.bmp");
    texHMBB_cloth_back = load_texture("/Users/yue/Desktop/Computer Graphics/Pro2/Pro2/HMBB_cloth_back.bmp");
    texHMBB_sock = load_texture("/Users/yue/Desktop/Computer Graphics/Pro2/Pro2/HMBB_sock.bmp");
    texFront = load_texture("/Users/yue/Desktop/Computer Graphics/Pro2/Pro2/Front.bmp");
    texLeft = load_texture("/Users/yue/Desktop/Computer Graphics/Pro2/Pro2/left.bmp");
    texRight = load_texture("/Users/yue/Desktop/Computer Graphics/Pro2/Pro2/Right.bmp");
    texUp = load_texture("/Users/yue/Desktop/Computer Graphics/Pro2/Pro2/Up.bmp");
    glutDisplayFunc(display);
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