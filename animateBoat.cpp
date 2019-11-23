
#include <windows.h>
#include <gl/Gl.h>
#include <gl/glut.h>
#include <cmath>

int screenheight = 600;
int screenwidth = 1200;
int newY = 0, newX = 0;
float ang = 0;

void Paddle(){
	float x1 = 105+ newX;
	float y1 = -50 + newY;
	float x2 = 115+ newX;
	float y2 = 90 + newY;
	float x0 = x1 + 0.5 * (x2 - x1);
	float y0 = y1 + 0.5 * (y2 - y1);

	ang = (ang * 3.14 )/ 180;
	
	float translateX1 = x1 - x0;
	float translateY1 = y1 - y0;
	float translateX2 = x2 - x0;
	float translateY2 = y2 - y0;

	float rotateX1 = translateX1 * cos(ang) - translateY1 * sin(ang);
	float rotateY1 = translateX1 * sin(ang) + translateY1 * cos(ang);

	float rotateX2 = translateX2 * cos(ang) - translateY2 * sin(ang);
	float rotateY2 = translateX2 * sin(ang) + translateY2 * cos(ang);
	float rotateX3 = translateX2 * cos(ang) - translateY1 * sin(ang);
	float rotateY3 = translateX2 * sin(ang) + translateY1 * cos(ang);
	float rotateX4 = translateX1 * cos(ang) - translateY2 * sin(ang);
	float rotateY4 = translateX1 * sin(ang) + translateY2 * cos(ang);


	glColor3d(1,1,0);
	glBegin(GL_QUADS);
		glVertex2f(rotateX1 + x0, rotateY1 + y0);
		glVertex2f(rotateX3 + x0, rotateY3 + y0);
		glVertex2f(rotateX2 + x0, rotateY2 + y0);
		glVertex2f(rotateX4 + x0, rotateY4 + y0);
	glEnd();
	glFlush();

	ang = ang * 180 / 3.14;

	
	//glRectf(105+ newX,-50 + newY,115+ newX,90 + newY);
}

void Bolt(){
	glColor3d(0,0,1);
	glRectf(102 + newX,newY + 12,118 + newX,newY + 18);
}

void Building(){
	glColor3d(1,0,0);
	glRectf(500,210,600,400);
}

void Boat(){
	glBegin(GL_QUADS);
	glColor3d(0,1,0);
	glVertex2f(20 + newX, newY + 0);
	glVertex2f(0 + newX, newY + 30);
	glVertex2f(220 + newX, newY + 30);
	glVertex2f(200 + newX, newY + 0);
	glEnd();
}

void myDisplay(){
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	Building();
	Boat();
	Paddle();
	Bolt();

	glFlush();
} 

void special(int key, int, int) {
	switch (key) {
		case GLUT_KEY_LEFT: newX = newX - 3; ang = ang - 5;break;
		case GLUT_KEY_RIGHT: newX = newX + 3; ang = ang + 5; break;

		case GLUT_KEY_UP: if (newY >= 0) newY = newY + 3; break;
		case GLUT_KEY_DOWN: if (newY <= 400) newY = newY - 3;  break;

		default: return;
	}
	glutPostRedisplay();
}

int main( int argc, char ** argv ) {

	glutInit( &argc, argv );
	glutInitWindowPosition( 0, 0 );
	glutInitWindowSize( screenwidth, screenheight );
	glutCreateWindow( "Boat" );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluOrtho2D( 0, screenwidth, 0, screenheight );
	glViewport(0, 0, screenwidth, screenheight);
	glutDisplayFunc( myDisplay );

	glutSpecialFunc(special);
	glutMainLoop();

	return( 0 );
}