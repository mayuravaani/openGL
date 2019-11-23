#include <iostream>
#include <GL/glut.h>
#include <math.h> 

int ww = 600, wh = 400;
int xi, yi, xf, yf, Y;


int round(double n) {
    return (n > 0.0) ? (n + 0.5) : (n - 0.5); 
}

void drawPixel (int x1, int y1)  
 {  
   glColor3f (1.0, 1.0, 0.0);   
   glBegin (GL_POINTS);  
   glVertex2i (x1, y1); 
   glEnd ();  
   glFlush ();  
 }

void drawLine(int xa,int ya,int xb,int yb){
int dx = abs (xb - xa);  
  int dy = abs (yb - ya);  
  int x, y;  
  if (dx >= dy)  
  {  
   int d = 2*dy-dx;  
   int ds = 2*dy;  
   int dt = 2*(dy-dx);  
       if (xa < xb)   
       {  
            x = xa;  
           y = ya;  
      }  
       else  
       {   
             x = xb;  
             y = yb;  
             xb = xa;  
             yb = ya;  
        }  
       drawPixel(x, y);  
   while (x < xb)  
   {  
        if (d < 0)  
        d += ds;  
        else {  
             if (y < yb) {  
              y++;  
              d += dt;  
             }   
            else {  
             y--;  
              d += dt;  
             }  
           }  
		 x++;  
        drawPixel (x, y);  
   }  
       }  
      else {   
            int d = 2*dx-dy;  
            int ds = 2*dx;  
            int dt = 2*(dx-dy);  
             if (ya < yb) {  
             x = xa;  
             y = ya;  
             }  
             else {   
             x = xb;  
             y = yb;  
             yb = ya;  
            xb = xa;  
            }  
           drawPixel(x, y);   
		   while (y < yb)  
       {  
              if (d < 0)  
                 d += ds;  
              else {  
                     if (x > xb){  
                     x--;  
                      d += dt;  
                  } else {  
                     x++;  
                      d += dt;  
                   }  
              }  
             y++;  
              drawPixel(x, y);  
        }  
       }  
}


void mouse(int btn, int state, int x, int y)
{
	if(btn==GLUT_LEFT_BUTTON ){
		if (state == GLUT_DOWN ) 
		{
			if(Y == 0)  
			{  
          
         xi = x;  
         yi = (wh-y);  
         Y = 1;  
			}  
			else if(Y == 1){  
         xf = x;  
         yf = (wh-y);  
         drawLine ( xi, yi, xf, yf);  
         Y = 0;  
             
        }
		}
	}
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 'q' || key == 'Q')
        exit(0);
	else if (key == 'e' || key == 'E'){
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();
	}
}

void display()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void myinit()
{            
     glViewport(0,0,ww,wh);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluOrtho2D(0.0,(GLdouble)ww,0.0,(GLdouble)wh);
     glMatrixMode(GL_MODELVIEW);	 
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(ww,wh);
	glutCreateWindow("Lines");
	myinit();
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard); 
	glutMainLoop();
     
	return 0;
}