#include <GL/glut.h>
#include <iostream>
#include <algorithm>

using namespace std;

#define WINSIZE 500
#define MAXVERT 10

int n = 0, intersection_count = 0;
int x[MAXVERT] = { 0 };
int y[MAXVERT] = { 0 };
int intersections[2 * MAXVERT] = { 0 };

void display();
void init();
void scanFill();
void edgeDetect(int, int, int, int, int);
void drawLine(int, int, int, int);

int main(int argc, char* argv[]) {
	cout << "Enter number of vertices: ";
	cin >> n;
	if (n > MAXVERT) {
		cout << "Too many vertices" << endl;
		exit(0);
	}
	cout << "Enter coordinates (x,y): " << endl;
	for (int i = 0; i < n; i++) {
		cin >> x[i] >> y[i];
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

	glutInitWindowSize(WINSIZE, WINSIZE);
	glutCreateWindow("Scan fill");
	init();

	glutDisplayFunc(display);
	glutIdleFunc(glutPostRedisplay);
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
	glLineWidth(2);
	glColor3f(0.0f, 1.0f, 0.0f);

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < n; i++) {
		glVertex2i(x[i], y[i]);
	}
	glEnd();

	scanFill();
	
	glFlush();
	return;
}

void scanFill() {
	for (int sl = 0; sl <= WINSIZE; sl++) {
		intersection_count = 0;
		for (int i = 0; i < n; i++) {
			edgeDetect(x[i], y[i], x[(i + 1) % n], y[(i + 1) % n], sl);
		}

		sort(intersections, (intersections + intersection_count));
		if (intersection_count >= 2) {
			for (int i = 0; i < intersection_count - 1; i += 2) {
				drawLine(intersections[i], sl, intersections[i + 1], sl);
			}
		}
	}
	return;
}

void edgeDetect(int x1, int yc1, int x2, int yc2, int scanline) {
	if (yc2 < yc1) {
		swap(x1, x2);
		swap(yc1, yc2);
	}

	if (scanline > yc1 && scanline < yc2) {
		intersections[intersection_count++] = x1 + ((scanline - yc1) * (x2 - x1) / (yc2 - yc1));
	}
	return;
}

void drawLine(int x1, int yc1, int x2, int yc2) {
	Sleep(100);
	glColor3f(1.0f, 0.0f, 0.0f);

	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2i(x1, yc1);
	glVertex2i(x2, yc2);
	glEnd();

	glFlush();
	return;
}