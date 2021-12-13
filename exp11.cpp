#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

#define WINSIZE 500
float house[11][2] = { { 100,200 },{ 200,250 },{ 300,200 },{ 100,200 },{ 100,100 },{ 175,100 },{ 175,150 },{ 225,150 },{ 225,100 },{ 300,100 },{ 300,200 } };
int angle = 0;
float m = 0.0f, c = 0.0f, theta = 0.0f;

void display();
void displayRotate();
void displayReflect();
void mousefunc(int, int, int, int);

int main(int argc, char* argv[]) {
	cout << "Enter rotation angle: ";
	cin >> angle;
	cout << "Enter m and c of reflection line: ";
	cin >> m >> c;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

	glutInitWindowSize(2*WINSIZE, 2*WINSIZE);
	glutCreateWindow("House operations");

	glutDisplayFunc(display);
	glutMouseFunc(mousefunc);

	glutMainLoop();
	return 0;
}

void display() {
	return;
}

void mousefunc(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		(button == GLUT_LEFT_BUTTON) ? displayRotate() : displayReflect();
	}

	return;
}

void displayRotate() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-(float)(WINSIZE - 1), (float)(WINSIZE - 1), -(float)(WINSIZE - 1), (float)(WINSIZE - 1), -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 11; i++) {
		glVertex2fv(house[i]);
	}
	glEnd();
	glFlush();

	glPushMatrix();
	glTranslatef(100.0, 100.0, 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glTranslatef(-100.0, -100.0, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glPushAttrib(GL_ENABLE_BIT);
	glLineStipple(1, 0xAAAA);
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 11; i++) {
		glVertex2fv(house[i]);
	}
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	glPopAttrib();
	glPopMatrix();
	glFlush();

	return;
}

void displayReflect() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-(float)(WINSIZE - 1), (float)(WINSIZE - 1), -(float)(WINSIZE - 1), (float)(WINSIZE - 1), -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 11; i++) {
		glVertex2fv(house[i]);
	}
	glEnd();
	glFlush();

	float y1 = -(m * WINSIZE) + c, y2 = (m * WINSIZE) + c;
	glBegin(GL_LINES);
	glVertex2f(-WINSIZE, y1);
	glVertex2f(WINSIZE, y2);
	glEnd();
	glFlush();

	glPushMatrix();
	glTranslatef(0.0f, c, 0.0f);
	theta = atan(m);
	theta = theta * (180.0 / 3.14);
	glRotatef(theta, 0.0f, 0.0f, 1.0f);
	glScalef(1.0f, -1.0f, 1.0f);
	glRotatef(-theta, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f, -c, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glPushAttrib(GL_ENABLE_BIT);
	glLineStipple(1, 0xAAAA);
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 11; i++) {
		glVertex2fv(house[i]);
	}
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	glPopAttrib();
	glPopMatrix();
	glFlush();

	return;
}