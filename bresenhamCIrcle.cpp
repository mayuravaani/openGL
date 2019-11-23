#include <gl\glut.h>

int ww = 600, wh = 400;
int xi, yi;
float borderCol[3] = {0.0, 0.0, 0.0}, fillCol[3] = {0.5, 0.3, 0.0};
int tx = 0, ty = 0;

void putPixel(int x, int y, float f[3]) {
	glColor3fv(f);
	glPointSize(1);
	glBegin(GL_POINTS);
		glVertex2i(x, y);
	glEnd();
	glFlush();
}

void translate(int x, int y, int tx, int ty) {
	x = x + tx;
	y = y + ty;
}

void getPixels(int x, int y, float f[3] ) {
	glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, f);
}

void boundaryFill(int x, int y, float fillCol[3], float borderCol[3]) {
	float interCol[3];
	getPixels(x, y, interCol);
	if((interCol[0] != borderCol[0]) && (interCol[1] != borderCol[1]) && (interCol[2] != borderCol[2]) &&
		(interCol[0] != fillCol[0]) && (interCol[1] != fillCol[1])  && (interCol[2] != fillCol[2])) {
			putPixel(x, y, fillCol);
			boundaryFill(x-1, y, fillCol, borderCol);
			boundaryFill(x+1, y, fillCol, borderCol);
			boundaryFill(x, y-1, fillCol, borderCol);
			boundaryFill(x, y+1, fillCol, borderCol);
	}

}

void bresenhamCircle(int r, int xt, int yt) {
	int x = 0, y = r, d = 2 - 3 * r;
	while(x <= y) {
		putPixel(100+x+xt, 100+y+yt, borderCol);
		putPixel(100+y+xt, 100+x+yt, borderCol);
		putPixel(100-x+xt, 100+y+yt, borderCol);
		putPixel(100-x+xt, 100-y+yt, borderCol);
		putPixel(100-y+xt, 100+x+yt, borderCol);
		putPixel(100-y+xt, 100-x+yt, borderCol);
		putPixel(100+y+xt, 100-x+yt, borderCol);
		putPixel(100+x+xt, 100-y+yt, borderCol);
		if(d < 0) {
			d = d + (4 * x) + 6;
		}
		else {
			d = d + (4 * (x - y)) +10;
			y--;
		}
		x++;
	}
}

void display() {
	glClearColor(0.6, 0.8, 0.1, 0.1);
	//glColor3f(0.5, 0.3, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void mouse(int btn, int state, int x, int y) {
	if(btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		xi = 0;
		yi = wh - y;
		bresenhamCircle(yi, tx, ty);
		putPixel(100+tx, 100+ty, borderCol);
	}
	else if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		boundaryFill(x, wh-y, fillCol, borderCol);
	}
}

void special(int key, int x, int y) {
	if(key == GLUT_KEY_RIGHT) {
		tx = tx + 3;
		glClear(GL_COLOR_BUFFER_BIT);
		bresenhamCircle(yi, tx, ty);
		putPixel(100+tx, 100+ty, borderCol);
	}
	else if(key == GLUT_KEY_LEFT) {
		tx = tx - 3;
		glClear(GL_COLOR_BUFFER_BIT);
		bresenhamCircle(yi, tx, ty);
	}
	else if(key == GLUT_KEY_UP) {
		ty = ty + 3;
		glClear(GL_COLOR_BUFFER_BIT);
		bresenhamCircle(yi, tx, ty);
	}
	else if(key == GLUT_KEY_DOWN) {
		ty = ty - 3;
		glClear(GL_COLOR_BUFFER_BIT);
		bresenhamCircle(yi, tx, ty);
	}
}

void myinit()  
  {  
       glViewport(0,0,ww,wh);  
       glMatrixMode(GL_PROJECTION);  
       glLoadIdentity();  
       gluOrtho2D(0.0,(GLdouble)ww,0.0,(GLdouble)wh);  
       glMatrixMode(GL_MODELVIEW);  
 }  
  int main(int argc,char** argv)  
{  
       glutInit(&argc,argv);  
       glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
       glutInitWindowSize(ww,wh);  
       glutCreateWindow("Bresenham-Circle");  
       glutDisplayFunc(display);  
       myinit();  
       glutMouseFunc(mouse); 
	   glutSpecialFunc(special);
       glutMainLoop();  
       return 0;  
 } 