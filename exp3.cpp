#include <GL/glut.h>

#define WINSIZE 500
int wid1 = 0, wid2 = 0, cur_wid = 0;
static GLfloat spinValue = 0.0;

void display();
void spin();
void mousefunc(int, int, int, int);
void init();

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	//glEnable(GL_DEPTH_TEST);
	glutInitWindowSize(WINSIZE, WINSIZE);
	wid1 = glutCreateWindow("Single");
	glutDisplayFunc(display);
	glutMouseFunc(mousefunc);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	//glEnable(GL_DEPTH_TEST);
	glutInitWindowSize(WINSIZE, WINSIZE);
	wid2 = glutCreateWindow("Double");
	glutDisplayFunc(display);
	glutMouseFunc(mousefunc);

	cur_wid = wid1;
	init();

	glutMainLoop();

	return 0;
}

void init() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glColor3f(1.0f, 0.0f, 0.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	return;
}

void mousefunc(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		button == GLUT_LEFT_BUTTON ? glutIdleFunc(spin) : glutIdleFunc(NULL);
	}
	return;
}

void spin() {
	spinValue += 0.02;
	glutPostRedisplay();
	return;
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSetWindow(cur_wid);
	glPushMatrix();
	glLoadIdentity();

	glRotatef(spinValue, 0.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
	glVertex3f(-0.25f, -0.25f, 0.25f);
	glVertex3f(0.25f, -0.25f, 0.25f);
	glVertex3f(0.25f, 0.25f, 0.25f);
	glVertex3f(-0.25f, 0.25f, 0.25f);
	glEnd();

	glPopMatrix();
	
	if (cur_wid == wid1) {
		glFlush();
		cur_wid = wid2;
	}
	else {
		glutSwapBuffers();
		cur_wid = wid1;
	}
	return;
}