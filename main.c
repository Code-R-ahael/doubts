#include<windows.h>
#include<GL/glut.h>
#include <stdio.h>
#include<math.h>
int x1=-80,x2=0,y3=-80,y2=0;
float u1=0,u2=1;
int xmin=-50,ymin=-50,xmax=50,ymax=50;
int p[4],q[4];
void init()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-320,320,-240,240);
}
void clip(int x1,int y1,int x2,int y2)
{
    printf("check2\n");
    int dx=x2-x1,dy=y2-y1,i;
    double t;
    p[0]=-dx;q[0]=x1-xmin;
    p[1]=dx;q[1]=xmax-x1;
    p[2]=-dy;q[2]=y1-ymin;
    p[3]=dy;q[3]=ymax-y1;
    for(i=0;i<4;i++)
    {
        printf("%d %d\n",p[i],q[i]);
        if(p[i]==0 && q[i]<0)
            return;
        if(p[i]<0)
        {
            printf("check3\n");
            t=(q[i])/(p[i]);printf("%f\n",t);
            if(t>u1 && t<u2)
                {u1=t;printf("%f\n",u1);}
        }
        else if(p[i]>0)
        {
            printf("check4\n");
            t=(q[i])/(p[i]);printf("%f\n",t);
            if(t>u1 && t<u2)
                {u2=t;printf("%f\n",u2);}
        }
    }
    if(u1<u2)
    {
        x1=x1+u1*(x2-x1);
        y1=y1+u1*(y2-y1);
        x2=x1+u2*(x2-x1);
        y2=y1+u2*(y2-y1);
        glBegin(GL_LINES);
        glVertex2i(x1,y1);
        glVertex2i(x2,y2);
    glEnd();
    }
}
void display()
{
    printf("check1\n");
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINES);
        glVertex2i(x1,y3);
        glVertex2i(x2,y2);
    glEnd();
    glFlush();
}
void myKey(unsigned char key,int x,int y)
{
glClear(GL_COLOR_BUFFER_BIT);
    if(key=='c')
    {
        printf("check5\n");
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
        glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINES);
    glVertex2i(-50,-50);
    glVertex2i(-50,50);
    glVertex2i(-50,50);
    glVertex2i(50,50);
    glVertex2i(50,50);
    glVertex2i(50,-50);
    glVertex2i(50,-50);
    glVertex2i(-50,-50);
    glEnd();
    clip(x1,y3,x2,y2);
    glFlush();
    }


}
int main(int argc,char ** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Clip");
    glutDisplayFunc(display);
    glutKeyboardFunc(myKey);
    init();
    glutMainLoop();
    return 0;
}
