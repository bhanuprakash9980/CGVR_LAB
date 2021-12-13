#include <GL/glut.h>
#include <iostream>
#include <math.h>

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

int xc, yc, r;
int p1_x, p2_x, p1_y, p2_y;
int point1_done = 0;

void draw_circle(int xc, int yc, int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(xc + x, yc + y);
	glVertex2i(xc - x, yc + y);
	glVertex2i(xc + x, yc - y);
	glVertex2i(xc - x, yc - y);
	glVertex2i(xc + y, yc + x);
	glVertex2i(xc - y, yc + x);
	glVertex2i(xc + y, yc - x);
	glVertex2i(xc - y, yc - x);
	glEnd();
}

void circleBres()
{
	glClear(GL_COLOR_BUFFER_BIT);
	int x = 0, y = r;
	int d = 3 - 2 * r;
	while (x <= y)
	{
		draw_circle(xc, yc, x, y);
		x++;
		if (d < 0)
			d = d + 4 * x + 6;
		else
		{
			y--;
			d = d + 4 * (x - y) + 10;
		}
		draw_circle(xc, yc, x, y);
	}
	glFlush();
}
void mouseFuncCircle(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && point1_done == 0)
	{
		p1_x = x - 250;
		p1_y = 250 - y;
		point1_done = 1;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		float exp;
		p2_x = x - 250;
		p2_y = 250 - y;
		xc = p1_x;
		yc = p1_y;
		exp = (p2_x - p1_x) * (p2_x - p1_x) + (p2_y - p1_y) * (p2_y - p1_y);
		r = (int)(sqrt(exp));
		circleBres();
		point1_done = 0;
	}
}

void drawingCircle(){}

void myInit()
{
	glClearColor(1, 1, 1, 1);
	glColor3f(0.0, 1.0, 0.0);
	glPointSize(3.0);
	gluOrtho2D(-250, 250, -250, 250);
}

int main(int argc, char** argv)
{
	int choice;
	std::cout << "Enter 1 for keyboard, 2 for mouse\n";
	std::cin >> choice;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	switch (choice)
	{
	case 1 : 
		std::cout << "Enter coordinates of the center and radius : \n";
		std::cin >> xc >> yc >> r;
		glutCreateWindow("Circle Keyboard");
		glutDisplayFunc(circleBres);
		myInit();
		break;
	case 2:
		glutCreateWindow("Circle Mouse");
		glutMouseFunc(mouseFuncCircle);
		glutDisplayFunc(drawingCircle);
		myInit();
		break;
	default:
		std::cout << "Invalid choice\n";
	}
	glutMainLoop();
}
