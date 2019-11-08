#include<gl\glut.h>
int ww=600, wh=400;
int first=0;
int xi,yi,xf,yf;

void init() {
	glViewport(0,0,ww,wh);  
    glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();  
    gluOrtho2D(0.0,(GLdouble)ww,0.0,(GLdouble)wh);  
    glMatrixMode(GL_MODELVIEW);
}

void drawLine(int x1, int y1, int x2, int y2) {
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(5);
	glBegin(GL_LINES);
		glVertex2i(x1,y1);
		glVertex2i(x2,y2);
	glEnd();
	glFlush();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(5.0);
	glBegin(GL_LINES);
		glColor3f(1.0,1.0,0.0);
		glVertex2f(0.5,0.5);
		glVertex2f(-0.5,0.5);
	glEnd();
	glFlush();
}

void mouse(int btn, int state, int x, int y) {
	if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		switch(first) {
		case 0 : 
			xi = x;
			yi = wh - y;
			first = 1;
			break;
		case 1 :
			xf = x;
			yf = wh -y;
			drawLine(xi, yi, xf, yf);
			first = 0;
			break;
		}
	}
}

int main(int argc, char** argv) {
	glutInit(&argc,argv);  
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
    glutInitWindowSize(ww,wh);  
    glutCreateWindow("Draw Line With Mouse Click");  
    glutDisplayFunc(display);  
    init();  
    glutMouseFunc(mouse);  
    glutMainLoop();  
    return 0;
}
