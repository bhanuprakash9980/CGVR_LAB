#include <GL/glut.h>
#include <iostream>

using namespace std;

#define WINSIZE 500
int plotflag = 0;
int x1 = 0, x2 = 0, yc1 = 0, yc2 = 0, keymouse = 0;

void init();
void mousefunc(int, int, int, int);
void display();
void plotPoint(int, int);
void plotLine(int, int, int, int);

int main(int argc, char* argv[]) {
	cout << "Coordinates from keyboard(1) or mouse(2): ";
	cin >> keymouse;
	if (keymouse == 1) {
		cout << "Enter first point (x1, yc1): ";
		cin >> x1 >> yc1;
		cout << "Enter second point (x2, yc2): ";
		cin >> x2 >> yc2;
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

	glutInitWindowSize(WINSIZE, WINSIZE);
	glutCreateWindow("Bresenham Line");

	init();

	if (keymouse == 2) {
		glutMouseFunc(mousefunc);
	}
	else {
		plotLine(x1, yc1, x2, yc2);
	}

	glutDisplayFunc(display);
	glutMainLoop();
}

void init() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, (float)(WINSIZE - 1), 0.0f, (float)(WINSIZE - 1), -1.0f, 1.0f);
}

void display() {
	return;
}

void mousefunc(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (plotflag == 1) {
			x2 = x;
			yc2 = WINSIZE - y;
			plotLine(x1, yc1, x2, yc2);
		}
		else if (plotflag == 0) {
			x1 = x;
			yc1 = WINSIZE - y;
		}
		plotflag = 1 - plotflag;
	}
	return;
}

void plotPoint(int x, int y) {
	glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();

	glFlush();
	return;
}

void plotLine(int x1, int yc1, int x2, int yc2) {
	int dx = (x2 - x1), dy = (yc2 - yc1), isDxNeg = (dx < 0) ? 1 : 0, isDyNeg = (dy < 0) ? 1 : 0, e, incX = (isDxNeg) ? -1 : 1, incY = (isDyNeg) ? -1 : 1, x = x1, y = yc1, incDown = 0, incUp = 0;

	if (dx == 0) {
		if (isDyNeg) {
			for (int i = 0; i > dy; i--) {
				plotPoint(x1, yc1 + i);
			}
		}
		else {
			for (int i = 0; i < dy; i++) {
				plotPoint(x1, yc1 + i);
			}
		}
	}
	else if (dy == 0) {
		if (isDxNeg) {
			for (int i = 0; i > dx; i--) {
				plotPoint(x1 + i, yc1);
			}
		}
		else {
			for (int i = 0; i < dx; i++) {
				plotPoint(x1 + i, yc1);
			}
		}
	}
	else {
		dx = (isDxNeg) ? -dx : dx;
		dy = (isDyNeg) ? -dy : dy;

		if (dx > dy) {
			plotPoint(x, y);
			e = (2 * dy) - dx;
			incUp = 2 * (dy - dx);
			incDown = 2 * dy;

			for (int i = 0; i < dx; i++) {
				if (e > 0) {
					y += incY;
					e += incUp;
				}
				else {
					e += incDown;
				}
				x += incX;
				plotPoint(x, y);
			}
		}
		else {
			plotPoint(x, y);
			e = (2 * dx) - dy;
			incUp = 2 * (dx - dy);
			incDown = 2 * dy;

			for (int i = 0; i < dy; i++) {
				if (e > 0) {
					x += incX;
					e += incUp;
				}
				else {
					e += incDown;
				}
				y += incY;
				plotPoint(x, y);
			}
		}
	}
	glFlush();
	return;
}