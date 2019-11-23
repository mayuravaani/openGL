#include <gl\glut.h>
#include <cmath>

int WinWidth = 500, WinHeight = 500;

typedef struct {
	float x, y;
} Point2D;

typedef struct {
	float x, y, z;
} Point3D;

Point3D A, B, C, D, E, F, G, H, I, J;

void InitCube() {
	A.x = -100, A.y = -100, A.z = 100;
	B.x =  100, B.y = -100, B.z = 100;
	C.x =  100, C.y =  100, C.z = 100;
	D.x = -100, D.y =  100, D.z = 100;

	E.x = -100, E.y = -100, E.z = -100; 
	F.x =  100, F.y = -100, F.z = -100;
	G.x =  100, G.y =  100, G.z = -100;
	H.x = -100, H.y =  100, H.z = -100;

	I.x = 0, I.y = 0, I.z = 0;
}

void drawCube(Point2D A, Point2D B, Point2D C, Point2D D, Point2D E, Point2D F, Point2D G, Point2D H) {
	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
	glVertex2i(A.x, A.y); glVertex2i(B.x, B.y); glVertex2i(C.x, C.y); glVertex2i(D.x, D.y);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex2i(E.x, E.y); glVertex2i(F.x, F.y); glVertex2i(G.x, G.y); glVertex2i(H.x, H.y);
	glEnd();

	glBegin(GL_LINES);
	glVertex2i(A.x, A.y); glVertex2i(E.x, E.y);
	glVertex2i(B.x, B.y); glVertex2i(F.x, F.y);
	glVertex2i(C.x, C.y); glVertex2i(G.x, G.y);
	glVertex2i(D.x, D.y); glVertex2i(H.x, H.y);
	glEnd();
	glFlush();
}

Point2D projectOrthoXY(Point3D p) {
	Point2D temp;
	temp.x = p.x;
	temp.y = p.y;
	return temp;
}

Point3D translate3D(Point3D p, float tx, float ty, float tz) {
	p.x = p.x + tx;
	p.y= p.y + ty;
	p.z = p.z + tz;
	return p;
}

Point3D rotate_y(Point3D p, Point3D q, float ang) {
	ang = ang * 3.14 / 180;
	Point3D temp;
	temp.y = p.y;
	temp.x = p.x * cos(ang) - p.z * sin(ang) + (q.x - (q.x * cos(ang) - q.z * sin(ang)));
	temp.z = p.x * sin(ang) + p.z * cos(ang) + (q.z - (q.x * sin(ang) + q.z * cos(ang)));
	return temp;
}

Point3D rotate_x(Point3D p, Point3D q, float ang) {
	ang = ang * 3.14 / 180;
	Point3D temp;
	temp.x = p.x;
	temp.y = p.y * cos(ang) - p.z * sin(ang) + (q.y - (q.y * cos(ang) - q.z * sin(ang)));
	temp.z = p.y * sin(ang) + p.z * cos(ang) + (q.z - (q.y * sin(ang) + q.z * cos(ang)));
	return temp;
}

void rotatebox_y(float ang) {
	A = rotate_y(A, J, ang);
	B = rotate_y(B, J, ang);
	C = rotate_y(C, J, ang);
	D = rotate_y(D, J, ang);
	E = rotate_y(E, J, ang);
	F = rotate_y(F, J, ang);
	G = rotate_y(G, J, ang);
	H = rotate_y(H, J, ang);
	glutPostRedisplay();
}

void rotatebox_x(float ang) {
	A = rotate_x(A, J, ang);
	B = rotate_x(B, J, ang);
	C = rotate_x(C, J, ang);
	D = rotate_x(D, J, ang);
	E = rotate_x(E, J, ang);
	F = rotate_x(F, J, ang);
	G = rotate_x(G, J, ang);
	H = rotate_x(H, J, ang);
	glutPostRedisplay();
}

void translateRight() {
	A = translate3D(A, 2, 0, 0); 
	B = translate3D(B, 2, 0, 0); 
	C = translate3D(C, 2, 0, 0); 
	D = translate3D(D, 2, 0, 0); 
	E = translate3D(E, 2, 0, 0); 
	F = translate3D(F, 2, 0, 0); 
	G = translate3D(G, 2, 0, 0); 
	H = translate3D(H, 2, 0, 0); 
	I = translate3D(I, 2, 0, 0); 
	J = I;
	glutPostRedisplay();
}

void translateLeft() {
	A = translate3D(A,-2, 0, 0); 
	B = translate3D(B, -2, 0, 0); 
	C = translate3D(C, -2, 0, 0); 
	D = translate3D(D, -2, 0, 0); 
	E = translate3D(E, -2, 0, 0); 
	F = translate3D(F, -2, 0, 0); 
	G = translate3D(G, -2, 0, 0); 
	H = translate3D(H, -2, 0, 0); 
	I = translate3D(I, -2, 0, 0); 
	J = I;
	glutPostRedisplay();
}

void translateUp() {
	A = translate3D(A, 0, 2, 0); 
	B = translate3D(B, 0, 2, 0); 
	C = translate3D(C, 0, 2, 0); 
	D = translate3D(D, 0, 2, 0); 
	E = translate3D(E, 0, 2, 0); 
	F = translate3D(F, 0, 2, 0); 
	G = translate3D(G, 0, 2, 0); 
	H = translate3D(H, 0, 2, 0); 
	I = translate3D(I, 0, 2, 0); 
	J = I;
	glutPostRedisplay();
}

Point3D tran(Point3D p, Point3D r) {
	p.x = p.x - r.x;
	p.y = p.y - r.y;
	p.z = p.z - r.z;
	return p;
}

Point3D tranR(Point3D p, Point3D r) {
	p.x = p.x + r.x;
	p.y = p.y + r.y;
	p.z = p.z + r.z;
	return p;
}

void translateDown() {
	A = translate3D(A, 0, -2, 0); 
	B = translate3D(B, 0, -2, 0); 
	C = translate3D(C, 0, -2, 0); 
	D = translate3D(D, 0, -2, 0); 
	E = translate3D(E, 0, -2, 0); 
	F = translate3D(F, 0, -2, 0); 
	G = translate3D(G, 0, -2, 0); 
	H = translate3D(H, 0, -2, 0); 
	I = translate3D(I, 0, -2, 0); 
	J = I;
	glutPostRedisplay();
}

Point3D zoom(Point3D p, float sx, float sy, float sz) {
	p.x = p.x * sx;
	p.y = p.y * sy;
	p.z = p.z * sz;
	return p;
}

void zoomIn() {
	A = zoom(tran(A, I), 1.5, 1.5, 1.5);
	B = zoom(tran(B, I), 1.5, 1.5, 1.5);
	C = zoom(tran(C, I), 1.5, 1.5, 1.5);
	D = zoom(tran(D, I), 1.5, 1.5, 1.5);
	E = zoom(tran(E, I), 1.5, 1.5, 1.5);
	F = zoom(tran(F, I), 1.5, 1.5, 1.5);
	G = zoom(tran(G, I), 1.5, 1.5, 1.5);
	H = zoom(tran(H, I), 1.5, 1.5, 1.5);

	A = tranR(A, I);
	B = tranR(B, I);
	C = tranR(C, I);
	D = tranR(D, I);
	E = tranR(E, I);
	F = tranR(F, I);
	G = tranR(G, I);
	H = tranR(H, I);
	glutPostRedisplay();
}

void zoomOut() {
	A = zoom(tran(A, I), 0.5, 0.5, 0.5);
	B = zoom(tran(B, I), 0.5, 0.5, 0.5);
	C = zoom(tran(C, I), 0.5, 0.5, 0.5);
	D = zoom(tran(D, I), 0.5, 0.5, 0.5);
	E = zoom(tran(E, I), 0.5, 0.5, 0.5);
	F = zoom(tran(F, I), 0.5, 0.5, 0.5);
	G = zoom(tran(G, I), 0.5, 0.5, 0.5);
	H = zoom(tran(H, I), 0.5, 0.5, 0.5);

	A = tranR(A, I);
	B = tranR(B, I);
	C = tranR(C, I);
	D = tranR(D, I);
	E = tranR(E, I);
	F = tranR(F, I);
	G = tranR(G, I);
	H = tranR(H, I);
	glutPostRedisplay();
}

void special(int key, int x, int y) {
	switch(key) {
	case GLUT_KEY_RIGHT :
		rotatebox_y(1);
		break;
	case GLUT_KEY_LEFT :
		rotatebox_y(-1);
		break;
	case GLUT_KEY_UP :
		rotatebox_x(1);
		break;
	case GLUT_KEY_DOWN :
		rotatebox_x(-1);
		break;
	}
}

void keyboard(unsigned char key, int x, int y) {
	switch(key) {
	case 'd' :
		translateRight();
		break;
	case 'a' :
		translateLeft();
		break;
	case 'w' :
		translateUp();
		break;
	case 'z' :
		translateDown();
		break;
	}
}

void myMouse(int btn, int state, int x, int y) {
	if(state == GLUT_DOWN) {
		if(btn == GLUT_LEFT_BUTTON) {
			zoomIn();
		}
		else if(btn == GLUT_RIGHT_BUTTON) {
			zoomOut();
		}
	}
}

void myDisplay() {
	glClearColor(0.0, 0.0, 0.0, 0.1);
	glColor3f(5.0, 3.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	drawCube(projectOrthoXY(A), projectOrthoXY(B), projectOrthoXY(C), projectOrthoXY(D), projectOrthoXY(E), projectOrthoXY(F), projectOrthoXY(G), projectOrthoXY(H));
	//glFlush();
}

int main( int argc, char ** argv ) {
	glutInit( &argc, argv );
	glutInitWindowPosition( 0, 0 );
	glutInitWindowSize( WinWidth, WinHeight );
	glutCreateWindow( "Projection of a Cube" );
	glMatrixMode( GL_PROJECTION ); 
	glLoadIdentity();
	gluOrtho2D( 0, WinWidth, 0, WinHeight );
	glViewport(0, 0, WinWidth, WinHeight);
	InitCube();
	glutKeyboardFunc(keyboard); 
	glutSpecialFunc(special);
	glutMouseFunc( myMouse );
	glutDisplayFunc( myDisplay );
	glutMainLoop();
	return 0;
}
