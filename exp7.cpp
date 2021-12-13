#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <windows.h>
#include <gl/glut.h>

int m, n;
int wx = 500, wy = 500;
static float intx[10] = { 0 };
float x[100], y[100];

void drawLine(float x1, float y1, float x2, float y2)
{
	Sleep(100);
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
	glFlush();
}

void edgeDetect(float x1, float y1, float x2, float y2, int scanline)
{
	if (y2 < y1)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}
	if (scanline > y1 && scanline < y2)
		intx[m++] = x1 + (scanline - y1) * (x2 - x1) / (y2 - y1);
}

void scanFill(float x[], float y[]) // coordinates of the polygon
{
	for (int s1 = 0; s1 <= wy; s1++)
	{
		m = 0;
		for (int i = 0; i < n; i++)
			edgeDetect(x[i], y[i], x[(i + 1) % n], y[(i + 1) % n], s1);
		std::sort(intx, intx + m);
		if (m >= 2)
		{
			for (int i = 0; i < m; i = i + 2)
				drawLine(intx[i], s1, intx[i + 1], s1);
		}
	}
}

void displayFilledPolygon()
{
	glClear(GL_COLOR_BUFFER_BIT); // clears the current window
	//glLineWidth(5);
	glBegin(GL_LINE_LOOP);
	glColor3f(1, 0, 0);
	for (int i = 0; i < n; i++)
		glVertex2f(x[i], y[i]);
	glEnd();
	scanFill(x, y);
}

void myInit()
{
	glClearColor(1, 1, 1, 1);
	gluOrtho2D(0, 200, 0, 200);
}

int main(int argc, char** argv)
{
	std::cout << "Enter the number of sides : ";
	std::cin >> n;
	std::cout << "Enter the coordinates of vertices : \n";
	for (int i = 0; i < n; i++)
	{
		std::cin >> x[i] >> y[i];
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("ScanLine fill polygon");
	glutDisplayFunc(displayFilledPolygon);
	myInit();
	glutMainLoop();
}
