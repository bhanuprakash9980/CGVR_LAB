#include <gl/glut.h>
#include <iostream>

float wid1, wid2, t;
static GLfloat spin = 0.0;

void display1()
{
	glutSetWindow(t);
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glLoadIdentity();
	glRotatef(spin, 0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-0.25, -0.25, 0.25);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.25, -0.25, 0.25);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.25, 0.25, 0.25);
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(-0.25, 0.25, 0.25);
	glEnd();
	glPopMatrix();
	if (t == wid1)
	{
		glFlush();
		t = wid2;
	}
	else
	{
		glutSwapBuffers();
		t = wid1;
	}
}

void spindisplay()
{
	spin += 0.02;
	glutPostRedisplay();
}

void mouse1(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON: if (state == GLUT_DOWN) glutIdleFunc(spindisplay);
		break;
	case GLUT_RIGHT_BUTTON: if (state == GLUT_DOWN) glutIdleFunc(NULL);
		break;
	default:
		break;
	}
}

void myInit()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	wid1 = glutCreateWindow("Single");
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutDisplayFunc(display1);
	glutMouseFunc(mouse1);
	glutInitWindowSize(500, 500);
	wid2 = glutCreateWindow("Double");
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	t = wid1;
	glutDisplayFunc(display1);
	glutMouseFunc(mouse1);
	myInit();
	glutMainLoop();
}
