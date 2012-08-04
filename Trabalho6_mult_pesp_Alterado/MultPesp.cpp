#include <GL/glut.h>    
#include <cstdlib>      
#include <cstdio> 
#include "ThreeMaxLoader.h"
#include "StdAfx.h"
     

const int WINDOW_WIDTH = 600; 
const int WINDOW_HEIGHT = 500;

//variaveis de panning
GLdouble ea=0;
GLdouble eb=0;
GLdouble ez=0;

//variaveis de zoom
GLdouble manObj=1;
obj_type object;

GLint plar=250;
GLint palt=250;

void onInit()
{
    glClearColor(0.0, 0.0, 0.0, 0.0); 
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light0pos[4] = {0.0, 0.0, -1, 1.0};
    GLfloat light0dir[4] = {0.0, 0.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0dir);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);
    //glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void desenha_img(){
     glColor3f(1,0,0);
    glLineWidth(2);
	//glTranslatef(0,30,0);
	//glRotatef(-90,1,0,0);
	glutWireCone(30, 30, 10, 8);
	//glTranslatef(0,-50,0);
	glutWireCube(30);
}

void desenha_quadrante(double angle, double x, double y, double z){
    glPushMatrix();
        glTranslated(ea,eb,ez);
        glRotatef(angle,x,y,z);
        //glutSolidCube(0.41*manObj); 
        glutSolidCube(0.36*manObj); 
        glutSolidTeapot(0.25*manObj);
        glutSolidCube(0.36*manObj); 
        
    glPopMatrix();

}

void onRedraw(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0,0,250,250);
    glColor3f(0.4,0.2,0.5);
    desenha_quadrante(0,0,0,0);

    glViewport(0,250,250,250);
    glColor3f(1,0,0);
    desenha_quadrante(180,0,1,1);

    glViewport(250,0,250,250);
    glColor3f(0,1,0);
    desenha_quadrante(90,0,1,0);

    glViewport(250,250,250,250);
    glColor3f(0.3,0.2,0.7);
    desenha_quadrante(30,1,1,1);
    
    glutSwapBuffers();
}


void onRedraw_1(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0,0,plar,palt);
    glColor3f(0.4,0.2,0.5);
    desenha_quadrante(0,0,0,0);

    glViewport(0,palt,plar,palt);
    glColor3f(1,0,0);
    desenha_quadrante(180,0,1,1);

    glViewport(plar,0,plar,palt);
    glColor3f(0,1,0);
    desenha_quadrante(90,0,1,0);

    glViewport(plar,palt,plar,palt);
    glColor3f(0.3,0.2,0.7);
    desenha_quadrante(30,1,1,1);
    
    glutSwapBuffers();
}


void keyboard(unsigned char key, int c, int d)
{
     //Panning A/a=esquerda; d/D=direita;  s/S=baixo e w/W=alto
     if(key==65 || key==97){        
           ea-=0.05;
     }
     if (key==68 || key==100 ){
           ea+=0.05;
     }
     if (key==87 || key==119 ){
           eb+=0.05;
     }
     if (key==83 || key==115 ){
           eb-=0.05;
     }
     //Zoom f/F aumenta e g/G diminui
     if(manObj<3){
         if(key=='f' || key=='F'){
           manObj+=0.7; 
         }      
     }      
     if(manObj>1){
        if(key=='g' || key=='G'){
           manObj-=0.7; 
         }      
     }
     
   switch (key) {
      case 27:
         exit(0);
         break;        
   }
         glutPostRedisplay();                   
}


void onResize_1 (int width, int height)
{  
    GLfloat r=1.5; 
    GLfloat asp=width/height;
     
    if(r>asp){
        plar = GLint ((width)/4);
        palt = GLint ((width)/4*r);
    }else{
        plar = GLint ((height*r)/4);
        palt = GLint ((height)/4);
         
    }

    onRedraw_1();
              
   //glViewport(0, 0, GLint(width), GLint(height));
}
void onResize (int width, int height)
{  
   glViewport(0, 0, GLint(width), GLint(height));
}

int main (int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutCreateWindow(argv[0]);
    onInit();
//  glutDisplayFunc(onRedraw_1);
//  glutReshapeFunc(onResize);
    glutDisplayFunc(onRedraw);
    glutReshapeFunc(onResize);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
