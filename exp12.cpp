#include <GL/glut.h>
#include <time.h>

#define WINSIZE 500
int axis = 0;
GLfloat vertices[] = { -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0 };
GLfloat normals[] = { -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0 };
GLfloat colors[] = { 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f };
GLubyte cubeIndices[] = { 0, 3, 2, 1, 2, 3, 7, 6, 0, 4, 7, 3, 1, 2, 6, 5, 4, 5, 6, 7 ,0 ,1 ,5 ,4 };

static GLfloat theta[] = { 0.0f, 0.0f, 0.0f };

void delay(float);
void display();
void mousefunc(int, int, int, int);
void spin();
void reshape(int, int);

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_SINGLE);

	glutInitWindowSize(WINSIZE, WINSIZE);
	glutCreateWindow("Cube");

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMouseFunc(mousefunc);

	glEnable(GL_DEPTH_TEST);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);
	glNormalPointer(GL_FLOAT, 0, normals);

	glColor3f(1.0f, 1.0f, 1.0f);
	glutMainLoop();

	return 0;
}

void delay(float time) {
	float end_time = (clock() / CLOCKS_PER_SEC) + time;
	while ((clock() / CLOCKS_PER_SEC) < end_time);
	return;
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	(w <= h) ? glOrtho(-2.0f, 2.0f, (-2.0 * (GLfloat)h / (GLfloat)w), (2.0 * (GLfloat)h / (GLfloat)w), -10.0f, 10.0f) : glOrtho(-2.0f, 2.0f, (-2.0 * (GLfloat)w / (GLfloat)h), (2.0 * (GLfloat)w / (GLfloat)h), -10.0f, 10.0f);

	glMatrixMode(GL_MODELVIEW);

	return;
}

void spin() {
	delay(0.01);
	theta[axis] += 2.0f;
	if (theta[axis] > 360.0f) {
		theta[axis] = -360.0f;
	}
	glutPostRedisplay();

	return;
}

void mousefunc(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		axis = (button == GLUT_LEFT_BUTTON) ? 0 : (button == GLUT_MIDDLE_BUTTON ? 1 : 2);
		glutIdleFunc(spin);
	}
	return;
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glRotatef(theta[0], 1.0f, 0.0f, 0.0f);
	glRotatef(theta[1], 0.0f, 1.0f, 0.0f);
	glRotatef(theta[2], 0.0f, 0.0f, 1.0f);

	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);

	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glEnd();

	glFlush();

	return;
}