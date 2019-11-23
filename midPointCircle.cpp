#include <gl\glut.h>
#include <cmath>
#include <iostream>

using namespace std;

int xi, yi, ox, oy, xf, yf;
int ww = 600, wh = 400;
float intCol[3] = {0.0, 0.0, 0.0}, fillCol[3]={5,3,0}, borderCol[3]= {2,2,5};
int radious;
void drawLine(GLint x1, GLint y1, GLint x2, GLint y2)
{	
	//glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(2.0);

	glBegin(GL_LINES);
		glVertex2i(x1, y1);
		glVertex2i(x2, y2);
	glEnd();
	glFlush();
}

void putPixel(int x, int y, float f[]) {
	glColor3fv(f);
	glBegin(GL_POINTS);
		glVertex2i(x, y);
	glEnd();
	glFlush();
}

void getPixels(int x, int y, float f[]) {
	glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, f);
}

void ddaLine(int x1, int y1, int x2, int y2) {
	int dx = x2 -x1, dy = y2 - y1, steps;
	float Xincrement, Yincrement, x = x1, y = y1;
	if(abs(dx) > abs(dy)) {
		steps = abs(dx);
	}
	else {
		steps = abs(dy);
	}
	Xincrement = dx/(float)steps;
	Yincrement = dy/(float)steps;
	putPixel(x, y, fillCol);
	for(int k=0; k<steps; k++) {
		x += Xincrement;
		y += Yincrement;
		putPixel(x, y, fillCol);
	}
}

void fillCircle() {

}

void floodFill(int x, int y, float oldColor[3], float newColor[3]) {
	float ic[3];
	getPixels(x, y, ic);
	if((ic[0] == oldColor[0] ) && (ic[1] == oldColor[1]) && (ic[2] == oldColor[2])) {
		putPixel(x, y, newColor);
		floodFill(x+1, y, oldColor, newColor);
		floodFill(x-1, y, oldColor, newColor);
		floodFill(x, y+1, oldColor, newColor);
		floodFill(x, y-1, oldColor, newColor);
	}
}

void midPointCircle(int r, int ox, int oy) {
	int x = 0, y = r, p = 1 - r;
	while(x <= y) {
		putPixel( x + ox,  y + oy, borderCol);
		putPixel( y + ox,  x + oy, borderCol);
		putPixel( x + ox, - y + oy, borderCol);
		putPixel( y + ox,  - x + oy, borderCol);
		putPixel( - x + ox,  y + oy, borderCol);
		putPixel(- x + ox, - y + oy, borderCol);
		putPixel(- y + ox,  x + oy, borderCol);
		putPixel( - y + ox,  - x + oy, borderCol);
		if(p < 0) {
			p = p + 2 * x + 3;
		}
		else {
			p = p + 2 * (x - y) + 5;
			y--;
		}
		x++;
	}
	 x = 0, y = r, p = 1 - r;
	while(x<=y) {
		ddaLine(ox, oy, x + ox,  y + oy);
		ddaLine(ox, oy, y + ox,  x + oy);
		ddaLine(ox, oy, x + ox, - y + oy);
		ddaLine(ox, oy, y + ox,  - x + oy);
		ddaLine(ox, oy, - x + ox,  y + oy);
		ddaLine(ox, oy, - x + ox, - y + oy);
		ddaLine(ox, oy, - y + ox,  x + oy);
		ddaLine(ox, oy,  - y + ox,  - x + oy);
		if(p < 0) {
			p = p + 2 * x + 3;
		}
		else {
			p = p + 2 * (x - y) + 5;
			y--;
		}
		x++;
	}
}

void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glColor3f(0.5, 0.3, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void mouse(int btn, int state, int x, int y) {
	if(btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		xi = x;
		yi = wh - y;
		ox = x;
		oy = wh -y;
		//midPointCircle(yi, ox, oy);
	}
	else if( btn == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
		xf = x;
		yf = wh - y;
		float num = (yf - yi)^ 2 + (xf - xi)^2;
			radious = sqrt(num);
			cout << radious;
			midPointCircle(yf, ox, oy);
	}
	else if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		floodFill(x, wh - y, intCol, fillCol);
	}
}

void myinit()  {  
	glViewport(0,0,ww,wh);  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();  
    gluOrtho2D(0.0,(GLdouble)ww,0.0,(GLdouble)wh);  
    glMatrixMode(GL_MODELVIEW);  
 }  

int main(int argc,char** argv)  {  
	glutInit(&argc,argv);  
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
    glutInitWindowSize(ww,wh);  
	glutCreateWindow("MidPoint-Circle");  
    glutDisplayFunc(display);  
	myinit();  
    glutMouseFunc(mouse); 
	glutMainLoop();  
    return 0;  
 } 