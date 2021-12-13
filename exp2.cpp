#include <GL/glut.h>
#include <iostream>
#include <cmath>

#define WINSIZE 500
int xc = 0, yc = 0, mouse_flag = 0;
float r = 0;

void init();
void display();
void mouseFunc(int, int, int, int);
void drawEightPoint(int, int, float, float);
void drawCircle();

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

	glutInitWindowSize(WINSIZE, WINSIZE);
	glutCreateWindow("Bresenham circle");
	init();


	glutMouseFunc(mouseFunc);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}

void init() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, (float)(WINSIZE - 1), 0.0f, (float)(WINSIZE - 1), -1.0f, 1.0f);
	return;
}

void display() {
	return;
}

void mouseFunc(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (mouse_flag == 1) {
			int x_edge = x, y_edge = (WINSIZE - y);
			r = (float)sqrt(pow((xc - x_edge), 2) + pow((yc - y_edge), 2));
			drawCircle();
		}
		else if (mouse_flag == 0) {
			xc = x;
			yc = (WINSIZE - y);
		}
		mouse_flag = 1 - mouse_flag;
	}
	return;
}

void drawCircle() {
	float x = 0, y = r, d = 3 - (2 * r);
	while (x <= y) {
		drawEightPoint(xc, yc, x, y);
		x++;
		if (d < 0) {
			d += (4 * x) + 6;
		}
		else {
			y--;
			d += (4 * (x - y)) + 10;
		}
		drawEightPoint(xc, yc, x, y);
	}

	glFlush();
	return;
}

void drawEightPoint(int xc, int yc, float h, float k) {
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	glVertex2f(xc + h, yc + k);
	glVertex2f(xc - h, yc + k);
	glVertex2f(xc + h, yc - k);
	glVertex2f(xc - h, yc - k);
	glVertex2f(xc + k, yc + h);
	glVertex2f(xc - k, yc + h);
	glVertex2f(xc + k, yc - h);
	glVertex2f(xc - k, yc - h);
	glEnd();
	return;
}