#include<gl\glut.h>
#include<cmath>
#include<iostream>
using namespace std;
typedef struct {
	float x;
	float y;
} Point;

float ang = 30;
Point p1, p2, p3;

void display() {
}

void drawLine(Point p1, Point p2, Point p3) {
	glBegin(GL_LINES);
	glVertex2i(p1.x, p1.y);
	glVertex2i(p2.x, p2.y);

	glVertex2i(p1.x, p1.y);
	glVertex2i(p3.x, p3.y);
	glEnd();
	glPointSize(6);
	glBegin(GL_POINTS);
	glVertex2i(p1.x, p1.y);
	glEnd();
	glFlush();
}

Point rotate(Point p, Point c, float angle) {
   ang = (ang * 3.14 )/ 180.0;                 //angle in radians  
   Point ptemp;  ptemp.x = 0; ptemp.y =0;
   ptemp.x = p.x * cos(ang) - p.y * sin(ang)+(c.x- cos(ang)*c.x +sin(ang)*c.y);  
   ptemp.y = p.x * sin(ang) + p.y * cos(ang)+(c.y- sin(ang)*c.x-cos(ang)*c.y); 
   ang = ang * 180 / 3.14;
   return ptemp;  
}

void myDisplay(){

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
}
 
void mouse(int btn, int state, int a, int b) {
	if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		p1.x = 0;
		p1.y = 0;
		p2.x = 150;
		p2.y = 0;
		p3.x = -150;
		p3.y = 0;
		drawLine(p1, p2, p3);
	}
	else if(btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		p3 = rotate(p3, p1, ang);
		p2 = rotate(p2, p1, ang);
		drawLine(p1, p2, p3);
	}
	glClear(GL_COLOR_BUFFER_BIT);
}

int main( int argc, char ** argv ) {
       glutInit( &argc, argv );
       glutInitWindowPosition( -400, -400 );
       glutInitWindowSize( 800, 600 );
       glutCreateWindow( "My Screen" );
	   glMatrixMode( GL_PROJECTION );
       glLoadIdentity();
       gluOrtho2D( -400, 800, -400, 600 );
       glViewport(-400, -400, 800, 600);
	   glutDisplayFunc( myDisplay);
       glutMouseFunc(mouse);
       glutMainLoop();
       return 0 ;
}