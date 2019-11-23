#include <windows.h>
#include <gl/Gl.h>
#include <gl/glut.h>
#include <math.h>

typedef struct {
	float x;
	float y;
} Point;


float rotateX(float x1, float y1, float ang) {
	ang = (ang * 3.14 )/ 180.0;                 //angle in radians  
   int xtemp;
   xtemp = x1 * cos(ang) - y1 * sin(ang);
  
   ang = ang * 180 / 3.14;
  
   return xtemp;
}

float rotateY(float x1, float y1,float ang) {
	ang = (ang * 3.14 )/ 180.0;                 //angle in radians  
   int ytemp;
  
   ytemp = x1 * sin(ang) + y1 * cos(ang);
   ang = ang * 180 / 3.14;

   return ytemp;
}

float tx =0, ty=0; float ang = 0;
void rect(GLfloat x, GLfloat y, GLfloat w, GLfloat h, float xt, float yt)
{
	glRectf(x+xt,y+yt,x+w+xt,y+h+yt);
}

void draw_LowerLeftArm(float xt, float yt)
{
	glBegin(GL_QUADS);
	glVertex2i(121 + xt, 147 + yt);
	glVertex2i(130 + xt, 147 + yt);
	glVertex2i(130 + xt, 172 + yt);
	glVertex2i(121 + xt, 172 + yt);
	glEnd();
	glFlush();
	//rect(121, 147, 9, 25, xt, yt);
}

float trans(float q, float tx) {
	q = q + tx;
	return q;
}
void draw_LeftArm(float xt, float yt)
{

	float transAX = trans(121+xt, -(121+xt));
	float transAY = trans(173 + yt, -(198+ty));

	float transBX = trans(130 + xt, -(121+tx));
	float transBY = trans(173 + yt, -(198+ty));

	float transCX = trans(130 + xt, -(121+tx));
	float transCY = trans(198 + yt, -(198+ty));

	float transDX = trans(121+xt, -(121+tx));
	float transDY = trans(198 + yt, -(198+ty));

	float rotAX =  rotateX(transAX, transAY, ang);
	float rotAY =  rotateY(transAX, transAY, ang);

	float rotBX =  rotateX(transBX, transBY, ang);
	float rotBY =  rotateY(transBX, transBY, ang);

	float rotCX =  rotateX(transCX, transCY, ang);
	float rotCY =  rotateY(transCX, transCY, ang);

	float rotDX =  rotateX(transDX, transDY, ang);
	float rotDY =  rotateY(transDX, transDY, ang);

	 transAX = trans(rotAX, (121+xt));
	 transAY = trans(rotAY,(198+ty));

	transBX = trans(rotBX,(121+tx));
	 transBY = trans(rotBY,(198+ty));

	 transCX = trans(rotCX,(121+tx));
	 transCY = trans(rotCY,(198+ty));

	 transDX = trans(rotDX, (121+tx));
	 transDY = trans(rotDY,(198+ty));

	glBegin(GL_QUADS);
	glVertex2i(transAX, transAY);
	glVertex2i(transBX, transBY);
	glVertex2i(transCX, transCY);
	glVertex2i(transDX, transDY);
	glEnd();
	glFlush();
	
	//rect(121, 173, 9, 25, xt, yt);
	//draw_LowerLeftArm(xt, yt);
}



void rotaee(float ang) {
	//float transX = trans(
}

void draw_LowerRightArm(float xt, float yt)
{	
	rect(50, 147, 9, 25, xt, yt);
}

void draw_RightArm(float xt, float yt)
{
	rect(50, 173, 9, 25, xt, yt);
	//draw_LowerRightArm(xt, yt);
}

void draw_Robot(float xt, float yt)
{
	glColor3f(1.0f, 1.0f, 0.0f);

	rect(70, 200, 40, 30, xt, yt); // head of the robot
	rect(60, 138, 60, 60, xt, yt); // body of the robot

	draw_LeftArm(xt, yt);
	draw_RightArm(xt, yt); 

	rect(70, 86, 19, 50, xt, yt); // left leg of the robot
	rect(91, 86, 19, 50, xt, yt); // right leg of the robot
	
}

void left_rotate(float xt, float yt) {
	rect(121, 173, 9, 25, xt, yt);
	draw_LowerLeftArm(xt, yt);
}


void myDisplay(){
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	draw_Robot(tx, ty);
	
	glFlush();
	glClear(GL_COLOR_BUFFER_BIT);
} 

void special(int key, int, int) {
	switch (key) {
	case GLUT_KEY_LEFT: 
		tx = tx - 5;
	
		ang = ang + 5;
		draw_Robot(tx, ty);
		glFlush();
		glClear(GL_COLOR_BUFFER_BIT);
		break;
	case GLUT_KEY_RIGHT:
		tx = tx + 5;
		if(ang <= 180) {
			ang = ang + 5;
		}
		
		draw_Robot(tx, ty);
		glFlush();
		glClear(GL_COLOR_BUFFER_BIT);
		break;
	case GLUT_KEY_UP:
		ty = ty + 5;
		draw_Robot(tx, ty);
		glFlush();
		glClear(GL_COLOR_BUFFER_BIT);
		break;
	case GLUT_KEY_DOWN: 
		ty = ty - 5;
		draw_Robot(tx, ty);
		glFlush();
		glClear(GL_COLOR_BUFFER_BIT);
		break;
	default: return;
	}
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 'q' || key == 'Q')
        exit(EXIT_SUCCESS);
}

void myMouse(int button, int state, int x, int y) {
	if(state == GLUT_DOWN) 
	{
		if(button == GLUT_LEFT_BUTTON) 
		{
			ang = ang + 5;
		draw_Robot(tx, ty);
		glFlush();
		glClear(GL_COLOR_BUFFER_BIT);
		}
		else if (button == GLUT_RIGHT_BUTTON) 
		{
			 
		}
	}
}

int main( int argc, char ** argv ) {

	glutInit( &argc, argv );
	glutInitWindowPosition( 0, 0 );
	glutInitWindowSize( 800, 600 );
	glutCreateWindow( "Robot" );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluOrtho2D( 0, 800, 0, 600 );
	glViewport(0, 0, 800, 600);
	
	glutKeyboardFunc(keyboard); 
	glutSpecialFunc(special);
	glutMouseFunc( myMouse );
	
	glutDisplayFunc( myDisplay );
	glutMainLoop();

	return( 0 );
}
