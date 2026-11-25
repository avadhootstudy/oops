#include<GL/glut.h>
#include<cmath>
using namespace std;

int ch=0;

void init(void){
    glClearColor(1.0,1.0,1.0,1.0);  //sets background color white
    glColor3f(0.0,0.0,0.0);         //sets drawing color black
    glPointSize(2.0);               //sets point size
    glMatrixMode(GL_PROJECTION);    
    glLoadIdentity();               //replaces current matrix with unit matrix
    gluOrtho2D(-320,320,-240,240);  //define left ,right, bottom ,top(2 dimensional) parameter of window
}

void dda(int x1, int y1, int x2, int y2){
    int dx=x2-x1;
    int dy=y2-y1;
    int length;
    if(abs(dx)>abs(dy)){
       length=dx;
    }else{
       length=dy;
    }
    
    float DX=dx/float(length);
    float DY=dy/float(length);
    float x=x1;
    float y=y1;
    
     
    for(int i=0;i<=length;i++){
    glBegin(GL_POINTS);                
       glVertex2f(round(x),round(y));  
       x+=DX;
       y+=DY;
       glEnd();                      
       
    }
    glFlush();                       
    
    
}

void axisPlot(){
     for(int i=-320;i<320;i++){  
        glBegin(GL_POINTS);
        glVertex2f(i,0);
        glEnd();
     }
     for(int i=-240;i<240;i++){  
        glBegin(GL_POINTS);
        glVertex2f(0,i);
        glEnd();
     }
     
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    axisPlot();
    switch(ch){
    case 1:
       dda(-300,50,-100,100);  
       break;
       
       case 2:
       
       dda(20,40,70,40);
       dda(70,40,70,90);
       dda(70,90,120,90);
       dda(120,40,120,90);
       dda(120,40,170,40);
       dda(170,40,170,90);
       dda(170,90,220,90);
       dda(220,40,220,90);
       dda(220,40,270,40);
       break;
       
       case 3:
       
       dda(20,-100,50,-10);
       dda(80,-100,50,-10);
       dda(80,-100,110,-10);
       dda(140,-100,110,-10);
       dda(140,-100,170,-10);
       dda(200,-100,170,-10);
       break;
       
       case 4:
       
       dda(-200,-100,-200,-50);  
       dda(-200,-50,-140,-100);
       dda(-140,-100,-140,-50);
       dda(-140,-50,-80,-100);
       dda(-80,-100,-80,-50);
       dda(-80,-50,-20,-100);
       break;
    }
    glFlush();
    glutSwapBuffers();          

void menu(int option){
   switch(option){
     case 1:
     ch=1;
     break;
     
     case 2:
     ch=2;
     break;
     
     case 3:
     ch=3;
     break;
     
     case 4:
     ch=4;
     break;
   }
   glutPostRedisplay();    
 }

int main(int argc, char** argv){
   glutInit(&argc,argv);      
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  
   glutInitWindowSize(640,480);                  
   glutInitWindowPosition(100,100);              
   glutCreateWindow("DDA Line Drawing Algorithm");  
   init();                                         
   glutCreateMenu(menu);                       
   glutAddMenuEntry("Simple line",1);            
   glutAddMenuEntry("Square Wave",2);           
   glutAddMenuEntry("Triangular wave 1",3);   
   glutAddMenuEntry("Triangular wave 2",4);     
   glutAttachMenu(GLUT_RIGHT_BUTTON);           
   glutDisplayFunc(display);                    
   glutMainLoop();                             
   return 0;
}