#include <GL/glut.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

GLint xpt = 0;
GLint ypt = 0;


GLint ea= 0;
GLint eb= 0;


GLsizei rsize = 20;
GLsizei rsizeInit = 20;

GLint windowWidth = 350;
GLint windowHeight = 350;

GLint domCena_x =350;
GLint domCena_y =350;

GLint vp_x=350;
GLint vp_y=350;


GLint xstep = 1;
GLint ystep = 1;

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);       
}

void cria_imagens (void) 
{
     glClear (GL_COLOR_BUFFER_BIT);
     //glViewport(0, 0, windowWidth, windowHeight);
     glViewport(0, 0, vp_x, vp_y); 
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     //gluOrtho2D(ea, windowWidth+ea, eb, windowHeight+eb);
     gluOrtho2D(ea, 300+ea, eb, 300+eb);
     glColor3f( 0, 1, 0 );
     glRectf(0.0,0.0,350.0,350.0);
     
     //gluOrtho2D (xpt, ypt, eb, ea);
     glColor3f( 0, 0, 1 );
     glRectf(0.0,0.0,350.0,190.0);
     glColor3f( 1, 0, 0);
     glRectf(0.0,100.0,350.0,250.0);
          glColor3f(1.0, 0.0, 1.0);
          glBegin(GL_QUADS);
               glVertex2i(xpt,ypt+rsizeInit); 
               glVertex2i(xpt,ypt);
               glVertex2i(xpt+rsizeInit,ypt);
                glColor3f(0.0f, 1.0f, 1.0f);
               glVertex2i(xpt+rsizeInit,ypt+rsizeInit);               
     glEnd();
     glFlush();
}

void Timer(int value){
     xpt += xstep;
     ypt += ystep;
      if(xpt > windowWidth-rsize || xpt < 0)
            xstep = -xstep;

    if(ypt > windowHeight-rsize || ypt < 0)
          ystep = -ystep;
          
   if(xpt > windowWidth-rsize)
         xpt = windowWidth-rsize-1;

   if(ypt > windowHeight-rsize)
         ypt = windowHeight-rsize-1;

    glutPostRedisplay();
    glutTimerFunc(25,Timer, 1);
}


void reshape (int w, int h)
{
   if(w<h){
        vp_x=w;
        vp_y=w;           
   }else
        vp_x=h;
        vp_y=h;
   
   //if(h == 0)  
     //   h = 1;
   //if (w==0)
     //   w=1;
         
   //glViewport(0, 0, w, h);
   //verificando a razão de espectro
   //float razao_espec=0;
   //if (w <= h){
      //windowHeight
      //razao_espec=h/w;
      //windowHeight=h*razao_espec;
      //gluOrtho2D (0.0f, windowWidth, 0.0f, windowHeight*razao_espec);
      //gluOrtho2D (0.0f, w, 0.0f, h*razao_espec);
   //}else {
      //razao_espec=w/h;
      //windowWidth=w*razao_espec;
      //gluOrtho2D (0.0f, w*razao_espec, 0.0f, h);   
   //}
}

void keyboard(unsigned char key, int c, int d)
{
     if(key==65 || key==97){        
           ea-=5;
     }
     if (key==68 || key==100 ){
           ea+=5;
     }
     if (key==87 || key==119 ){
           eb+=5;
     }
     if (key==83 || key==115 ){
           eb-=5;
     }
   switch (key) {
      case 27:
         exit(0);
         break;        
   }
         glutPostRedisplay();                   
}


int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (350, 350); 
   glutInitWindowPosition (10, 10);
   glutCreateWindow ("Desenhando Imagem");
   init ();
   glutDisplayFunc(cria_imagens);
   glutTimerFunc(25, Timer, 1); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
