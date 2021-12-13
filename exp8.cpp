#include<iostream>
#include<stdlib.h>
#include<gl/glut.h>

#define regcode int
#define true 1
#define false 0
double xmin, ymin, xmax, ymax;
double xvmin, yvmin, xvmax, yvmax;


const int RIGHT = 4;
const int LEFT = 8;
const int TOP = 1; // in all top codes 1st bit is 1
const int BOTTOM = 2;

int n;

struct line_segment {
	int x1;
	int y1;
	int x2;
	int y2;
};
struct line_segment ls[10];

regcode computeregcode(double x, double y)
{
	regcode code = 0;
	if (y > ymax)
		code |= TOP;
	else if (y < ymin)
		code |= BOTTOM;
	if (x > xmax)
		code |= RIGHT;
	else if (x < xmin)
		code |= LEFT;
	return code;
}


void cohensuther(double x0, double y0, double x1, double y1)
{
	regcode regcode0, regcode1, regcodeout;
	bool accept = false, done = false;

	regcode0 = computeregcode(x0, y0); // region code of first point
	regcode1 = computeregcode(x1, y1); // region code of second point

	do
	{
		if ((regcode0 | regcode1) == 0)
		{
			// both points inside the window
			accept = true;
			done = true;
		}
		else if (regcode0 & regcode1)
		{
			// both outside
			done = true;
		}
		else
		{
			double x, y;
			regcodeout = regcode0 != 0 ? regcode0 : regcode1;
			if (regcodeout & TOP)
			{
				x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
				y = ymax;
			}
			else if (regcodeout & BOTTOM)
			{
				x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
				y = ymin;
			}
			else if (regcodeout & RIGHT)
			{
				y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
				x = xmax;
			}
			else
			{
				y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
				x = xmin;
			}

			if (regcodeout == regcode0)
			{
				x0 = x;
				y0 = y;
				regcode0 = computeregcode(x0, y0);
			}
			else
			{
				x1 = x;
				y1 = y;
				regcode1 = computeregcode(x1, y1);
			}
		}

	} while (!done);

	if (accept)
	{
		double sx = (xvmax - xvmin) / (xmax - xmin);
		double sy = (yvmax - yvmin) / (ymax - ymin);
		double vx0 = xvmin + (x0 - xmin) * sx;
		double vy0 = yvmin + (y0 - ymin) * sy;
		double vx1 = xvmin + (x1 - xmin) * sx;
		double vy1 = yvmin + (y1 - ymin) * sy;

		// drawing the clipping window
		glColor3f(1, 0, 0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(xvmin, yvmin);
		glVertex2f(xvmax, yvmin);
		glVertex2f(xvmax, yvmax);
		glVertex2f(xvmin, yvmax);
		glEnd();

		// drawing the line
		glColor3f(0, 0, 1);
		glBegin(GL_LINES);
		glVertex2d(vx0, vy0);
		glVertex2d(vx1, vy1);
		glEnd();
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// WINDOW 
	glColor3f(0, 0, 1);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xmin, ymin);
	glVertex2f(xmax, ymin);
	glVertex2f(xmax, ymax);
	glVertex2f(xmin, ymax);
	glEnd();

	for (int i = 0; i < n; i++)
	{
		glBegin(GL_LINES);
		glVertex2d(ls[i].x1, ls[i].y1);
		glVertex2d(ls[i].x2, ls[i].y2);
		glEnd();
	}

	// NOW DRAW CLIPPING WINDOW AND CLIPPED LINES
	for (int i = 0; i < n; i++)
		cohensuther(ls[i].x1, ls[i].y1, ls[i].x2, ls[i].y2);

	glFlush();
}
void myinit()
{
	glClearColor(1, 1, 1, 1);
	//glColor3f(1, 0, 0);
	//glPointSize(1.0);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	gluOrtho2D(0, 600, 0, 600);
}

int main(int argc, char** argv)
{
	// Original
	std::cout << "Enter window coordinates (xmin ymin xmax ymax): \n";
	std::cin >> xmin >> ymin >> xmax >> ymax;
	// Clipped
	std::cout << "Enter viewport coordinates (xvmin yvmin xvmax yvmax) :\n";
	std::cin >> xvmin >> yvmin >> xvmax >> yvmax;
	std::cout << "Enter no. of lines:\n";
	std::cin >> n;
	for (int i = 0; i < n; i++)
	{
		std::cout << "Enter line endpoints (x1 y1 x2 y2) : \n";
		std::cin >> ls[i].x1 >> ls[i].y1 >> ls[i].x2 >> ls[i].y2;
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutCreateWindow("clip");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
}