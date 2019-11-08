#include<gl\glut.h>
#include<Windows.h>

int ww = 600, wh = 400;
int xi, yi, xf, yf, first = 0;

void init() {
	glViewport(0,0,ww,wh);  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();  
    gluOrtho2D(0.0,(GLdouble)ww,0.0,(GLdouble)wh);  
    glMatrixMode(GL_MODELVIEW);  
}

void display(void) {
	glColor3f(0.2, 0.3, 0.3);  
	glClear(GL_COLOR_BUFFER_BIT);  
	glFlush();  
}

void putPixel(int x, int y) {
	glColor3f (0.3, 0.2, 0.0);
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

void ddaLineAlgo(int x1, int y1, int x2, int y2) {
	int dx = x2 - x1, dy = y2 - y1, steps;
	float xIncrement, yIncrement, x = x1, y = y1;
	if(abs(dx) > abs(dy)) {
		steps = abs(dx);
	} 
	else {
		steps =	abs(dy);
	}
	xIncrement = dx/(float)steps;
	yIncrement = dy/(float)steps;
	putPixel(x, y);
	for(int k = 0; k < steps; k++) {
		x += xIncrement;
		y += yIncrement;
		putPixel(x, y);
	}
}

void mouse(int btn, int state, int x, int y) {
	if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		switch(first) {
		case 0: 
			xi = x;
			yi = wh - y;
			first = 1;
			break;
		case 1:
			xf = x;
			yf = wh - y;
			ddaLineAlgo(xi, yi, xf, yf);
			first  = 0;
			break;
		}
	} 
}

int main(int argc, char** argv) {
	glutInit(&argc,argv);  
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);  
    glutInitWindowSize(ww,wh);  
    glutCreateWindow("DDA Line Algorithm");  
    glutDisplayFunc(display);  
    init();  
    glutMouseFunc(mouse);  
    glutMainLoop();  
    return 0;  
}