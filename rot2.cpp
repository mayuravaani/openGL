#include<gl\glut.h>
#include<cmath>

typedef struct {
	float x;
	float y;
} Point2D;

Point2D p1, p2;

void display() {
	p1.x = 0;
	p2.x = 0;
	glClearColor(1.0f,1.0f,1.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void drawLine(Point2D p) {
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_LINES);
	glVertex2i(p1.x, p1.y);
	glVertex2i(p.x, p.y);
	glEnd();

	glPointSize(6.0);
    glBegin(GL_POINTS);
    glVertex2i(p.x, p.y);
	glEnd();
	glFlush();
}

Point2D rotate(Point2D p, float ang) {
	ang = (ang * 3.14) / 180;
	Point2D ptemp;
	ptemp.x = p.x * cos(ang) - p.y * sin(ang);
	ptemp.y = p.x * sin(ang) + p.y * cos(ang);
	return ptemp;
}

void mouse(int btn, int state, int x, int y) {
	if(state == GLUT_DOWN) {
		if(btn == GLUT_LEFT_BUTTON) {
			 p2.x = x; p2.y = 600 - y;
			drawLine(p2);
		}
		else if( btn == GLUT_RIGHT_BUTTON) {
			p2 = rotate(p2, 30);
			drawLine(p2);
		}
	}
	glClear(GL_COLOR_BUFFER_BIT);
}

int main( int argc, char ** argv ) {
       glutInit( &argc, argv );
       glutInitWindowPosition( 0, 0 );
       glutInitWindowSize( 800, 600 );
       glutCreateWindow( "My Drawing Screen" );
	   glMatrixMode( GL_PROJECTION );
       glLoadIdentity();
       gluOrtho2D( 0, 800, 0, 600 );
       glViewport(0, 0, 800, 600);
	   glutMouseFunc( mouse );
       glutDisplayFunc( display );
	   glutMainLoop();
       return 0 ;
}