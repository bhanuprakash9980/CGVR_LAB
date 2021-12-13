#include<stdlib.h>
#include<gl/glut.h>
#include<iostream>

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 600

int x1, x2, yc1, y2, flag = 0;

// function to draw a pixel
void drawPixel(int x, int y)
{
	glColor3f(0, 0, 1); //blue
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

// function to draw line using Bresenham's line drawing algorithm
void drawLine()
{
	int dx, dy, i, e;
	int incx = 1, incy = 1, inc1, inc2;
	int x, y;
	dx = x2 - x1;
	dy = y2 - yc1;
	if (dx == 0)
	{
		for (i = 0; i <= dy; i++)
			drawPixel(x1, yc1 + i);
		return;
	}
	if (dy == 0)
	{
		for (i = 0; i <= dx; i++)
			drawPixel(x1 + i, yc1);
		return;
	}
	if (dx < 0)
		dx = -dx;
	if (dy < 0)
		dy = -dy;
	if (x2 < x1)
		incx = -1;
	if (y2 < yc1)
		incy = -1;
	x = x1;
	y = yc1;
	if (dx > dy)
	{
		drawPixel(x, y);
		e = 2 * dy - dx;
		inc1 = 2 * (dy - dx);
		inc2 = 2 * dy;
		for (i = 0; i < dx; i++)
		{
			if (e > 0)
			{
				y = y + incy;
				e = e + inc1;
			}
			else
			{
				e = e + inc2;
			}
			x = x + incx;
			drawPixel(x, y);
		}
	}
	else
	{
		drawPixel(x, y);
		e = 2 * dx - dy;
		inc1 = 2 * (dx - dy);
		inc2 = 2 * dx;
		for (i = 0; i < dy; i++)
		{
			if (e > 0)
			{
				x = x + incx;
				e = e + inc1;
			}
			else
				e = e + inc2;
			y = y + incy;
			drawPixel(x, y);
		}
	}
	glFlush();
}

void myInit()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	gluOrtho2D(-250, 250, -250, 250);
}

void mouseFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (flag == 0)
		{
			std::cout << "x1, y1 : ";
			x1 = x - 250;
			yc1 = 250 - y;
			flag++;
			std::cout << x1 << " " << yc1 << " \n";
		}
		else
		{
			std::cout << "x2, y2 : ";
			x2 = x - 250;
			y2 = 250 - y;
			flag = 0;
			std::cout << x2 << " " << y2 << " \n";
			drawLine();
		}
	}
}

void display() {}

int main(int argc, char** argv)
{
	int choice;
	std::cout << "Enter 1 for keyboard and 2 for mouse \n";
	std::cin >> choice;
	if (choice == 1)
	{
		std::cout << "Enter x1 : ";
		std::cin >> x1;
		std::cout << "Enter yc1 : ";
		std::cin >> yc1;
		std::cout << "Enter x2 : ";
		std::cin >> x2;
		std::cout << "Enter y2 : ";
		std::cin >> y2;
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("Line Drawing");
	if (choice == 2)
	{
		glutMouseFunc(mouseFunc);
		glutDisplayFunc(display);
		myInit();
	}
	else
	{
		glutDisplayFunc(drawLine);
		myInit();
	}
	glutMainLoop();
}
